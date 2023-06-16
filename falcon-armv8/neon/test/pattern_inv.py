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


def compute_bar(x, n):
    ret = 0
    for i in range(x):
        ret += n // (1 << (i + 1))
    return ret


def gen_table06_invntt(zetas, n):
    zetas = list(map(lambda x: -x, zetas[::-1]))

    bar = [0, 1, 2, 3, 4, 5, 6]

    bar = list(map(lambda x: compute_bar(x, n), bar))

    final_zetas = []

    for iter in range(0, n, 128):
        # Layer 0 = Distance 1
        pool = zetas[bar[0] : bar[0] + 64]
        block1 = pool[0::2]
        block2 = pool[1::2]

        final_zetas += block1
        final_zetas += block2

        bar[0] += 64

        # Layer 1 = Distance 2
        pool = zetas[bar[1] : bar[1] + 32]
        block3 = pool

        final_zetas += block3

        bar[1] += 32

        # Layer 2 = Distance 4
        pool = zetas[bar[2] : bar[2] + 16]
        block5 = pool[0::2]
        block6 = pool[1::2]

        block5 = dup(block5, 4)
        block6 = dup(block6, 4)

        final_zetas += block5
        final_zetas += block6

        bar[2] += 16

        # Layer 3 = Distance 8
        pool = zetas[bar[3] : bar[3] + 8]
        block7 = pool

        final_zetas += block7
        bar[3] += 8

        # Layer 4 = Distance 16
        pool = zetas[bar[4] : bar[4] + 4]

        block8 = pool

        final_zetas += block8
        bar[4] += 4

        # Layer 5 = Distance 32
        pool = zetas[bar[5] : bar[5] + 2]

        block9 = pool

        final_zetas += block9
        bar[5] += 2

        # Layer 6 = Distance 64
        pool = zetas[bar[6] : bar[6] + 1]

        block10 = pool

        final_zetas += block10
        bar[6] += 1

        final_zetas += [0]

        assert len(final_zetas) % 8 == 0

    return final_zetas


def gen_table79_invntt(zetas, n, twisted=None):
    zetas = list(map(lambda x: -x, zetas[::-1]))

    n_inv = pow(n, -1, FALCON_Q)
    n_inv_twisted = (n_inv << 16) // FALCON_Q // 2

    if n == 1024:
        bar = [7, 8, 9]
    elif n == 512:
        bar = [7, 8]

    bar = list(map(lambda x: compute_bar(x, n), bar))

    final_zetas = []

    # Layer 7 = Distance 128
    if n == 1024:
        final_zetas += zetas[bar[0] : bar[0] + 4]
    elif n == 512:
        final_zetas += zetas[bar[0] : bar[0] + 2]

    # Layer 8 = Distance 256
    if n == 1024:
        final_zetas += zetas[bar[1] : bar[1] + 2]
    elif n == 512:
        if twisted:
            final_zetas += list(
                map(lambda x: x * n_inv_twisted % FALCON_Q, zetas[bar[1] : bar[1] + 1])
            )
        else:
            final_zetas += list(
                map(lambda x: x * n_inv % FALCON_Q, zetas[bar[1] : bar[1] + 1])
            )

    # Layer 9 = Distance 512, Embed N^-1 to the last layer for N = 1024
    # print("{} -> {}".format(bar9, bar9 + 1))
    if n == 1024:
        if twisted:
            final_zetas += list(
                map(lambda x: x * n_inv_twisted % FALCON_Q, zetas[bar[2] : bar[2] + 1])
            )
        else:
            final_zetas += list(
                map(lambda x: x * n_inv % FALCON_Q, zetas[bar[2] : bar[2] + 1])
            )
    elif n == 512:
        pass

    # N^-1
    if twisted:
        final_zetas += [n_inv_twisted]
    else:
        final_zetas += [n_inv]

    final_zetas += ((len(final_zetas) % 8)) * [0]

    assert len(final_zetas) % 8 == 0

    return final_zetas


# Input table already in Montgomery domain, thus `mont = False`
table_invntt512_br = gen_table06_invntt(ntt512_br, 512)
table_invntt512_br += gen_table79_invntt(ntt512_br, 512)

table_invntt512_qinv_br = gen_table06_invntt(ntt512_qinv_br, 512)
table_invntt512_qinv_br += gen_table79_invntt(ntt512_qinv_br, 512)


table_invntt1024_br = gen_table06_invntt(ntt1024_br, 1024)
table_invntt1024_br += gen_table79_invntt(ntt1024_br, 1024)

table_invntt1024_qinv_br = gen_table06_invntt(ntt1024_qinv_br, 1024)
table_invntt1024_qinv_br += gen_table79_invntt(ntt1024_qinv_br, 1024)


if __name__ == "__main__":

    if len(sys.argv) == 2:
        N = int(sys.argv[1])
        if N == 1024:
            print_table(table_invntt1024_br, "invntt_br")
            print_table(table_invntt1024_qinv_br, "invntt_qinv_br")
        elif N == 512:
            print_table(table_invntt512_br, "invntt_br")
            print_table(table_invntt512_qinv_br, "invntt_qinv_br")
    else:
        print("./patter_inv 512 or ./patter_inv 1024")
