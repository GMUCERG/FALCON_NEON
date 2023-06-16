
#include <stdio.h>
#include <arm_neon.h>


// gcc -o test_fpr test_fpr.c -O3;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / 128371289.0;
    // printf("f = %f\n", f);
    return fMin + f * (fMax - fMin);
}


typedef double fpr;
#define TESTS 10000000

static const fpr fpr_ptwo63 = 9223372036854775808.0 ;

uint64_t
fpr_expm_p63(fpr x, fpr ccs)
{
	/*
	 * Polynomial approximation of exp(-x) is taken from FACCT:
	 *   https://eprint.iacr.org/2018/1234
	 * Specifically, values are extracted from the implementation
	 * referenced from the FACCT article, and available at:
	 *   https://github.com/raykzhao/gaussian
	 * Tests over more than 24 billions of random inputs in the
	 * 0..log(2) range have never shown a deviation larger than
	 * 2^(-50) from the true mathematical value.
	 */
	/*
	 * Normal implementation uses Horner's method, which minimizes
	 * the number of operations.
	 */

	double d, y;

	d = x;
	y = 0.000000002073772366009083061987;
	y = 0.000000025299506379442070029551 - y * d;
	y = 0.000000275607356160477811864927 - y * d;
	y = 0.000002755586350219122514855659 - y * d;
	y = 0.000024801566833585381209939524 - y * d;
	y = 0.000198412739277311890541063977 - y * d;
	y = 0.001388888894063186997887560103 - y * d;
	y = 0.008333333327800835146903501993 - y * d;
	y = 0.041666666666110491190622155955 - y * d;
	y = 0.166666666666984014666397229121 - y * d;
	y = 0.500000000000019206858326015208 - y * d;
	y = 0.999999999999994892974086724280 - y * d;
	y = 1.000000000000000000000000000000 - y * d;
	y *= ccs;
    y *= fpr_ptwo63;
	// return (uint64_t)(y * fpr_ptwo63);
    // printf("ref__ret: %.20f\n", y);

    return (uint64_t) y;
}

uint64_t
fpr_expm_p63_neon(fpr x, fpr ccs)
{
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
    float64x2_t neon_x, neon_x0, neon_1x, neon_x2, 
                neon_x4, neon_x8, neon_x12, neon_ccs;
    float64x2x4_t neon_exp0;
    float64x2x3_t neon_exp1;
    float64x2_t y1, y2, y3, y4, y;
    double ret;
    
    neon_exp0 = vld1q_f64_x4(&C_expm[0]);
    neon_exp1 = vld1q_f64_x3(&C_expm[8]);
    neon_ccs = vdupq_n_f64(ccs);
    neon_ccs = vmulq_n_f64(neon_ccs, fpr_ptwo63);

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
    y = vfmaq_f64( y, y3, neon_x8);
    y = vfmaq_f64( y, neon_exp1.val[2], neon_x12);
    y = vmulq_f64( y, neon_ccs);
    ret = vaddvq_f64(y);

    return (uint64_t) ret;

}

int main()
{
    fpr tmp, ccs;
    fpr x;
    float64x1_t neon_x, neon_ccs;
    uint64_t neon_ret;
    uint64_t ret;
    int count = 0;
    srand(123);
    for (int i = 0; i < TESTS; i++)
    {
        ccs = fRand(0, 0.6931471805599453);
        x = fRand(-10, 10);

        neon_ret = fpr_expm_p63_neon(x, ccs);
        ret = fpr_expm_p63(x, ccs);

        if (ret != neon_ret)
        {
            // printf("Wrong fpr_expm_p63 %d: %f -- %f\n", i, x, ccs);
            // printf("Wrong fpr_expm_p63 %d: %lu != %lu \n", i, ret, neon_ret);
            count++;
        }
    }
    printf("Error: %d/%d\n", count, TESTS);
    return 0;
}