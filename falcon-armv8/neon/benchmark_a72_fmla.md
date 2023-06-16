# NEON A72 FMLA

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |        9 |       12
| FFT 1 |        9 |       12
| FFT 2 |       17 |       20
| FFT 3 |       47 |       48
| FFT 4 |       91 |       93
| FFT 5 |      213 |      217
| FFT 6 |      522 |      526
| FFT 7 |     1154 |     1185
| FFT 8 |     2849 |     2912
| FFT 9 |     5892 |     6158
| FFT 10 |    14187 |    14678

| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |     3561 |     3776
| NTT 10 |     7688 |     8247

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
| poly_adj_fft |        9 |      389
| poly_adj_fft |       10 |      794

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_fft |        0 |       10
| poly_mul_fft |        1 |       11
| poly_mul_fft |        2 |        9
| poly_mul_fft |        3 |       17
| poly_mul_fft |        4 |       47
| poly_mul_fft |        5 |       83
| poly_mul_fft |        6 |      155
| poly_mul_fft |        7 |      299
| poly_mul_fft |        8 |      587
| poly_mul_fft |        9 |     1163
| poly_mul_fft |       10 |     2332

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_invnorm2_fft |        0 |       10
| poly_invnorm2_fft |        1 |        9
| poly_invnorm2_fft |        2 |       19
| poly_invnorm2_fft |        3 |       28
| poly_invnorm2_fft |        4 |      132
| poly_invnorm2_fft |        5 |      260
| poly_invnorm2_fft |        6 |      516
| poly_invnorm2_fft |        7 |     1028
| poly_invnorm2_fft |        8 |     2052
| poly_invnorm2_fft |        9 |     4100
| poly_invnorm2_fft |       10 |     8196

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
| poly_LDL_fft |        0 |       12
| poly_LDL_fft |        1 |       30
| poly_LDL_fft |        2 |       34
| poly_LDL_fft |        3 |       71
| poly_LDL_fft |        4 |      187
| poly_LDL_fft |        5 |      386
| poly_LDL_fft |        6 |      796
| poly_LDL_fft |        7 |     1580
| poly_LDL_fft |        8 |     3180
| poly_LDL_fft |        9 |     6415
| poly_LDL_fft |       10 |    12791

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDLmv_fft |        0 |       12
| poly_LDLmv_fft |        1 |       30
| poly_LDLmv_fft |        2 |       35
| poly_LDLmv_fft |        3 |       73
| poly_LDLmv_fft |        4 |      193
| poly_LDLmv_fft |        5 |      394
| poly_LDLmv_fft |        6 |      796
| poly_LDLmv_fft |        7 |     1600
| poly_LDLmv_fft |        8 |     3208
| poly_LDLmv_fft |        9 |     6425
| poly_LDLmv_fft |       10 |    12923

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_split_fft |        0 |       10
| poly_split_fft |        1 |        9
| poly_split_fft |        2 |       11
| poly_split_fft |        3 |       20
| poly_split_fft |        4 |       47
| poly_split_fft |        5 |       81
| poly_split_fft |        6 |      149
| poly_split_fft |        7 |      285
| poly_split_fft |        8 |      557
| poly_split_fft |        9 |     1101
| poly_split_fft |       10 |     2206

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_merge_fft |        0 |       10
| poly_merge_fft |        1 |        9
| poly_merge_fft |        2 |       19
| poly_merge_fft |        3 |       23
| poly_merge_fft |        4 |       45
| poly_merge_fft |        5 |       78
| poly_merge_fft |        6 |      141
| poly_merge_fft |        7 |      267
| poly_merge_fft |        8 |      519
| poly_merge_fft |        9 |     1042
| poly_merge_fft |       10 |     2077

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| compute_bnorm |        9 |      815
| compute_bnorm |       10 |     1656

|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 33191.44 |   196.37 |   991.03 |  1072.90 |   715.65 |   797.19 |    62.17 |   138.95 |
|1024: | 92707.33 |   422.70 |  2035.03 |  2192.45 |  1443.90 |  1600.27 |   132.21 |   272.74 |

|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 18448.07 |   109.17 |   550.63 |   596.13 |   397.65 |   442.96 |    34.59 |    77.26 |
|1024: | 51508.63 |   234.91 |  1130.65 |  1218.13 |   802.24 |   889.11 |    73.50 |   151.57 |


## Benchmark 59b message

### N = 512

mlen, smlen = 59, 715
| Median   | sign | verify |
| ---   | --:  | ---: |
| kc |  1000.31 |    58.68 |
| us |   556.06 |    32.80 |
| Ghz|     1.80 |     1.79 |

| Average | sign | verify |
| ---   | --:  | ---: |
| kc |  1001.93 |    58.76 |
| us |   560.05 |    32.87 |
| Ghz|     1.79 |     1.79 |

### N = 1024

mlen, smlen = 59, 1332
| Median   | sign | verify |
| ---   | --:  | ---: |
| kc |  2046.53 |   129.98 |
| us |  1136.89 |    72.30 |
| Ghz|     1.80 |     1.80 |

| Average | sign | verify |
| ---   | --:  | ---: |
| kc |  2048.93 |   130.37 |
| us |  1137.05 |    72.53 |
| Ghz|     1.80 |     1.80 |

OK