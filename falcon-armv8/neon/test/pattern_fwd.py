import sys
from ntt_br_1024 import *
from ntt_br_512 import *

FALCON_Q = 12289
FALCON_QINV = -12287
FALCON_N = 1024
FALCON_PADDING = 0


assert FALCON_Q * FALCON_QINV % pow(2, 16) == 1

assert len(ntt512_br) == 512
assert len(ntt512_qinv_br) == 512
assert len(intt512_br) == 512
assert len(intt512_qinv_br) == 512

assert len(ntt1024_br) == 1024
assert len(ntt1024_qinv_br) == 1024
assert len(intt1024_br) == 1024
assert len(intt1024_qinv_br) == 1024


def print_table(a, string):
    print("extern const int16_t %s[] = {" % string)
    for i in range(0, len(a), 8):
        for j in range(8):
            if a[i + j] == FALCON_PADDING:
                print("{:>8}".format("PADDING"), end=", ")
            else:
                print("{:8d}".format(a[i + j]), end=", ")
        print()
    print("}; // %s" % len(a), end="\n\n")


def dup(a, x):
    b = []
    for i in a:
        for j in range(x):
            b.append(i)
    return b


def gen_table97_ntt(zetas, n):
    if n == 1024:
        bar = [0, 1, 2]
    elif n == 512:
        bar = [0, 1]

    bar = list(map(lambda x: 1 << x, bar))

    final_zetas = [0]

    # Layer 9 = Distance 512
    final_zetas += zetas[bar[0] : bar[0] + 1]

    # Layer 8 = Distance 256
    final_zetas += zetas[bar[1] : bar[1] + 2]

    if n == 1024:
        # Layer 7 = Distance 128
        final_zetas += zetas[bar[2] : bar[2] + 4]
    else:
        # Padding
        final_zetas += [0] * 4

    # print(final_zetas, len(final_zetas))
    assert len(final_zetas) % 8 == 0

    return final_zetas


# 1024
# 512
def gen_table60_ntt(zetas, n):
    final_zetas = []

    if n == 1024:
        bar = [3, 4, 5, 6, 7, 8, 9]
    elif n == 512:
        bar = [2, 3, 4, 5, 6, 7, 8]

    bar = list(map(lambda x: 1 << x, bar))

    for iter in range(0, n, 128):

        # Layer 6 = Distance 64
        pool = zetas[bar[0] : bar[0] + 1]

        block0 = pool

        final_zetas += block0

        bar[0] += 1

        # Layer 5 = Distance 32
        pool = zetas[bar[1] : bar[1] + 2]

        block1 = pool

        final_zetas += block1

        bar[1] += 2

        # Layer 4 = Distance 16
        pool = zetas[bar[2] : bar[2] + 4]

        block2 = pool

        final_zetas += block2

        bar[2] += 4

        # Layer 3 = Distance 8
        pool = zetas[bar[3] : bar[3] + 8]

        block3 = pool

        final_zetas += block3

        bar[3] += 8

        # Padding
        final_zetas += [0]

        assert len(final_zetas) % 8 == 0

        # Layer 2 = Distance 4
        pool = zetas[bar[4] : bar[4] + 16]

        block4 = pool[0::2]
        block5 = pool[1::2]

        block4 = dup(block4, 4)
        block5 = dup(block5, 4)

        final_zetas += block4
        final_zetas += block5

        bar[4] += 16

        # Layer 1 = Distance 2
        pool = zetas[bar[5] : bar[5] + 32]

        block5 = pool

        final_zetas += block5

        bar[5] += 32

        # Layer 0 = Distance 1
        pool = zetas[bar[6] : bar[6] + 64]

        block6 = pool[0::2]
        block7 = pool[1::2]

        final_zetas += block6
        final_zetas += block7

        bar[6] += 64

    assert len(final_zetas) % 8 == 0

    return final_zetas


table_ntt1024_br = gen_table97_ntt(ntt1024_br, 1024)
table_ntt1024_br += gen_table60_ntt(ntt1024_br, 1024)

table_ntt1024_qinv_br = gen_table97_ntt(ntt1024_qinv_br, 1024)
table_ntt1024_qinv_br += gen_table60_ntt(ntt1024_qinv_br, 1024)

table_ntt512_br = gen_table97_ntt(ntt512_br, 512)
table_ntt512_br += gen_table60_ntt(ntt512_br, 512)

table_ntt512_qinv_br = gen_table97_ntt(ntt512_qinv_br, 512)
table_ntt512_qinv_br += gen_table60_ntt(ntt512_qinv_br, 512)

if __name__ == "__main__":

    if len(sys.argv) == 2:
        N = int(sys.argv[1])
        if N == 1024:
            print_table(table_ntt1024_br, "ntt_br")
            print_table(table_ntt1024_qinv_br, "ntt_qinv_br")
        elif N == 512:
            print_table(table_ntt512_br, "ntt_br")
            print_table(table_ntt512_qinv_br, "ntt_qinv_br")
    else:
        print("./patter_fwd 512 or ./patter_fwd 1024")
