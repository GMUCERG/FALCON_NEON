#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "inner.h"

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

#define ITERATIONS 20000
uint64_t times[ITERATIONS];

void print_header()
{
    printf("\n| Function (logn) | Improved | Ref |\n");
    printf("|:-------------|----------:|-----------:|\n");
}

void print_header1()
{
    printf("\n| Function (logn) | SplitFFT | AdjFFT |\n");
    printf("|:-------------|----------:|-----------:|\n");
}

void print_header2()
{
    printf("\n| Function (logn) | Fast FFT | Ref FFT |\n");
    printf("|:-------------|----------:|-----------:|\n");
}

static int cmp_uint64_t(const void *a, const void *b)
{
    return (int)((*((const uint64_t *)a)) - (*((const uint64_t *)b)));
}

double drand(double low, double high)
{
    return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
}

void combine(fpr *out, fpr *in, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;

    int i_out = 0;
    fpr re, im;
    for (int i = 0; i < hn; i++)
    {
        re = in[i];
        im = in[i + hn];
        out[i_out++] = re;
        out[i_out++] = im;
    }
}

void split(fpr *out, fpr *in, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;

    int i_out = 0;
    fpr re, im;
    for (int i = 0; i < n; i += 2)
    {
        re = in[i];
        im = in[i + 1];
        out[i_out] = re;
        out[i_out + hn] = im;
        i_out += 1;
    }
}

void print_double(fpr *f, unsigned logn, const char *string)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;

    printf("%s:\n", string);
    for (int i = 0; i < n; i += 2)
    {
        printf("%.1f, %.1f, ", f[i].v, f[i + 1].v);
    }
    printf("\n");
}

int cmp_double(fpr *f, fpr *g, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;

    for (int i = 0; i < n; i++)
    {
        if (fabs(f[i].v - g[i].v) > 0.000001)
        {
            printf("[%d]: %.2f != %.2f \n", i, f[i].v, g[i].v);
            printf("ERROR\n");
            return 1;
        }
    }
    return 0;
}

int test_with_adj_FFT(unsigned logn, unsigned tests)
{
    fpr f[1024], g[1024], tmp[1024];
    const unsigned n = 1 << logn;
    for (int i = 0; i < n; i++)
    {
        f[i].v = drand(-12289.0, 12289);
    }
    combine(g, f, logn);

    long long fast_fft, adj_fft;
    long long start, stop;

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        Zf(FFT)(f, logn);

        TIME(stop);
        times[j] = stop - start;
        Zf(iFFT)(f, logn);
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    fast_fft = times[tests >> 1];

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        fwd_FFT_adj(g, logn);

        TIME(stop);
        times[j] = stop - start;
        inv_FFT_adj(g, logn);
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    adj_fft = times[tests >> 1];

    split(tmp, g, logn);

    if (cmp_double(f, tmp, logn))
    {
        return 1;
    }

    printf("| FWD_FFT %u | %8lld | %8lld\n", logn, fast_fft, adj_fft);

    for (int j = 0; j < tests; j++)
    {
        Zf(FFT)(f, logn);
        TIME(start);

        Zf(iFFT)(f, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    fast_fft = times[tests >> 1];

    for (int j = 0; j < tests; j++)
    {
        fwd_FFT_adj(g, logn);
        TIME(start);

        inv_FFT_adj(g, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    adj_fft = times[tests >> 1];

    split(tmp, g, logn);

    if (cmp_double(f, tmp, logn))
    {
        return 1;
    }

    printf("| INV_FFT %u | %8lld | %8lld\n", logn, fast_fft, adj_fft);

    return 0;
}

int test_with_ref_FFF(unsigned logn, unsigned tests)
{
    fpr f[1024], g[1024];
    const unsigned n = 1 << logn;
    for (int i = 0; i < n; i++)
    {
        f[i].v = drand(-12289.0, 12289);
        g[i].v = f[i].v;
    }

    long long fast_fft, ref_fft;
    long long start, stop;

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        Zf(FFT)(f, logn);

        TIME(stop);
        times[j] = stop - start;
        Zf(iFFT)(f, logn);
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    fast_fft = times[tests >> 1];

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        Zf(FFT_ref)(g, logn);

        TIME(stop);
        times[j] = stop - start;
        Zf(iFFT_ref)(g, logn);
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    ref_fft = times[tests >> 1];

    if (cmp_double(f, g, logn))
    {
        return 1;
    }
    printf("| FWD_FFT %u | %8lld | %8lld\n", logn, fast_fft, ref_fft);

    for (int j = 0; j < tests; j++)
    {
        Zf(FFT)(f, logn);
        TIME(start);

        Zf(iFFT)(f, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    fast_fft = times[tests >> 1];

    for (int j = 0; j < tests; j++)
    {
        Zf(FFT_ref)(g, logn);
        TIME(start);

        Zf(iFFT_ref)(g, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    ref_fft = times[tests >> 1];

    if (cmp_double(f, g, logn))
    {
        return 1;
    }
    printf("| INV_FFT %u | %8lld | %8lld\n", logn, fast_fft, ref_fft);

    return 0;
}

int test_variant_fft(unsigned logn, unsigned tests)
{
    fpr f[1024], g[1024];
    const unsigned n = 1 << logn;
    for (int i = 0; i < n; i++)
    {
        f[i].v = drand(-12289.0, 12289);
        g[i].v = f[i].v;
    }

    long long fast_fft, short_fft;
    long long start, stop;

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        Zf(FFT)(f, logn);
        Zf(iFFT)(f, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    fast_fft = times[tests >> 1];

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        fwd_FFT_short(g, logn);
        inv_FFT_short(g, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    short_fft = times[tests >> 1];

    if (cmp_double(f, g, logn))
    {
        return 1;
    }
    printf("| FFT %u | %8lld | %8lld\n", logn, fast_fft, short_fft);
    return 0;
}

int test_split_merge_function(unsigned logn, unsigned tests)
{
    fpr f[1024] = {0}, f0[1024] = {0}, f1[1024] = {0};
    fpr g[1024] = {0}, g0[1024] = {0}, g1[1024] = {0};
    const unsigned n = 1 << logn;
    for (int i = 0; i < n; i++)
    {
        f[i].v = drand(-12289.0, 12289);
    }

    long long fast, ref;
    long long start, stop;

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        Zf(poly_split_fft)(f0, f1, f, logn);
        Zf(poly_merge_fft)(f, f0, f1, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    fast = times[tests >> 1];

    for (int j = 0; j < tests; j++)
    {
        TIME(start);

        Zf(poly_split_fft_ref)(g0, g1, f, logn);
        Zf(poly_merge_fft_ref)(g, g0, g1, logn);

        TIME(stop);
        times[j] = stop - start;
    }
    qsort(times, tests, sizeof(uint64_t), cmp_uint64_t);
    ref = times[tests >> 1];

    if (cmp_double(f, g, logn))
    {
        print_double(f, logn, "f");
        print_double(g, logn, "g");
        printf("f != g\n");
        return 1;
    }

    printf("| Split/Merge %u | %8lld | %8lld\n", logn, fast, ref);

    return 0;
}

int main(void)
{
#if APPLE_M1 == 1
    setup_rdtsc();
#endif

    printf("\ntest_with_adj_FFT: ");
    printf("\nCompare split FFT versus adjacent FFT setting\n");
    print_header1();
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_with_adj_FFT(logn, ITERATIONS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }

    printf("\ntest_variant_fft: ");
    printf("\nCompare my (loop separated) FFT versus my (without loop separateed) FFT code\n");

    print_header();
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_variant_fft(logn, ITERATIONS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }

    printf("\ntest_with_ref_FFF: ");
    printf("\nCompare my FFT versus reference FFT code\n");
    print_header2();
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_with_ref_FFF(logn, ITERATIONS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }

    printf("\ntest_split_merge_function: ");
    printf("\nCompare my split/merge FFT versus reference split/merge FFT code\n");
    print_header();
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_split_merge_function(logn, ITERATIONS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }

    return 0;
}


// Compile flags:
// make test_fft_m1; sudo ./test_fft_m1
// make test_fft_a72; sudo ./test_fft_a72