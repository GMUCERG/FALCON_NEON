# NEON M1 

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |       77 |       81
| FFT 1 |       77 |       81
| FFT 2 |       79 |       83
| FFT 3 |       87 |       88
| FFT 4 |      110 |      105
| FFT 5 |      147 |      148
| FFT 6 |      242 |      234
| FFT 7 |      439 |      426
| FFT 8 |      851 |      851
| FFT 9 |     1752 |     1762
| FFT 10 |     3842 |     3890

| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |      847 |      811
| NTT 10 |     1699 |     1701

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_add |        0 |       78
| poly_add |        1 |       75
| poly_add |        2 |       76
| poly_add |        3 |       78
| poly_add |        4 |       81
| poly_add |        5 |       89
| poly_add |        6 |      101
| poly_add |        7 |      133
| poly_add |        8 |      261
| poly_add |        9 |      371
| poly_add |       10 |      604

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_sub |        0 |       78
| poly_sub |        1 |       75
| poly_sub |        2 |       76
| poly_sub |        3 |       78
| poly_sub |        4 |       81
| poly_sub |        5 |       89
| poly_sub |        6 |      101
| poly_sub |        7 |      134
| poly_sub |        8 |      261
| poly_sub |        9 |      372
| poly_sub |       10 |      618

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_neg |        0 |       76
| poly_neg |        1 |       75
| poly_neg |        2 |       75
| poly_neg |        3 |       76
| poly_neg |        4 |       78
| poly_neg |        5 |       83
| poly_neg |        6 |       91
| poly_neg |        7 |      113
| poly_neg |        8 |      248
| poly_neg |        9 |      361
| poly_neg |       10 |      594

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_adj_fft |        0 |       77
| poly_adj_fft |        1 |       74
| poly_adj_fft |        2 |       75
| poly_adj_fft |        3 |       75
| poly_adj_fft |        4 |       77
| poly_adj_fft |        5 |       84
| poly_adj_fft |        6 |       84
| poly_adj_fft |        7 |       93
| poly_adj_fft |        8 |      188
| poly_adj_fft |        9 |      163
| poly_adj_fft |       10 |      307

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_fft |        0 |       76
| poly_mul_fft |        1 |       77
| poly_mul_fft |        2 |       75
| poly_mul_fft |        3 |       80
| poly_mul_fft |        4 |       87
| poly_mul_fft |        5 |       97
| poly_mul_fft |        6 |      123
| poly_mul_fft |        7 |      173
| poly_mul_fft |        8 |      297
| poly_mul_fft |        9 |      452
| poly_mul_fft |       10 |      735

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_invnorm2_fft |        0 |       77
| poly_invnorm2_fft |        1 |       78
| poly_invnorm2_fft |        2 |       80
| poly_invnorm2_fft |        3 |       83
| poly_invnorm2_fft |        4 |       87
| poly_invnorm2_fft |        5 |      102
| poly_invnorm2_fft |        6 |      136
| poly_invnorm2_fft |        7 |      189
| poly_invnorm2_fft |        8 |      308
| poly_invnorm2_fft |        9 |      496
| poly_invnorm2_fft |       10 |      828

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_autoadj_fft |        0 |       77
| poly_mul_autoadj_fft |        1 |       76
| poly_mul_autoadj_fft |        2 |       77
| poly_mul_autoadj_fft |        3 |       79
| poly_mul_autoadj_fft |        4 |       84
| poly_mul_autoadj_fft |        5 |       87
| poly_mul_autoadj_fft |        6 |       99
| poly_mul_autoadj_fft |        7 |      128
| poly_mul_autoadj_fft |        8 |      263
| poly_mul_autoadj_fft |        9 |      402
| poly_mul_autoadj_fft |       10 |      723

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDL_fft |        0 |       76
| poly_LDL_fft |        1 |       94
| poly_LDL_fft |        2 |       91
| poly_LDL_fft |        3 |       94
| poly_LDL_fft |        4 |      102
| poly_LDL_fft |        5 |      136
| poly_LDL_fft |        6 |      198
| poly_LDL_fft |        7 |      293
| poly_LDL_fft |        8 |      568
| poly_LDL_fft |        9 |      923
| poly_LDL_fft |       10 |     1699

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDLmv_fft |        0 |       76
| poly_LDLmv_fft |        1 |       93
| poly_LDLmv_fft |        2 |       91
| poly_LDLmv_fft |        3 |       94
| poly_LDLmv_fft |        4 |      110
| poly_LDLmv_fft |        5 |      141
| poly_LDLmv_fft |        6 |      205
| poly_LDLmv_fft |        7 |      312
| poly_LDLmv_fft |        8 |      560
| poly_LDLmv_fft |        9 |      989
| poly_LDLmv_fft |       10 |     1845

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_split_fft |        0 |       77
| poly_split_fft |        1 |       74
| poly_split_fft |        2 |       77
| poly_split_fft |        3 |       80
| poly_split_fft |        4 |       90
| poly_split_fft |        5 |      103
| poly_split_fft |        6 |      139
| poly_split_fft |        7 |      197
| poly_split_fft |        8 |      304
| poly_split_fft |        9 |      514
| poly_split_fft |       10 |      935

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_merge_fft |        0 |       77
| poly_merge_fft |        1 |       74
| poly_merge_fft |        2 |       77
| poly_merge_fft |        3 |       79
| poly_merge_fft |        4 |       89
| poly_merge_fft |        5 |      102
| poly_merge_fft |        6 |      134
| poly_merge_fft |        7 |      191
| poly_merge_fft |        8 |      289
| poly_merge_fft |        9 |      488
| poly_merge_fft |       10 |      872


| Function | logn | cycles |
|:-------------|----------:|-----------:|
| compute_bnorm |        9 |      471
| compute_bnorm |       10 |      866

|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 15594.11 |    46.85 |   448.46 |   493.00 |   364.29 |   407.76 |    22.06 |    67.49 |
|1024: | 48497.19 |   100.32 |   897.02 |   982.62 |   718.97 |   805.77 |    42.05 |   135.11 |

|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: |  4872.92 |    16.00 |   141.54 |   155.50 |   115.25 |   128.92 |     7.96 |    22.17 |
|1024: | 15237.83 |    33.21 |   284.04 |   309.29 |   228.88 |   255.21 |    14.25 |    43.29 |

|degree|  kg(Ghz)|   ek(Ghz)|   sd(Ghz)|  sdc(Ghz)|   st(Ghz)|  stc(Ghz)|   vv(Ghz)|  vvc(Ghz)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
|  512:|   3.06 |   3.10 |   3.07 |   3.08 |   3.06 |   3.13 |   3.16 |      3.15 |
| 1024:|   3.14 |   3.08 |   3.13 |   3.14 |   3.14 |   3.14 |   3.15 |      3.15 |

## Benchmark 59 bytes message

### N = 512

mlen, smlen = 59, 715
| Median   | sign | verify |
|  --  | --:  | ---: |
| kc |   459.19 |    21.16 |
| us |   144.17 |     6.58 |
| Ghz|     3.19 |     3.21 |

| Average | sign | verify |
|  --  | --:  | ---: |
| kc |   459.44 |    21.17 |
| us |   147.12 |     6.66 |
| Ghz|     3.12 |     3.18 |


### N = 1024

mlen, smlen = 59, 1332
| Median   | sign | verify |
|  --   | --:  | ---: |
| kc |   914.91 |    42.20 |
| us |   288.25 |    13.42 |
| Ghz|     3.17 |     3.15 |

| Average | sign | verify |
|  --  | --:  | ---: |
| kc |   914.78 |    42.20 |
| us |   289.64 |    13.51 |
| Ghz|     3.16 |     3.12 |
