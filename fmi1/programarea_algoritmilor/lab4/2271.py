n = int(input())

l = input().split()
l = sorted([int(i) for i in l])

print(max(l[0]*l[1],l[-1]*l[-2]))
    