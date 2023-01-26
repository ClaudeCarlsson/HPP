#include <stdio.h>

int main() {
    int i = 10;
    double d = 10;
    char c[2] = "10";

    printf("%d\n", i);
    printf("%lf\n", d);
    printf("%s\n\n", c);

    printf("%p\n", &i);
    printf("%p\n", &d);
    printf("%p\n\n", &c);

    printf("%zu\n", sizeof(i));
    printf("%zu\n", sizeof(d));
    printf("%zu\n", sizeof(c));
}