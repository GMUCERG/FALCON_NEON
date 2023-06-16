# NEON A72

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |        9 |       12
| FFT 1 |        9 |       12
| FFT 2 |       17 |       20
| FFT 3 |       50 |       49
| FFT 4 |       94 |       97
| FFT 5 |      228 |      230
| FFT 6 |      566 |      574
| FFT 7 |     1282 |     1338
| FFT 8 |     3105 |     3192
| FFT 9 |     6609 |     6997
| FFT 10 |    15503 |    16200

| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |     3656 |     3569
| NTT 10 |     7662 |     7848

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_add |        0 |       18
| poly_add |        1 |        9
| poly_add |        2 |        9
| poly_add |        3 |       18
| poly_add |        4 |       35
| poly_add |        5 |       65
| poly_add |        6 |      125
| poly_add |        7 |      245
| poly_add |        8 |      485
| poly_add |        9 |      985
| poly_add |       10 |     1945

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_sub |        0 |       18
| poly_sub |        1 |        9
| poly_sub |        2 |        9
| poly_sub |        3 |       18
| poly_sub |        4 |       35
| poly_sub |        5 |       65
| poly_sub |        6 |      125
| poly_sub |        7 |      245
| poly_sub |        8 |      485
| poly_sub |        9 |      985
| poly_sub |       10 |     1945

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_neg |        0 |       15
| poly_neg |        1 |        9
| poly_neg |        2 |        9
| poly_neg |        3 |       15
| poly_neg |        4 |       27
| poly_neg |        5 |       51
| poly_neg |        6 |       99
| poly_neg |        7 |      195
| poly_neg |        8 |      387
| poly_neg |        9 |      793
| poly_neg |       10 |     1561

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_adj_fft |        0 |       17
| poly_adj_fft |        1 |        9
| poly_adj_fft |        2 |        9
| poly_adj_fft |        3 |        9
| poly_adj_fft |        4 |       17
| poly_adj_fft |        5 |       29
| poly_adj_fft |        6 |       53
| poly_adj_fft |        7 |      101
| poly_adj_fft |        8 |      197
| poly_adj_fft |        9 |      410
| poly_adj_fft |       10 |      794

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_fft |        0 |       11
| poly_mul_fft |        1 |       12
| poly_mul_fft |        2 |       13
| poly_mul_fft |        3 |       25
| poly_mul_fft |        4 |       57
| poly_mul_fft |        5 |      101
| poly_mul_fft |        6 |      189
| poly_mul_fft |        7 |      365
| poly_mul_fft |        8 |      742
| poly_mul_fft |        9 |     1461
| poly_mul_fft |       10 |     2867

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_invnorm2_fft |        0 |       10
| poly_invnorm2_fft |        1 |       10
| poly_invnorm2_fft |        2 |       19
| poly_invnorm2_fft |        3 |       55
| poly_invnorm2_fft |        4 |      133
| poly_invnorm2_fft |        5 |      261
| poly_invnorm2_fft |        6 |      517
| poly_invnorm2_fft |        7 |     1029
| poly_invnorm2_fft |        8 |     2053
| poly_invnorm2_fft |        9 |     4101
| poly_invnorm2_fft |       10 |     8197

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_autoadj_fft |        0 |       10
| poly_mul_autoadj_fft |        1 |       10
| poly_mul_autoadj_fft |        2 |        9
| poly_mul_autoadj_fft |        3 |       13
| poly_mul_autoadj_fft |        4 |       31
| poly_mul_autoadj_fft |        5 |       57
| poly_mul_autoadj_fft |        6 |      109
| poly_mul_autoadj_fft |        7 |      213
| poly_mul_autoadj_fft |        8 |      421
| poly_mul_autoadj_fft |        9 |      837
| poly_mul_autoadj_fft |       10 |     1690

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDL_fft |        0 |       11
| poly_LDL_fft |        1 |       30
| poly_LDL_fft |        2 |       45
| poly_LDL_fft |        3 |       86
| poly_LDL_fft |        4 |      223
| poly_LDL_fft |        5 |      446
| poly_LDL_fft |        6 |      892
| poly_LDL_fft |        7 |     1784
| poly_LDL_fft |        8 |     3591
| poly_LDL_fft |        9 |     7181
| poly_LDL_fft |       10 |    14554

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDLmv_fft |        0 |       12
| poly_LDLmv_fft |        1 |       30
| poly_LDLmv_fft |        2 |       47
| poly_LDLmv_fft |        3 |       88
| poly_LDLmv_fft |        4 |      201
| poly_LDLmv_fft |        5 |      399
| poly_LDLmv_fft |        6 |      795
| poly_LDLmv_fft |        7 |     1587
| poly_LDLmv_fft |        8 |     3204
| poly_LDLmv_fft |        9 |     6398
| poly_LDLmv_fft |       10 |    12895

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_split_fft |        0 |       10
| poly_split_fft |        1 |        9
| poly_split_fft |        2 |       12
| poly_split_fft |        3 |       23
| poly_split_fft |        4 |       51
| poly_split_fft |        5 |       89
| poly_split_fft |        6 |      163
| poly_split_fft |        7 |      311
| poly_split_fft |        8 |      607
| poly_split_fft |        9 |     1201
| poly_split_fft |       10 |     2405

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_merge_fft |        0 |       11
| poly_merge_fft |        1 |        9
| poly_merge_fft |        2 |       11
| poly_merge_fft |        3 |       21
| poly_merge_fft |        4 |       48
| poly_merge_fft |        5 |       85
| poly_merge_fft |        6 |      159
| poly_merge_fft |        7 |      307
| poly_merge_fft |        8 |      603
| poly_merge_fft |        9 |     1197
| poly_merge_fft |       10 |     2402

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| compute_bnorm |        9 |     1324
| compute_bnorm |       10 |     2675

|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 33267.27 |   201.92 |  1027.88 |  1108.51 |   736.85 |   819.06 |    62.12 |   138.72 |
|1024: | 92889.54 |   436.54 |  2117.41 |  2274.31 |  1487.99 |  1645.69 |   129.72 |   271.72 |

|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 18481.93 |   112.24 |   571.11 |   615.91 |   409.43 |   455.11 |    34.56 |    77.11 |
|1024: | 51633.52 |   242.59 |  1176.42 |  1263.57 |   826.74 |   914.35 |    72.13 |   151.02 |

## Benchmark 59b message

### N = 512

mlen, smlen = 59, 715
| Median   | sign | verify |
|  --  | --:  | ---: |
| kc |  1038.14 |    58.91 |
| us |   577.22 |    32.74 |
| Ghz|     1.80 |     1.80 |

| Average | sign | verify |
|  --  | --:  | ---: |
| kc |  1040.58 |    59.07 |
| us |   582.91 |    32.84 |
| Ghz|     1.79 |     1.80 |

### N = 1024

mlen, smlen = 59, 1332
| Median   | sign | verify |
|  --   | --:  | ---: |
| kc |  2132.08 |   128.44 |
| us |  1184.96 |    71.37 |
| Ghz|     1.80 |     1.80 |

| Average | sign | verify |
|  --  | --:  | ---: |
| kc |  2133.78 |   128.83 |
| us |  1190.03 |    71.51 |
| Ghz|     1.79 |     1.80 |

