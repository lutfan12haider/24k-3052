#include <stdio.h>

int calculateBoundarySum(int *arr, int rows, int columns) {
    int sum = 0;
    for (int j = 0; j < columns; j++) {
        sum += *(arr + 0 * columns + j);
    }

    for (int j = 0; j < columns; j++) {
        sum += *(arr + (rows - 1) * columns + j);
    }

    for (int i = 1; i < rows - 1; i++) {
        sum += *(arr + i * columns + 0); 
        sum += *(arr + i * columns + (columns - 1)); 
    }

    return sum;
}

int main() {
    int array[3][3];

    printf("Enter elements of the 3x3 array:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    int sum = calculateBoundarySum((int *)array, 3, 3);
    printf("Sum of all boundary elements: %d\n", sum);

    return 0;
}
