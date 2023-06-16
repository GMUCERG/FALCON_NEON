CC = clang
CFLAGS = -fomit-frame-pointer -W -Wall -O1 -Wextra -Wpedantic -Wshadow -Wundef


all: experiment

experiment: experiment.c
	$(CC) $(CFLAGS) -o $@ mtwister.c experiment.c
	./$@

clean:
	rm -f experiment


