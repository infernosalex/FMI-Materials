# se citeste un numar natural n, determinare palindrom
# 1
# n = int(input())
# reversed_n = str(n)[::-1]
# print(int(reversed_n) == n)

# 2
# n = int(input())
# crestere = 0
# x = float(input())
# for i in range (n-1):
#     y = float(input())
#     dif = y-x
#     crestere = max(crestere, dif)
#     x = y
# print(round(crestere, 2))

# 3
# def gcd(a, b):
#     while b != 0:
#         a, b = b, a % b
#     return a
#
# from math import gcd
# l1 = int(input())
# l2 = int(input())
#
# placa = gcd(l1, l2)
# print(l1*l2//placa**2)

# 4
# n = int(input())
# # Se citeste un numar natural n, urmat de n numere naturale . sa se afiseze cele mai mari 2 valori distincte din sir sau mesajul imposobo;, daca aceasta nu exista
#
# max1 = -1
# max2 = -1
# for i in range(n):
#     x = int(input())
#     if x > max1:
#         max2 = max1
#         max1 = x
#     elif x > max2 and x != max1:
#         max2 = x
# if max2 == -1:
#     print("imposibil")

# # 5
# a = int(input())
# b = int(input())
# c = int(input())
#
# d = b**2 - 4*a*c
# if d < 0:
#     print("Nu are nicio solutie")
# elif d == 0:
#     print("Are o solutie reala")
#     print(-b/(2*a))
# else:
#     print("Are doua solutii reale")
#     x1 = (-b-d**0.5)/(2*a)
#     x2 = (-b+d**0.5)/(2*a)
#     print(f"x1={x1}")
#     print(f"x2={x2}")

# # 6
# n = (input())
# ln = [int(x) for x in n]
# ln.sort()
# low = int("".join([str(x) for x in ln]))
# ln.sort(reverse=True)
# high = int("".join([str(x) for x in ln]))
# print(low)
# print(high)

# # 7
# x = int(input())
# n = int(input())
# p = int(input())
# m = int(input())
# d = 0
#
# for i in range(1,m+1):
#     d += x
#     if i%n==0:
#         x -= p/100*x
# print(d)

print("Am terminat!", end="")