#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* num_to_str(double n) {
    char* buf = malloc(32);
    snprintf(buf, 32, "%g", n);
    return buf;
}

char* str_concat(const char* a, const char* b) {
    if (!a) a = "";
    if (!b) b = "";
    size_t l1 = strlen(a), l2 = strlen(b);
    char* r = malloc(l1 + l2 + 1);
    strcpy(r, a);
    strcat(r, b);
    return r;
}

double add(double a, double b);
double add(double a, double b) {
    return (a + b);
    return 0;
}

int main() {
    printf("%s\n", "Hello, World!");
    return 0.000000;
    return 0;
}
