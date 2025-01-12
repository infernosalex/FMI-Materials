# 3
# Scrieți un program care să înlocuiască într-o propoziție toate aparițiile unui cuvânt s cu un cuvânt t.
import datetime

# text = input("text ").strip()
# s = input("s ").strip()
# t = input("t ").strip()
#
# words = text.split(" ")
#
# for i in range(len(words)):
#     if(words[i] == s):
#         words[i] = t
#
# text = ' '.join(words)
# print(text)

# 4
# Scrieți un program care să se verifice dacă două șiruri de caractere sunt anagrame sau nu. Două șiruri sunt anagrame dacă unul se poate obține din celălalt printr-o permutare a caracterelor sale

# s1 = input().strip()
# s2 = input().strip()
#
# print(sorted(s1) == sorted(s2))

# 5 caesar cipher

# def encrypt(s, k):
#     encrypted = []
#     for char in s:
#         if char.isalpha():
#             shift = ord('a') if char.islower() else ord('A')
#             encrypted_char = chr((ord(char) - shift + k) % 26 + shift)
#             encrypted.append(encrypted_char)
#         else:
#             encrypted.append(char)
#     return ''.join(encrypted)
#
# def decrypt(s, k):
#     decrypted = []
#     for char in s:
#         if char.isalpha():
#             shift = ord('a') if char.islower() else ord('A')
#             decrypted_char = chr((ord(char) - shift - k) % 26 + shift)
#             decrypted.append(decrypted_char)
#         else:
#             decrypted.append(char)
#     return ''.join(decrypted)
#
# text = input("text: ").strip()
# k = int(input("k "))
# encrypted_text = encrypt(text, k)
# print("Encriptat:", encrypted_text)
#
# decrypted_text = decrypt(encrypted_text, k)
# print("Decriptat", decrypted_text)

# 6

# text = input("Fraza: ").strip()
#
# import re
# numbers = re.findall(r'[0-9]+',text)
# numbers = [int(num) for num in re.findall(r'[0-9]+',text)]
# s = sum(numbers)
# print(s)

# import re
# print(sum(int(num) for num in re.findall(r'[0-9]+',input("Fraza: ").strip())))

# 7
# year, month, day = map(int, input().split())
# day_of_week = (datetime.datetime(year,month,day).weekday())
# days = ["luni","marti","miercuri","joi","vineri","sambata","duminica"]
# print(days[day_of_week])


 # 12
# 12. Operații pe stringuri:
# Vom considera următoarea operație <op>:
# • dacă ultima literă a primului string este diferită de prima a celui de-al doilea, atunci:
# ◦ <op> este echivalentă cu concatenarea de string-uri: “ad” <op> “a” = “ad” + “a” = “ada”
# • dacă ultima literă a primului string este aceeași cu prima literă a celui de-al doilea string, atunci:
# ◦ “de” <op> “eea” = “d” <op> “a” = “d” + “a” = “da” (toate literele ‘din mijloc’ comune dispar, și se continuă cu <op> aplicat resturilor din fiecare șir.
# • Încă un exemplu:
# ◦ “absf” <op> “ffsc” = “abs” <op> “sc” = “ab” <op> “c” = “ab” + “c” = “abc”
# Cerință:
# Pentru un șir format numai din litere citit de la tastatură decideți din care dintre operațiile sir_1 <op> sir_1_oglindit sau sir_1_oglindit<op> sir_1 se obține un șir mai lung. Afișați șirurile obținute la fiecare pas după aplicarea operației <op>.


s = input().strip()
s1 = input().strip()

def op(s, t):
    if ( s == "" or t == ""):
        return s+t
    if s[-1] != t[0]:
        return s+t
    else:
        c = t[0]
        s = s.rstrip(c)
        t = t.lstrip(c)
        return op(s, t)

print(op(s, s1))
