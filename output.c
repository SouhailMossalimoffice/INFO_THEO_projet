#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* num_to_str(double n) { char buf[32]; snprintf(buf, sizeof(buf), "%g", n); return strdup(buf); }
char* str_concat(const char* a, const char* b) { size_t l1 = strlen(a), l2 = strlen(b); char* r = malloc(l1+l2+1); strcpy(r,a); strcat(r,b); return r; }

int main() {
    double x = 10.000000;
    double y = 5.000000;
    if ((x > y)) {
    printf("%s\n", "x is greater than y");
    } else {
    printf("%s\n", "x is not greater than y");
    }
    double i = 0.000000;
    while ((i < 5.000000)) {
    printf("%s\n", str_concat("i = ", num_to_str(i)));
    i = (i + 1.000000);
    }
    return 0.000000;
    return 0;
}
