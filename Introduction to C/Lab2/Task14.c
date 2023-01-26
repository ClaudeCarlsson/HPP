#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[]) { 
    FILE *fptr;
    char product[25];
    double price;
  
    // Open file
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read header
    fscanf(fptr, "%s %lf", product, &price);

    while (fscanf(fptr, "%s %lf", product, &price) != EOF) {
        printf("%s %lf\n", product, price);
    }

    fclose(fptr);
    return 0;

}