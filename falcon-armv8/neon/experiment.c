#include <arm_neon.h>
#include <stdio.h>
#include <stdlib.h>

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
    a2 = vmulq_f64(neon_exp0.val[3], neon_x2);
    a3 = vmulq_f64(neon_exp1.val[1], neon_x2);

    y1 = vaddq_f64(neon_exp0.val[0], a1);
    y2 = vaddq_f64(neon_exp0.val[2], a2);
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
    a2 = vmulq_f64(y3, neon_x8);
    a3 = vmulq_f64(neon_exp1.val[2], neon_x12);

    y = vaddq_f64(y1, a1);
    y = vaddq_f64(y, a2);
    y = vaddq_f64(y, a3);
    // End conversion

    y = vmulq_f64(y, neon_ccs);
    ret = vaddvq_f64(y);

    return (uint64_t) ret;
}

#define TESTS 100ULL
#define DEBUG 1

int main()
{
    fpr ccs, tmp;
    uint64_t a, b, diff;
    uint64_t count = 0; 
    srand(0); 

    for (int i = 0; i < TESTS; i++)
    {
        ccs = (fpr)rand() / RAND_MAX;
        tmp = (fpr)rand() / RAND_MAX;

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
                printf("a: %llu\n", a);
                printf("b: %llu\n", b);
                printf("diff: %llu\n", diff);
                printf("=====\n");
            }
            count++;
        }
    }
    printf("Total incorrect: %llu/%llu\n", count, TESTS);

    return 0;
}

/* 
Input that show rounding differences between fmla and (fmul, fadd)

ccs: 0.0677689729
tmp: 0.9931269297
a: 231532032786398208
b: 231532032786398336
diff: 128
=====
ccs: 0.9326404403
tmp: 0.8878795341
a: 3539996132600134656
b: 3539996132600132608
diff: 2048
=====
ccs: 0.8351854067
tmp: 0.9611296141
a: 2946180401908340736
b: 2946180401908338688
diff: 2048
=====
ccs: 0.2400622485
tmp: 0.7262111985
a: 1071085352550712832
b: 1071085352550712320
diff: 512
=====
ccs: 0.9963487159
tmp: 0.6328673119
a: 4880342603999947776
b: 4880342603999949824
diff: 2048
=====
ccs: 0.9891460780
tmp: 0.5781329524
a: 5117645620162873344
b: 5117645620162875392
diff: 2048
=====
ccs: 0.6457790307
tmp: 0.6081689455
a: 3242270527487101952
b: 3242270527487102464
diff: 512
=====
Total incorrect: 7/100
 */
