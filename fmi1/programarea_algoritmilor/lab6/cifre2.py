# cifre2 infoarena
with open('cifre2.in', 'r') as f:
    n , k = (f.readline().strip().split())
    n = int(n)
    k = int(k)

    numere = [0] * k
    # print(type(n), type(m)) 
    # print(n, k)
    a = sorted([int(x) for x in f.readline().split() if int(x) != 0])
    zeros = n - len(a)
    #print(a)
    a[k:k] = [0] * zeros
    #print(a)
    for i in range(n):
        numere[i%k] = numere[i%k] * 10 + a[i]

with open("cifre2.out", 'w') as f:
    f.write(str(sum(numere)) + '\n')