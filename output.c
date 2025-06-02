#include <stdio.h>

double add(double x, double y);
double subtract(double x, double y);
double multiply(double x, double y);
double divide(double x, double y);
double add(double x, double y) {
    return (x + y);
}

double subtract(double x, double y) {
    return (x - y);
}

double multiply(double x, double y) {
    return (x * y);
}

double divide(double x, double y) {
    return (x / y);
}

int main() {
    double a = 10.000000;
    double b = 5.000000;
    printf("Testing add function\n");
    double sum = add(a, b);
    printf("a + b = \n");
    printf("%f\n", sum);
    printf("Testing subtract function\n");
    double diff = subtract(a, b);
    printf("a - b = \n");
    printf("%f\n", diff);
    printf("Testing multiply function\n");
    double product = multiply(a, b);
    printf("a * b = \n");
    printf("%f\n", product);
    printf("Testing divide function\n");
    double quotient = divide(a, b);
    printf("a / b = \n");
    printf("%f\n", quotient);
    return 0;
}
