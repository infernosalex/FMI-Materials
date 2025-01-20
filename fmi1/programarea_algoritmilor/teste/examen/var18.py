m = 16
n = 3
a = [1,0,4]
b = [6,7,8]

k = 0

st = [0]*n

def init():
    st[k] = a[k] -1

def succesor():
    if(st[k] < b[k]):
        st[k] += 1
        return True
    return False

def ok():
    if(k >= len(a)):
        return False
    for i in range(k):
        if (not (a[i] <= st[i] <= b[i])):
            return False
    return True

def sol():
    s = 0
    for i in range(n):
        s += st[i]
    return s == m

def afisare():
    for i in range(k+1):
        print(st[i], end=" ")
    print()

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
            elif k<n:               
                k += 1
                init()
        else:
            k -= 1

back()