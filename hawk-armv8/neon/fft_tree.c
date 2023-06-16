/*
 * High-speed vectorize FFT tree for arbitrary `logn`.
 *
 * =============================================================================
 * Copyright (c) 2021 by Cryptographic Engineering Research Group (CERG)
 * ECE Department, George Mason University
 * Fairfax, VA, U.S.A.
 * Author: Duc Tri Nguyen
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * =============================================================================
 * @author   Duc Tri Nguyen <dnguye69@gmu.edu>
 */

#include "inner.h"
#include "macrof.h"
#include "macrofx4.h"

static inline 
void ZfN(poly_mergeFFT_log2)(fpr *f, const fpr *f0, const fpr *f1)
{

    /*
    n = 4; hn = 2; qn = 1;
    a_re = f0[0];
    a_im = f0[1];
    d_re = f1[0];
    d_im = f1[1];

    b_re = 0*4 - 1*5
    b_im = 0*5 + 1*4
     */
    fpr a_re, a_im, b_re, b_im, d_re, d_im, s;
    a_re = f0[0];
    a_im = f0[1];
    s = fpr_tab_log2[0];
    b_re = f1[0] * s;
    b_im = f1[1] * s;

    d_re = b_re - b_im;
    d_im = b_re + b_im;

    f[0] = a_re + d_re;
    f[2] = a_im + d_im;
    f[1] = a_re - d_re;
    f[3] = a_im - d_im;
}

static inline 
void ZfN(poly_mergeFFT_log3)(fpr *f, const fpr *f0, const fpr *f1)
{
    /* 
    f1(   0,    2) * (   0,    1)
    f1(   1,    3) * (   2,    3)

    f(   0,    4) = f0(   0,    2) - @
    f(   2,    6) = f0(   1,    3) - @

    f(   1,    5) = f0(   0,    2) + @
    f(   3,    7) = f0(   1,    3) + @
     */

    float64x2x2_t g1, g0, g_re, g_im, s_re_im;
    float64x2_t t_re, t_im;

    vloadx2(g1, &f1[0]);

    vload2(s_re_im, &fpr_tab_log3[0]);

    FWD_TOP(t_re, t_im, g1.val[0], g1.val[1], s_re_im.val[0], s_re_im.val[1]);

    vloadx2(g0, &f0[0]);

    FPC_ADD(g_re.val[0], g_im.val[0], g0.val[0], g0.val[1], t_re, t_im);
    FPC_SUB(g_re.val[1], g_im.val[1], g0.val[0], g0.val[1], t_re, t_im);

    vstore2(&f[0], g_re);
    vstore2(&f[4], g_im);
}

static inline 
void ZfN(poly_mergeFFT_log4)(fpr *f, const fpr *f0, const fpr *f1, const unsigned logn)
{
    /* 
    n = 16; hn = 8; ht = 4
    f1(   0,    4) * (   0,    1)
    f1(   2,    6) * (   2,    3)
    
    f(   0,    8) = f0(   0,    4) + @
    f(   4,   12) = f0(   2,    6) + @

    f(   1,    9) = f0(   0,    4) - @
    f(   5,   13) = f0(   2,    6) - @
    ===
    f1(   1,    5) * (   0,    1)
    f1(   3,    7) * (   2,    3)
    
    f(   2,   10) = f0(   1,    5) + j@
    f(   6,   14) = f0(   3,    7) + j@
    
    f(   3,   11) = f0(   1,    5) - j@
    f(   7,   15) = f0(   3,    7) - j@
    ---------
     */
    const unsigned n = 1 << logn;
    const unsigned ht = n >> 2;
    const fpr *fpr_merge = fpr_table[logn - 2];

    // Total SIMD register 22 = 14 + 8
    float64x2x2_t g1_re, g1_im, g0_re, g0_im, s_re_im, t_re, t_im; // 14
    float64x2x4_t g_re, g_im;                                      // 8

    for (unsigned j = 0; j < ht; j+= 4)
    {
        vload2(g1_re, &f1[j]);
        vload2(g1_im, &f1[j + ht]);

        vload2(s_re_im, &fpr_merge[j]);

        FWD_TOP(t_re.val[0], t_im.val[0], g1_re.val[0], g1_im.val[0], s_re_im.val[0], s_re_im.val[1]);
        vload2(g0_re, &f0[j]);

        FWD_TOP(t_re.val[1], t_im.val[1], g1_re.val[1], g1_im.val[1], s_re_im.val[0], s_re_im.val[1]);
        vload2(g0_im, &f0[j + ht]);

        FPC_ADD (g_re.val[0], g_im.val[0], g0_re.val[0], g0_im.val[0], t_re.val[0], t_im.val[0]);
        FPC_SUB (g_re.val[1], g_im.val[1], g0_re.val[0], g0_im.val[0], t_re.val[0], t_im.val[0]);
        FPC_ADDJ(g_re.val[2], g_im.val[2], g0_re.val[1], g0_im.val[1], t_re.val[1], t_im.val[1]);
        FPC_SUBJ(g_re.val[3], g_im.val[3], g0_re.val[1], g0_im.val[1], t_re.val[1], t_im.val[1]);

        vstore4(&f[j << 1], g_re);
        vstore4(&f[(j + ht) << 1], g_im);
    }
}

static void 
ZfN(poly_splitFFT_log2)(fpr *restrict f0, fpr *restrict f1, const fpr *restrict f)
{

    /*
    n = 4; hn = 2; qn = 1;
    f0[0] = 0 = 0 + 1
    f0[1] = 2 = 2 + 3
    
    f1[1] = 3 = (2 - 3)*4 - (0 - 1)*5
    f1[0] = 1 = (2 - 3)*5 + (0 - 1)*4

    f0:(   0,    1) = (   0,    2) + (   1,    3)
    (   0,    2) - (   1,    3)
    f1:(   0,    1) = @ * (   4,    5)
    */

    fpr a_re, a_im, b_re, b_im, d_re, d_im, s;
    a_re = f[0];
    b_re = f[1];
    a_im = f[2];
    b_im = f[3];
    s = fpr_tab_log2[0] * 0.5;

    f0[0] = (a_re + b_re) * 0.5;
    f0[1] = (a_im + b_im) * 0.5;

    d_re = (a_re - b_re) * s;
    d_im = (a_im - b_im) * s;

    f1[0] = d_im + d_re;
    f1[1] = d_im - d_re;

}

static inline 
void ZfN(poly_splitFFT_log3)(fpr *f0, fpr *f1, const fpr *f)
{
    /* 
    f0: (   0,    2) = (   0,    4) + (   1,    5)
    f0: (   1,    3) = (   2,    6) + (   3,    7)
    
    @ = (   0,    4) - (   1,    5)
    @ = (   2,    6) - (   3,    7)

    f1: (   0,    2) = @ * (   8,    9)
    f1: (   1,    3) = @ * (  10,   11) 
    */

    /*
     * g0 = 0, 2 | 1, 3
     * g1 = 4, 6 | 5, 7 
     */
    float64x2x2_t re, im, g0, g1, s_re_im, tm; 
    
    vload2(re, &f[0]);
    vload2(im, &f[4]);

    FPC_ADD(g0.val[0], g0.val[1], re.val[0], im.val[0], re.val[1], im.val[1]);
    FPC_SUB(tm.val[0], tm.val[1], re.val[0], im.val[0], re.val[1], im.val[1]);
    vload2(s_re_im, &fpr_tab_log3[0]);

    vfmuln(g0.val[0], g0.val[0], 0.5);
    vfmuln(g0.val[1], g0.val[1], 0.5);
    vstorex2(&f0[0], g0);

    vfmuln(s_re_im.val[0], s_re_im.val[0], 0.5);
    vfmuln(s_re_im.val[1], s_re_im.val[1], 0.5);

    INV_BOTJ(g1.val[0], g1.val[1], tm.val[0], tm.val[1], s_re_im.val[0], s_re_im.val[1]);

    vstorex2(&f1[0], g1);
}

static inline 
void ZfN(poly_splitFFT_log4)(fpr *f0, fpr *f1, const fpr *f, const unsigned logn)
{
    const unsigned n = 1 << logn; 
    const unsigned hn = n >> 1; 
    const unsigned ht = n >> 2; 
    const fpr *fpr_split = fpr_table[logn - 2];

    // Total SIMD register 23 = 8 + 14 + 1

    float64x2x4_t g_re, g_im;                                         // 8
    float64x2x2_t s_re_im, t_re, t_im, g1_re, g1_im, g0_re, g0_im;    // 14
    float64x2_t half;                                                 // 1
    /*
    f0: (   0,    4) = (   0,    8) + (   1,    9)
    f0: (   2,    6) = (   4,   12) + (   5,   13)
    f0: (   1,    5) = (   2,   10) + (   3,   11)
    f0: (   3,    7) = (   6,   14) + (   7,   15)

    @ = (   0,    8) - (   1,    9)
    @ = (   4,   12) - (   5,   13)
    f1: (   0,    4) = @ * (  16,   17)
    f1: (   2,    6) = @ * (  20,   21)

    @ = (   2,   10) - (   3,   11)
    @ = (   6,   14) - (   7,   15)
    f1: (   1,    5) = j@ * (  18,   19)
    f1: (   3,    7) = j@ * (  22,   23) 
    */

    half = vdupq_n_f64(0.5);
    for (unsigned j = 0; j < ht; j+= 4)
    {
        unsigned j2 = j << 1; 
        vload4(g_re, &f[j2]);
        vload4(g_im, &f[j2 + hn]);

        FPC_ADD(g0_re.val[0], g0_im.val[0], g_re.val[0], g_im.val[0], g_re.val[1], g_im.val[1]);
        FPC_ADD(g0_re.val[1], g0_im.val[1], g_re.val[2], g_im.val[2], g_re.val[3], g_im.val[3]);

        FPC_SUB(t_re.val[0], t_im.val[0], g_re.val[0], g_im.val[0], g_re.val[1], g_im.val[1]);
        FPC_SUB(t_re.val[1], t_im.val[1], g_re.val[3], g_im.val[3], g_re.val[2], g_im.val[2]);

        vload2(s_re_im, &fpr_split[j]);
        
        vfmul(g0_re.val[0], g0_re.val[0], half);
        vfmul(g0_re.val[1], g0_re.val[1], half);
        vstore2(&f0[j], g0_re);

        vfmul(g0_im.val[0], g0_im.val[0], half);
        vfmul(g0_im.val[1], g0_im.val[1], half);
        vstore2(&f0[j + ht], g0_im);
        
        vfmul(s_re_im.val[0], s_re_im.val[0], half);
        vfmul(s_re_im.val[1], s_re_im.val[1], half);

        INV_BOTJ (g1_re.val[0], g1_im.val[0], t_re.val[0], t_im.val[0], s_re_im.val[0], s_re_im.val[1]);
        INV_BOTJm(g1_re.val[1], g1_im.val[1], t_re.val[1], t_im.val[1], s_re_im.val[0], s_re_im.val[1]);

        vstore2(&f1[j], g1_re);
        vstore2(&f1[j + ht], g1_im);
    }
}

/*
 * Recursive Split FFT
 */
void ZfN(poly_split_fft)(fpr *restrict f0, fpr *restrict f1, const fpr *f, const unsigned logn)
{
    switch (logn)
    {
    case 1:
        //  n = 2; hn = 1; qn = 0;
        f0[0] = f[0];
        f1[0] = f[1];
        break;

    case 2:
        ZfN(poly_splitFFT_log2)(f0, f1, f);
        break;

    case 3:
        ZfN(poly_splitFFT_log3)(f0, f1, f);
        break;

    default:
        ZfN(poly_splitFFT_log4)(f0, f1, f, logn);
        break;
    }
}

/*
 * see inner.h
 * Only support logn >= 3
 */
void ZfN(poly_merge_fft)(fpr *restrict f, const fpr *restrict f0,
                         const fpr *restrict f1, const unsigned logn)
{
    switch (logn)
    {
    case 1:
        // n = 2; hn = 1;
        f[0] = f0[0];
        f[1] = f1[0];
        break;

    case 2:
        ZfN(poly_mergeFFT_log2)(f, f0, f1);
        break;

    case 3:
        ZfN(poly_mergeFFT_log3)(f, f0, f1);
        break;

    default:
        ZfN(poly_mergeFFT_log4)(f, f0, f1, logn);
        break;
    }
}
