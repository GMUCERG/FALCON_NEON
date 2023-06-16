# Fast Compressed FFT versus reference FFT code

Iterations: 50,000

## Compile with -O0 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |      110 |      236
| FWD_FFT 3 |      194 |      634
| FWD_FFT 4 |      368 |     1806
| FWD_FFT 5 |      790 |     4583
| FWD_FFT 6 |     1783 |    11041
| FWD_FFT 7 |     4093 |    25556
| FWD_FFT 8 |     9297 |    58587
| FWD_FFT 9 |    20874 |   132696
| FWD_FFT 10 |    46370 |   297056



| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |      157 |      276
| INV_FFT 3 |      255 |      701
| INV_FFT 4 |      476 |     1891
| INV_FFT 5 |      983 |     4673
| INV_FFT 6 |     2156 |    10990
| INV_FFT 7 |     4787 |    25358
| INV_FFT 8 |    10643 |    57826
| INV_FFT 9 |    23529 |   130257
| INV_FFT 10 |    51684 |   290135

## Compile with -O1 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       78 |      104
| FWD_FFT 3 |      100 |      180
| FWD_FFT 4 |      147 |      369
| FWD_FFT 5 |      234 |      864
| FWD_FFT 6 |      425 |     1988
| FWD_FFT 7 |      864 |     4515
| FWD_FFT 8 |     1863 |    10166
| FWD_FFT 9 |     4140 |    22714
| FWD_FFT 10 |     9155 |    50475


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       85 |      166
| INV_FFT 3 |      111 |      260
| INV_FFT 4 |      164 |      479
| INV_FFT 5 |      262 |     1040
| INV_FFT 6 |      481 |     2297
| INV_FFT 7 |      982 |     5096
| INV_FFT 8 |     2072 |    11252
| INV_FFT 9 |     4503 |    24823
| INV_FFT 10 |     9891 |    54634

## Compile with -O2 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       83 |       86
| FWD_FFT 3 |      111 |      125
| FWD_FFT 4 |      178 |      170
| FWD_FFT 5 |      278 |      251
| FWD_FFT 6 |      501 |      419
| FWD_FFT 7 |      967 |      775
| FWD_FFT 8 |     1988 |     2055
| FWD_FFT 9 |     4361 |     4144
| FWD_FFT 10 |     9481 |     8670


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       83 |       98
| INV_FFT 3 |      107 |      126
| INV_FFT 4 |      175 |      180
| INV_FFT 5 |      282 |      258
| INV_FFT 6 |      501 |      431
| INV_FFT 7 |      968 |      866
| INV_FFT 8 |     2035 |     2334
| INV_FFT 9 |     4405 |     4523
| INV_FFT 10 |     9486 |     9257

## Compile with -O3 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       83 |       84
| FWD_FFT 3 |      110 |      118
| FWD_FFT 4 |      173 |      164
| FWD_FFT 5 |      272 |      240
| FWD_FFT 6 |      482 |      401
| FWD_FFT 7 |      926 |      746
| FWD_FFT 8 |     1936 |     1980
| FWD_FFT 9 |     4223 |     4026
| FWD_FFT 10 |     9232 |     8434


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       83 |       95
| INV_FFT 3 |      107 |      126
| INV_FFT 4 |      173 |      173
| INV_FFT 5 |      273 |      254
| INV_FFT 6 |      484 |      418
| INV_FFT 7 |      927 |      839
| INV_FFT 8 |     1973 |     2252
| INV_FFT 9 |     4243 |     4399
| INV_FFT 10 |     9216 |     9043


## Compile with -Os for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       78 |       82
| FWD_FFT 3 |       98 |       99
| FWD_FFT 4 |      144 |      153
| FWD_FFT 5 |      212 |      216
| FWD_FFT 6 |      365 |      368
| FWD_FFT 7 |      736 |      734
| FWD_FFT 8 |     1578 |     1576
| FWD_FFT 9 |     3520 |     3542
| FWD_FFT 10 |     7783 |     7751


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       79 |       86
| INV_FFT 3 |      103 |      113
| INV_FFT 4 |      146 |      164
| INV_FFT 5 |      221 |      246
| INV_FFT 6 |      396 |      434
| INV_FFT 7 |      805 |      871
| INV_FFT 8 |     1700 |     1818
| INV_FFT 9 |     3723 |     3941
| INV_FFT 10 |     8187 |     8526


## Compare Split FFT versus Adjacent FFT, with -Os for both

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       78 |       79
| FWD_FFT 3 |       98 |      102
| FWD_FFT 4 |      145 |      146
| FWD_FFT 5 |      212 |      213
| FWD_FFT 6 |      365 |      376
| FWD_FFT 7 |      738 |      726
| FWD_FFT 8 |     1580 |     1540
| FWD_FFT 9 |     3515 |     3395
| FWD_FFT 10 |     7799 |     7583


| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       78 |       79
| INV_FFT 3 |      106 |      102
| INV_FFT 4 |      148 |      146
| INV_FFT 5 |      222 |      216
| INV_FFT 6 |      401 |      377
| INV_FFT 7 |      805 |      745
| INV_FFT 8 |     1702 |     1577
| INV_FFT 9 |     3732 |     3472
| INV_FFT 10 |     8201 |     7681
