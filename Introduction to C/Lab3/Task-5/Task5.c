#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int CmpString(const void* a, const void* b) {
    char* x = *(char**)a;
    char* y = *(char**)b;
    return strcmp(x, y);
}

int main() {
    char *arrStr[] = {"daa", "cbab", "bbbb", "bababa", "ccccc", "aaaa"};
    int arrStrLen = sizeof(arrStr) / sizeof(char *);
    qsort(arrStr, arrStrLen, sizeof(char *), CmpString);
    for (int i = 0; i < arrStrLen; i++) {
        printf("%s ", arrStr[i]);
    }
    return 0;
}
