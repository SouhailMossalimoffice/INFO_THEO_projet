#include <stdio.h>

double add(double a, double b) {
    return (a + b);
}

double subtract(double a, double b) {
    return (a - b);
}

double multiply(double a, double b) {
    return (a * b);
}

double divide(double a, double b) {
    return (a / b);
}

double main() {
    double x = 10.000000;
    double y = 5.000000;
    double sum = add(x, y);
    double diff = subtract(x, y);
    double prod = multiply(x, y);
    double quot = divide(x, y);
    printf("%f\n", sum);
    printf("%f\n", diff);
    printf("%f\n", prod);
    printf("%f\n", quot);
}

int main() {
    return 0;
}
