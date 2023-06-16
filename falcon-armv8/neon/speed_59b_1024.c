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
#include "api.h"
#include "config.h"

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
uint64_t times[ITERATIONS];
uint64_t cycles[ITERATIONS];

/*
 * This code uses only the external API.
 */

#include "falcon.h"

static int cmp_uint64_t(const void *a, const void *b)
{
    return (int)((*((const uint64_t *)a)) - (*((const uint64_t *)b)));
}

long long sum(uint64_t *a, int interation)
{
    uint64_t s = 0;
    for (int i = 0; i < interation; i++)
    {
        s += a[i];
    }
    return s;
}

int benchmark_59b_message(int iteration)
{

    unsigned char sk[CRYPTO_SECRETKEYBYTES], pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char m[64] = {0}, m1[64] = {0};
    unsigned char sm[128 * 12];
    unsigned long long mlen = 0, mlen1 = 0, smlen = 0;
    int ret = 0;
    long long start, stop;
    struct timespec start_tt, stop_tt;

    double scc, vcc;

    unsigned long long sign_time = 0, sign_cycle = 0,
             verify_time = 0, verify_cycle = 0,
             avg_sign_time = 0, avg_sign_cycle = 0,
             avg_verify_time = 0, avg_verify_cycle = 0;

    mlen = 59;

    ret |= crypto_sign_keypair(pk, sk);
    if (ret)
    {
        return 1;
    }

    // Warmup
    for (int i = 0; i < 10; i++)
    {
        ret |= crypto_sign(sm, &smlen, m, mlen, sk);
    }

    if (ret)
    {
        printf("crypto_sign error\n");
        return 1;
    }
    // Benchmark
    for (int i = 0; i < iteration; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_tt);
        ret |= crypto_sign(sm, &smlen, m, mlen, sk);
        clock_gettime(CLOCK_MONOTONIC_RAW, &stop_tt);
        times[i] = (stop_tt.tv_sec - start_tt.tv_sec) * 1000000000 + (stop_tt.tv_nsec - start_tt.tv_nsec);
    }
    for (int i = 0; i < iteration; i++)
    {
        TIME(start);
        ret |= crypto_sign(sm, &smlen, m, mlen, sk);
        TIME(stop);
        cycles[i] = stop - start;
    }
    qsort(times, iteration, sizeof(uint64_t), cmp_uint64_t);
    qsort(cycles, iteration, sizeof(uint64_t), cmp_uint64_t);
    sign_time = times[iteration >> 1];
    sign_cycle = cycles[iteration >> 1];
    avg_sign_cycle = sum(cycles, iteration);
    printf("sum %llu\n", avg_sign_cycle);
    avg_sign_time = sum(times, iteration);

    // Warmup
    for (int i = 0; i < 10; i++)
    {
        ret |= crypto_sign_open(m1, &mlen1, sm, smlen, pk);

        if (mlen != mlen1)
        {
            printf("crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n", mlen1, mlen);
            return -1;
        }

        if (memcmp(m, m1, mlen))
        {
            printf("crypto_sign_open returned bad 'm' value\n");
            return -1;
        }
    }

    if (ret)
    {
        printf("crypto_sign_open error\n");
        return 1;
    }

    // Benchmark
    for (int i = 0; i < iteration; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_tt);
        ret |= crypto_sign_open(m1, &mlen1, sm, smlen, pk);
        clock_gettime(CLOCK_MONOTONIC_RAW, &stop_tt);
        times[i] = (stop_tt.tv_sec - start_tt.tv_sec) * 1000000000 + (stop_tt.tv_nsec - start_tt.tv_nsec);
    }
    printf("mlen, smlen = %llu, %llu\n", mlen, smlen);
    for (int i = 0; i < iteration; i++)
    {
        TIME(start);
        ret |= crypto_sign_open(m1, &mlen1, sm, smlen, pk);
        TIME(stop);
        cycles[i] = stop - start;
    }
    qsort(times, iteration, sizeof(uint64_t), cmp_uint64_t);
    qsort(cycles, iteration, sizeof(uint64_t), cmp_uint64_t);
    verify_time = times[iteration >> 1];
    verify_cycle = cycles[iteration >> 1];
    avg_verify_cycle = sum(cycles, iteration);
    avg_verify_time = sum(times, iteration);

    printf("| Median   | sign | verify |\n");
    printf("|  --   | --:  | ---: |\n");

    scc = sign_cycle / 1000.0;
    vcc = verify_cycle / 1000.0;
    printf("| kc | %8.2f | %8.2f |\n", scc, vcc);

    scc = sign_time / 1000.0;
    vcc = verify_time / 1000.0;
    printf("| us | %8.2f | %8.2f |\n", scc, vcc);

    scc = ((double)sign_cycle) / sign_time;
    vcc = ((double)verify_cycle) / verify_time;
    printf("| Ghz| %8.2f | %8.2f |\n\n", scc, vcc);

    printf("| Average | sign | verify |\n");
    printf("|  --  | --:  | ---: |\n");

    scc = ((double)avg_sign_cycle) / 1000.0 / iteration;
    vcc = ((double)avg_verify_cycle) / 1000.0 / iteration;
    printf("| kc | %8.2f | %8.2f |\n", scc, vcc);

    scc = ((double)avg_sign_time) / 1000.0 / iteration;
    vcc = ((double)avg_verify_time) / 1000.0 / iteration;
    printf("| us | %8.2f | %8.2f |\n", scc, vcc);

    scc = ((double)avg_sign_cycle) / avg_sign_time;
    vcc = ((double)avg_verify_cycle) / avg_verify_time;
    printf("| Ghz| %8.2f | %8.2f |\n\n", scc, vcc);

    if (ret)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
#if BENCH_CYCLES == 1
#if APPLE_M1 == 1
    setup_rdtsc();
#endif
#endif

    int iteration = ITERATIONS;

    int ret = benchmark_59b_message(iteration);

    if (ret)
    {
        printf("ERROR\n");
    }
    printf("OK\n");
    return 0;
}
