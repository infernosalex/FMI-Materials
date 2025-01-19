# Problema 1
# f = open("matrice.in",'r')
# g = open("matrice.out",'w')
# for line in f:
#     l = [int(x) for x in line.split()]
#     l.remove(max(l))
#     l.remove(max(l))
#     l = [str(x)+" " for x in l] + ["\n"]
#     g.writelines(l)


# # Problema 2
# file_name = "exemplu.txt"
# f = open(file_name)
# s = f.read().lower().strip().split()
# s1 = list(set(s)) # cuvinte
# d = {}
# for i in s1:
#     if s.count(i) not in d: 
#         d[s.count(i)] = [i] 
#     else:
#         d[s.count(i)].append(i)

# # Sortare dictionar dupa frecventa descrescator si dupa cuvinte crescator
# d = (sorted(d.items(), key=lambda x: (-x[0])))
# print(d)
# for i in range(len(d)):
#     d[i] = (d[i][0],sorted(d[i][1]))
#     print(f"Frecventa {d[i][0]}: {', '.join(d[i][1])}")

f = open("cinema.in",'r')

d = dict()
for line in f.readlines():
    cinema = line.split('%')[0].strip()
    film = line.split('%')[1].strip()
    ore = line.split('%')[2].strip()
    if cinema not in d:
        d[cinema]={film:set(ore.split())}
    else:
        if film not in d[cinema]:
            d[cinema][film] = set(ore.split())
        else:
            d[cinema][film].update(ore.split())

# for key in d.keys():
#     print(key)
#     for k in d[key].keys():
#         print(f"  {k}: {d[key][k]}")



def sterge_ore(d,cinema,film, ore):
    for ora in ore.split():
        if ora in d[cinema][film]:
            d[cinema][film].remove(ora)
            if not len(d[cinema][film]):
                del d[cinema][film]
    l = []
    print(list(d[cinema].keys()))
    return d
        
#sterge_ore(d,"Cinema 1","Buna dimineata","19:30")
#print(d)

def cinema_film(d,*cinemas, ora_min="", ora_max=""):
    l = []
    for cinema in cinemas:
        #print(d[cinema].keys())
        for film in d[cinema].keys():
            # t = ()
            ore = []
            for ora in d[cinema][film]:
                if(ora_min <= ora <= ora_max):
                    ore.append(ora)
            ore.sort()
            t = (film,cinema,ore)
            l.append(t)
    
    l = sorted(l, key=lambda x: (x[0], -len(x[2])))
    # Remove null ore
    lung = len(l)
    i = 0
    while i < lung:
        if l[i][2] == []:
            del l[i]
            i -= 1
            lung -=1
        i += 1
    return l

a = cinema_film(d,"Cinema 1", "Cinema 2", ora_min="14:00",ora_max="22:00")
print(a)