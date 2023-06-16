# Benchmark

Disable Spectre and Meltdown. I let turbo boost on. 
Just want to see maximize performance comparison. 

```
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   39 bits physical, 48 bits virtual
CPU(s):                          8
On-line CPU(s) list:             0-7
Thread(s) per core:              2
Core(s) per socket:              4
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           140
Model name:                      11th Gen Intel(R) Core(TM) i7-1165G7 @ 2.80GHz
Stepping:                        1
CPU MHz:                         2800.000
CPU max MHz:                     4700.0000
CPU min MHz:                     400.0000
BogoMIPS:                        5606.40
Virtualization:                  VT-x
L1d cache:                       192 KiB
L1i cache:                       128 KiB
L2 cache:                        5 MiB
L3 cache:                        12 MiB
NUMA node0 CPU(s):               0-7
Vulnerability Itlb multihit:     Not affected
Vulnerability L1tf:              Not affected
Vulnerability Mds:               Not affected
Vulnerability Meltdown:          Not affected
Vulnerability Spec store bypass: Vulnerable
Vulnerability Spectre v1:        Vulnerable: __user pointer sanitization and usercopy barriers only; n
                                 o swapgs barriers
Vulnerability Spectre v2:        Vulnerable, IBPB: disabled, STIBP: disabled
Vulnerability Srbds:             Not affected
Vulnerability Tsx async abort:   Not affected
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse
                                 36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb
                                  rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopo
                                 logy nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64
                                  monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1
                                  sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdr
                                 and lahf_lm abm 3dnowprefetch cpuid_fault epb cat_l2 invpcid_single c
                                 dp_l2 ssbd ibrs ibpb stibp ibrs_enhanced tpr_shadow vnmi flexpriority
                                  ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid
                                  rdt_a avx512f avx512dq rdseed adx smap avx512ifma clflushopt clwb in
                                 tel_pt avx512cd sha_ni avx512bw avx512vl xsaveopt xsavec xgetbv1 xsav
                                 es split_lock_detect dtherm ida arat pln pts hwp hwp_notify hwp_act_w
                                 indow hwp_epp hwp_pkg_req avx512vbmi umip pku ospke avx512_vbmi2 gfni
                                  vaes vpclmulqdq avx512_vnni avx512_bitalg avx512_vpopcntdq rdpid mov
                                 diri movdir64b fsrm avx512_vp2intersect md_clear flush_l1d arch_capab
                                 ilities
```


## Falcon

### AVX2 disable

#### 4th run 
|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 13719.24 |   176.19 |   583.35 |   613.02 |   355.99 |   385.64 |    48.86 |    81.75 |
|1024: | 40633.90 |   355.29 |  1172.75 |  1231.24 |   706.90 |   765.80 |   100.33 |   163.13 |


|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: |  4894.17 |    62.88 |   208.12 |   218.71 |   127.02 |   137.59 |    17.45 |    29.18 |
|1024: | 14495.57 |   126.76 |   418.38 |   439.25 |   252.20 |   273.21 |    35.81 |    58.21 |


#### Frequency

`./avx_speed_ghz`

|degree|  kg(Ghz)|   ek(Ghz)|   sd(Ghz)|  sdc(Ghz)|   st(Ghz)|  stc(Ghz)|   vv(Ghz)|  vvc(Ghz)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
|  512:|      2.80|      2.80|      2.80|      2.80|      2.80|      2.81|      2.80|      2.80|
| 1024:|      2.82|      2.80|      2.80|      2.80|      2.81|      2.81|      2.80|      2.80|


#### FFT 

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |       63 |       60
| FFT 1 |       63 |       16
| FFT 2 |       25 |       29
| FFT 3 |       50 |       53
| FFT 4 |       98 |      103
| FFT 5 |      192 |      206
| FFT 6 |      405 |      418
| FFT 7 |      787 |      873
| FFT 8 |     1640 |     1798
| FFT 9 |     3486 |     3790
| FFT 10 |     7341 |     7961

#### NTT

| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |     8468 |     9117
| NTT 10 |    17897 |    19150


### AVX2 enable

#### 4th Run 
`taskset -c 0 ./avx_speed`


|degree|  kg(kc)|   ek(kc)|  sd(kc)| sdc(kc)|  st(kc)| stc(kc)|  vv(kc)| vvc(kc)|
| ---- | ------ |  ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: | 13568.03 |   167.04 |   427.13 |   456.68 |   220.47 |   250.51 |    50.05 |    81.52 |
|1024: | 40305.86 |   342.61 |   862.04 |   919.19 |   439.32 |   497.52 |   101.83 |   163.25 |

|degree|  kg(us)|  ek(us)|  sd(us)| sdc(us)|  st(us)| stc(us)|  vv(us)| vvc(us)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 512: |  4840.23 |    59.62 |   152.39 |   162.93 |    78.67 |    89.39 |    17.87 |    29.10 |
|1024: | 14378.55 |   122.24 |   307.54 |   327.93 |   156.74 |   177.50 |    36.34 |    58.26 |


#### Frequency

`taskset -c 0 ./avx_speed_ghz`

|degree|  kg(Ghz)|   ek(Ghz)|   sd(Ghz)|  sdc(Ghz)|   st(Ghz)|  stc(Ghz)|   vv(Ghz)|  vvc(Ghz)|
| ---- |  ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
|  512:|      2.90|      2.80|      2.80|      2.80|      2.80|      2.80|      2.83|      2.80|
| 1024:|      2.80|      2.80|      2.80|      2.80|      2.80|      2.80|      2.83|      2.81|

#### FFT 

| FFT | Foward FFT | Inverse FFT
|:-------------|----------:|-----------:|
| FFT 0 |       63 |       61
| FFT 1 |       63 |       16
| FFT 2 |       24 |       27
| FFT 3 |       50 |       52
| FFT 4 |       73 |       77
| FFT 5 |      130 |      156
| FFT 6 |      270 |      273
| FFT 7 |      481 |      499
| FFT 8 |      966 |     1024
| FFT 9 |     2040 |     2138
| FFT 10 |     4370 |     4572

#### NTT

| NTT | Foward NTT | Inverse NTT
|:-------------|----------:|-----------:|
| NTT 9 |     8481 |     9084
| NTT 10 |    17944 |    19108



## Dilithium

## AVX Enable

### Dilithium2 

```
taskset -c 0 ./test_speed2
Keypair:
median: 49092 cycles/ticks
average: 49482 cycles/ticks

Sign:
median: 113531 cycles/ticks
average: 144546 cycles/ticks

Verify:
median: 52746 cycles/ticks
average: 52870 cycles/ticks
```

### Dilthium3 

```
taskset -c 0 ./test_speed3
Keypair:
median: 84735 cycles/ticks
average: 85202 cycles/ticks

Sign:
median: 186288 cycles/ticks
average: 232221 cycles/ticks

Verify:
median: 85317 cycles/ticks
average: 85735 cycles/ticks
```

### Dilithium5

```
taskset -c 0 ./test_speed5
Keypair:
median: 132123 cycles/ticks
average: 134132 cycles/ticks

Sign:
median: 230714 cycles/ticks
average: 275100 cycles/ticks

Verify:
median: 133260 cycles/ticks
average: 133893 cycles/ticks
```