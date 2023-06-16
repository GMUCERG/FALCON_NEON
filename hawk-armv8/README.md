# Hawk ARMv8

## Reproduce Benchmark

If you don't have the hardware, inside each folder has `*.md` files,
which are the benchmarked results for AVX (Intel chip), Apple M1, Cortex-A72.

Feel free to reproduce results. 
Steps are described below. 


### Apple M1

#### NEON 

Go to `neon` folder, `make build` first, then run: 

- `make m1`: to run default Hawk speed benchmark

To clean up, run `make clean`.

Note: You may need `sudo` password to perform benchmark (cycle count in Apple M1 requires `sudo`). 


### Cortex-A72

#### NEON

Go to `neon` folder, `make build` first, then run: 

- `make a72`: to run default Hawk speed benchmark

To clean up, run `make clean`.

There is no need for `sudo`. 

## Compressed Twiddle Factor Implementation

See `fft.c` file for my compressed FFT roots in  `C` code. 
