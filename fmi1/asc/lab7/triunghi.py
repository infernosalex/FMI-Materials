import math

def dist(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def is_triangle(x1, y1, x2, y2, x3, y3):
    a = dist(x1, y1, x2, y2)
    b = dist(x2, y2, x3, y3)
    c = dist(x3, y3, x1, y1)
    return (a + b > c) and (b + c > a) and (c + a > b)

def tip_triunghi(x1, y1, x2, y2, x3, y3):
    a = dist(x1, y1, x2, y2)
    b = dist(x2, y2, x3, y3)
    c = dist(x3, y3, x1, y1)
    
    if abs(a - b) < 1e-6 and abs(b - c) < 1e-6:
        return "echilateral"
    elif abs(a - b) < 1e-6 or abs(b - c) < 1e-6 or abs(c - a) < 1e-6:
        return "isoscel"
    elif abs(a**2 + b**2 - c**2) < 1e-6 or abs(b**2 + c**2 - a**2) < 1e-6 or abs(c**2 + a**2 - b**2) < 1e-6:
        return "dreptunghic"
    else:
        return "oarecare"

def aria(x1, y1, x2, y2, x3, y3):
    return 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2))

x1, y1 = map(float, input("Introduceți coordonatele pentru primul punct (x y): ").split())
x2, y2 = map(float, input("Introduceți coordonatele pentru al doilea punct (x y): ").split())
x3, y3 = map(float, input("Introduceți coordonatele pentru al treilea punct (x y): ").split())

if is_triangle(x1, y1, x2, y2, x3, y3):
    print(f"Tipul triunghiului: {tip_triunghi(x1, y1, x2, y2, x3, y3)}")
    print(f"Aria triunghiului: {aria(x1,y1,x2,y2,x3,y3)}")
else:
    print("Punctele nu formează un triunghi.")
