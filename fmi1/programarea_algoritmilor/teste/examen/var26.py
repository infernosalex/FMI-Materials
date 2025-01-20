# p ='un exemplu de propozitie'

# lung = [(x,len(x)) for x in p.split() if x[0] in "aeiouAEIOU"]
# print(lung)

m = 4
st = [0]*21
k = 0
cnt = 0

def init():
    if(k == 0):
        st[k] = 0
    else:
        st[k] = -1

def succesor():
    if(st[k]<9):
        st[k] += 1
        return True
    return False

def ok():
    if(k >= m):
        return False
    if (k >= 1):
        if(abs(st[k]-st[k-1]) >= 2 ):
            return False
    return True

def sol():
    if(abs(st[k]-st[0]) >= 2):
        return False
    else:
        return k == m-1
    
def afisare():
    global cnt
    for i in range(k+1):
        print(st[i],end="")
    print()
    cnt += 1

def back():
    global k
    init()
    while(k>=0):
        are_suc = succesor()
        while( not ok() and are_suc):
            are_suc = succesor()
        if(are_suc):
            if(sol()):
                afisare()
            else:
                k +=1
                init()
        else:
            k -= 1
back()
print(cnt)