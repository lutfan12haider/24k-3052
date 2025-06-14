#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int compareStrings(const void *a, const void *b) {
    const char **strA = (const char **)a;
    const char **strB = (const char **)b;
    return strcmp(*strA, *strB);
}

int main() {
    int n;

    printf("Enter the number of strings: ");
    scanf("%d", &n);

    char **strings = (char **)malloc(n * sizeof(char *));
    if (strings == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter each string:\n");
    for (int i = 0; i < n; i++) {
        char buffer[100];
        printf("String %d: ", i + 1);
        scanf(" %[^\n]", buffer);  

       
        strings[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (strings[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        strcpy(strings[i], buffer);
    }

    qsort(strings, n, sizeof(char *), compareStrings);

    printf("\nSorted strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]); 
    }

    free(strings);  

    return 0;
}
