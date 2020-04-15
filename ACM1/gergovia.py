# problem found on https://www.spoj.com/problems/GERGOVIA/
if __name__ == '__main__':
    while True:
        houses = int(input())
        if houses == 0:
            break
        *wine_delta, = map(int, input().split())
        cumsum = 0
        cumsumTo = []
        for delta in wine_delta:
            cumsumTo.append(cumsum)
            cumsum += delta
        print(sum(map(abs, cumsumTo)))

