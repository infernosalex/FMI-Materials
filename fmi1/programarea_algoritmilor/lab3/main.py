# 1

import string
import random
from cmath import inf

# with open("date.in", "r") as f, open("date.out", "w") as g:
#     for line in f:
#         nume = line.split()[0]
#         prenume = line.split()[1]
#         email = nume.lower() + "." + prenume.lower() + "@myfmi.unibuc.ro"
#         # random.choice(string.ascii_letters, k=1).upper()  + random.choice(string.ascii_letters, k=3) + random.choice(string.digits, k=4)
#         password = ''.join(random.choice(string.ascii_uppercase))
#         password += ''.join(random.choice(string.ascii_lowercase) for i in range(3))
#         password += ''.join(random.choice(string.digits) for i in range(4))
#         print(f"{email},{password}", file=g)

#2
# nota = 1
# with open("date.in", "r") as f, open("date.out", "w") as g:
#     for line in f:
#         line = line.strip()
#         sep = "*"
#         n1 = line.split(sep, 1)[0]
#         n2 = line.split(sep, 1)[1].split("=")[0]
#         rez = line.split(sep, 1)[1].split("=")[1]
#         print(line,end=" ", file=g)
#         if int(n1) * int(n2) == int(rez):
#             print(f"Corect", file=g)
#             nota += 1
#         else:
#             ecuatia = f"{n1} * {n2}"
#             print(f"Gresit {eval(ecuatia)}", file=g)
#     print(f"Nota {nota}", file=g)


#3
# import re
# s = 0
# with open("date.in", "r") as f, open("date.out", "w") as g:
#     for line in f:
#         line = line.strip()
#         sep = "."
#         a = line
#         result = re.findall(r"[-+]?\d*\.\d+|\d+", a)
#         for i in range(0,len(result),2):
#             s += float(result[i])*float(result[i+1])
#         print(s, file=g)

#4
#
# l = [int(x) for x in input().split()]
# max1 = float(-inf)
# max2 = float(-inf)
# for i in range(len(l)):
#     x = l[i]
#     if x > max1:
#         max2 = max1
#         max1 = x
#     elif x > max2 and x != max1:
#         max2 = x
# if max2 == -1:
#     print("imposibil")
# else:
#     print(max1, max2)

#5
# s = input()
# hashmap = {}
# sl = s.lower().split()
# for i in range(len(sl)):
#     if sl[i] in hashmap:
#         hashmap[sl[i]] += 1
#     else:
#         hashmap[sl[i]] = 1
#
# maxim = -1
# minim = 100000
# for key in hashmap:
#     #print(hashmap[key], key)
#     if(hashmap[key] > maxim):
#         maxim = hashmap[key]
#     if(hashmap[key] < minim):
#         minim = hashmap[key]
# print(maxim, minim)

#6
import lorem

s = lorem.text()
print(s)