#include <stdio.h>
int main() {

	// for
	for (int i = 100; i > 0; i = i - 4) {
		printf("%d ,", i);
	}

	// while
        int i = 100;
	while (i > 0) {
		printf("%d ,", i);
		i = i - 4;
	}

	// do...while
	i = 100;
	do {
	printf("%d ,", i);
	i = i - 4;
	}
	while (i > 0);

	return 0;
}
