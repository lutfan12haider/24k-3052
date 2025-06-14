#include <stdio.h>
#include <stdlib.h>

int main() {
    int size, generation;

    // Input the size and number of generations
    printf("Enter the size of cellular automaton: ");
    scanf("%d", &size);

    printf("Enter the number of generations: ");
    scanf("%d", &generation);

    // Allocate memory for the current and next states
    int *current = (int *)malloc(size * sizeof(int));
    int *next = (int *)malloc(size * sizeof(int));

    // Check if memory allocation was successful
    if (current == NULL || next == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Input the initial state
    printf("Enter the initial state (0s and 1s): ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &current[i]);
    }

    // Process each generation
    for (int gen = 0; gen < generation; gen++) {
        // Print the current state
        printf("Generation %d: ", gen);
        for (int i = 0; i < size; i++) {
            printf("%d ", current[i]);
        }
        printf("\n");

        // Compute the next state
        for (int i = 0; i < size; i++) {
            int left, right;

            // Handle boundary conditions
            if (i == 0) {
                left = 0; // First cell's left neighbor is OFF
            } else {
                left = current[i - 1];
            }

            if (i == size - 1) {
                right = 0; // Last cell's right neighbor is OFF
            } else {
                right = current[i + 1];
            }

            // Apply the rules
            if (left == 1 || right == 1) {
                next[i] = 1;
            } else {
                next[i] = 0;
            }
        }

        // Copy the next state into the current state
        for (int i = 0; i < size; i++) {
            current[i] = next[i];
        }
    }

    // Free allocated memory
    free(current);
    free(next);

    return 0;
}
