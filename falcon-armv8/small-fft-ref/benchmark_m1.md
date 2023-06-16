# Bechmark test_fft on Apple M1

## -O1 Flag

### 1st run
test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       99 |      105
| FFT 3 |      154 |      156
| FFT 4 |      235 |      233
| FFT 5 |      407 |      373
| FFT 6 |      821 |      761
| FFT 7 |     1775 |     1632
| FFT 8 |     3887 |     3618
| FFT 9 |     8649 |     8188
| FFT 10 |    19194 |    18231

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       99 |      109
| FFT 3 |      154 |      174
| FFT 4 |      235 |      251
| FFT 5 |      406 |      428
| FFT 6 |      820 |      844
| FFT 7 |     1775 |     1803
| FFT 8 |     3888 |     3951
| FFT 9 |     8669 |     8793
| FFT 10 |    19199 |    19429

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       99 |      120
| FFT 3 |      154 |      180
| FFT 4 |      235 |      252
| FFT 5 |      406 |      400
| FFT 6 |      820 |      731
| FFT 7 |     1775 |     1512
| FFT 8 |     3887 |     4168
| FFT 9 |     8648 |     8367
| FFT 10 |    19177 |    17420

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |      108 |      101
| Split/Merge 3 |      119 |      115
| Split/Merge 4 |      137 |      135
| Split/Merge 5 |      192 |      165
| Split/Merge 6 |      267 |      221
| Split/Merge 7 |      444 |      324
| Split/Merge 8 |      773 |      530
| Split/Merge 9 |     1429 |      987
| Split/Merge 10 |     2753 |     1791

### 2nd run
test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |       99 |      105
| FFT 3 |      154 |      156
| FFT 4 |      235 |      234
| FFT 5 |      406 |      373
| FFT 6 |      820 |      760
| FFT 7 |     1775 |     1632
| FFT 8 |     3888 |     3618
| FFT 9 |     8651 |     8136
| FFT 10 |    19187 |    18227

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |       99 |      109
| FFT 3 |      154 |      174
| FFT 4 |      235 |      251
| FFT 5 |      406 |      428
| FFT 6 |      820 |      844
| FFT 7 |     1776 |     1803
| FFT 8 |     3888 |     3952
| FFT 9 |     8651 |     8762
| FFT 10 |    19191 |    19361

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |       99 |      122
| FFT 3 |      154 |      180
| FFT 4 |      235 |      251
| FFT 5 |      407 |      401
| FFT 6 |      821 |      733
| FFT 7 |     1775 |     1512
| FFT 8 |     3888 |     4167
| FFT 9 |     8651 |     8373
| FFT 10 |    19175 |    17420

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |      108 |      101
| Split/Merge 3 |      119 |      115
| Split/Merge 4 |      137 |      135
| Split/Merge 5 |      192 |      165
| Split/Merge 6 |      270 |      221
| Split/Merge 7 |      446 |      325
| Split/Merge 8 |      772 |      530
| Split/Merge 9 |     1429 |      987
| Split/Merge 10 |     2754 |     1793

## -O2 flag

### 1st run
test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      106
| FFT 3 |      163 |      174
| FFT 4 |      269 |      242
| FFT 5 |      478 |      383
| FFT 6 |      929 |      759
| FFT 7 |     1880 |     1613
| FFT 8 |     3885 |     3560
| FFT 9 |     8177 |     7991
| FFT 10 |    17270 |    17891

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      112
| FFT 3 |      163 |      184
| FFT 4 |      270 |      288
| FFT 5 |      480 |      508
| FFT 6 |      929 |      977
| FFT 7 |     1880 |     1995
| FFT 8 |     3998 |     4889
| FFT 9 |     8805 |     9932
| FFT 10 |    19122 |    20748

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      123
| FFT 3 |      163 |      180
| FFT 4 |      270 |      253
| FFT 5 |      478 |      401
| FFT 6 |      929 |      732
| FFT 7 |     1880 |     1512
| FFT 8 |     3997 |     4168
| FFT 9 |     8804 |     8363
| FFT 10 |    19116 |    17421

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       97 |      101
| Split/Merge 3 |       97 |      115
| Split/Merge 4 |      117 |      132
| Split/Merge 5 |      156 |      165
| Split/Merge 6 |      216 |      220
| Split/Merge 7 |      325 |      324
| Split/Merge 8 |      545 |      530
| Split/Merge 9 |      985 |      986
| Split/Merge 10 |     1893 |     1790

### 2nd run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      106
| FFT 3 |      163 |      174
| FFT 4 |      270 |      242
| FFT 5 |      479 |      385
| FFT 6 |      929 |      761
| FFT 7 |     1880 |     1613
| FFT 8 |     3885 |     3560
| FFT 9 |     8176 |     7990
| FFT 10 |    17273 |    17886

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      112
| FFT 3 |      163 |      184
| FFT 4 |      270 |      287
| FFT 5 |      479 |      508
| FFT 6 |      929 |      977
| FFT 7 |     1880 |     1995
| FFT 8 |     3998 |     4867
| FFT 9 |     8807 |     9933
| FFT 10 |    19122 |    20749

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      123
| FFT 3 |      163 |      180
| FFT 4 |      270 |      254
| FFT 5 |      478 |      401
| FFT 6 |      929 |      732
| FFT 7 |     1880 |     1512
| FFT 8 |     3999 |     4168
| FFT 9 |     8806 |     8366
| FFT 10 |    19114 |    17423

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       97 |      101
| Split/Merge 3 |       97 |      115
| Split/Merge 4 |      118 |      132
| Split/Merge 5 |      156 |      165
| Split/Merge 6 |      216 |      221
| Split/Merge 7 |      325 |      324
| Split/Merge 8 |      545 |      531
| Split/Merge 9 |      985 |      985
| Split/Merge 10 |     1893 |     1794


## -O3 flag

### 1st run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |      103 |      106
| FFT 3 |      162 |      169
| FFT 4 |      262 |      244
| FFT 5 |      457 |      389
| FFT 6 |      883 |      760
| FFT 7 |     1794 |     1613
| FFT 8 |     3769 |     3559
| FFT 9 |     7882 |     8088
| FFT 10 |    16731 |    17896

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      109
| FFT 3 |      162 |      180
| FFT 4 |      262 |      278
| FFT 5 |      457 |      480
| FFT 6 |      882 |      924
| FFT 7 |     1793 |     1895
| FFT 8 |     3894 |     4713
| FFT 9 |     8540 |     9622
| FFT 10 |    18684 |    20197

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      123
| FFT 3 |      162 |      181
| FFT 4 |      262 |      253
| FFT 5 |      457 |      401
| FFT 6 |      883 |      732
| FFT 7 |     1793 |     1511
| FFT 8 |     3892 |     4167
| FFT 9 |     8536 |     8359
| FFT 10 |    18684 |    17420

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       97 |      102
| Split/Merge 3 |       97 |      114
| Split/Merge 4 |      117 |      132
| Split/Merge 5 |      156 |      164
| Split/Merge 6 |      216 |      221
| Split/Merge 7 |      325 |      324
| Split/Merge 8 |      545 |      531
| Split/Merge 9 |      986 |      984
| Split/Merge 10 |     1893 |     1790

### 2nd run

test_with_adj_FFT: 
Compare split FFT versus adjacent FFT setting

| Function (logn) | SplitFFT | AdjFFT |
|:-------------|----------:|-----------:|
| FFT 2 |      146 |      106
| FFT 3 |      162 |      169
| FFT 4 |      261 |      243
| FFT 5 |      457 |      388
| FFT 6 |      882 |      762
| FFT 7 |     1793 |     1613
| FFT 8 |     3767 |     3559
| FFT 9 |     7882 |     8057
| FFT 10 |    16734 |    17887

test_variant_fft: 
Compare my (loop separated) FFT versus my (without loop separateed) FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      109
| FFT 3 |      162 |      180
| FFT 4 |      261 |      277
| FFT 5 |      456 |      480
| FFT 6 |      883 |      925
| FFT 7 |     1793 |     1895
| FFT 8 |     3893 |     4715
| FFT 9 |     8535 |     9624
| FFT 10 |    18684 |    20197

test_with_ref_FFF: 
Compare my FFT versus reference FFT code

| Function (logn) | Fast FFT | Ref FFT |
|:-------------|----------:|-----------:|
| FFT 2 |      102 |      123
| FFT 3 |      162 |      181
| FFT 4 |      262 |      253
| FFT 5 |      457 |      400
| FFT 6 |      882 |      732
| FFT 7 |     1793 |     1511
| FFT 8 |     3893 |     4168
| FFT 9 |     8536 |     8367
| FFT 10 |    18684 |    17423

test_split_merge_function: 
Compare my split/merge FFT versus reference split/merge FFT code

| Function (logn) | Improved | Ref |
|:-------------|----------:|-----------:|
| Split/Merge 2 |       97 |      102
| Split/Merge 3 |       98 |      114
| Split/Merge 4 |      117 |      131
| Split/Merge 5 |      156 |      164
| Split/Merge 6 |      216 |      221
| Split/Merge 7 |      325 |      323
| Split/Merge 8 |      545 |      530
| Split/Merge 9 |      985 |      983
| Split/Merge 10 |     1892 |     1790