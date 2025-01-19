# Subiectul 1

# f = open("numere.in", 'r')
# g = open("numere.out", 'w')
# d = dict()
# for linie in f:
#     l = list(int(x) for x in linie.split())
#     s = sum(l)

#     if s not in d:
#         d[s] = list()
#     d[s].append(l)

# k = sorted(d.keys())
# for key in k:
#     g.write(f"Suma {key}:\n")
#     #print(d[key])
#     d[key] = sorted(d[key], key=lambda x: -len(x))
#     for lst in d[key]:
#         g.write(" ".join(str(x) for x in lst) + "\n")
#     #print(d[key])
# print(d)


# # Subiectul 2

# def citire_matrice(filename):
#     f = open(filename,'r')
#     n = int(f.readline())
#     cnt = 0
#     nr = [int(x) for x in f.readline().split()]
#     l = [[0 for i in range(n)] for j in range(n)]
#     for i in range(n):
#         for j in range(n):
#             l[i][j] = nr[cnt]
#             cnt +=1
#     return l


# def duplicare(m,*indexs):
#     res = []
#     n = len(m)
#     for i in range(n):
#         res.append(m[i].copy())
#         if i in indexs:
#             res.append(m[i].copy())
#     return res

# def pctc():
#     m = (citire_matrice("matrice.in"))
#     m1 = duplicare(m,0,1)
#     m1[0][0] += 1
#     n = len(m1)
#     n1 = len(m1[0])
#     for i in range(n):
#         for j in range(n1):
#             print(m1[i][j], end=" ")
#         print()

# pctc()

# Subiectul 3

f = open("drumuri.in",'r')
d = dict()
for linie in f:
    linie = linie.strip()
    oras1 = linie.split('-')[0].strip()
    rest = linie.split('-')[1].strip().split()
    oras2 = ' '.join(rest[:-2])
    dist = int(rest[-2])
    calitate = int(rest[-1])
    if oras1 not in d:
        d[oras1] = {oras2:[dist,calitate]}
    else:
        d[oras1][oras2] = [dist,calitate]
print(d)

def modifica_stare(d,s,o1,o2=""):
    cnt = 0
    if o2 != "":
        d[o1][o2][1]=s
        cnt +=1
    else:
        for city in d[o1].keys():
            d[o1][city][1] = s
            cnt +=1
    return cnt

k = modifica_stare(d,2,"Oraselul Mic")
print(k)
print(d)

def accesibil(d, *orase):
    result = set()
    
    for oras in orase:
        if oras in d:
            result.update(d[oras].keys())
    
    result = result - set(orase)
    return result

rezultat = accesibil(d, "Oraselul Mic", "Capitala")
print(rezultat)