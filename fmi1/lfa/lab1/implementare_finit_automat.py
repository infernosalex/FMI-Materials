# Implementarea unui finit automat

Q = {0, 1, 2, 3}
Sigma = {'a', 'b'}
Delta = {
    (0, 'a'): 1,
    (0, 'b'): 0,
    (1, 'a'): 1,
    (1, 'b'): 2,
    (2, 'a'): 1,
    (2, 'b'): 3,
    (3, 'a'): 3,
    (3, 'b'): 3
}
q0 = 0
F = {3}

def accepta_cuvant(w):
    q = q0
    for lit in w:
        q = Delta.get((q, lit), None)
        if q is None:
            return False
    return q in F

# w = 'ababab'
# print(accepta_cuvant(w))
# w = 'abb'
# print(accepta_cuvant(w))


def citire():
    noduri = input("Introduceti nodurile separate prin virgula: ")
    noduri = noduri.split(',')
    noduri = set(map(int, noduri))
    Sigma = input("Introduceti alfabetul: ")
    Sigma = Sigma.split(',')
    Sigma = set(map(str, Sigma))
    Delta = {}
    for nod in noduri:
        for lit in Sigma:
            urm = input(f"Delta({nod}, {lit}) = ")
            Delta[(nod, lit)] = int(urm)
    q0 = input("Introduceti starea initiala: ")
    q0 = int(q0)

    F = input("Introduceti starile finale separate prin virgula: ")
    F = F.split(',')
    F = set(map(int, F))

    return noduri, Sigma, Delta, q0, F

citire()
word = input("Introduceti cuvantul: ")
print(accepta_cuvant(word))