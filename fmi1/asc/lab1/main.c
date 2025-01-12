#include <stdlib.h>
#include <stdio.h>

///*
//    Scrieti un program in limbajul C care permite interschimbarea a doua valori a unor variabile
//fara a folosi o variabila auxiliara pentru acest lucru.
// */
//int main() {
//    int a,b;
//    scanf("%d %d", &a, &b);
//    a = a^b;
//    b = a^b;
//    a = a^b;
//    printf("%d %d",a,b);
//    return 0;
////////////////////////////////////////
//    int a,b;
//    scanf("%d %d", &a, &b);
//    a = a+b;
//    b = a-b;
//    a = a-b;
//    printf("%d %d",a,b);
//    return 0;
//}

//Scrieti un program in limbajul C care permite interschimbarea a doua valori a unor variabile
//        fara a folosi o variabila auxiliara pentru acest lucru.


int main() {
    int n, num, result = 0;

    // Deschidere fisier pentru citire
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        printf("%d\n", num);
        result ^= num;
    }

    // Citim toate numerele din fișier și aplicăm operația XOR
//    //while (fscanf(file, "%d", &num) != EOF) {
//        printf("%d\n", num);
//        result ^= num;
//    }

    // Închidem fișierul

    // Afișăm rezultatul - numărul fără pereche
    printf("Numarul fara pereche este: %d\n", result);

    return 0;
}
