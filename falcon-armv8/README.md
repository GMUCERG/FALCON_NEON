# Falcon ARMv8

## Overall status

NEON implementation of Signature Generation and Verification. 
There is negligible speed up Key generation from FFT implementation.

## Reproduce Benchmark

If you don't have the hardware, inside each folder has `*.md` files,
which are the benchmarked results for AVX (Intel chip), Apple M1, Cortex-A72.

Feel free to reproduce results. 
Steps are described below. 

### Intel i7 1165G

#### AVX2 

Go to `ref-avx` (reference implementation of Falcon), then run:

- `make avx_59b`: to run speed benchmark for 59b message (as shown in paper)
- `make avx_ghz`: to run speed benchmark and frequency of the CPU
- `make avx`: to run default Falcon speed benchmark and my function benchmark

There is no need for `sudo`. 


### Apple M1

#### NEON 

Go to `neon` folder, `make build` first, then run: 

- `make m1_59b`: to run speed benchmark for 59b message (as shown in paper)
- `make m1_ghz`: to run speed benchmark and frequency of the CPU
- `make m1`: to run default Falcon speed benchmark and my function benchmark
- `make m1_test`: to run default Falcon test vectors
- `make kat`: to generate KAT file. 

To clean up, run `make clean`.

Note: You may need `sudo` password to perform benchmark (cycle count in Apple M1 requires `sudo`). 

#### REF

Go to `ref-avx` (reference implementation of Falcon), then run:

- `make m1_59b`: to run speed benchmark for 59b message (as shown in paper)
- `make m1_ghz`: to run speed benchmark and frequency of the CPU
- `make m1`: to run default Falcon speed benchmark and my function benchmark

To clean up, run `make clean`.
Note: You may need `sudo` password to perform benchmark (cycle count in Apple M1 requires `sudo`). 


### Cortex-A72

#### NEON

Go to `neon` folder, `make build` first, then run: 

- `make a72_59b`: to run speed benchmark for 59b message (as shown in paper)
- `make a72_ghz`: to run speed benchmark and frequency of the CPU
- `make a72`: to run default Falcon speed benchmark and my function benchmark
- `make a72_test`: to run default Falcon test vectors
- `make kat`: to generate KAT file. 

To clean up, run `make clean`.

There is no need for `sudo`. 

#### REF

Go to `ref-avx` (reference implementation of Falcon), then run:

- `make a72_59b`: to run speed benchmark for 59b message (as shown in paper)
- `make a72_ghz`: to run speed benchmark and frequency of the CPU
- `make a72`: to run default Falcon speed benchmark and my function benchmark

There is no need for `sudo`. 


## Compressed Twiddle Factor Implementation

See `small-fft-ref/fast_fft.c` file for my compressed FFT roots in  `C` code. 
