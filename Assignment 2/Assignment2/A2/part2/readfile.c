#include <stdio.h>

int main() {
    // Set filename and read mode 
    char filename[] = "little_bin_file";
    char readmode[] = "rb";

    // Open file
    FILE* fp = fopen(filename, readmode);
    
    // Check if opening the file is successful 
    if (fp == NULL) {
        printf("Error! File can not be opened.\n");
        return 1;
    }

    // Define the contents of the file
    int a;
    double b;
    char c;
    float d;

    // Read contents of the file and store it in the variables
    fread(&a, sizeof(int), 1, fp);
    fread(&b, sizeof(double), 1, fp);
    fread(&c, sizeof(char), 1, fp);
    fread(&d, sizeof(float), 1, fp);

    // Print the contents of the file
    printf("%d\n", a);
    printf("%lf\n", b);
    printf("%c\n", c);
    printf("%f\n", d);

    // Close file
    fclose(fp);

    return 0;
}