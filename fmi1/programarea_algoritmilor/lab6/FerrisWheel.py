# https://cses.fi/problemset/task/1090

def solve(arr, N, X):
    arr.sort()

    l, h = 0, N - 1

    ans = 0

    while h >= l:
        # Cate 2
        if arr[l] + arr[h] <= X:
            ans += 1
            l += 1
            h -= 1
        # Unul singur
        else:
            ans += 1
            h -= 1

    return ans

s = input().strip().split()

N = int(s[0])
X = int(s[1])

arr = [int(x) for x in input().strip().split()]


print(solve(arr, N, X))
