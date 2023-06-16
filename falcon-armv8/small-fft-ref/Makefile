# This Makefile compiles the implementation in this directory along with
# the known answer tests generator located in the
# ../../../KAT/generator/ directory. The output is an executable program
# in the build/ subdirectory, whose name starts with 'kat', followed by
# the implementation name (e.g. 'kat512int' for the 'falcon512int'
# implementation). This program, when executed, generates the .req and
# .rsp files in the expected NIST format.

.POSIX:

CC = clang
CFLAGS = -w -Wall -Wextra -Wpedantic -Wshadow -Wundef -O3
LD = clang
LDFLAGS = -Os
FFTFLAGS = -Os
LIBS = 

OBJ1 = build/codec.o build/poly_fft.o build/common.o build/fft.o build/keygen.o build/rng.o build/shake.o build/sign.o build/vrfy.o

OBJ2a = build/nist_512.o 
OBJ2 = build/PQCgenKAT_sign_512.o build/katrng.o

OBJ3a = build/nist_1024.o 
OBJ3 = build/PQCgenKAT_sign_1024.o build/katrng.o

HEAD1 = api.h fpr.h inner.h
HEAD2 = api.h katrng.h

all: build build/kat512fpu build/kat1024fpu

build:
	-mkdir build

clean:
	-rm -f test_fft_a72 test_fft_m1 build/kat512fpu build/kat1024fpu build/*.o

build/kat512fpu: $(OBJ1) $(OBJ2) $(OBJ2a)
	$(LD) $(LDFLAGS) -o build/kat512fpu $(OBJ1) $(OBJ2a) $(OBJ2) $(LIBS)
	./$@

build/kat1024fpu: $(OBJ1) $(OBJ3) $(OBJ3a)
	$(LD) $(LDFLAGS) -o build/kat1024fpu $(OBJ1) $(OBJ3a) $(OBJ3) $(LIBS)
	./$@

test_fft_a72: ref_fft.c build/test_fft.o test_fft.c hal.c
	$(LD) $(LDFLAGS) -o $@ hal.c      ref_fft.c build/test_fft.o -DAPPLE_M1=0 test_fft.c

test_fft_m1:  ref_fft.c build/test_fft.o test_fft.c m1cycles.c
	$(LD) $(LDFLAGS) -o $@ m1cycles.c ref_fft.c build/test_fft.o -DAPPLE_M1=1 test_fft.c

build/codec.o: codec.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/codec.o codec.c

build/common.o: common.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/common.o common.c

build/poly_fft.o: poly_fft.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o $@ poly_fft.c

build/fft.o: fast_fft.c $(HEAD1)
	$(CC) -w -Wall -Wextra -Wpedantic -Wshadow -Wundef -O1 -c -o $@ fast_fft.c

build/test_fft.o: fast_fft.c $(HEAD1)
	$(CC) -w -Wall -Wextra -Wpedantic -Wshadow -Wundef $(FFTFLAGS) -c -o $@ -DTEST_FFT=1 fast_fft.c

build/fft_consts.o: fft_consts.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o $@ fft_consts.c

build/keygen.o: keygen.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/keygen.o keygen.c

build/nist_512.o: nist_512.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o $@ nist_512.c

build/nist_1024.o: nist_1024.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o $@ nist_1024.c

build/rng.o: rng.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/rng.o rng.c

build/shake.o: shake.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/shake.o shake.c

build/sign.o: sign.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/sign.o sign.c

build/vrfy.o: vrfy.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o build/vrfy.o vrfy.c

build/PQCgenKAT_sign_512.o: PQCgenKAT_sign_512.c $(HEAD2)
	$(CC) $(CFLAGS) -I . -DALGNAME=falcon512fpu -c -o $@ PQCgenKAT_sign_512.c

build/PQCgenKAT_sign_1024.o: PQCgenKAT_sign_1024.c $(HEAD2)
	$(CC) $(CFLAGS) -I . -DALGNAME=falcon1024fpu -c -o $@ PQCgenKAT_sign_1024.c

build/katrng.o: katrng.c $(HEAD2)
	$(CC) $(CFLAGS) -I . -c -o build/katrng.o katrng.c 
