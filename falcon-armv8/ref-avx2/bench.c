#include "inner.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define ITERATIONS 10000
uint64_t times[ITERATIONS];

#define FALCON_Q 12289
#define FALCON_N 1024
#define FALCON_LOGN 10

#if AVX2 == 1
#include "cpucycles.h"

#define TIME(s) s = cpucycles();
#define CALC(start, stop, ntests) (stop - start) / ntests;
#else 
#if BENCH_CYCLES == 1
#if APPLE_M1 == 1

// Result is cycle per call
#include "m1cycles.h"

#define TIME(s) s = rdtsc();
#define CALC(start, stop, ntests) (stop - start) / ntests;
#else

// Result is cycle per call
#include "hal.h"

#define TIME(s) s = hal_get_time();
#define CALC(start, stop, ntests) (stop - start) / ntests;
#endif

#else

#include <time.h>
// Result is nanosecond per call

#define TIME(s) clock_gettime(CLOCK_MONOTONIC_RAW, &s);
#define CALC(start, stop, ntests) ((double)((stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec - start.tv_nsec))) / ntests;

#endif
#endif 

#define NTESTS 10000

void print_header()
{
    printf("\n| Function | logn | cycles |\n");
    printf("|:-------------|----------:|-----------:|\n");
}

static int cmp_uint64_t(const void *a, const void *b)
{
    return (int)((*((const uint64_t *)a)) - (*((const uint64_t *)b)));
}

void test_FFT(fpr *f, unsigned logn)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft, ifft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(FFT)(f, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(iFFT)(f, logn);
        TIME(stop);
        times[i] = stop - start;
    }

    /* =================================== */
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    ifft = times[ITERATIONS >> 1];
    printf("| FFT %u | %8lld | %8lld\n", logn, fft, ifft);
}

void test_NTT(uint16_t *a, unsigned logn)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft, ifft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        mq_NTT(a, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        mq_iNTT(a, logn);
        TIME(stop);
        times[i] = stop - start;
    }

    /* =================================== */
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    ifft = times[ITERATIONS >> 1];
    printf("| NTT %u | %8lld | %8lld\n", logn, fft, ifft);
}

void test_poly_add(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_add)(c, a, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_sub(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_sub)(c, a, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_neg(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_neg)(c, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_adj_fft(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_adj_fft)(c, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_mul_fft(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_mul_fft)(c, a, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_invnorm2_fft(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_invnorm2_fft)(c, a, b, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_mul_autoadj_fft(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_mul_autoadj_fft)(c, a, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_LDL_fft(fpr *c, fpr *a, fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_LDL_fft)(c, a, b, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_LDLmv_fft(fpr *d11, fpr *l01, const fpr *c, const fpr *a, const fpr *b, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_LDLmv_fft)(d11, l01, c, a, b, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_split_fft(fpr *restrict f0, fpr *restrict f1,
                         const fpr *restrict f, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_split_fft)(f0, f1, f, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

void test_poly_merge_fft(fpr *restrict f, const fpr *restrict f0,
                         const fpr *restrict f1, unsigned logn, char *string)
{
#if BENCH_CYCLES == 0
    struct timespec start, stop;
#else
    long long start, stop;
#endif
    long long fft;
    unsigned ntests = ITERATIONS;
    
    /* =================================== */
    for (unsigned i = 0; i < ntests; i++)
    {
        TIME(start);
        Zf(poly_merge_fft)(f, f0, f1, logn);
        TIME(stop);
        times[i] = stop - start;
    }
    qsort(times, ITERATIONS, sizeof(uint64_t), cmp_uint64_t);
    fft = times[ITERATIONS >> 1];

    printf("| %8s | %8u | %8lld\n", string, logn, fft);
}

int main()
{
    fpr f[FALCON_N], fa[FALCON_N], fb[FALCON_N], fc[FALCON_N], tmp[FALCON_N] = {0};
    uint16_t a[FALCON_N];
    for (int i = 0; i < FALCON_N; i++)
    {
        double_t t;
        t = (double)i;
        f[i].v = t;
        fa[i].v = t;
        fb[i].v = t;
        fc[i].v = t;
        a[i] = rand() % FALCON_Q;
    }

#if BENCH_CYCLES == 1
#if APPLE_M1 == 1
    setup_rdtsc();
#endif
#endif

    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_FFT(f, i);
    }

    test_NTT(a, 9);
    test_NTT(a, 10);

    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_add(fc, fa, fb, i, "poly_add");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_sub(fc, fa, fb, i, "poly_sub");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_neg(fc, fa, fb, i, "poly_neg");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_adj_fft(fc, fa, fb, i, "poly_adj_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_mul_fft(fc, fa, fb, i, "poly_mul_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_invnorm2_fft(fc, fa, fb, i, "poly_invnorm2_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_mul_autoadj_fft(fc, fa, fb, i, "poly_mul_autoadj_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_LDL_fft(fc, fa, fb, i, "poly_LDL_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_LDLmv_fft(f, tmp, fc, fa, fb, i, "poly_LDLmv_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_split_fft(fa, fb, f, i, "poly_split_fft");
    }
    print_header();
    for (unsigned i = 0; i <= FALCON_LOGN; i++)
    {
        test_poly_merge_fft(f, fa, fb, i, "poly_merge_fft");
    }

    return 0;
}