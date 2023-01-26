#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_int_1(int x) {
    printf("Here is the number: %d\n", x);
}

void print_int_2(int x) {
    printf("Wow, %d is really an impressive number!\n", x);
}

int main() {
    void (*print_int)(int); // Declare function pointer
    print_int = &print_int_1; // Set pointer to point to print_int_1
    print_int(5); // Call print_int_1 using the pointer
    print_int = &print_int_2; // Set pointer to point to print_int_2
    print_int(10); // Call print_int_2 using the pointer
    return 0;
}
