# problem found at https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=196&page=show_problem&problem=1731
from math import factorial

def nCr(n: int, r: int):
    return factorial(n) // factorial(r) // factorial(n-r)

if __name__ == '__main__':
    a, b = map(int, input().split())
    case = 1
    while (a, b) != (0, 0):
        # print(f'Case {case}: {nCr(a, 2) * nCr(b, 2)}')
        print(f'Case {case}: {( ( a*(a-1) ) // 2 ) * ( ( b * (b-1) ) // 2 )}')
        a, b = map(int, input().split())
        case += 1
