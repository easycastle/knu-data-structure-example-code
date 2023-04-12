#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 101

typedef struct {
    float coef;
    int expon;
} term;
term terms[MAX_DEGREE];
int avail = 0;

void attach(float coefficient, int exponent);
void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce);
void poly_print(int S, int E);

int main() {
    int As, Ae, Bs, Be, Cs, Ce;

    As = 0;
    printf("Enter the number of terms of A(x): ");
    scanf("%d", &Ae);
    Ae--;
    printf("Enter the terms of A(x) in descending order of exponents: ");
    for (int i = As; i <= Ae; i++)
        scanf("%f %d", &terms[i].coef, &terms[i].expon);

    Bs = Ae + 1;
    printf("Enter the number of terms of B(x): ");
    scanf("%d", &Be);
    Be += Bs - 1;
    printf("Enter the terms of B(x) in descending order of exponents: ");
    for (int i = Bs; i <= Be; i++)
        scanf("%f %d", &terms[i].coef, &terms[i].expon);

    avail = Be + 1;

    poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
    printf("\nA(x) = ");
    poly_print(As, Ae);
    printf("\nB(x) = ");
    poly_print(Bs, Be);
    printf("\nC(x) = ");
    poly_print(Cs, Ce);

    return 0;
}

void attach(float coefficient, int exponent) {
    if (avail >= MAX_DEGREE) {
        fprintf(stderr, "The number of terms exceeds");
        exit(EXIT_FAILURE);
    }

    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
    float coefficient;
    *Cs = avail;
    while (As <= Ae && Bs <= Be) {
        if (terms[As].expon > terms[Bs].expon) {
            attach(terms[As].coef, terms[As].expon);
            As++;
        }
        else if (terms[As].expon < terms[Bs].expon) {
            attach(terms[Bs].coef, terms[Bs].expon);
            Bs++;
        }
        else {
            coefficient = terms[As].coef + terms[Bs].coef;
            if (coefficient)
                attach(coefficient, terms[As].expon);
            As++;
            Bs++;
        }
    }
    for (; As <= Ae; As++)
        attach(terms[As].coef, terms[As].expon);
    for (; Bs <= Be; Bs++)
        attach(terms[Bs].coef, terms[Bs].expon);
    *Ce = avail - 1;
}

void poly_print(int S, int E) {
    for (int i = S; i < E; i++)
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    printf("%3.1fx^%d", terms[E].coef, terms[E].expon);
}