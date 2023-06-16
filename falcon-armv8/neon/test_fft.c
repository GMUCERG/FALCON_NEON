#include "inner.h"

#include <stdio.h>
#include "fft_consts.c"

// Compile flags:
// gcc -o test_fft fft.c test_fft.c fft_consts.c fpr.c -O0 -g3; ./test_fft

#define PRINT 55555

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
        printf("%.1f, %.1f, ", f[i], f[i + 1]);
    }
    printf("\n");
}

int cmp_double(fpr *f, fpr *g, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;

    for (int i = 0; i < n; i++)
    {
        if (fabs(f[i] - g[i]) > 0.000000001)
        {
            printf("[%d]: %.2f != %.2f \n", i, f[i], g[i]);
            printf("ERROR\n");
            return 1;
        }
    }
    return 0;
}

void fwd_FFT(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * We read the twiddle table in forward order
     */
    int level = 1;
    const fpr *fpr_tab = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10};

    fpr_tab = table[0];
    zeta_re = fpr_tab[0];
    zeta_im = fpr_tab[1];
    for (j = 0; j < hn; j += 2)
    {
        a_re = f[j];
        a_im = f[j + 1];
        b_re = f[j + hn];
        b_im = f[j + hn + 1];

        FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
        FPC_SUB(f[j + hn], f[j + hn + 1], a_re, a_im, t_re, t_im);
        FPC_ADD(f[j], f[j + 1], a_re, a_im, t_re, t_im);
    }

    for (len = hn / 2; len > 1; len >>= 1)
    {
        fpr_tab = table[level++];
        k = 0;
        for (start = 0; start < n; start = j + len)
        {
            zeta_re = fpr_tab[k];
            zeta_im = fpr_tab[k + 1];
            k += 2;

            for (j = start; j < start + len; j += 2)
            {
                a_re = f[j];
                a_im = f[j + 1];
                b_re = f[j + len];
                b_im = f[j + len + 1];

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                FPC_SUB(f[j + len], f[j + len + 1], a_re, a_im, t_re, t_im);
                FPC_ADD(f[j], f[j + 1], a_re, a_im, t_re, t_im);
            }

            start = j + len;

            for (j = start; j < start + len; j += 2)
            {
                a_re = f[j];
                a_im = f[j + 1];
                b_re = f[j + len];
                b_im = f[j + len + 1];

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                FPC_SUBJ(f[j + len], f[j + len + 1], a_re, a_im, t_re, t_im);
                FPC_ADDJ(f[j], f[j + 1], a_re, a_im, t_re, t_im);
            }
        }
    }
}

void inv_FFT(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * This time we read the table in reverse order,
     * so the pointer point to the end of the table
     */
    int level = logn - 2;
    const fpr *fpr_tab_inv = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10,
    };

    for (len = 2; len < hn; len <<= 1)
    {
        fpr_tab_inv = table[level--];
        k = 0;

        for (start = 0; start < n; start = j + len)
        {
            // Conjugate of zeta is embeded in MUL
            zeta_re = fpr_tab_inv[k];
            zeta_im = fpr_tab_inv[k + 1];
            k += 2;

            for (j = start; j < start + len; j += 2)
            {
                a_re = f[j];
                a_im = f[j + 1];
                b_re = f[j + len];
                b_im = f[j + len + 1];

                FPC_ADD(f[j], f[j + 1], a_re, a_im, b_re, b_im);
                FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
                FPC_MUL_CONJ(f[j + len], f[j + len + 1], t_re, t_im, zeta_re, zeta_im);
            }

            start = j + len;

            for (j = start; j < start + len; j += 2)
            {
                a_re = f[j];
                a_im = f[j + 1];
                b_re = f[j + len];
                b_im = f[j + len + 1];

                /*
                 * Notice we swap the (a - b) to (b - a) in FPC_SUB
                 */
                FPC_ADD(f[j], f[j + 1], a_re, a_im, b_re, b_im);
                FPC_SUB(t_re, t_im, b_re, b_im, a_re, a_im);
                FPC_MUL_CONJ_J_m(f[j + len], f[j + len + 1], t_re, t_im, zeta_re, zeta_im);
            }
        }
    }

    fpr_tab_inv = table[0];
    zeta_re = fpr_tab_inv[0] * fpr_p2_tab[logn];
    zeta_im = fpr_tab_inv[1] * fpr_p2_tab[logn];

    for (j = 0; j < hn; j += 2)
    {
        a_re = f[j];
        a_im = f[j + 1];
        b_re = f[j + hn];
        b_im = f[j + hn + 1];

        FPC_ADD(f[j], f[j + 1], a_re, a_im, b_re, b_im);
        FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
        FPC_MUL_CONJ(f[j + hn], f[j + hn + 1], t_re, t_im, zeta_re, zeta_im);

        f[j] *= fpr_p2_tab[logn];
        f[j + 1] *= fpr_p2_tab[logn];
    }
}


void split_fwd_FFT(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    const unsigned ht = n >> 2;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * We read the twiddle table in forward order
     */
    int level = 1;
    const fpr *fpr_tab = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10};

    fpr_tab = table[0];
    zeta_re = fpr_tab[0];
    zeta_im = fpr_tab[1];

    for (j = 0; j < ht; j += 1)
    {
        a_re = f[j];
        a_im = f[j + hn];
        b_re = f[j + ht];
        b_im = f[j + ht + hn];

        if (logn == PRINT)
        {
            // printf("(%4d, %4d) * (%4d, %4d)\n", j + ht, j + ht + hn, 
            //             0, 1);
            // printf("(%4d, %4d) = (%4d, %4d) - @\n", j + ht, j + ht + hn, j, j + hn);
            // printf("(%4d, %4d) = (%4d, %4d) + @\n", j, j + hn, j, j + hn);
        }

        FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
        // if (logn == PRINT) printf("t_re = %.2f, t_im = %.2f\n", t_re, t_im);
        FPC_SUB(f[j + ht], f[j + ht + hn], a_re, a_im, t_re, t_im);
        FPC_ADD(f[j], f[j + hn], a_re, a_im, t_re, t_im);
    }
    // if (logn == PRINT) print_double(f, logn, "1st loop");

    for (len = ht / 2; len > 0; len >>= 1)
    {
        fpr_tab = table[level++];
        k = 0;
        // if (logn == PRINT) printf("level = %d\n", level + 1);
        for (start = 0; start < hn; start = j + len)
        {
            zeta_re = fpr_tab[k];
            zeta_im = fpr_tab[k + 1];
            k += 2;
            // if (logn == PRINT) printf("---\n");
            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                if (level < 6)
                if (logn == PRINT)
                {
                    // printf("(%4d, %4d) * (%4d, %4d)\n", j + len, j + len + hn, 
                    //             k - 2, k - 1);
                    // printf("(%4d, %4d) = (%4d, %4d) - @\n", j + len, j + len + hn, j, j + hn);
                    // printf("(%4d, %4d) = (%4d, %4d) + @\n", j, j + hn, j, j + hn);
                }

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                // if (level < 6) if (logn == PRINT) printf("t_re = %.2f, t_im = %.2f\n", t_re, t_im);
                FPC_SUB(f[j + len], f[j + len + hn], a_re, a_im, t_re, t_im);
                FPC_ADD(f[j], f[j + hn], a_re, a_im, t_re, t_im);
            }

            start = j + len;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];
                
                if (level < 6)
                if (logn == PRINT)
                {
                    // printf("(%4d, %4d) * (%4d, %4d)\n", j + len, j + len + hn, 
                    //             k - 2, k - 1);
                    // printf("(%4d, %4d) = (%4d, %4d) - j@\n", j + len, j + len + hn, j, j + hn);
                    // printf("(%4d, %4d) = (%4d, %4d) + j@\n", j, j + hn, j, j + hn);
                }

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                // if (level < 6) if (logn == PRINT) printf("t_re = %.2f, t_im = %.2f\n", t_re, t_im);
                FPC_SUBJ(f[j + len], f[j + len + hn], a_re, a_im, t_re, t_im);
                FPC_ADDJ(f[j], f[j + hn], a_re, a_im, t_re, t_im);
            }
        }

        // if (level < 6) if (logn == PRINT) print_double(f, logn, "nth loop");
    }
}


void split_fwd_FFT_v0(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    const unsigned ht = n >> 2;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * We read the twiddle table in forward order
     */
    int level = 0;
    const fpr *fpr_tab = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10};

    for (len = ht; len > 0; len >>= 1)
    {
        fpr_tab = table[level++];
        k = 0;
        for (start = 0; start < hn; start = j + len)
        {
            zeta_re = fpr_tab[k];
            zeta_im = fpr_tab[k + 1];
            k += 2;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                FPC_SUB(f[j + len], f[j + len + hn], a_re, a_im, t_re, t_im);
                FPC_ADD(f[j], f[j + hn], a_re, a_im, t_re, t_im);
            }

            start = j + len;
            if (start >= hn) break;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                FPC_SUBJ(f[j + len], f[j + len + hn], a_re, a_im, t_re, t_im);
                FPC_ADDJ(f[j], f[j + hn], a_re, a_im, t_re, t_im);
            }
        }
    }
}

void split_inv_FFT(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    const unsigned ht = n >> 2;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * This time we read the table in reverse order,
     * so the pointer point to the end of the table
     */
    int level = logn - 2;
    const fpr *fpr_tab_inv = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10,
    };

    for (len = 1; len < ht; len <<= 1)
    {
        fpr_tab_inv = table[level--];
        k = 0;
        if (logn == PRINT) printf("level = %d\n", level + 1);
        for (start = 0; start < hn; start = j + len)
        {
            // Conjugate of zeta is embeded in MUL
            zeta_re = fpr_tab_inv[k];
            zeta_im = fpr_tab_inv[k + 1];
            k += 2;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                if (logn == PRINT)
                {
                    printf("(%4d, %4d) - (%4d, %4d)\n", j, j + hn, j + len, j + len + hn);
                    printf("(%4d, %4d) + (%4d, %4d)\n", j, j + hn, j + len, j + len + hn);
                    printf("(%4d, %4d) = @ * (%4d, %4d)\n",  j + len, j + len + hn, k - 2, k - 1);
                }

                FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
                FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
                if (logn == PRINT) printf("t_re = %.2f, t_im = %.2f\n", t_re, t_im);
                FPC_MUL_CONJ(f[j + len], f[j + len + hn], t_re, t_im, zeta_re, zeta_im);
            }

            start = j + len;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                if (logn == PRINT)
                {
                    printf("(%4d, %4d) - (%4d, %4d)\n", j, j + hn, j + len, j + len + hn);
                    printf("(%4d, %4d) + (%4d, %4d)\n", j, j + hn, j + len, j + len + hn);
                    printf("(%4d, %4d) = j@ * (%4d, %4d)\n",  j + len, j + len + hn, k - 2, k - 1);
                }

                /*
                 * Notice we swap the (a - b) to (b - a) in FPC_SUB
                 */
                FPC_SUB(t_re, t_im, b_re, b_im, a_re, a_im);
                FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
                if (logn == PRINT) printf("t_re = %.2f, t_im = %.2f\n", t_re, t_im);
                FPC_MUL_CONJ_J_m(f[j + len], f[j + len + hn], t_re, t_im, zeta_re, zeta_im);
            }
        }
        if (logn == PRINT) print_double(f, logn, "nth");
    }


    fpr_tab_inv = table[0];
    zeta_re = fpr_tab_inv[0] * fpr_p2_tab[logn];
    zeta_im = fpr_tab_inv[1] * fpr_p2_tab[logn];
    if (logn == PRINT) printf("level = %d\n", level);
    for (j = 0; j < ht; j += 1)
    {
        a_re = f[j];
        a_im = f[j + hn];
        b_re = f[j + ht];
        b_im = f[j + ht + hn];

        if (logn == PRINT)
        {
            printf("(%4d, %4d) - (%4d, %4d)\n", j, j + hn, j + len, j + len + hn);
            printf("(%4d, %4d) + (%4d, %4d)\n", j, j + hn, j + len, j + len + hn);
            printf("(%4d, %4d) = @ * (%4d, %4d)\n",  j + len, j + len + hn, k - 2, k - 1);
        }

        FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
        FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
        if (logn == PRINT) printf("t_re = %.2f, t_im = %.2f\n", t_re, t_im);
        FPC_MUL_CONJ(f[j + ht], f[j + ht + hn], t_re, t_im, zeta_re, zeta_im);

        f[j] *= fpr_p2_tab[logn];
        f[j + hn] *= fpr_p2_tab[logn];
    }
    if (logn == PRINT) print_double(f, logn, "1st");
}


void split_inv_FFT_v0(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    const unsigned ht = n >> 2;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * This time we read the table in reverse order,
     * so the pointer point to the end of the table
     */
    int level = logn - 2;
    const fpr *fpr_tab_inv = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10,
    };

    for (len = 1; len < hn; len <<= 1)
    {
        fpr_tab_inv = table[level--];
        k = 0;

        for (start = 0; start < hn; start = j + len)
        {
            // Conjugate of zeta is embeded in MUL
            zeta_re = fpr_tab_inv[k];
            zeta_im = fpr_tab_inv[k + 1];
            k += 2;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
                FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
                FPC_MUL_CONJ(f[j + len], f[j + len + hn], t_re, t_im, zeta_re, zeta_im);
            }

            start = j + len;
            if (start >= hn) break;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                /*
                 * Notice we swap the (a - b) to (b - a) in FPC_SUB
                 */
                FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
                FPC_SUB(t_re, t_im, b_re, b_im, a_re, a_im);
                FPC_MUL_CONJ_J_m(f[j + len], f[j + len + hn], t_re, t_im, zeta_re, zeta_im);
            }
        }
    }

    for (j = 0; j < hn; j += 1)
    {
        f[j] *= fpr_p2_tab[logn];
        f[j + hn] *= fpr_p2_tab[logn];
    }
}


void my_split_fft(fpr *f0, fpr *f1, fpr *f, const unsigned logn)
{
    const unsigned n = 1 << logn; 
    const unsigned hn = n >> 1; 
    const unsigned ht = n >> 2; 

    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10,
    };

    const fpr *fpr_split = table[logn - 2];
    unsigned k = 0;


    f0[0] = f[0];
    f1[0] = f[hn];

    fpr a_re, a_im, b_re, b_im, t_re, t_im, v_re, v_im, s_re, s_im;
    for (unsigned j = 0; j < ht; j+=1)
    {
        unsigned j2 = j << 1; 
        a_re = f[j2];
        b_re = f[j2 + 1];
        a_im = f[j2 + hn];
        b_im = f[j2 + 1 + hn];

        FPC_ADD(v_re, v_im, a_re, a_im, b_re, b_im);
        f0[j] = v_re * 0.5; 
        f0[j + ht] = v_im * 0.5; 

        s_re = fpr_split[k++] * 0.5;
        s_im = fpr_split[k++] * 0.5;

        if (logn == PRINT)
        {
            // printf("f0: (%4d, %4d) = (%4d, %4d) + (%4d, %4d)\n", j, j + ht, j2, j2 + hn, j2 + 1, j2 + 1 + hn);
            // printf("@ = (%4d, %4d) - (%4d, %4d)\n", j2, j2 + hn, j2 + 1, j2 + 1 + hn);
            // printf("f1: (%4d, %4d) = @ * (%4d, %4d)\n",  j, j + ht, j2 + n, j2 + n + 1);
        }

        FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
        // printf("a_re, a_im, b_re, b_im = %.2f, %.2f, %.2f, %.2f\n", a_re, a_im, b_re, b_im);
        // printf("t_re, t_im = %.2f, %.2f, %.2f, %.2f, %d\n", t_re, t_im, s_re, s_im, ht);
        FPC_MUL_CONJ(f1[j], f1[j + ht], t_re, t_im, s_re, s_im);
        
        // ===========
        j += 1; 
        j2 = j << 1; 

        if (j >= ht) 
        {
            // printf("break %d\n", logn);
            break;
        }

        a_re = f[j2];
        b_re = f[j2 + 1];
        a_im = f[j2 + hn];
        b_im = f[j2 + 1 + hn];

        FPC_ADD(v_re, v_im, a_re, a_im, b_re, b_im);
        f0[j] = v_re * 0.5; 
        f0[j + ht] = v_im * 0.5; 

        if (logn == PRINT)
        {
            // printf("f0: (%4d, %4d) = (%4d, %4d) + (%4d, %4d)\n", j, j + ht, j2, j2 + hn, j2 + 1, j2 + 1 + hn);
            // printf("@ = (%4d, %4d) - (%4d, %4d)\n", j2, j2 + hn, j2 + 1, j2 + 1 + hn);
            // printf("f1: (%4d, %4d) = j@ * (%4d, %4d)\n",  j, j + ht, j2 + n, j2 + n + 1);
        }

        /*
        * Notice we swap the (a - b) to (b - a) in FPC_SUB
        */
        FPC_SUB(t_re, t_im, b_re, b_im, a_re, a_im);
        FPC_MUL_CONJ_J_m(f1[j], f1[j + ht], t_re, t_im, s_re, s_im);

        if (logn == PRINT) printf("====%d, %d\n", j, j2);
    }
}



void my_merge_fft(fpr *f, const fpr *f0, const fpr *f1, const unsigned logn)
{
    const unsigned n = 1 << logn; 
    const unsigned hn = n >> 1; 
    const unsigned ht = n >> 2; 

    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10,
    };

    const fpr *fpr_merge = table[logn - 2];
    unsigned k = 0, j2;

    fpr a_re, a_im, b_re, b_im, t_re, t_im, v_re, v_im, s_re, s_im;

    for (unsigned j = 0; j < ht; j+= 1)
    {
        j2 = j << 1;

        a_re = f0[j];
        a_im = f0[j + ht];
        
        b_re = f1[j];
        b_im = f1[j + ht];

        s_re = fpr_merge[k++];
        s_im = fpr_merge[k++];

        if (logn == PRINT)
        {
            printf("f1(%4d, %4d) * (%4d, %4d)\n", j, j + ht, k - 2, k - 1);
            printf("f(%4d, %4d) = f0(%4d, %4d) + @\n", j2, j2 + hn, j, j + ht);
            printf("f(%4d, %4d) = f0(%4d, %4d) - @\n", j2 + 1, j2 + 1+ hn, j, j + ht);
        }

        FPC_MUL(t_re, t_im, b_re, b_im, s_re, s_im);
        FPC_ADD(f[j2], f[j2 + hn], a_re, a_im, t_re, t_im);
        FPC_SUB(f[j2 + 1], f[j2 + 1 + hn], a_re, a_im, t_re, t_im);

        j += 1; 
        j2 = j << 1; 

        if (j >= ht) break; 

        a_re = f0[j];
        a_im = f0[j + ht];
        
        b_re = f1[j];
        b_im = f1[j + ht];

        if (logn == PRINT)
        {
            printf("===\n");
            printf("f1(%4d, %4d) * (%4d, %4d)\n", j, j + ht, k - 2, k - 1);
            printf("f(%4d, %4d) = f0(%4d, %4d) + j@\n", j2, j2 + hn, j, j + ht);
            printf("f(%4d, %4d) = f0(%4d, %4d) - j@\n", j2 + 1, j2 + 1+ hn, j, j + ht);
        }

        FPC_MUL(t_re, t_im, b_re, b_im, s_re, s_im);
        FPC_ADDJ(f[j2], f[j2 + hn], a_re, a_im, t_re, t_im);
        FPC_SUBJ(f[j2 + 1], f[j2 + 1 + hn], a_re, a_im, t_re, t_im);
    }
}

int test_fft_ifft(unsigned logn, unsigned tests)
{
    fpr f[1024], g[1024], tmp[1024];
    for (int j = 0; j < tests; j++)
    {
        for (int i = 0; i < 1024; i++)
        {
            f[i] = drand(-12289.0, 12289);
        }
        combine(g, f, logn);

        ZfN(FFT)(f, logn);
        ZfN(iFFT)(f, logn);

        fwd_FFT(g, logn);
        inv_FFT(g, logn);
        split(tmp, g, logn);

        // print_double(f, logn, "f");
        // print_double(tmp, logn, "g");

        if (cmp_double(f, tmp, logn))
        {
            return 1;
        }
    }
    return 0;
}


int test_variant_fft(unsigned logn, unsigned tests)
{
    fpr f[1024], g[1024];
    for (int j = 0; j < tests; j++)
    {
        for (int i = 0; i < 1024; i++)
        {
            f[i] = drand(-12289.0, 12289);
            g[i] = f[i];
        }

        split_fwd_FFT(f, logn);
        split_fwd_FFT_v0(g, logn);

        split_inv_FFT(f, logn);
        split_inv_FFT_v0(g, logn);

        if (cmp_double(f, g, logn))
        {
            return 1;
        }
    }
    return 0;
}

int test_split_fft_ifft(unsigned logn, unsigned tests)
{
    fpr f[1024], g[1024];
    for (int j = 0; j < tests; j++)
    {
        for (int i = 0; i < 1024; i++)
        {
            f[i] = drand(-12289.0, 12289);
            g[i] = f[i];
        }
        split_fwd_FFT(g, logn);
        split_inv_FFT(g, logn);

        ZfN(FFT)(f, logn);
        ZfN(iFFT)(f, logn);


        // print_double(f, logn, "f");
        // print_double(g, logn, "g");

        if (cmp_double(f, g, logn))
        {
            return 1;
        }
    }
    return 0;
}


int test_split_merge_function(unsigned logn, unsigned tests)
{
    fpr f[1024] = {0}, f0[1024] = {0}, f1[1024] = {0};
    fpr g[1024] = {0}, g0[1024] = {0}, g1[1024] = {0};
    const unsigned n = 1 << logn;
    for (int j = 0; j < tests; j++)
    {
        for (int i = 0; i < n; i++)
        {
            f[i] = drand(-12289.0, 12289);
        }
        ZfN(poly_split_fft)(f0, f1, f, logn);
        my_split_fft(g0, g1, f, logn);

        if (cmp_double(g0, f0, logn))
        {
            print_double(f0, logn - 1, "f0");
            print_double(g0, logn - 1, "g0");
            printf("f0\n");
            return 1; 
        }
        if (cmp_double(g1, f1, logn))
        {
            print_double(f1, logn - 1, "f1");
            print_double(g1, logn - 1, "g1");
            printf("f1\n");
            return 1;
        }

        ZfN(poly_merge_fft)(f, f0, f1, logn);
        my_merge_fft(g, g0, g1, logn);

        if (cmp_double(f, g, logn))
        {
            print_double(f, logn, "f");
            print_double(g, logn, "g");
            printf("f != g\n");
            return 1;
        }
    }

    return 0; 
}

#define TESTS 10000

int main(void)
{
    printf("\ntest_fft_ifft: ");
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_fft_ifft(logn, TESTS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }
    printf("OK\n");

    printf("\ntest_variant_fft: ");
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_variant_fft(logn, TESTS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }
    printf("OK\n");

    printf("\ntest_split_fft_ifft: \n");
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_split_fft_ifft(logn, TESTS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }
    printf("OK\n");

    printf("\ntest_split_merge_function: \n");
    for (int logn = 2; logn < 11; logn++)
    {
        if (test_split_merge_function(logn, TESTS))
        {
            printf("Error at LOGN = %d\n", logn);
            return 1;
        }
    }
    printf("OK\n");
    
    return 0;
}
