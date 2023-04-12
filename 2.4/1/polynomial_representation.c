#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 101

typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

polynomial poly_add1(polynomial A, polynomial B);
void poly_print(polynomial P);

int main() {
    polynomial A = { 5, {3, 6, 0, 0, 0, 10} };
    polynomial B = { 4, {7, 0, 5, 0, 1} };
    polynomial C;

    C = poly_add1(A, B);
    printf("A(x) = ");
    poly_print(A);
    printf("\nB(x) = ");
    poly_print(B);
    printf("\nC(x) = ");
    poly_print(C);

    return 0;
}

polynomial poly_add1(polynomial A, polynomial B) {
    polynomial C;
    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;
    C.degree = A.degree > B.degree ? A.degree : B.degree;
    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--;
            degree_b--;
        }
        else {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

void poly_print(polynomial P) {
    for (int i = P.degree; i > 0; i--)
        printf("%3.1fx^%d + ", P.coef[P.degree - i], i);
    printf("%3.1f", P.coef[P.degree]);
}