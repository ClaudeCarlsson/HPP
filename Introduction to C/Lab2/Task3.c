#include <stdio.h>
#include <stdlib.h>
int main() {

    //Part 1

	int a = 0;
	int b = 0;
    int c = 0;
    
	printf("Enter a: ");
	scanf(" %d", &a);

	printf("Enter b: ");
    scanf(" %d", &b);

    if (a % 2 == 0 && b % 2 == 0) {
        c = a + b;
        printf(" %d", c);
    } else {
         c = a * b;
         printf(" %d", c);
    }

    // Part 2
    
	printf("Enter a: ");
	scanf(" %d", &a);

	printf("Enter b: ");
    scanf(" %d", &b);

	printf("Enter c: ");
    scanf(" %d", &c);

    a = abs(a);
    b = abs(b);
    c = abs(c);

    if (a >= b && a >= c) {
        printf(" %d", a);
    }
    else if (b >= a && b >= c) {
        printf(" %d", b);
    }
    else if (c >= a && c >= b) {
        printf(" %d", c);
    }

    // Part 3
 
 	printf("Enter a: ");
	scanf(" %d", &a);

	printf("Enter b: ");
    scanf(" %d", &b);

	printf("Enter c: ");
    scanf(" %d", &c);

    a = abs(a);
    b = abs(b);
    c = abs(c);

    if (a >= b && a <= c) {
        printf(" %d", a);
    }
    else if (a <= b && a >= c) {
        printf(" %d", a);
    }
    else if (b >= a && b <= c) {
        printf(" %d", b);
    }
    else if (b <= a && b >= c) {
        printf(" %d", b);
    }
    else if (c >= a && c <= b) {
        printf(" %d", c);
    }
    else if (c <= a && c >= b) {
        printf(" %d", c);
    }

	return 0;
}
