/*
 * Common functions for Hawk
 *
 * ==========================(LICENSE BEGIN)============================
 *
 * Copyright (c) 2022 Hawk Project
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
 * @author   Ludo Pulles <ludo.pulles@cwi.nl>
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

#include "inner.h"
#include "macrofx4.h"

/* see inner.h */
/* NIST-1: */
const uint32_t Zf(l2bound_512)[10] = {
	0u /* unused */, 32u, 64u, 129u, 259u, 519u, 1039u, 2079u, 4158u, 8317u
};

/* NIST-5: */
const uint32_t Zf(l2bound_1024)[11] = {
	0u /* unused */, 39u, 79u, 158u, 316u, 632u, 1265u, 2530u, 5060u, 10121u, 20243u
};

/* see inner.h */
const unsigned Zf(bits_q00)[11] = {
	0 /* unused */, 5, 6, 6, 7, 7,  8,  8,  9,  9, 10
};
const unsigned Zf(bits_q01)[11] = {
	0 /* unused */, 5, 6, 7, 8, 8,  9, 10, 11, 12, 14
};
const unsigned Zf(bits_q11)[11] = {
	0 /* unused */, 5, 6, 7, 8, 9, 10, 12, 13, 15, 17
};

/* see inner.h */
const unsigned Zf(bits_s0)[11] = {
	0 /* unused */, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};
const unsigned Zf(bits_s1)[11] = {
	0 /* unused */, 5, 6, 6, 7, 7,  8,  8,  9,  9, 10
};

/* see inner.h */
void
Zf(int8_to_fft)(fpr *p, const int8_t *x, unsigned logn)
{
	size_t u;

	u = MKN(logn);
	while (u -- > 0) {
		p[u] = fpr_of(x[u]);
	}
	ZfN(FFT)(p, logn);
}
void
ZfN(int8_to_fft)(fpr *p, const int8_t *x, unsigned logn)
{
    int8x16x4_t neon_x;
    int16x8x4_t neon_x16_0, neon_x16_1;
    int32x4x4_t neon_x32_0, neon_x32_1, neon_x32_2, neon_x32_3;
    int64x2x4_t neon_x64_0, neon_x64_1, neon_x64_2, neon_x64_3;
    float64x2x4_t neon_p;
    const unsigned hawk_n = 1 << logn;
    for (unsigned u = 0; u < hawk_n; u += 64)
    {
        neon_x = vld1q_s8_x4(&x[u]);

        neon_x16_0.val[0] = vmovl_s8(vget_low_s8(neon_x.val[0]));
        neon_x16_0.val[1] = vmovl_high_s16(neon_x.val[0]);
        neon_x16_0.val[2] = vmovl_s8(vget_low_s8(neon_x.val[1]));
        neon_x16_0.val[3] = vmovl_high_s16(neon_x.val[1]);

        neon_x16_1.val[0] = vmovl_s8(vget_low_s8(neon_x.val[2]));
        neon_x16_1.val[1] = vmovl_high_s16(neon_x.val[2]);
        neon_x16_1.val[2] = vmovl_s8(vget_low_s8(neon_x.val[3]));
        neon_x16_1.val[3] = vmovl_high_s16(neon_x.val[3]);

        neon_x32_0.val[0] = vmovl_s16(vget_low_s16(neon_x16_0.val[0]));
        neon_x32_0.val[1] = vmovl_high_s16(neon_x16_0.val[0]);
        neon_x32_0.val[2] = vmovl_s16(vget_low_s16(neon_x16_0.val[1]));
        neon_x32_0.val[3] = vmovl_high_s16(neon_x16_0.val[1]);

        neon_x32_1.val[0] = vmovl_s16(vget_low_s16(neon_x16_0.val[2]));
        neon_x32_1.val[1] = vmovl_high_s16(neon_x16_0.val[2]);
        neon_x32_1.val[2] = vmovl_s16(vget_low_s16(neon_x16_0.val[3]));
        neon_x32_1.val[3] = vmovl_high_s16(neon_x16_0.val[3]);

        neon_x32_2.val[0] = vmovl_s16(vget_low_s16(neon_x16_1.val[0]));
        neon_x32_2.val[1] = vmovl_high_s16(neon_x16_1.val[0]);
        neon_x32_2.val[2] = vmovl_s16(vget_low_s16(neon_x16_1.val[1]));
        neon_x32_2.val[3] = vmovl_high_s16(neon_x16_1.val[1]);

        neon_x32_3.val[0] = vmovl_s16(vget_low_s16(neon_x16_1.val[2]));
        neon_x32_3.val[1] = vmovl_high_s16(neon_x16_1.val[2]);
        neon_x32_3.val[2] = vmovl_s16(vget_low_s16(neon_x16_1.val[3]));
        neon_x32_3.val[3] = vmovl_high_s16(neon_x16_1.val[3]);
        
        neon_x64_0.val[0] = vmovl_s32(vget_low_s32(neon_x32_0.val[0]));
        neon_x64_0.val[1] = vmovl_high_s32(neon_x32_0.val[0]);
        neon_x64_0.val[2] = vmovl_s32(vget_low_s32(neon_x32_0.val[1]));
        neon_x64_0.val[3] = vmovl_high_s32(neon_x32_0.val[1]);

        vfcvtx4(neon_p, neon_x64_0);
        vstorex4(&p[u], neon_p);

        neon_x64_1.val[0] = vmovl_s32(vget_low_s32(neon_x32_0.val[2]));
        neon_x64_1.val[1] = vmovl_high_s32(neon_x32_0.val[2]);
        neon_x64_1.val[2] = vmovl_s32(vget_low_s32(neon_x32_0.val[3]));
        neon_x64_1.val[3] = vmovl_high_s32(neon_x32_0.val[3]);

        vfcvtx4(neon_p, neon_x64_1);
        vstorex4(&p[u + 8], neon_p);

        neon_x64_2.val[0] = vmovl_s32(vget_low_s32(neon_x32_1.val[0]));
        neon_x64_2.val[1] = vmovl_high_s32(neon_x32_1.val[0]);
        neon_x64_2.val[2] = vmovl_s32(vget_low_s32(neon_x32_1.val[1]));
        neon_x64_2.val[3] = vmovl_high_s32(neon_x32_1.val[1]);

        vfcvtx4(neon_p, neon_x64_2);
        vstorex4(&p[u + 16], neon_p);

        neon_x64_3.val[0] = vmovl_s32(vget_low_s32(neon_x32_1.val[2]));
        neon_x64_3.val[1] = vmovl_high_s32(neon_x32_1.val[2]);
        neon_x64_3.val[2] = vmovl_s32(vget_low_s32(neon_x32_1.val[3]));
        neon_x64_3.val[3] = vmovl_high_s32(neon_x32_1.val[3]);

        vfcvtx4(neon_p, neon_x64_3);
        vstorex4(&p[u + 24], neon_p);

        neon_x64_0.val[0] = vmovl_s32(vget_low_s32(neon_x32_2.val[0]));
        neon_x64_0.val[1] = vmovl_high_s32(neon_x32_2.val[0]);
        neon_x64_0.val[2] = vmovl_s32(vget_low_s32(neon_x32_2.val[1]));
        neon_x64_0.val[3] = vmovl_high_s32(neon_x32_2.val[1]);

        vfcvtx4(neon_p, neon_x64_0);
        vstorex4(&p[u + 32], neon_p);

        neon_x64_1.val[0] = vmovl_s32(vget_low_s32(neon_x32_2.val[2]));
        neon_x64_1.val[1] = vmovl_high_s32(neon_x32_2.val[2]);
        neon_x64_1.val[2] = vmovl_s32(vget_low_s32(neon_x32_2.val[3]));
        neon_x64_1.val[3] = vmovl_high_s32(neon_x32_2.val[3]);

        vfcvtx4(neon_p, neon_x64_1);
        vstorex4(&p[u + 40], neon_p);

        neon_x64_2.val[0] = vmovl_s32(vget_low_s32(neon_x32_3.val[0]));
        neon_x64_2.val[1] = vmovl_high_s32(neon_x32_3.val[0]);
        neon_x64_2.val[2] = vmovl_s32(vget_low_s32(neon_x32_3.val[1]));
        neon_x64_2.val[3] = vmovl_high_s32(neon_x32_3.val[1]);

        vfcvtx4(neon_p, neon_x64_2);
        vstorex4(&p[u + 48], neon_p);

        neon_x64_3.val[0] = vmovl_s32(vget_low_s32(neon_x32_3.val[2]));
        neon_x64_3.val[1] = vmovl_high_s32(neon_x32_3.val[2]);
        neon_x64_3.val[2] = vmovl_s32(vget_low_s32(neon_x32_3.val[3]));
        neon_x64_3.val[3] = vmovl_high_s32(neon_x32_3.val[3]);

        vfcvtx4(neon_p, neon_x64_3);
        vstorex4(&p[u + 56], neon_p);
    }
    ZfN(FFT)(p, logn);
}

void
Zf(int16_to_fft)(fpr *p, const int16_t *x, unsigned logn)
{
	size_t u;

	u = MKN(logn);
	while (u -- > 0) {
		p[u] = fpr_of(x[u]);
	}
	ZfN(FFT)(p, logn);
}

/* see inner.h */
void ZfN(int16_to_fft)(fpr *p, const int16_t *x, unsigned logn)
{
    int32x4x4_t neon_x32_0, neon_x32_1;
    int64x2x4_t neon_x64_0, neon_x64_1, neon_x64_2, neon_x64_3;
    int16x8x4_t neon_x;
    float64x2x4_t neon_p;
    const unsigned hawk_n = 1 << logn;
    for (unsigned u = 0; u < hawk_n; u += 32)
    {
        neon_x = vld1q_s16_x4(&x[u]);

        neon_x32_0.val[0] = vmovl_s16(vget_low_s16(neon_x.val[0]));
        neon_x32_0.val[1] = vmovl_high_s16(neon_x.val[0]);
        neon_x32_0.val[2] = vmovl_s16(vget_low_s16(neon_x.val[1]));
        neon_x32_0.val[3] = vmovl_high_s16(neon_x.val[1]);

        neon_x32_1.val[0] = vmovl_s16(vget_low_s16(neon_x.val[2]));
        neon_x32_1.val[1] = vmovl_high_s16(neon_x.val[2]);
        neon_x32_1.val[2] = vmovl_s16(vget_low_s16(neon_x.val[3]));
        neon_x32_1.val[3] = vmovl_high_s16(neon_x.val[3]);
        
        neon_x64_0.val[0] = vmovl_s32(vget_low_s32(neon_x32_0.val[0]));
        neon_x64_0.val[1] = vmovl_high_s32(neon_x32_0.val[0]);
        neon_x64_0.val[2] = vmovl_s32(vget_low_s32(neon_x32_0.val[1]));
        neon_x64_0.val[3] = vmovl_high_s32(neon_x32_0.val[1]);

        vfcvtx4(neon_p, neon_x64_0);
        vstorex4(&p[u], neon_p);

        neon_x64_1.val[0] = vmovl_s32(vget_low_s32(neon_x32_0.val[2]));
        neon_x64_1.val[1] = vmovl_high_s32(neon_x32_0.val[2]);
        neon_x64_1.val[2] = vmovl_s32(vget_low_s32(neon_x32_0.val[3]));
        neon_x64_1.val[3] = vmovl_high_s32(neon_x32_0.val[3]);

        vfcvtx4(neon_p, neon_x64_1);
        vstorex4(&p[u + 8], neon_p);

        neon_x64_2.val[0] = vmovl_s32(vget_low_s32(neon_x32_1.val[0]));
        neon_x64_2.val[1] = vmovl_high_s32(neon_x32_1.val[0]);
        neon_x64_2.val[2] = vmovl_s32(vget_low_s32(neon_x32_1.val[1]));
        neon_x64_2.val[3] = vmovl_high_s32(neon_x32_1.val[1]);

        vfcvtx4(neon_p, neon_x64_2);
        vstorex4(&p[u + 16], neon_p);

        neon_x64_3.val[0] = vmovl_s32(vget_low_s32(neon_x32_1.val[2]));
        neon_x64_3.val[1] = vmovl_high_s32(neon_x32_1.val[2]);
        neon_x64_3.val[2] = vmovl_s32(vget_low_s32(neon_x32_1.val[3]));
        neon_x64_3.val[3] = vmovl_high_s32(neon_x32_1.val[3]);

        vfcvtx4(neon_p, neon_x64_3);
        vstorex4(&p[u + 24], neon_p);
    }
    ZfN(FFT)(p, logn);
}

/* see inner.h */
int
Zf(in_positive_half)(const int16_t *s, const uint8_t *h, unsigned logn)
{
	size_t n, u, v;
	uint32_t value, flag, set, result;
	uint8_t hash;

	n = MKN(logn);
	/*
	 * flag:   indicates whether a nonzero entry is seen yet,
	 * result: indicates whether the error vector e = h - 2s is valid so far,
	 * set:    indicates if the current value is nonzero.
	 */
	flag = 0;
	result = 1;

	if (logn <= 3) {
		for (u = 0; u < n; u ++) {
			value = (uint32_t)((h[0] >> u) & 1) - 2u * (uint32_t) s[u];
			set = (value | -value) >> 31;
			result &= flag | (set ^ 1u) | (-value >> 31);
			flag |= set;
		}
	} else {
		for (u = 0; u < n; ) {
			hash = *h++;
			for (v = 0; v < 8; v ++, u ++) {
				value = (uint32_t)(hash & 1u) - 2u * (uint32_t) s[u];
				/*
				 * set = (value != 0);
				 * if (flag == 0 && set == 1) {
				 *     result = (value > 0);
				 *     flag = 1;
				 * }
				 */
				set = (value | -value) >> 31;
				/*
				 * result = 0 is only possible when flag = 0, set = 1 and
				 * -value >= 0, which is equivalent to flag = 0 and value < 0.
				 */
				result &= flag | (set ^ 1u) | (-value >> 31);
				flag |= set;
				hash >>= 1;
			}
		}
	}
	/*
	 * Both flag must be set and result must still be equal to 1.
	 */
	return (int) flag & result;
}
