# Fatih Baskın
# 150210710

import numpy as np
from math import sqrt


PI = np.pi
OMEGA = PI / 4


def calc_k_n_exp(k: int, n: int) -> np.complex128:
    return np.exp(-1j * k * OMEGA * n)


def table_n_exp(k: int, n: int) -> list:
    return [calc_k_n_exp(k, i) for i in range(n)]


def table_k_exp(k: int, n: int) -> list:
    return [table_n_exp(i, n) for i in range(k)]


def dft_coefficients(x: np.array, n: int) -> np.array:
    table = table_k_exp(n, n)
    return np.array([sum([x[j] * table[i][j] for j in range(n)]) for i in range(n)])/n


if __name__ == "__main__":
    n = 8
    k = 8
    table_ = table_k_exp(k, n)

    for i in range(k):
        print(f"Table for k = {i}", end=": ")
        for j in range(n):
            print(f"n = {j} {table_[i][j]:.3f}", end="\t")
        print("\n")

    x_1 = np.array([0, 1/sqrt(2), 1, 1/sqrt(2), 0, -1/sqrt(2), -1, -1/sqrt(2)])
    x_2 = np.array([1, 1, 1, -1, -1, -1, 1/2, 1/2])
    x_3 = np.array([0, 1/3, 2/3, 1, 0, -1, -2/3, -1/3])
    x_4 = np.array([-1/sqrt(2), 0, 1/sqrt(2), 1, 1/sqrt(2), 0, -1/sqrt(2), -1])

    print(f"\nDFT Coefficients for x_1: ", end="")
    for i in dft_coefficients(x_1, n):
        print(f"{i:.3f}", end=" ")
    print()

    print(f"DFT Coefficients for x_2: ", end="")
    for i in dft_coefficients(x_2, n):
        print(f"{i:.3f}", end=" ")

    print(f"\nDFT Coefficients for x_3: ", end="")
    for i in dft_coefficients(x_3, n):
        print(f"{i:.3f}", end=" ")

    print(f"\nDFT Coefficients for x_4: ", end="")
    for i in dft_coefficients(x_4, n):
        print(f"{i:.3f}", end=" ")

    print()
