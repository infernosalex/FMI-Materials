def citire_liste(filepath):
    with open(filepath,'r') as f:
        m = int(f.readline())
        l = [[0 for i in range(m)] for j in range(m)]
        cnt = -1 
        for line in f.readlines():
            x, k = [int(i) for i in line.split()]
            for _ in range(k):
                cnt += 1
                linie = cnt // m
                rest  = cnt % m
                l[linie][rest] = x
        return l
def prelucrare_liste(M,x):
    m = len(M)
    for i in range(len(M)):
        M[i][x:x+1] = []
    i = 0 
    while i < m:
        s = set(M[i])
        if(len(s) == 1):
            M[i:i+1]=[]
            m -= 1
            i -=1
        i += 1

    return M
def printc():
    M = citire_liste("liste.in")
    #print(M)
    M = prelucrare_liste(M,2)
    #print(M)
    for i in range(len(M)):
        for j in range(len(M[0])):
            print(M[i][j],end=" ")
        print()
    # print(M[i][j] for i in range(len(M)) for j in range(len(M[0])))
    # print("\n".join(" ".join(M[i] for i in range(len(M)))))
def functied():
    M = citire_liste("liste.in")
    out = open("multipli.out",'w')
    k = int(input())
    l = []
    for i in range(len(M)):
        for j in range(len(M[0])):
            if(M[i][j]%k == 0 and M[i][j]%(k**2) != 0):
                l.append(M[i][j])
    l = sorted(set(l),reverse=True)
    l = [str(x)+"\n" for x in l]
    out.writelines(l)
# Subiectul 2 
f = open("hoteluri.in",'r')

# Punctul a
d = {}
for line in f:
    dest = line.split(";")[0].split(":")[1].strip()
    cazare = line.split(";")[1].split(":")[1].strip()
    dist = float(line.split(";")[2].split()[0])
    # print(dest,cazare,dist)
    if dest not in d:
        d[dest] = {cazare:dist}
    else:
        d[dest][cazare] = dist

    #print(d)

def cazare_centru(d,*orase,distanta_max=0.5):
    m = []
    for oras in orase:
        l = []
        for centru in d[oras]:
            if(d[oras][centru] < distanta_max):
                l.append((centru,d[oras][centru]))
        a = []
        l = sorted(l , key = lambda x: (x[1]    ))
        for i in range(len(l)):
            a.append(l[i][0])
        m.append((oras,a))
    sorted(m, key= lambda)
cazare_centru(d,"Busteni","Sinaia","Azuga","Acasa")