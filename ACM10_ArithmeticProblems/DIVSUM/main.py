# problem found at https://www.spoj.com/problems/DIVSUM/
from math import sqrt


def divisor_sum(i):
    if i == 1:
        return 0
    else:
        divisor_sum = 1
        for potential_div in range(2, int(sqrt(i) + 1)):
            if i % potential_div == 0:
                divisor_sum += potential_div
                other_div = i // potential_div
                if other_div != potential_div:
                    divisor_sum += other_div
        return divisor_sum


if __name__ == '__main__':
    test_cases = int(input())
    for _ in range(test_cases):
        number = int(input())
        print(divisor_sum(number))
