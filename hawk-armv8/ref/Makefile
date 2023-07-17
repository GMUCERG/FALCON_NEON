# This Makefile compiles the implementation in this directory.
.POSIX:

CC = clang
CFLAGS = -W -Wall -Wshadow -O3
OBJ = build/common.o build/codec.o build/fft.o build/ffo.o build/fpr.o build/keygen.o build/ntt.o build/rng.o build/shake.o build/sign.o build/vrfy.o
M1_CYCLES = build/m1cycles.o
A72_CYCLES = build/hal.o
PROGS = bin/speed
HEAD = fpr.h inner.h

all: build bin

m1: bin/m1_speed
a72: bin/a72_speed

build:
	-mkdir -p build
bin:
	-mkdir -p bin

clean:
	-rm -f $(OBJ) build/hawk.o $(PROGS)

# Binaries:

# C
bin/m1_speed: tests/speed.c build/hawk.o $(OBJ) $(M1_CYCLES)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(M1_CYCLES) build/hawk.o tests/speed.c -DAPPLE_M1=1
	sudo ./$@
	
bin/a72_speed: tests/speed.c build/hawk.o $(OBJ) $(A72_CYCLES)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(A72_CYCLES) build/hawk.o build/hal.c tests/speed.c -DAPPLE_M1=0
	./$@

# Object files:
build/common.o: common.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/common.o common.c
build/codec.o: codec.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/codec.o codec.c
build/hal.o: hal.c
	$(CC) $(CFLAGS) -c -o $@ hal.c
build/m1cycles.o: m1cycles.c
	$(CC) $(CFLAGS) -c -o $@ m1cycles.c
build/fft.o: fft.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/fft.o fft.c
build/ffo.o: ffo.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/ffo.o ffo.c
build/fpr.o: fpr.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/fpr.o fpr.c
build/keygen.o: keygen.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/keygen.o keygen.c
build/ntt.o: ntt.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/ntt.o ntt.c
build/rng.o: rng.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/rng.o rng.c
build/shake.o: shake.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/shake.o shake.c
build/sign.o: sign.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/sign.o sign.c
build/vrfy.o: vrfy.c $(HEAD)
	$(CC) $(CFLAGS) -c -o build/vrfy.o vrfy.c

build/hawk.o: hawk.c hawk.h $(HEAD)
	$(CC) $(CFLAGS) -c -o build/hawk.o hawk.c

