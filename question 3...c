#include <stdio.h>

void searchElement(int *arr, int rows, int columns, int target) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (*(arr + i * columns + j) == target) {
                printf("Element %d found at row %d, column %d\n", target, i, j);
                return;
            }
        }
    }
    printf("Element %d not found in the array.\n", target);
}

int main() {
    int rows, columns, target;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &columns);

    int array[rows][columns];
    printf("Enter elements of the 2D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    printf("Enter the element to search: ");
    scanf("%d", &target);

    searchElement((int *)array, rows, columns, target);

    return 0;
}
