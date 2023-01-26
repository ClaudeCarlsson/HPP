#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct product
{
char name[50];
double price;
}
product_t;

int main() { 
    FILE *fptr;
  
    // Open file
    fptr = fopen("data.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read header
    product_t arr_of_prod[100];
    fscanf(fptr, "%s %lf", arr_of_prod[0].name, &arr_of_prod[0].price);
    int i = 1;
    while (fscanf(fptr, "%s %lf", arr_of_prod[i].name, &arr_of_prod[i].price) != EOF) {
        printf("%s %lf\n", arr_of_prod[i].name, arr_of_prod[i].price);
        i++;
    }

    fclose(fptr);
    return 0;

}

