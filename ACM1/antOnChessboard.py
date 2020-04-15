from math import sqrt

if __name__ == '__main__':
    while True:
        a = int(input())
        if a == 0:
            break
        sqr = sqrt(a)
        r = round(sqr)
        if r % 2 == 0:
            # print(f'col {r}')
            if sqr > r:
                # print("here")
                col = r +1
                row = a - r**2
            else:
                col = r
                row = r**2 - a + 1
        else:
            # print("row")
            if sqr > r :
                row = r + 1
                col = a - r **2
            else:
                row = r
                col = r**2 - a + 1

        print(f'{col} {row}')