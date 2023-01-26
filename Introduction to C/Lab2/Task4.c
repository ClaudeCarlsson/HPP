#include <stdio.h>

int main() {

    char op;
    double first, second;
    printf("Enter the calculation: ");
    scanf(" %lf %c %lf", &first, &op, &second);

    switch (op) {
        case '+':
        printf("%.1lf + %.1lf = %.1lf", first, second, first + second);
        break;
        case '-':
        printf("%.1lf - %.1lf = %.1lf", first, second, first - second);
        break;
        case '*':
        printf("%.1lf * %.1lf = %.1lf", first, second, first * second);
        break;
        case '/':
        printf("%.1lf / %.1lf = %.1lf", first, second, first / second);
        break;
        // operator doesn't match any case constant
        default:
        printf("Error! operator is not correct");

        return 0;
     }
}