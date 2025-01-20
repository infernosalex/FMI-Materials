# # subiectul 3 pd 

# m = []
# n = int(input())
# for i in range(n):
#     l = [int(x) for x in input().split()]
#     m.append(l)

# dp = [[float("-inf") for i in range(n)] for j in range(n)]
# print(dp)

# for i in range(n):
#     # Initializare
#     if m[0][i] == -1:
#         dp[0][i] = 0
#     else:
#         dp[0][i] = m[0][i]   

#     if m[i][0] == -1:
#         dp[i][0] = 0
#     else:
#         dp[i][0] = m[i][0]

#     # Recurenta
#     for i in range(n):
#         for j in range(n):


# Varianta 4
st = [0]*100
n = 6
k = 0
solves = 0

L = ('a','b','c','D')
S = ('@',',')

tipar = 'lslsll'

def init():
    st[k] = -1

def succesor():
    if (tipar[k] == 'l'):
        if(st[k] < len(L)-1):
            st[k] += 1
            return True
        else:
            return False
    else:
        if(st[k] < len(S)-1):
            st[k] += 1
            return True
        else:
            return False

def ok():
    for i in range(k):
        if(tipar[i] == tipar[k] and st[i] == st[k]):
            return False
    return True

def sol():
    return k == n-1

def afisare():
    # if(L[st[0]] not in "aeiouAEIOU"):
    #     return
    global solves
    for i in range(k+1):
        if(tipar[i] == 'l'):
            print(L[st[i]],end="")
        else:
            print(S[st[i]],end="")
    print()
    solves += 1

def back():
    global k
    init()
    while(k >= 0):
        are_suc = succesor()
        while( not ok() and are_suc == True):
            are_suc = succesor()
        if(are_suc):
            if(sol()):
                afisare()
            else:
                k += 1
                init()
        else:
            k -=1

back()
if(solves == 0):
    print("Imposibil")

