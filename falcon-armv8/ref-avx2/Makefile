# Build script for the Falcon implementation.
#
# ==========================(LICENSE BEGIN)============================
#
# Copyright (c) 2017-2019  Falcon Project
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# ===========================(LICENSE END)=============================
#
# @author   Thomas Pornin <thomas.pornin@nccgroup.com>

.POSIX:

# =====================================================================
#
# Configurable options:
#   CC       C compiler; GCC or Clang are fine; MSVC (2015+) works too.
#   CFLAGS   Compilation flags:
#             * Optimization level -O2 or higher is recommended
#            See config.h for some possible configuration macros.
#   LD       Linker; normally the same command as the compiler.
#   LDFLAGS  Linker options, not counting the extra libs.
#   LIBS     Extra libraries for linking:
#             * If using the native FPU, test_falcon and application
#               code that calls this library may need: -lm
#               (normally not needed on x86, both 32-bit and 64-bit)

CC = clang
CFLAGS = -O3 -Wall -Wextra -Wshadow -Wundef #-pg -fno-pie
LD = clang -O3 -Wall -Wextra -Wshadow -Wundef #-pg -fno-pie
LDFLAGS = #-pg -no-pie
LIBS =

# =====================================================================

OBJ = codec.o common.o falcon.o fft.o my_fft.o fpr.o keygen.o rng.o shake.o sign.o vrfy.o katrng.o

all: test_falcon
a72: a72_speed a72_bench
a72_59b: a72_speed_59b_512 a72_speed_59b_1024
m1: m1_speed m1_bench
m1_59b: m1_speed_59b_512 m1_speed_59b_1024
avx: avx_speed avx_bench
avx_59b: avx2_speed_59b_512 avx2_speed_59b_1024
a72_ghz: a72_speed_ghz
m1_ghz: m1_speed_ghz
avx_ghz: avx_speed_ghz

clean:
	-rm -f $(OBJ) test_falcon test_falcon.o speed speed.o
	-rm -f bench_a72.o hal.o speed_a72.o speed_a72_ghz.o
	-rm -f bench_m1.o m1cycles.o speed_m1.o speed_m1_ghz.o
	-rm -f a72_bench a72_speed a72_speed_ghz
	-rm -f a72_speed_59b_512 a72_speed_59b_1024
	-rm -f m1_bench m1_speed m1_speed_ghz
	-rm -f m1_speed_59b_512 m1_speed_59b_1024
	-rm -f avx_bench avx_speed avx_speed_ghz
	-rm -f avx2_speed_59b_512 avx2_speed_59b_1024
	-rm -f *.o

test_falcon: test_falcon.o $(OBJ)
	$(LD) $(LDFLAGS) -o test_falcon test_falcon.o $(OBJ) $(LIBS)

a72_speed: hal.o speed_a72.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ hal.o speed_a72.o $(OBJ) $(LIBS)
	./$@

a72_bench: hal.o bench_a72.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ hal.o bench_a72.o $(OBJ) $(LIBS)
	./$@

a72_speed_ghz: hal.o speed_a72_ghz.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ hal.o speed_a72_ghz.o $(OBJ) $(LIBS)
	./$@

a72_speed_59b_512: hal.o nist_512.o speed_a72_59b_512.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ hal.o nist_512.o speed_a72_59b_512.o $(OBJ) $(LIBS)
	./$@

a72_speed_59b_1024: hal.o nist_1024.o speed_a72_59b_1024.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ hal.o nist_1024.o speed_a72_59b_1024.o $(OBJ) $(LIBS)
	./$@

m1_speed: m1cycles.o speed_m1.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ m1cycles.o speed_m1.o $(OBJ)
	sudo ./$@

m1_bench: m1cycles.o bench_m1.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ m1cycles.o bench_m1.o $(OBJ) $(LIBS)
	sudo ./$@

m1_speed_ghz: m1cycles.o speed_m1_ghz.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ m1cycles.o speed_m1_ghz.o $(OBJ)
	sudo ./$@

m1_speed_59b_512: m1cycles.o nist_512.o speed_m1_59b_512.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ m1cycles.o nist_512.o speed_m1_59b_512.o $(OBJ) $(LIBS)
	sudo ./$@

m1_speed_59b_1024: m1cycles.o nist_1024.o speed_m1_59b_1024.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ m1cycles.o nist_1024.o speed_m1_59b_1024.o $(OBJ) $(LIBS)
	sudo ./$@

avx_speed: cpucycles.o speed_avx.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ cpucycles.o speed_avx.o $(OBJ)
	echo "You have to enable FALCON_AVX2 in 'config.h' to get correct result"
	./$@

avx_speed_59b_512: cpucycles.o speed_avx_59b_512.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ cpucycles.o speed_avx_59b_512.o $(OBJ)
	echo "You have to enable FALCON_AVX2 in 'config.h' to get correct result"
	./$@

avx_speed_59b_1024: cpucycles.o speed_avx_59b_1024.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ cpucycles.o speed_avx_59b_1024.o $(OBJ)
	echo "You have to enable FALCON_AVX2 in 'config.h' to get correct result"
	./$@

avx_bench: cpucycles.o bench_avx.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ cpucycles.o bench_avx.o $(OBJ) $(LIBS)
	echo "You have to enable FALCON_AVX2 in 'config.h' to get correct result"
	./$@

avx_speed_ghz: cpucycles.o speed_avx_ghz.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ cpucycles.o speed_avx_ghz.o $(OBJ)
	echo "You have to enable FALCON_AVX2 in 'config.h' to get correct result"
	./$@

codec.o: codec.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o codec.o codec.c

m1cycles.o: m1cycles.c m1cycles.h
	$(CC) $(CFLAGS) -c -o $@ m1cycles.c

hal.o: hal.c hal.h
	$(CC) $(CFLAGS) -c -o $@ hal.c

cpucycles.o: cpucycles.c cpucycles.h
	$(CC) $(CFLAGS) -c -o $@ cpucycles.c

common.o: common.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o common.o common.c

falcon.o: falcon.c falcon.h config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o falcon.o falcon.c

my_fft.o: my_fft.c config.h inner.h fpr.h
	$(CC) -O1 -mtune=native -c -o $@ my_fft.c

fft.o: fft.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o fft.o fft.c

fpr.o: fpr.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o fpr.o fpr.c

keygen.o: keygen.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o keygen.o keygen.c

rng.o: rng.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o rng.o rng.c

shake.o: shake.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o shake.o shake.c

sign.o: sign.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o sign.o sign.c

katrng.o: katrng.c katrng.h
	$(CC) $(CFLAGS) -c -o $@ katrng.c

nist_512.o: nist_512.c api_512.h
	$(CC) $(CFLAGS) -c -o $@ nist_512.c

nist_1024.o: nist_1024.c api_1024.h
	$(CC) $(CFLAGS) -c -o $@ nist_1024.c

speed_a72.o: speed.c falcon.h
	$(CC) $(CFLAGS) -DAPPLE_M1=0 -DAVX2=0 -c -o $@ speed.c

speed_a72_59b_512.o: speed_59b_512.c falcon.h api_512.h
	$(CC) $(CFLAGS) -DAPPLE_M1=0 -DAVX2=0 -c -o $@ speed_59b_512.c

speed_a72_59b_1024.o: speed_59b_1024.c falcon.h api_1024.h
	$(CC) $(CFLAGS) -DAPPLE_M1=0 -DAVX2=0 -c -o $@ speed_59b_1024.c

speed_m1.o: speed.c falcon.h
	$(CC) $(CFLAGS) -DAPPLE_M1=1 -DBENCH_CYCLES=1 -DAVX2=0 -c -o $@ speed.c

speed_m1_59b_512.o: speed_59b_512.c falcon.h api_512.h
	$(CC) $(CFLAGS) -DAPPLE_M1=1 -DBENCH_CYCLES=1 -DAVX2=0 -c -o $@ speed_59b_512.c

speed_m1_59b_1024.o: speed_59b_1024.c falcon.h api_1024.h
	$(CC) $(CFLAGS) -DAPPLE_M1=1 -DBENCH_CYCLES=1 -DAVX2=0 -c -o $@ speed_59b_1024.c

speed_avx.o: speed.c falcon.h
	$(CC) $(CFLAGS) -DAVX2=1 -c -o $@ speed.c

speed_avx_59b_512.o: speed_59b_512.c falcon.h api_512.h
	$(CC) $(CFLAGS) -DAVX2=1 -c -o $@ speed_59b_512.c

speed_avx_59b_1024.o: speed_59b_1024.c falcon.h api_1024.h
	$(CC) $(CFLAGS) -DAVX2=1 -c -o $@ speed_59b_1024.c

speed_a72_ghz.o: speed.c falcon.h
	$(CC) $(CFLAGS) -DAPPLE_M1=0 -c -o $@ speed_freq.c

speed_m1_ghz.o: speed.c falcon.h
	$(CC) $(CFLAGS) -DAPPLE_M1=1 -DBENCH_CYCLES=1 -c -o $@ speed_freq.c

speed_avx_ghz.o: speed.c falcon.h
	$(CC) $(CFLAGS) -DAVX2=1 -c -o $@ speed_freq.c

bench_a72.o: bench.c $(OBJ)
	$(CC) $(CFLAGS) -DAPPLE_M1=0 -DBENCH_CYCLES=1 -c -o $@ bench.c

bench_m1.o: bench.c $(OBJ)
	$(CC) $(CFLAGS) -DAPPLE_M1=1 -DBENCH_CYCLES=1 -c -o $@ bench.c

bench_avx.o: bench.c $(OBJ)
	$(CC) $(CFLAGS) -DAVX2=1 -DBENCH_CYCLES=1 -c -o $@ bench.c

test_falcon.o: test_falcon.c falcon.h config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o test_falcon.o test_falcon.c

vrfy.o: vrfy.c config.h inner.h fpr.h
	$(CC) $(CFLAGS) -c -o vrfy.o vrfy.c
