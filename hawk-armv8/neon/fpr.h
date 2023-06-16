/*
 * Floating-point operations.
 *
 * =============================================================================
 * Copyright (c) 2022 by Cryptographic Engineering Research Group (CERG)
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
 * 
 * 
 * THIS COPYRIGHT CAN BE DELETED FOR THE SAKE OF READABILITY
 * THIS IS A DEMONSTRATION HOW ANNOYING STACKED HEADER CAN BE FOR SUCH TRIVIAL PIECE OF CODE.
 */

/*
 * Floating-point operations.
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


/* ====================================================================== */

#include <math.h>

/*
 * We wrap the native 'double' type into a structure so that the C compiler
 * complains if we inadvertently use raw arithmetic operators on the 'fpr'
 * type instead of using the inline functions below. This should have no
 * extra runtime cost, since all the functions below are 'inline'.
 */
typedef double fpr;

static inline fpr
FPR(double v)
{
	fpr x;

	x = v;
	return x;
}

static inline fpr
fpr_of(int64_t i)
{
	return (double)i;
}

static const fpr fpr_zero = 0.0 ;
static const fpr fpr_one = 1.0 ;
static const fpr fpr_two = 2.0 ;
static const fpr fpr_onehalf =  0.5 ;
static const fpr fpr_ptwo31  =  2147483648.0 ;
static const fpr fpr_ptwo31m1 =  2147483647.0 ;
static const fpr fpr_mtwo31m1 =  -2147483647.0 ;
static const fpr fpr_ptwo63m1 =  9223372036854775807.0 ;
static const fpr fpr_mtwo63m1 =  -9223372036854775807.0 ;
static const fpr fpr_ptwo63 =  9223372036854775808.0 ;
static const fpr fpr_almost_one =  0.98 ;

static inline int64_t
fpr_rint(fpr x)
{
    int64_t t;
    __asm__ ( "fcvtns   %x0, %d1": "=r" (t) : "w" (x));
    return t;
}

static inline int64_t
fpr_floor(fpr x)
{
	int64_t r;

	/*
	 * The cast performs a trunc() (rounding toward 0) and thus is
	 * wrong by 1 for most negative values. The correction below is
	 * constant-time as long as the compiler turns the
	 * floating-point conversion result into a 0/1 integer without a
	 * conditional branch or another non-constant-time construction.
	 * This should hold on all modern architectures with an FPU (and
	 * if it is false on a given arch, then chances are that the FPU
	 * itself is not constant-time, making the point moot).
	 */
	r = (int64_t)x;
	return r - (x < (double)r);
}

static inline int64_t
fpr_trunc(fpr x)
{
	return (int64_t)x;
}

static inline fpr
fpr_add(fpr x, fpr y)
{
	return (x + y);
}

static inline fpr
fpr_sub(fpr x, fpr y)
{
	return (x - y);
}

static inline fpr
fpr_neg(fpr x)
{
	return (-x);
}

static inline fpr
fpr_half(fpr x)
{
	return (x * 0.5);
}

static inline fpr
fpr_double(fpr x)
{
	return (x + x);
}

static inline fpr
fpr_mul(fpr x, fpr y)
{
	return (x * y);
}

static inline fpr
fpr_sqr(fpr x)
{
	return (x * x);
}

static inline fpr
fpr_inv(fpr x)
{
	return (1.0 / x);
}

static inline fpr
fpr_div(fpr x, fpr y)
{
	return (x / y);
}

static inline int
fpr_lt(fpr x, fpr y)
{
	return x < y;
}

#define fpr_p2_tab   Zf(fpr_p2_tab)
extern const fpr fpr_p2_tab[];

#define fpr_tab_log2   Zf(fpr_tab_log2)
#define fpr_tab_log3   Zf(fpr_tab_log3)
#define fpr_tab_log4   Zf(fpr_tab_log4)
#define fpr_tab_log5   Zf(fpr_tab_log5)
#define fpr_tab_log6   Zf(fpr_tab_log6)
#define fpr_tab_log7   Zf(fpr_tab_log7)
#define fpr_tab_log8   Zf(fpr_tab_log8)
#define fpr_tab_log9   Zf(fpr_tab_log9)
#define fpr_tab_log10  Zf(fpr_tab_log10)
#define fpr_table      Zf(fpr_table)

extern const fpr fpr_tab_log2[];
extern const fpr fpr_tab_log3[];
extern const fpr fpr_tab_log4[];
extern const fpr fpr_tab_log5[];
extern const fpr fpr_tab_log6[];
extern const fpr fpr_tab_log7[];
extern const fpr fpr_tab_log8[];
extern const fpr fpr_tab_log9[];
extern const fpr fpr_tab_log10[];
extern const fpr *fpr_table[];

/* ====================================================================== */

