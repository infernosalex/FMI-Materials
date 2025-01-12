
# ██████████████████████████████████████████████████████████████████████████
# █▄─▄█▄─▀█▄─▄█▄─▄▄─█▄─▄▄─█▄─▄▄▀█▄─▀█▄─▄█─▄▄─█─▄▄▄▄██▀▄─██▄─▄███▄─▄▄─█▄─▀─▄█
# ██─███─█▄▀─███─▄████─▄█▀██─▄─▄██─█▄▀─██─██─█▄▄▄▄─██─▀─███─██▀██─▄█▀██▀─▀██
# ▀▄▄▄▀▄▄▄▀▀▄▄▀▄▄▄▀▀▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▄▄▀▄▄▄▄▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄█▄▄▀

# Tema 1 - Seminar 1

# 0
# O(log n)  
def lung_maxima_secv_de_1(n):
    baza2 = bin(n)[2:]
    #print(baza2)
    secv1 = baza2.split('0')
    #print(secv1)
    return max(len(secventa) for secventa in secv1)

#print(lung_maxima_secv_de_1(439))

# 1
# Complexitate O(n)
def nr_imp_aparitii(lista):
    rez = 0
    for i in lista:
        rez ^= i
    return rez

#print(nr_imp_aparitii([1, 2, 3, 2, 3, 1, 3, 4, 4, 4, 4]))

# 2

def xor_submultimi(A):
    if len(A) > 1:
        return 0
    else:
        return A[0] 
#print(xor_submultimi([1, 2, 3]))
# ex [1, 2, 3] => 1^2^3^1^2^1^3^2^3^1^2^3 = 0, 1- 4 ori ,2 - 4 ori, 3 - 4 ori

# 3
def numar_biti_de_comutat(x, y):
    t = x ^ y
    #print(bin(t))
    return bin(t).count('1') 

#print(numar_biti_de_comutat(4, 7)) # 4 = 100, 7 = 111 => 100 ^ 111 = 011 => 2 biti de comutat

# 4

def nextPowerOf2(n):
    count = 0
    if (n and not(n & (n - 1))): # daca n este putere a lui 2
        return n
     
    while( n != 0):
        n >>= 1 #  n = n // 2
        count += 1 
     
    return 1 << count # 1 << count = 2^count

#print(nextPowerOf2(14))

# 5
def numar_biti_nuli(n):
    baza2 = bin(n)[2:]
    return baza2.count('0')

#print(numar_biti_nuli(439))

#6
def xor_submultimi_pana_la_n(n):
    if n > 1:
        return 0
    else:
        return n

#print(xor_submultimi_pana_la_n(3))


