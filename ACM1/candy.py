# found on https://www.spoj.com/problems/CANDY
if __name__ == '__main__':
    while True:
        packets = int(input())
        if packets == -1:
            break
        candy_packets = [int(input()) for _ in range(packets)]
        average = sum(candy_packets)/packets
        if not average.is_integer():
            print(-1)
        else:
            print(int(sum(x-average for x in candy_packets if x > average)))