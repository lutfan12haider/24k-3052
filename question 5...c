#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter the initial size of the array: ");
    scanf("%d", &n);

    int *array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d elements for the array:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    int newSize = 2 * n;
    array = (int *)realloc(array, newSize * sizeof(int));
    if (array == NULL) {
        printf("Memory reallocation failed!\n");
        return 1;
    }

    printf("Enter %d additional elements to fill the resized array:\n", n);
    for (int i = n; i < newSize; i++) {
        scanf("%d", &array[i]);
    }

    printf("Updated array:\n");
    for (int i = 0; i < newSize; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}
