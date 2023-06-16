# REF A72

## Old FFT 
| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |       14 |       15
| FFT 1 |       14 |       46
| FFT 2 |       37 |       47
| FFT 3 |      100 |      116
| FFT 4 |      232 |      259
| FFT 5 |      516 |      570
| FFT 6 |     1132 |     1249
| FFT 7 |     2529 |     2799
| FFT 8 |     5474 |     6037
| FFT 9 |    11807 |    13136
| FFT 10 |    27366 |    28151

## New FFT

With `-O1 -mtune=native`. `-O2, -O3` option create longer assembly, slower code.

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |        9 |        9
| FFT 1 |        9 |        9
| FFT 2 |       16 |       19
| FFT 3 |       59 |       66
| FFT 4 |      162 |      178
| FFT 5 |      400 |      441
| FFT 6 |      953 |     1044
| FFT 7 |     2274 |     2506
| FFT 8 |     5170 |     5692
| FFT 9 |    11677 |    12854
| FFT 10 |    25824 |    28533


| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |    22582 |    22251
| NTT 10 |    48097 |    47196

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_add |        0 |        9
| poly_add |        1 |       13
| poly_add |        2 |       19
| poly_add |        3 |       32
| poly_add |        4 |       56
| poly_add |        5 |      103
| poly_add |        6 |      215
| poly_add |        7 |      408
| poly_add |        8 |      792
| poly_add |        9 |     1559
| poly_add |       10 |     3108

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_sub |        0 |        9
| poly_sub |        1 |       13
| poly_sub |        2 |       20
| poly_sub |        3 |       32
| poly_sub |        4 |       55
| poly_sub |        5 |      103
| poly_sub |        6 |      216
| poly_sub |        7 |      408
| poly_sub |        8 |      791
| poly_sub |        9 |     1559
| poly_sub |       10 |     3108

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_neg |        0 |        9
| poly_neg |        1 |       13
| poly_neg |        2 |       19
| poly_neg |        3 |       31
| poly_neg |        4 |       55
| poly_neg |        5 |      103
| poly_neg |        6 |      214
| poly_neg |        7 |      406
| poly_neg |        8 |      790
| poly_neg |        9 |     1558
| poly_neg |       10 |     3094

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_adj_fft |        0 |        9
| poly_adj_fft |        1 |        9
| poly_adj_fft |        2 |       14
| poly_adj_fft |        3 |       12
| poly_adj_fft |        4 |       18
| poly_adj_fft |        5 |       29
| poly_adj_fft |        6 |       49
| poly_adj_fft |        7 |       89
| poly_adj_fft |        8 |      169
| poly_adj_fft |        9 |      348
| poly_adj_fft |       10 |      667

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_fft |        0 |        9
| poly_mul_fft |        1 |       11
| poly_mul_fft |        2 |       20
| poly_mul_fft |        3 |       34
| poly_mul_fft |        4 |       55
| poly_mul_fft |        5 |       97
| poly_mul_fft |        6 |      181
| poly_mul_fft |        7 |      349
| poly_mul_fft |        8 |      703
| poly_mul_fft |        9 |     1375
| poly_mul_fft |       10 |     2745

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_invnorm2_fft |        0 |        9
| poly_invnorm2_fft |        1 |       14
| poly_invnorm2_fft |        2 |       27
| poly_invnorm2_fft |        3 |       54
| poly_invnorm2_fft |        4 |      104
| poly_invnorm2_fft |        5 |      237
| poly_invnorm2_fft |        6 |      493
| poly_invnorm2_fft |        7 |     1005
| poly_invnorm2_fft |        8 |     2038
| poly_invnorm2_fft |        9 |     4086
| poly_invnorm2_fft |       10 |     8187

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_autoadj_fft |        0 |        9
| poly_mul_autoadj_fft |        1 |       10
| poly_mul_autoadj_fft |        2 |       16
| poly_mul_autoadj_fft |        3 |       24
| poly_mul_autoadj_fft |        4 |       38
| poly_mul_autoadj_fft |        5 |       62
| poly_mul_autoadj_fft |        6 |      110
| poly_mul_autoadj_fft |        7 |      206
| poly_mul_autoadj_fft |        8 |      416
| poly_mul_autoadj_fft |        9 |      800
| poly_mul_autoadj_fft |       10 |     1568

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDL_fft |        0 |        9
| poly_LDL_fft |        1 |       41
| poly_LDL_fft |        2 |       64
| poly_LDL_fft |        3 |      107
| poly_LDL_fft |        4 |      192
| poly_LDL_fft |        5 |      364
| poly_LDL_fft |        6 |      709
| poly_LDL_fft |        7 |     1397
| poly_LDL_fft |        8 |     2795
| poly_LDL_fft |        9 |     5547
| poly_LDL_fft |       10 |    11083

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDLmv_fft |        0 |        9
| poly_LDLmv_fft |        1 |       62
| poly_LDLmv_fft |        2 |       94
| poly_LDLmv_fft |        3 |      137
| poly_LDLmv_fft |        4 |      266
| poly_LDLmv_fft |        5 |      497
| poly_LDLmv_fft |        6 |      958
| poly_LDLmv_fft |        7 |     1872
| poly_LDLmv_fft |        8 |     3707
| poly_LDLmv_fft |        9 |     5915
| poly_LDLmv_fft |       10 |    11832

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_split_fft |        0 |        9
| poly_split_fft |        1 |        9
| poly_split_fft |        2 |       27
| poly_split_fft |        3 |       45
| poly_split_fft |        4 |       67
| poly_split_fft |        5 |      111
| poly_split_fft |        6 |      199
| poly_split_fft |        7 |      375
| poly_split_fft |        8 |      727
| poly_split_fft |        9 |     1455
| poly_split_fft |       10 |     2996

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_merge_fft |        0 |        9
| poly_merge_fft |        1 |        9
| poly_merge_fft |        2 |       26
| poly_merge_fft |        3 |       58
| poly_merge_fft |        4 |       78
| poly_merge_fft |        5 |      117
| poly_merge_fft |        6 |      194
| poly_merge_fft |        7 |      373
| poly_merge_fft |        8 |      682
| poly_merge_fft |        9 |     1301
| poly_merge_fft |       10 |     2567


|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 18053.33 |   258.52 |   828.26 |   885.96 |   498.93 |   557.37 |    70.20 |   130.81 |
|1024: | 52207.41 |   548.33 |  1713.87 |  1827.85 |  1007.91 |  1122.91 |   152.44 |   265.11 |

|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 32495.83 |   465.19 |  1490.72 |  1594.55 |   897.93 |  1003.10 |   126.29 |   235.38 |
|1024: | 93973.14 |   986.85 |  3084.80 |  3289.99 |  1814.10 |  2021.09 |   274.31 |   477.14 |


## Benchmark 59 bytes message

### N = 512

mlen, smlen = 59, 717
| Median   | sign | verify |
| --   | --:  | ---: |
| kc |  1503.08 |   129.51 |
| us |   840.07 |    72.28 |
| Ghz|     1.79 |     1.79 |

| Average | sign | verify |
| --   | --:  | ---: |
| kc |  1506.04 |   131.73 |
| us |   855.20 |    72.43 |
| Ghz|     1.76 |     1.82 |



### N = 1024

mlen, smlen = 59, 1332
| Median   | sign | verify |
| --   | --:  | ---: |
| kc |  3076.36 |   270.07 |
| us |  1709.78 |   150.06 |
| Ghz|     1.80 |     1.80 |

| Average | sign | verify |
| --  | --:  | ---: |
| kc |  3076.90 |   270.59 |
| us |  1717.60 |   150.37 |
| Ghz|     1.79 |     1.80 |
