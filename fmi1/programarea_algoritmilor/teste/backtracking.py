# # Submultimi

# st = [0] * 100
# vect = [1,5,7,10] # date
# k = 0

# # Init Succesor Ok Solutie Afisare Bck

# def init():
#     st[k] = -1

# def succesor():
#     if(st[k]<1): # 0, 1 pt submultimii
#         st[k] += 1
#         return True
#     else:
#         return False

# def ok():
#     return True

# def sol():
#     return k == len(vect)-1

# def afis():
#     for i in range(k+1):
#         if(st[i] == 1):
#             print(vect[i], end=" ")

# def back():
#     global k
#     init()
#     while(k>=0):
#         are_succ = succesor()
#         while( ok() == False and are_succ == True):
#             are_succ = succesor()
#         if(are_succ):
#             if(sol()):
#                 afis()
#                 print()
#             else:
#                 k +=1
#                 init()
#         else:
#             k -= 1 

# back()

# # Permutari
# st = [0] * 100
# k = 0
# n = 3
# # vect = [ i+1 for i in range(n)]
# # init ok succesor solutie afist back
# def init():
#     st[k] = 0

# def succesor():
#     if(st[k]<n):
#         st[k] += 1
#         return True
#     return False

# def ok():
#     if st[k] in st[:k]: # Se afla pe stiva pana la k
#         return False
#     return True

# def sol():
#     return k == n-1

# def afisare():
#     i = 0 
#     while i <= k:
#         print(st[i], end=" ")
#         i += 1
#     print()

# def back():
#     global k
#     init()
#     while(k>=0):
#         are_suc = succesor()
#         while(not ok() and are_suc == True):
#             are_suc = succesor()
#         if(are_suc):
#             if(sol()):
#                 afisare()
#             else:
#                 k += 1
#                 init()
#         else:
#             k -= 1

# back()


