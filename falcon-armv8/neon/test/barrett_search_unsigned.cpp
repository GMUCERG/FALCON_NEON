#include <stdio.h>
#include <arm_neon.h>


#define FALCON_Q 12289
#define FALCON_QINV (-12287)

uint16_t barrett_reduce(uint16_t a)
{
    uint16_t t;
    const int sr = 28;
    const uint16_t v = (1 << sr) / FALCON_Q + 1;

    t = ((uint32_t)v * a) >> sr;
    t *= FALCON_Q;
    return a - t;
}

template <int shift>
uint16_t barrett_simd(uint16_t a, int k, int ROUNDING, int SHIFT_ROUNDING, int SHIFT_SIGNED)
{
    uint16x8_t t, z;
    z = vdupq_n_u16(a);

    if (ROUNDING)
        t = vqrdmulhq_n_s16(z, k);
    else
        t = vqdmulhq_n_s16(z, k);

    if (SHIFT_ROUNDING)
    {
        if (SHIFT_SIGNED) 
            t = vrshrq_n_s16(t, shift);
        else
            t = vrshrq_n_u16(t, shift);
    }
    else
    {
        if (SHIFT_SIGNED)
            t = vshrq_n_s16(t, shift);
        else
            t = vshrq_n_u16(t, shift);
    }

    if (t[0] != a/FALCON_Q)
    {
        // The shift right rounding toward infinite, which mismatch with the correct result
        // printf("%d: %d, t >>%d = %d - |%d|\n", a, bk[0], 14, t[0] & 0xffff, a / FALCON_Q);
    }

    z = vmlaq_n_u16(z, t, -FALCON_Q);
    return z[0];
}


int search(uint16_t k, uint16_t (*func)(uint16_t, int, int, int, int), const char *string, int ROUNDING, int SHIFT_ROUNDING, int SHIFT_SIGNED, int verbose)
{
    // if (verbose)
    //     printf("test_barrett_reduction: %s\n", string);

    uint16_t gold, test;
    int count = 0;
    uint16_t start, end;
    unsigned already_set = 0;
    unsigned already_print = 0;
    uint16_t min = UINT16_MAX, max = 0;

    for (uint16_t i = 0; i < 5*FALCON_Q; i++)
    {
        gold = i % FALCON_Q;
        test = func(i, k, ROUNDING, SHIFT_ROUNDING, SHIFT_SIGNED);

        if (test < min) min = test;
        if (max < test) max = test;

        // if ( (((uint16_t) gold + FALCON_Q) == test) || ( ((uint16_t)test + FALCON_Q) == gold) || (gold == test))
        if (gold == test)
        {
            // printf("%u : %u == %u\n\n", i & 0xffff, gold &0xffff, test & 0xffff);
            count++;
            if (!already_set)
            {
                start = i;
                already_set = 1;
                already_print = 0;
            }
        }
        else
        {
            end = i;
            if (verbose)
            {
                printf("%u : %u != %u |%u|\n\n", i & 0xffff, gold &0xffff, test & 0xffff, (gold - test) & 0xffff);
                if (!already_print)
                {
                    printf("%d: %d -> %d | %d | \n", i, start, end, end - start);
                }
                already_print = 1;
            }
            already_set = 0;
        }
    }

    if (verbose)
    {
        printf("k = %d, count = %d\n", k, count);
        printf("min = %d, max = %d\n\n", min, max);
    }
    return count;
}


#define ASSIGN(x, y, z, w) {x = y; z = w;}

int test_barrett_red(int shift, int k, int i, int j, int m)
{
    switch (shift)
    {
    case 11:
        search(k, barrett_simd<11>, "barrett_simd_11", i, j, m, 1);
        break;
    
    case 12:
        search(k, barrett_simd<12>, "barrett_simd_12", i, j, m, 1);
        break;

    case 13:
        search(k, barrett_simd<13>, "barrett_simd_13", i, j, m, 1);
        break;
    
    case 14:
        search(k, barrett_simd<14>, "barrett_simd_14", i, j, m, 1);
        break;
    
    case 15:
        search(k, barrett_simd<15>, "barrett_simd_15", i, j, m, 1);
        break;
    }
    return 0;
}

int search_barrett_red()
{
    int c11 = 0, c12 = 0, c13 = 0, c14 = 0, c15 = 0;
    int s11 = 0, s12 = 0, s13 = 0, s14 = 0, s15 = 0;
    int k11 = 0, k12 = 0, k13 = 0, k14 = 0, k15 = 0;

    int i = 0;
    int j = 1;
    int m = 0;

    for (i = 0; i < 2; i++)
    for (j = 0; j < 2; j++)
    for (m = 0; m < 2; m++)
    {
        for (uint16_t k = 0; k < UINT16_MAX; k++)
        {
            c11 = search(k, barrett_simd<11>, "barrett_simd_11", i, j, m, 0);
            c12 = search(k, barrett_simd<12>, "barrett_simd_12", i, j, m, 0);
            c13 = search(k, barrett_simd<13>, "barrett_simd_13", i, j, m, 0);
            c14 = search(k, barrett_simd<14>, "barrett_simd_14", i, j, m, 0);
            c15 = search(k, barrett_simd<15>, "barrett_simd_15", i, j, m, 0);

            if (s11 <= c11) ASSIGN(s11, c11, k11, k);
            if (s12 <= c12) ASSIGN(s12, c12, k12, k);
            if (s13 <= c13) ASSIGN(s13, c13, k13, k);
            if (s14 <= c14) ASSIGN(s14, c14, k14, k);
            if (s15 <= c15) ASSIGN(s15, c15, k15, k);

        }
        printf("ROUNDING, SHIFT_ROUNDING, SHIFT_SIGNED = %d, %d, %d:\n", i, j, m);
        printf("11: score = %d [k = %d]\n", s11, k11);
        test_barrett_red(11, k11, i, j, m);

        printf("12: score = %d [k = %d]\n", s12, k12);
        test_barrett_red(12, k12, i, j, m);

        printf("13: score = %d [k = %d]\n", s13, k13);
        test_barrett_red(13, k13, i, j, m);

        printf("14: score = %d [k = %d]\n", s14, k14);
        test_barrett_red(14, k14, i, j, m);

        printf("15: score = %d [k = %d]\n", s15, k15);
        test_barrett_red(15, k15, i, j, m);
        
        
        s11 = 0; k11 = 0;
        s12 = 0; k12 = 0;
        s13 = 0; k13 = 0;
        s14 = 0; k14 = 0;
        s15 = 0; k15 = 0;
    }



    return 0;
}


int main()
{

    int ret = 0;

    // ret |= search_barrett_red();
    ret |= test_barrett_red(14, 28089, 0, 1, 0);
    // ret |= test_barrett_red(13, 21843, 0, 0, 1);
    // ret |= test_barrett_red(14, 32767, 0, 0, 0);

    if (ret)
        return 1;

    return 0;
}

/*
g++ -o barrett_search_unsigned barrett_search_unsigned.cpp -O3; ./barrett_search_unsigned
Unsigned bound check q = 12289

DONE: Center around 0 bound check, q = 12289:
test_montgomery_rounding: OK
min, max = -24568, 24568
test_montgomery_doubling: OK
min, max = -12285, 12288
test_barrett_reduction: OK
min, max = -6145, 6145
test_barrett_mul: OK
min, max = -18431, 18430
 */