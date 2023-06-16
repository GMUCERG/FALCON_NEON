# Bechmark test_fft on Cortex-A72

## -O1 flag

### 1st run


test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       37 |       37
| FFT 3 |      133 |      131
| FFT 4 |      355 |      322
| FFT 5 |      880 |      825
| FFT 6 |     2102 |     2011
| FFT 7 |     5045 |     4877
| FFT 8 |    11493 |    11281
| FFT 9 |    25770 |    25439
| FFT 10 |    57224 |    56983

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       35 |       61
| FFT 3 |      132 |      168
| FFT 4 |      354 |      410
| FFT 5 |      879 |      978
| FFT 6 |     2101 |     2299
| FFT 7 |     4991 |     5409
| FFT 8 |    11455 |    12304
| FFT 9 |    25751 |    27338
| FFT 10 |    57315 |    60193

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       35 |       97
| FFT 3 |      132 |      233
| FFT 4 |      354 |      514
| FFT 5 |      879 |     1123
| FFT 6 |     2101 |     2451
| FFT 7 |     5009 |     5469
| FFT 8 |    11489 |    11820
| FFT 9 |    25788 |    25667
| FFT 10 |    57302 |    55262

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       48 |       51
| Split/Merge 3 |       68 |      101
| Split/Merge 4 |      107 |      141
| Split/Merge 5 |      186 |      217
| Split/Merge 6 |      344 |      369
| Split/Merge 7 |      696 |      694
| Split/Merge 8 |     1311 |     1467
| Split/Merge 9 |     2595 |     3108
| Split/Merge 10 |     5629 |     5986

### 2nd run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       37 |       37
| FFT 3 |      133 |      114
| FFT 4 |      355 |      322
| FFT 5 |      880 |      825
| FFT 6 |     2102 |     2046
| FFT 7 |     5009 |     4874
| FFT 8 |    11471 |    11278
| FFT 9 |    25770 |    25541
| FFT 10 |    57256 |    57839

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       35 |       61
| FFT 3 |      132 |      168
| FFT 4 |      354 |      410
| FFT 5 |      879 |      978
| FFT 6 |     2101 |     2299
| FFT 7 |     4991 |     5405
| FFT 8 |    11474 |    12308
| FFT 9 |    25755 |    27384
| FFT 10 |    57256 |    61338

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       35 |       97
| FFT 3 |      132 |      233
| FFT 4 |      354 |      514
| FFT 5 |      879 |     1123
| FFT 6 |     2101 |     2483
| FFT 7 |     4991 |     5469
| FFT 8 |    11456 |    11836
| FFT 9 |    25751 |    25812
| FFT 10 |    57237 |    55815

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       48 |       65
| Split/Merge 3 |       68 |      117
| Split/Merge 4 |      107 |      168
| Split/Merge 5 |      186 |      288
| Split/Merge 6 |      344 |     1015
| Split/Merge 7 |      679 |     1527
| Split/Merge 8 |     1311 |     1729
| Split/Merge 9 |     2595 |     3177
| Split/Merge 10 |     5123 |     6708

## -O2 flag

### 1st run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       48 |       34
| FFT 3 |      191 |      158
| FFT 4 |      523 |      353
| FFT 5 |     1249 |      828
| FFT 6 |     2838 |     1976
| FFT 7 |     6370 |     4726
| FFT 8 |    13994 |    10856
| FFT 9 |    30357 |    24702
| FFT 10 |    66022 |    56020

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       76
| FFT 3 |      189 |      234
| FFT 4 |      514 |      578
| FFT 5 |     1226 |     1327
| FFT 6 |     2783 |     2958
| FFT 7 |     6243 |     6587
| FFT 8 |    13688 |    14312
| FFT 9 |    29703 |    31026
| FFT 10 |    64442 |    66517

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       98
| FFT 3 |      189 |      233
| FFT 4 |      514 |      514
| FFT 5 |     1226 |     1123
| FFT 6 |     2783 |     2451
| FFT 7 |     6243 |     5468
| FFT 8 |    13704 |    11836
| FFT 9 |    29703 |    25664
| FFT 10 |    64467 |    55158

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       48 |       51
| Split/Merge 3 |       67 |      101
| Split/Merge 4 |      106 |      141
| Split/Merge 5 |      184 |      217
| Split/Merge 6 |      342 |      369
| Split/Merge 7 |      657 |      694
| Split/Merge 8 |     1308 |     1415
| Split/Merge 9 |     2587 |     2597
| Split/Merge 10 |     5173 |     5726

### 2nd run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       48 |       34
| FFT 3 |      191 |      156
| FFT 4 |      519 |      353
| FFT 5 |     1237 |      829
| FFT 6 |     2812 |     1964
| FFT 7 |     6316 |     4711
| FFT 8 |    13870 |    10907
| FFT 9 |    30140 |    24684
| FFT 10 |    65561 |    55995

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       76
| FFT 3 |      189 |      234
| FFT 4 |      514 |      578
| FFT 5 |     1226 |     1327
| FFT 6 |     2783 |     2958
| FFT 7 |     6281 |     6587
| FFT 8 |    13737 |    14312
| FFT 9 |    29703 |    31048
| FFT 10 |    64478 |    66515

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       97
| FFT 3 |      189 |      233
| FFT 4 |      514 |      514
| FFT 5 |     1226 |     1123
| FFT 6 |     2783 |     2451
| FFT 7 |     6261 |     5468
| FFT 8 |    13688 |    11835
| FFT 9 |    29702 |    25665
| FFT 10 |    64568 |    55198

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       48 |       51
| Split/Merge 3 |       67 |      101
| Split/Merge 4 |      126 |      141
| Split/Merge 5 |      184 |      217
| Split/Merge 6 |      342 |      369
| Split/Merge 7 |      657 |      694
| Split/Merge 8 |     1287 |     1302
| Split/Merge 9 |     2974 |     2539
| Split/Merge 10 |     6022 |     5129

## -O3 Flag

### 1st run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       48 |       34
| FFT 3 |      190 |      158
| FFT 4 |      522 |      353
| FFT 5 |     1248 |      828
| FFT 6 |     2837 |     1976
| FFT 7 |     6364 |     4760
| FFT 8 |    13990 |    10984
| FFT 9 |    30334 |    24966
| FFT 10 |    65875 |    56230

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       76
| FFT 3 |      188 |      234
| FFT 4 |      513 |      578
| FFT 5 |     1225 |     1327
| FFT 6 |     2782 |     2958
| FFT 7 |     6237 |     6587
| FFT 8 |    13679 |    14310
| FFT 9 |    29694 |    31077
| FFT 10 |    64419 |    66573

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       98
| FFT 3 |      188 |      233
| FFT 4 |      513 |      514
| FFT 5 |     1225 |     1123
| FFT 6 |     2782 |     2451
| FFT 7 |     6237 |     5502
| FFT 8 |    13697 |    11835
| FFT 9 |    29664 |    25719
| FFT 10 |    64419 |    55487

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       48 |       51
| Split/Merge 3 |       67 |      101
| Split/Merge 4 |      125 |      141
| Split/Merge 5 |      184 |      217
| Split/Merge 6 |      342 |      390
| Split/Merge 7 |      657 |      694
| Split/Merge 8 |     1287 |     1302
| Split/Merge 9 |     2587 |     2597
| Split/Merge 10 |     5121 |     6039

### 2nd run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       48 |       35
| FFT 3 |      190 |      156
| FFT 4 |      520 |      356
| FFT 5 |     1239 |      840
| FFT 6 |     2816 |     1969
| FFT 7 |     6319 |     4809
| FFT 8 |    13896 |    10941
| FFT 9 |    30144 |    24853
| FFT 10 |    65480 |    56809

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       76
| FFT 3 |      188 |      234
| FFT 4 |      513 |      578
| FFT 5 |     1225 |     1327
| FFT 6 |     2782 |     2992
| FFT 7 |     6237 |     6587
| FFT 8 |    13696 |    14327
| FFT 9 |    29646 |    31060
| FFT 10 |    64313 |    66645

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       47 |       97
| FFT 3 |      188 |      233
| FFT 4 |      513 |      514
| FFT 5 |     1225 |     1123
| FFT 6 |     2782 |     2451
| FFT 7 |     6237 |     5468
| FFT 8 |    13707 |    11819
| FFT 9 |    29691 |    25668
| FFT 10 |    64315 |    57857

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       48 |       51
| Split/Merge 3 |       67 |      101
| Split/Merge 4 |      106 |      141
| Split/Merge 5 |      184 |      217
| Split/Merge 6 |      342 |      369
| Split/Merge 7 |      657 |      694
| Split/Merge 8 |     1287 |     1302
| Split/Merge 9 |     2587 |     2636
| Split/Merge 10 |     6193 |     6363