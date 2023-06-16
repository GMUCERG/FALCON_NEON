#include <stdio.h>
#include <arm_neon.h>

#define FALCON_Q 12289
#define FALCON_QINV (-12287)

/* const uint32_t rlog = 18;

uint16_t mont_mul(uint16_t x, uint16_t y)
{
    uint32_t u, a;

    a = (uint32_t) x * y; 
    u = (a * FALCON_QINV);
    u &= ((1<<rlog)-1);
    u *= FALCON_Q;
    a = a + u;
    a = a >> 18;
    return a;
}


uint16_t mont_mul_simd(uint16_t a, uint16_t b)
{
    uint16x8_t l, h, t;

    uint32_t c; 
    c = a; 
    c = c * b; 
    c = c % FALCON_Q;

    return c;
    
}
 */

uint16_t barrett_reduce(uint16_t a)
{
  uint32_t u;

  u = ((uint32_t) a * 5) >> 16;
//   printf("br: u = %d\n", u);
  u *= FALCON_Q;
  a -= u;
  return a;
}

uint16_t barrett_red_simd(uint16_t a)
{
    uint16x8_t t, tl, th, z;

    z = vdupq_n_u16(a);

    tl = vmull_n_u16( vget_low_u16(z), 5);
    th = vmull_high_n_u16(z, 5);
    t = vuzp2q_u16(tl, th);
    z = vmlsq_n_u16(z, t, FALCON_Q);

    return z[0];
}


int search(uint16_t x, const char *string, int verbose)
{
    if (verbose)
        printf("%s:\n", string);

    uint16_t gold, test;
    int count = 0;
    uint16_t start, end;
    unsigned already_set = 0;
    unsigned already_print = 0;
    uint16_t min = UINT16_MAX, max = 0;

    for (uint16_t y = 0; y < x; y++)
    {
        // gold = y % FALCON_Q;
        gold = barrett_reduce(y);
        test = barrett_red_simd(y);

        if (test < min) min = test;
        if (max < test) max = test;

        if ( gold == test)
        {
            // printf("%u : %u == %u\n\n", i & 0xffff, gold &0xffff, test & 0xffff);
            count++;
            if (!already_set)
            {
                start = y;
                already_set = 1;
                already_print = 0;
            }
        }
        else
        {
            end = y;
            if (verbose)
            {
                // printf("%u : %u != %u |%u| |%u|\n", y & 0xffff, gold &0xffff, test & 0xffff, (test - gold) & 0xffff, (gold - test)&0xffff);
                if (!already_print)
                {
                    printf("%d: %d -> %d | %d | \n", y, start, end, end - start);
                }
                already_print = 1;
            }
            already_set = 0;
        }
    }

    if (verbose)
    {
        printf("min, max = %d, %d, count = %d\n", min, max, count);

    }
    return count;
}


int main()
{

    int ret = 0;

    // ret |= search_mont_mul();
    ret |= search(UINT16_MAX, "test barrett red", 1);

    if (ret)
        return 1;

    return 0;
}

/*
g++ -o barrett_search_unsigned barrett_search_unsigned.cpp -O3; ./barrett_search_unsigned
TODO: Unsigned bound check q = 12289

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