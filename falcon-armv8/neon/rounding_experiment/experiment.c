#include <arm_neon.h>
#include <stdio.h>
#include "mtwister.h"

typedef double fpr;

static const fpr fpr_ptwo63 = 9223372036854775808.0;
static const double C_expm[] = {
    1.000000000000000000000000000000,  // c0
    -0.999999999999994892974086724280, // c1
    0.500000000000019206858326015208,  // c2
    -0.166666666666984014666397229121, // c3
    0.041666666666110491190622155955,  // c4
    -0.008333333327800835146903501993, // c5
    0.001388888894063186997887560103,  // c6
    -0.000198412739277311890541063977, // c7
    0.000024801566833585381209939524,  // c8
    -0.000002755586350219122514855659, // c9
    0.000000275607356160477811864927,  // c10
    -0.000000025299506379442070029551, // c11
    0.000000002073772366009083061987,  // c12
    0.000000000000000000000000000000,
};

/* 
 * Output assembly: via radare2
┌ 108: sym._fpr_expm_p63_fmla ();
│           0x100003dfc      a8070010       adr x8, sym._C_expm        ; 0x100003ef0
│           0x100003e00      1f2003d5       nop
│           0x100003e04      022ddf4c       ld1 {v2.2d, v3.2d, v4.2d, v5.2d}, [x8], 0x40
│           0x100003e08      106d404c       ld1 {v16.2d, v17.2d, v18.2d}, [x8]
│           0x100003e0c      087ce8d2       movz x8, 0x43e0, lsl 48
│           0x100003e10      0601679e       fmov d6, x8
│           0x100003e14      2108661e       fmul d1, d1, d6
│           0x100003e18      06f6036f       fmov v6.2d, 1.00000000
│           0x100003e1c      0604186e       ins v6.d[1], v0.d[0]
│           0x100003e20      0008601e       fmul d0, d0, d0
│           0x100003e24      0708601e       fmul d7, d0, d0
│           0x100003e28      f304084e       dup v19.2d, v7.d[0]
│           0x100003e2c      f408671e       fmul d20, d7, d7
│           0x100003e30      7392d44f       fmul v19.2d, v19.2d, v20.d[0]
│           0x100003e34      6210c04f       fmla v2.2d, v3.2d, v0.d[0]
│           0x100003e38      a410c04f       fmla v4.2d, v5.2d, v0.d[0]
│           0x100003e3c      3012c04f       fmla v16.2d, v17.2d, v0.d[0]
│           0x100003e40      c0dc626e       fmul v0.2d, v6.2d, v2.2d
│           0x100003e44      c2dc646e       fmul v2.2d, v6.2d, v4.2d
│           0x100003e48      c3dc706e       fmul v3.2d, v6.2d, v16.2d
│           0x100003e4c      4010c74f       fmla v0.2d, v2.2d, v7.d[0]
│           0x100003e50      6010d44f       fmla v0.2d, v3.2d, v20.d[0]
│           0x100003e54      60ce724e       fmla v0.2d, v19.2d, v18.2d
│           0x100003e58      0090c14f       fmul v0.2d, v0.2d, v1.d[0]
│           0x100003e5c      00d8707e       faddp d0, v0.2d
│           0x100003e60      0000799e       fcvtzu x0, d0
└           0x100003e64      c0035fd6       ret
 */
static uint64_t __attribute__((noinline)) 
fpr_expm_p63_fmla(const fpr x, const fpr ccs)
{
    float64x2_t neon_x, neon_1x, neon_x2,
        neon_x4, neon_x8, neon_x12, neon_ccs;
    float64x2x4_t neon_exp0;
    float64x2x3_t neon_exp1;
    float64x2_t y1, y2, y3, y;
    double ret;

    neon_exp0 = vld1q_f64_x4(&C_expm[0]);
    neon_exp1 = vld1q_f64_x3(&C_expm[8]);
    neon_ccs = vdupq_n_f64(ccs * fpr_ptwo63);

    // x | x
    neon_x = vdupq_n_f64(x);
    // 1 | x
    neon_1x = vsetq_lane_f64(1.0, neon_x, 0);
    neon_x2 = vmulq_f64(neon_x, neon_x);
    neon_x4 = vmulq_f64(neon_x2, neon_x2);
    neon_x8 = vmulq_f64(neon_x4, neon_x4);
    neon_x12 = vmulq_f64(neon_x8, neon_x4);

    y1 = vfmaq_f64(neon_exp0.val[0], neon_exp0.val[1], neon_x2);
    y2 = vfmaq_f64(neon_exp0.val[2], neon_exp0.val[3], neon_x2);
    y3 = vfmaq_f64(neon_exp1.val[0], neon_exp1.val[1], neon_x2);

    y1 = vmulq_f64(y1, neon_1x);
    y2 = vmulq_f64(y2, neon_1x);
    y3 = vmulq_f64(y3, neon_1x);

    y = vfmaq_f64(y1, y2, neon_x4);
    y = vfmaq_f64(y, y3, neon_x8);
    y = vfmaq_f64(y, neon_exp1.val[2], neon_x12);
    
    y = vmulq_f64(y, neon_ccs);
    ret = vaddvq_f64(y);

    return (uint64_t) ret;
}

/* 
 * Output assembly: via radare2
┌ 132: sym._fpr_expm_p63 ();
│           0x100003d78      c80b0010       adr x8, sym._C_expm        ; 0x100003ef0
│           0x100003d7c      1f2003d5       nop
│           0x100003d80      022ddf4c       ld1 {v2.2d, v3.2d, v4.2d, v5.2d}, [x8], 0x40
│           0x100003d84      106d404c       ld1 {v16.2d, v17.2d, v18.2d}, [x8]
│           0x100003d88      087ce8d2       movz x8, 0x43e0, lsl 48
│           0x100003d8c      0601679e       fmov d6, x8
│           0x100003d90      2108661e       fmul d1, d1, d6
│           0x100003d94      06f6036f       fmov v6.2d, 1.00000000
│           0x100003d98      0604186e       ins v6.d[1], v0.d[0]
│           0x100003d9c      0008601e       fmul d0, d0, d0
│           0x100003da0      0708601e       fmul d7, d0, d0
│           0x100003da4      f304084e       dup v19.2d, v7.d[0]
│           0x100003da8      f408671e       fmul d20, d7, d7
│           0x100003dac      7392d44f       fmul v19.2d, v19.2d, v20.d[0]
│           0x100003db0      7590c04f       fmul v21.2d, v3.2d, v0.d[0]
│           0x100003db4      b690c04f       fmul v22.2d, v5.2d, v0.d[0]
│           0x100003db8      2092c04f       fmul v0.2d, v17.2d, v0.d[0]
│           0x100003dbc      55d4754e       fadd v21.2d, v2.2d, v21.2d
│           0x100003dc0      82d4764e       fadd v2.2d, v4.2d, v22.2d
│           0x100003dc4      00d6604e       fadd v0.2d, v16.2d, v0.2d
│           0x100003dc8      c3dc756e       fmul v3.2d, v6.2d, v21.2d
│           0x100003dcc      c2dc626e       fmul v2.2d, v6.2d, v2.2d
│           0x100003dd0      c0dc606e       fmul v0.2d, v6.2d, v0.2d
│           0x100003dd4      4290c74f       fmul v2.2d, v2.2d, v7.d[0]
│           0x100003dd8      0090d44f       fmul v0.2d, v0.2d, v20.d[0]
│           0x100003ddc      64de726e       fmul v4.2d, v19.2d, v18.2d
│           0x100003de0      62d4624e       fadd v2.2d, v3.2d, v2.2d
│           0x100003de4      40d4604e       fadd v0.2d, v2.2d, v0.2d
│           0x100003de8      80d4604e       fadd v0.2d, v4.2d, v0.2d
│           0x100003dec      0090c14f       fmul v0.2d, v0.2d, v1.d[0]
│           0x100003df0      00d8707e       faddp d0, v0.2d
│           0x100003df4      0000799e       fcvtzu x0, d0
└           0x100003df8      c0035fd6       ret
 */
static uint64_t __attribute__((noinline)) 
fpr_expm_p63(const fpr x, const fpr ccs)
{

    float64x2_t neon_x, neon_1x, neon_x2,
        neon_x4, neon_x8, neon_x12, neon_ccs;
    float64x2x4_t neon_exp0;
    float64x2x3_t neon_exp1;
    float64x2_t y1, y2, y3, y;
    double ret;

    neon_exp0 = vld1q_f64_x4(&C_expm[0]);
    neon_exp1 = vld1q_f64_x3(&C_expm[8]);
    neon_ccs = vdupq_n_f64(ccs * fpr_ptwo63);

    // x | x
    neon_x = vdupq_n_f64(x);
    // 1 | x
    neon_1x = vsetq_lane_f64(1.0, neon_x, 0);
    neon_x2 = vmulq_f64(neon_x, neon_x);
    neon_x4 = vmulq_f64(neon_x2, neon_x2);
    neon_x8 = vmulq_f64(neon_x4, neon_x4);
    neon_x12 = vmulq_f64(neon_x8, neon_x4);

    float64x2_t a1, a2, a3;

    // y1 = vfmaq_f64(neon_exp0.val[0], neon_exp0.val[1], neon_x2);
    // y2 = vfmaq_f64(neon_exp0.val[2], neon_exp0.val[3], neon_x2);
    // y3 = vfmaq_f64(neon_exp1.val[0], neon_exp1.val[1], neon_x2);
    // Convert to below code

    a1 = vmulq_f64(neon_exp0.val[1], neon_x2);
    y1 = vaddq_f64(neon_exp0.val[0], a1);

    a2 = vmulq_f64(neon_exp0.val[3], neon_x2);
    y2 = vaddq_f64(neon_exp0.val[2], a2);
    
    a3 = vmulq_f64(neon_exp1.val[1], neon_x2);
    y3 = vaddq_f64(neon_exp1.val[0], a3);
    // End conversion

    y1 = vmulq_f64(y1, neon_1x);
    y2 = vmulq_f64(y2, neon_1x);
    y3 = vmulq_f64(y3, neon_1x);

    // y = vfmaq_f64(y1, y2, neon_x4);
    // y = vfmaq_f64(y, y3, neon_x8);
    // y = vfmaq_f64(y, neon_exp1.val[2], neon_x12);
    // Convert to below code
    a1 = vmulq_f64(y2, neon_x4);
    y = vaddq_f64(y1, a1);
    
    a2 = vmulq_f64(y3, neon_x8);
    y = vaddq_f64(y, a2);
    
    a3 = vmulq_f64(neon_exp1.val[2], neon_x12);
    y = vaddq_f64(y, a3);
    // End conversion

    y = vmulq_f64(y, neon_ccs);
    ret = vaddvq_f64(y);

    return (uint64_t) ret;
}

#define TESTS 100000ULL
#define DEBUG 1

int main()
{
    fpr ccs, tmp;
    uint64_t a, b, diff;
    uint64_t count = 0; 
    
    MTRand r = seedRand(0x123456);

    for (uint64_t i = 0; i < TESTS; i++)
    {
        ccs = genRand(&r);
        tmp = genRand(&r);

        a = fpr_expm_p63(tmp, ccs);
        b = fpr_expm_p63_fmla(tmp, ccs);

        diff = a - b;
        // abs(diff)
        if (diff & 0x1000000000000000) diff = -diff;
        

        if (a != b)
        {
            if (DEBUG)
            {
                printf("ccs: %.10f\n", ccs);
                printf("tmp: %.10f\n", tmp);
                printf("%3lu: a, b: %8lx | %8lx\n", i, a, b);
                printf("diff: %lu\n", diff);
                printf("=====\n");
            }
            count++;
        }
        if (!DEBUG) printf("%3lu: %08lx\n", i, a);
    }
    printf("Total incorrect: %lu/%llu\n", count, TESTS);

    return 0;
}

/* 
Input that show rounding differences between fmla and (fmul, fadd)

- Apple M1, Cortex-A72 over the same input
ccs: 0.2580461167
tmp: 0.9669854429
  2: a, b: c8f12a7b6931c00 | c8f12a7b6931e00
diff: 512
=====
ccs: 0.6310408659
tmp: 0.5769365662
 10: a, b: 2d5d11fb1ecdb000 | 2d5d11fb1ecdac00
diff: 1024
=====
ccs: 0.6147814027
tmp: 0.9990875227
 44: a, b: 1cf9c129ebbb3c00 | 1cf9c129ebbb4400
diff: 2048
=====
ccs: 0.1861301493
tmp: 0.8928304473
 49: a, b: 9c18e77bf126e00 | 9c18e77bf126c00
diff: 512
=====
ccs: 0.1376206992
tmp: 0.7580903107
 63: a, b: 840ffb32db7d300 | 840ffb32db7d200
diff: 256
=====
ccs: 0.3532692032
tmp: 0.6281543962
 75: a, b: 1820a1c965ccc100 | 1820a1c965ccc500
diff: 1024
=====
ccs: 0.9403613421
tmp: 0.8524000428
 79: a, b: 3352b0a680b3d800 | 3352b0a680b3e000
diff: 2048
=====
Total incorrect: 7/100
 */
