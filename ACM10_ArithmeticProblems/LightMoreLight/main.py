# problem found at https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=416&page=show_problem&problem=1051
from math import sqrt

if __name__ == '__main__':
    num = int(input())
    while num != 0:
        print("yes" if sqrt(num).is_integer() else "no")
        num = int(input())


