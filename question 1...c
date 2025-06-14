#include <stdio.h>
void swapRows(int *arr, int row1, int row2, int columns) {
    for (int i = 0; i < columns; i++) {
        int temp = *(arr + row1 * columns + i);
        *(arr + row1 * columns + i) = *(arr + row2 * columns + i);
        *(arr + row2 * columns + i) = temp;
    }
}

void printMatrix(int arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("Original Matrix:\n");
    printMatrix(matrix);

    swapRows((int *)matrix, 0, 2, 3);

    printf("\nMatrix after swapping rows 0 and 2:\n");
    printMatrix(matrix);

    return 0;
}
