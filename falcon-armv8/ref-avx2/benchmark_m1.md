# REF M1

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |       76 |       77
| FFT 1 |       76 |       79
| FFT 2 |       85 |      101
| FFT 3 |      115 |      127
| FFT 4 |      167 |      178
| FFT 5 |      245 |      261
| FFT 6 |      408 |      424
| FFT 7 |      759 |      847
| FFT 8 |     1633 |     1810
| FFT 9 |     3640 |     3930
| FFT 10 |     7998 |     8541


| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |     6607 |     6449
| NTT 10 |    13783 |    13335


| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_add |        0 |       75
| poly_add |        1 |       76
| poly_add |        2 |       81
| poly_add |        3 |       86
| poly_add |        4 |       95
| poly_add |        5 |      109
| poly_add |        6 |      155
| poly_add |        7 |      241
| poly_add |        8 |      390
| poly_add |        9 |      648
| poly_add |       10 |     1161

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_sub |        0 |       75
| poly_sub |        1 |       76
| poly_sub |        2 |       83
| poly_sub |        3 |       86
| poly_sub |        4 |       95
| poly_sub |        5 |      109
| poly_sub |        6 |      155
| poly_sub |        7 |      241
| poly_sub |        8 |      390
| poly_sub |        9 |      647
| poly_sub |       10 |     1161

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_neg |        0 |       75
| poly_neg |        1 |       76
| poly_neg |        2 |       82
| poly_neg |        3 |       86
| poly_neg |        4 |       93
| poly_neg |        5 |      109
| poly_neg |        6 |      148
| poly_neg |        7 |      231
| poly_neg |        8 |      385
| poly_neg |        9 |      637
| poly_neg |       10 |     1154

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_adj_fft |        0 |       76
| poly_adj_fft |        1 |       76
| poly_adj_fft |        2 |       77
| poly_adj_fft |        3 |       82
| poly_adj_fft |        4 |       77
| poly_adj_fft |        5 |       78
| poly_adj_fft |        6 |       83
| poly_adj_fft |        7 |       90
| poly_adj_fft |        8 |      183
| poly_adj_fft |        9 |      156
| poly_adj_fft |       10 |      275

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_fft |        0 |       76
| poly_mul_fft |        1 |       78
| poly_mul_fft |        2 |       78
| poly_mul_fft |        3 |       83
| poly_mul_fft |        4 |       87
| poly_mul_fft |        5 |       95
| poly_mul_fft |        6 |      115
| poly_mul_fft |        7 |      163
| poly_mul_fft |        8 |      336
| poly_mul_fft |        9 |      482
| poly_mul_fft |       10 |      755

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_invnorm2_fft |        0 |       77
| poly_invnorm2_fft |        1 |       85
| poly_invnorm2_fft |        2 |       85
| poly_invnorm2_fft |        3 |       86
| poly_invnorm2_fft |        4 |       86
| poly_invnorm2_fft |        5 |      100
| poly_invnorm2_fft |        6 |      132
| poly_invnorm2_fft |        7 |      189
| poly_invnorm2_fft |        8 |      303
| poly_invnorm2_fft |        9 |      457
| poly_invnorm2_fft |       10 |      754

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_mul_autoadj_fft |        0 |       76
| poly_mul_autoadj_fft |        1 |       76
| poly_mul_autoadj_fft |        2 |       77
| poly_mul_autoadj_fft |        3 |       78
| poly_mul_autoadj_fft |        4 |       80
| poly_mul_autoadj_fft |        5 |       86
| poly_mul_autoadj_fft |        6 |       96
| poly_mul_autoadj_fft |        7 |      125
| poly_mul_autoadj_fft |        8 |      264
| poly_mul_autoadj_fft |        9 |      421
| poly_mul_autoadj_fft |       10 |      759

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDL_fft |        0 |       76
| poly_LDL_fft |        1 |       99
| poly_LDL_fft |        2 |       99
| poly_LDL_fft |        3 |      105
| poly_LDL_fft |        4 |      122
| poly_LDL_fft |        5 |      157
| poly_LDL_fft |        6 |      217
| poly_LDL_fft |        7 |      323
| poly_LDL_fft |        8 |      596
| poly_LDL_fft |        9 |     1018
| poly_LDL_fft |       10 |     1889

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_LDLmv_fft |        0 |       76
| poly_LDLmv_fft |        1 |      103
| poly_LDLmv_fft |        2 |       99
| poly_LDLmv_fft |        3 |      108
| poly_LDLmv_fft |        4 |      122
| poly_LDLmv_fft |        5 |      156
| poly_LDLmv_fft |        6 |      219
| poly_LDLmv_fft |        7 |      324
| poly_LDLmv_fft |        8 |      611
| poly_LDLmv_fft |        9 |     1029
| poly_LDLmv_fft |       10 |     1848

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_split_fft |        0 |       76
| poly_split_fft |        1 |       76
| poly_split_fft |        2 |       82
| poly_split_fft |        3 |       86
| poly_split_fft |        4 |       93
| poly_split_fft |        5 |      109
| poly_split_fft |        6 |      140
| poly_split_fft |        7 |      199
| poly_split_fft |        8 |      295
| poly_split_fft |        9 |      487
| poly_split_fft |       10 |      886

| Function | logn | cycles |
|:-------------|----------:|-----------:|
| poly_merge_fft |        0 |       76
| poly_merge_fft |        1 |       76
| poly_merge_fft |        2 |       83
| poly_merge_fft |        3 |       96
| poly_merge_fft |        4 |      104
| poly_merge_fft |        5 |      123
| poly_merge_fft |        6 |      161
| poly_merge_fft |        7 |      226
| poly_merge_fft |        8 |      336
| poly_merge_fft |        9 |      569
| poly_merge_fft |       10 |     1010

|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: |  4986.21 |    50.17 |   209.67 |   223.42 |   140.29 |   154.17 |    14.92 |    30.04 |
|1024: | 15443.62 |   102.58 |   419.67 |   446.79 |   277.58 |   305.50 |    29.58 |    59.29 |

|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 15670.10 |   154.31 |   653.97 |   698.08 |   437.00 |   480.04 |    43.54 |    91.00 |
|1024: | 48668.19 |   318.49 |  1310.80 |  1395.80 |   865.13 |   952.65 |    89.33 |   182.96 |


## Benchmark 59 bytes message

### N = 512

| Median   | sign | verify |
| --   | --:  | ---: |
| kc |   668.36 |    43.41 |
| us |   214.12 |    13.54 |
| Ghz|     3.12 |     3.21 |

| Average | sign | verify |
| --   | --:  | ---: |
| kc |   668.49 |    43.41 |
| us |   216.27 |    13.62 |
| Ghz|     3.09 |     3.19 |

### N = 1024

mlen, smlen = 59, 1332
| Median   | sign | verify |
| --   | --:  | ---: |
| kc |  1338.44 |    89.01 |
| us |   419.96 |    27.79 |
| Ghz|     3.19 |     3.20 |

| Average | sign | verify |
| --   | --:  | ---: |
| kc |  1338.46 |    89.01 |
| us |   421.96 |    27.89 |
| Ghz|     3.17 |     3.19 |
