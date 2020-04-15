if __name__ == '__main__':
    lines = int(input())
    for _ in range(lines):
        line = input()
        [a, b] = [int(''.join(reversed(num))) for num in line.split(' ')]
        res = str(a + b)

        print(int(''.join(reversed(res)).strip('0')))
