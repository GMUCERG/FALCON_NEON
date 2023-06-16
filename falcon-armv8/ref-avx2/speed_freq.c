/*
 * Speed benchmark code for Falcon implementation.
 *
 * ==========================(LICENSE BEGIN)============================
 *
 * Copyright (c) 2017-2019  Falcon Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * ===========================(LICENSE END)=============================
 *
 * @author   Thomas Pornin <thomas.pornin@nccgroup.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#if AVX2 == 1
#include "cpucycles.h"

#define TIME(s) s = cpucycles();
#define CALC(start, stop, ntests) (stop - start) / ntests;

#else 
#if APPLE_M1 == 1
#include "m1cycles.h"

// Result is cycle per call
#define TIME(s) s = rdtsc();
#define CALC(start, stop, ntests) (stop - start) / ntests;
#else 
#include "hal.h"

// Result is cycle per call
#define TIME(s) s = hal_get_time();
#define CALC(start, stop, ntests) (stop - start) / ntests;
#endif 
#endif

#define ITERATIONS 10000

/*
 * This code uses only the external API.
 */

#include "falcon.h"

static int cmp_uint64_t(const void *a, const void *b)
{
    return (int)((*((const uint64_t *)a)) - (*((const uint64_t *)b)));
}

static void *
xmalloc(size_t len)
{
	void *buf;

	if (len == 0) {
		return NULL;
	}
	buf = malloc(len);
	if (buf == NULL) {
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	return buf;
}

static void
xfree(void *buf)
{
	if (buf != NULL) {
		free(buf);
	}
}

/*
 * Benchmark function takes an opaque context and an iteration count;
 * it returns 0 on success, a negative error code on error.
 */
typedef int (*bench_fun)(void *ctx, unsigned long num);


static long long 
do_bench_cycles(bench_fun bf, void *ctx, long long *walltime, int iteration)
{
    long long start, stop;
    int r;
    long long times[ITERATIONS];
    struct timespec start_tt, stop_tt;   

    bf(ctx, 10);
    /*
    * Always do a few blank runs to "train" the caches and branch
    * prediction.
    */

    for (int i = 0; i < iteration; i++)
    {
        // Benchmark time
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_tt);
        r = bf(ctx, 1);
        clock_gettime(CLOCK_MONOTONIC_RAW, &stop_tt);
        if (r != 0) {
                fprintf(stderr, "ERR: %d\n", r);
                return 0;
        }
        times[i] = (stop_tt.tv_sec - start_tt.tv_sec) * 1000000000 + (stop_tt.tv_nsec - start_tt.tv_nsec);
    }
    qsort(times, iteration, sizeof(uint64_t), cmp_uint64_t);
    *walltime = times[iteration >> 1];

    for (int i = 0; i < iteration; i++)
    {
        // Benchmark cycles
        TIME(start);
        r = bf(ctx, 1);
        TIME(stop);
        if (r != 0) {
                fprintf(stderr, "ERR: %d\n", r);
                return 0;
        }
        times[i] = stop - start;
    }
    qsort(times, iteration, sizeof(uint64_t), cmp_uint64_t);

    return times[iteration >> 1];

}


typedef struct {
	unsigned logn;
	shake256_context rng;
	uint8_t *tmp;
	size_t tmp_len;
	uint8_t *pk;
	uint8_t *sk;
	uint8_t *esk;
	uint8_t *sig;
	size_t sig_len;
	uint8_t *sigct;
	size_t sigct_len;
} bench_context;

static inline size_t
maxsz(size_t a, size_t b)
{
	return a > b ? a : b;
}

#define CC(x)   do { \
		int ccr = (x); \
		if (ccr != 0) { \
			return ccr; \
		} \
	} while (0)

static int
bench_keygen(void *ctx, unsigned long num)
{
	bench_context *bc;

	bc = ctx;
	while (num -- > 0) {
		CC(falcon_keygen_make(&bc->rng, bc->logn,
			bc->sk, FALCON_PRIVKEY_SIZE(bc->logn),
			bc->pk, FALCON_PUBKEY_SIZE(bc->logn),
			bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_sign_dyn(void *ctx, unsigned long num)
{
	bench_context *bc;

	bc = ctx;
	while (num -- > 0) {
		bc->sig_len = FALCON_SIG_COMPRESSED_MAXSIZE(bc->logn);
		CC(falcon_sign_dyn(&bc->rng,
			bc->sig, &bc->sig_len, FALCON_SIG_COMPRESSED,
			bc->sk, FALCON_PRIVKEY_SIZE(bc->logn),
			"data", 4, bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_sign_dyn_ct(void *ctx, unsigned long num)
{
	bench_context *bc;

	bc = ctx;
	while (num -- > 0) {
		bc->sigct_len = FALCON_SIG_CT_SIZE(bc->logn);
		CC(falcon_sign_dyn(&bc->rng,
			bc->sigct, &bc->sigct_len, FALCON_SIG_CT,
			bc->sk, FALCON_PRIVKEY_SIZE(bc->logn),
			"data", 4, bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_expand_privkey(void *ctx, unsigned long num)
{
	bench_context *bc;

	bc = ctx;
	while (num -- > 0) {
		CC(falcon_expand_privkey(
			bc->esk, FALCON_EXPANDEDKEY_SIZE(bc->logn),
			bc->sk, FALCON_PRIVKEY_SIZE(bc->logn),
			bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_sign_tree(void *ctx, unsigned long num)
{
	bench_context *bc;

	bc = ctx;
	while (num -- > 0) {
		bc->sig_len = FALCON_SIG_COMPRESSED_MAXSIZE(bc->logn);
		CC(falcon_sign_tree(&bc->rng,
			bc->sig, &bc->sig_len, FALCON_SIG_COMPRESSED,
			bc->esk,
			"data", 4, bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_sign_tree_ct(void *ctx, unsigned long num)
{
	bench_context *bc;

	bc = ctx;
	while (num -- > 0) {
		bc->sigct_len = FALCON_SIG_CT_SIZE(bc->logn);
		CC(falcon_sign_tree(&bc->rng,
			bc->sigct, &bc->sigct_len, FALCON_SIG_CT,
			bc->esk,
			"data", 4, bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_verify(void *ctx, unsigned long num)
{
	bench_context *bc;
	size_t pk_len;

	bc = ctx;
	pk_len = FALCON_PUBKEY_SIZE(bc->logn);
	while (num -- > 0) {
		CC(falcon_verify(
			bc->sig, bc->sig_len, FALCON_SIG_COMPRESSED,
			bc->pk, pk_len,
			"data", 4, bc->tmp, bc->tmp_len));
	}
	return 0;
}

static int
bench_verify_ct(void *ctx, unsigned long num)
{
	bench_context *bc;
	size_t pk_len;

	bc = ctx;
	pk_len = FALCON_PUBKEY_SIZE(bc->logn);
	while (num -- > 0) {
		CC(falcon_verify(
			bc->sigct, bc->sigct_len, FALCON_SIG_CT,
			bc->pk, pk_len,
			"data", 4, bc->tmp, bc->tmp_len));
	}
	return 0;
}


static void
test_speed_falcon_Ghz(unsigned logn, int iteration)
{


        bench_context bc;

        size_t len;
        printf("%4u:", 1u << logn);
        fflush(stdout);

        bc.logn = logn;
        if (shake256_init_prng_from_system(&bc.rng) != 0) {
                fprintf(stderr, "random seeding failed\n");
                exit(EXIT_FAILURE);
        }
        len = FALCON_TMPSIZE_KEYGEN(logn);
        len = maxsz(len, FALCON_TMPSIZE_SIGNDYN(logn));
        len = maxsz(len, FALCON_TMPSIZE_SIGNTREE(logn));
        len = maxsz(len, FALCON_TMPSIZE_EXPANDPRIV(logn));
        len = maxsz(len, FALCON_TMPSIZE_VERIFY(logn));
        bc.tmp = xmalloc(len);
        bc.tmp_len = len;
        bc.pk = xmalloc(FALCON_PUBKEY_SIZE(logn));
        bc.sk = xmalloc(FALCON_PRIVKEY_SIZE(logn));
        bc.esk = xmalloc(FALCON_EXPANDEDKEY_SIZE(logn));
        bc.sig = xmalloc(FALCON_SIG_COMPRESSED_MAXSIZE(logn));
        bc.sig_len = 0;
        bc.sigct = xmalloc(FALCON_SIG_CT_SIZE(logn));
        bc.sigct_len = 0;

        long long walltime = 0;
        long long cc = 0;

        cc = do_bench_cycles(&bench_keygen, &bc, &walltime, iteration/10);
        printf("| %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);

        cc = (double) do_bench_cycles(&bench_expand_privkey, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);
        
        cc = (double) do_bench_cycles(&bench_sign_dyn, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);
        
        cc = (double) do_bench_cycles(&bench_sign_dyn_ct, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);

        cc = (double) do_bench_cycles(&bench_sign_tree, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);

        cc = (double) do_bench_cycles(&bench_sign_tree_ct, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);

        cc = (double) do_bench_cycles(&bench_verify, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);

        cc = (double) do_bench_cycles(&bench_verify_ct, &bc, &walltime, iteration);
        printf(" %9.2f|",  ((double) cc) / walltime);
        fflush(stdout);

        printf("\n");
        fflush(stdout);

        xfree(bc.tmp);
        xfree(bc.pk);
        xfree(bc.sk);
        xfree(bc.esk);
        xfree(bc.sig);
        xfree(bc.sigct);
}


int
main(void)
{
#if BENCH_CYCLES == 1
#if APPLE_M1 == 1
    setup_rdtsc();
#endif
#endif
        const int iteration = ITERATIONS/2;
    
        printf("degree  kg(Ghz)   ek(Ghz)   sd(Ghz)  sdc(Ghz)   st(Ghz)  stc(Ghz)   vv(Ghz)  vvc(Ghz)\n");
        test_speed_falcon_Ghz(9, iteration);
        test_speed_falcon_Ghz(10, iteration);
        return 0;
}
