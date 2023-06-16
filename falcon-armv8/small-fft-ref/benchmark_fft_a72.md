# Fast Compressed FFT versus reference FFT code

Iterations: 10,000

## Compile with -O0 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       90 |      365
| FWD_FFT 3 |      413 |     1439
| FWD_FFT 4 |      933 |     4019
| FWD_FFT 5 |     2,219 |    10,354
| FWD_FFT 6 |     5,270 |    25,530
| FWD_FFT 7 |    12,296 |    60,714
| FWD_FFT 8 |    28,679 |   140,857
| FWD_FFT 9 |    65,048 |   320,489
| FWD_FFT 10 |   144,732 |   718,356

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |      192 |      516
| INV_FFT 3 |      471 |     1,659
| INV_FFT 4 |     1,189 |     4,411
| INV_FFT 5 |     2,718 |    11,070
| INV_FFT 6 |     6,255 |    27,078
| INV_FFT 7 |    14,179 |    63,151
| INV_FFT 8 |    31,877 |   144,380
| INV_FFT 9 |    71,033 |   325,271
| INV_FFT 10 |   156,166 |   723,942

## Compile with -O1 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       20 |       30
| FWD_FFT 3 |       68 |       74
| FWD_FFT 4 |      180 |      171
| FWD_FFT 5 |      445 |      395
| FWD_FFT 6 |     1,064 |      909
| FWD_FFT 7 |     2,518 |     2,151
| FWD_FFT 8 |     5,815 |     4,915
| FWD_FFT 9 |    13,057 |    10,864
| FWD_FFT 10 |    29,018 |    24,884



| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |        23 |       40
| INV_FFT 3 |        72 |       94
| INV_FFT 4 |       182 |      203
| INV_FFT 5 |       442 |      455
| INV_FFT 6 |      1,046 |     1,035
| INV_FFT 7 |      2,501 |     2,369
| INV_FFT 8 |      5,646 |     5,378
| INV_FFT 9 |     12,724 |    11,703
| INV_FFT 10 |    28,243 |    26,309

## Compile  with -O2 for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       26 |       53
| FWD_FFT 3 |       98 |      117
| FWD_FFT 4 |      260 |      255
| FWD_FFT 5 |      616 |      553
| FWD_FFT 6 |     1,397 |     1,203
| FWD_FFT 7 |     3,127 |     2,673
| FWD_FFT 8 |     6,871 |     5,806
| FWD_FFT 9 |    14,893 |    12,587
| FWD_FFT 10 |    32,403 |    27,427


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       29 |       51
| INV_FFT 3 |       98 |      120
| INV_FFT 4 |      261 |      267
| INV_FFT 5 |      617 |      585
| INV_FFT 6 |     1,395 |     1,278
| INV_FFT 7 |     3,124 |     2,859
| INV_FFT 8 |     6,838 |     6,172
| INV_FFT 9 |    14,811 |    13,353
| INV_FFT 10 |    32,043 |    28,601


## Compile with -O3 for both


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       26 |       51
| FWD_FFT 3 |       97 |      117
| FWD_FFT 4 |      259 |      255
| FWD_FFT 5 |      615 |      553
| FWD_FFT 6 |     1,394 |     1,203
| FWD_FFT 7 |     3,124 |     2,673
| FWD_FFT 8 |     6,852 |     5,806
| FWD_FFT 9 |    14,846 |    12,584
| FWD_FFT 10 |    32,342 |    27,159


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       29 |       53
| INV_FFT 3 |       97 |      122
| INV_FFT 4 |      260 |      266
| INV_FFT 5 |      616 |      577
| INV_FFT 6 |     1,394 |     1,255
| INV_FFT 7 |     3,121 |     2,802
| INV_FFT 8 |     6,850 |     6,036
| INV_FFT 9 |    14,819 |    13,081
| INV_FFT 10 |    32,003 |    28,088


## Compile with -Os for both

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       19 |       28
| FWD_FFT 3 |       58 |       70
| FWD_FFT 4 |      142 |      162
| FWD_FFT 5 |      346 |      369
| FWD_FFT 6 |      824 |      849
| FWD_FFT 7 |     1964 |     2022
| FWD_FFT 8 |     4605 |     4709
| FWD_FFT 9 |    10451 |    10118
| FWD_FFT 10 |    22797 |    23496


| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       20 |       35
| INV_FFT 3 |       59 |       80
| INV_FFT 4 |      147 |      183
| INV_FFT 5 |      359 |      421
| INV_FFT 6 |      852 |      968
| INV_FFT 7 |     2036 |     2283
| INV_FFT 8 |     4696 |     5151
| INV_FFT 9 |    10559 |    11052
| INV_FFT 10 |    23524 |    24867


## Compare Split FFT versus Adjacent FFT, with -Os for both

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FWD_FFT 2 |       19 |       17
| FWD_FFT 3 |       56 |       55
| FWD_FFT 4 |      142 |      137
| FWD_FFT 5 |      346 |      335
| FWD_FFT 6 |      825 |      804
| FWD_FFT 7 |     1983 |     1954
| FWD_FFT 8 |     4606 |     4512
| FWD_FFT 9 |    10434 |    10276
| FWD_FFT 10 |    22840 |    22573


| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| INV_FFT 2 |       21 |       25
| INV_FFT 3 |       59 |       56
| INV_FFT 4 |      147 |      139
| INV_FFT 5 |      359 |      339
| INV_FFT 6 |      852 |      813
| INV_FFT 7 |     2016 |     1991
| INV_FFT 8 |     4693 |     4504
| INV_FFT 9 |    10604 |    10219
| INV_FFT 10 |    23456 |    23141
