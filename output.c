#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* num_to_str(double n) { char buf[32]; snprintf(buf, sizeof(buf), "%g", n); return strdup(buf); }
char* str_concat(const char* a, const char* b) { size_t l1 = strlen(a), l2 = strlen(b); char* r = malloc(l1+l2+1); strcpy(r,a); strcat(r,b); return r; }

double add(double a, double b);
double add(double a, double b) {
    return (a + b);
}

int main() {
    printf("%s\n", "Hello, World!");
    return 0.000000;
    return 0;
}
