# Subectia 1
# a)
def cifre_comune(*args, x = 135579):
    d = dict()

    for num in args:
        digits = set(str(num))
        for digit in digits:
            if digit in str(x):
                try:
                    d[int(digit)].append(num)
                except:
                    d[int(digit)] = [num]

    result = {key: tuple(sorted(value)) for key, value in d.items()}

    return result

print(cifre_comune(54572,9559,2024,75917))

# b)
M = [[2,3,5],[1,14,7],[0,1,2]]
pare = [x for x in M[0]+M[-1] if x%2==0]
print(pare)

# c)
# T(n) = a*T(n/b) + f(n)

# 1. f(n) < n ^ (logb(a)-epsilon) => T(n) = O(n^(logb(a)))
# 2. f(n) = n ^ (logb(a)) => T(n) = O(n^(logb(a)) * (lg (n))^k)
# 3. f(n) = x(n ^ (logb(a)+epsilon)) => T(n) = O(f(n))

# # Subiectul 2 Greedy

# # 3 -2  5 -1 4
# # 7 8 -5 2 -4 -1 5 

# A = [ int(x) for x in input().split() ]
# n = len(A)

# B = [ int(x) for x in input().split() ]
# m = len(B)

# # print(A)
# # print(B)

# A.sort()
# B.sort()

# # print(A)
# # print(B)

# s = 0

# leftB = 0 
# rightB = len(B) - 1

# leftA = 0
# rightA = len(A) - 1

# for i in range(len(A)):
#     if (B[rightB]*A[rightA]>B[leftB]*A[leftA]):
#         s += B[rightB]*A[rightA]
#         # print(B[rightB]*A[rightA])
#         rightB -= 1
#         rightA -= 1
#     else:        
#         # print(B[leftB]*A[leftA])
#         s += B[leftB]*A[leftA]
#         leftB += 1
#         leftA += 1
# print(s)