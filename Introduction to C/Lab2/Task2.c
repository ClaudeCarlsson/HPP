#include <stdio.h>
int main() {

	int a;
	int b;

	printf("Enter a: ");
	scanf("%d", &a);

	printf("Enter b: ");
        scanf("%d", &b);


	for (int i = a+2; i > 0; i = i - 1) {
		printf("*");
	}
	printf("\n");
	for (int i = a; i > 2; i = i - 1) {

		printf("*");
		for (int i = b; i > 2; i = i - 1) {
			printf(".");
		}
		printf("*\n");

	}


	for (int i = a+2; i > 0; i = i - 1) {
		printf("*");
	}

	printf("\n");

	return 0;
}
