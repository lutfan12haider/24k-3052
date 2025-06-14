#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n, p;
    printf("Enter the number of rows and columns for matrix A (m x n): ");
    scanf("%d %d", &m, &n);

    printf("Enter the number of columns for matrix B (n x p): ");
    scanf("%d", &p);

    int *A = (int *)malloc(m * n * sizeof(int));
    int *B = (int *)malloc(n * p * sizeof(int));
    int *C = (int *)malloc(m * p * sizeof(int));

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", (A + i * n + j));
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", (B + i * p + j));
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            *(C + i * p + j) = 0;
            for (int k = 0; k < n; k++) {
                *(C + i * p + j) += *(A + i * n + k) * *(B + k * p + j);
            }
        }
    }

    printf("Product matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d ", *(C + i * p + j));
        }
        printf("\n");
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
