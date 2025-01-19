# Subiect 1

f = open("numere.in",'r')
g = open("numere.out",'w')

l = [int(x) for x in f.read().split()]
print(l)

d = dict()

for nr in l:
    n = str(bin(nr)[2:])
    nrbitinenuli = n.count('1')
    if nrbitinenuli not in d:
        d[nrbitinenuli] = set()
    d[nrbitinenuli].add(nr)

for i in d:
    d[i] = sorted(list(d[i]))
print(d)
d = dict(sorted(d.items(), key= lambda x:(-len(x[1]),-x[0])))

for bit in d:
    print(f"{bit} biti nenuli: " + ",".join(str(x) for x in d[bit]))


