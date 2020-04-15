# found on https://www.spoj.com/problems/PERMUT2/
if __name__ == '__main__':
    while True:
        permutation_length = int(input())
        if permutation_length == 0:
            break
        *permutation, = map(int, input().split())
        ambiguous = True
        for perm_idx, val in enumerate(permutation, start=1):
            if permutation[val-1] != perm_idx:
                ambiguous = False
                break
        print(f'{"" if ambiguous else "not "}ambiguous')

