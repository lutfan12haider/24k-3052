#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Declare the tree structure
struct tree {
    int age;
    float height;
    char type[10];  // Tree type (Oak, Palm, Pine, etc.)
};

// Function to assign a tree type based on index
void assigntree(char *type, int index) {
    if (index % 3 == 0) {
        strcpy(type, "oak");
    } else if (index % 3 == 1) {
        strcpy(type, "palm");
    } else {
        strcpy(type, "pine");
    }
}

// Function to initialize the forest with random values for height, age, and type
void initializeforest(struct tree** forest, int row, int col) {
    // Loop through each row and column in the forest
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // Assign height based on indices
            forest[i][j].height = i + j + 1; // Height formula: i + j + 1
            // Assign age based on indices
            forest[i][j].age = (i + j) * 2 + 1; // Age formula: (i + j) * 2 + 1
            // Assign tree type based on the sum of indices
            assigntree(forest[i][j].type, i + j);  // Type assigned based on i + j
        }
    }
}

// Function to print the tree with colors
void printTree(struct tree t) {
    // ANSI escape codes for colors
    const char* oakColor = "\033[0;32m";    // Green for Oak
    const char* palmColor = "\033[0;33m";   // Yellow for Palm
    const char* pineColor = "\033[0;34m";   // Blue for Pine
    const char* resetColor = "\033[0m";     // Reset color to default

    // Print the tree details with colors
    if (strcmp(t.type, "oak") == 0) {
        printf("Type: %s%s\033[0m, Age: %d, Height: %.2f\n", oakColor, t.type, t.age, t.height);
    } else if (strcmp(t.type, "palm") == 0) {
        printf("Type: %s%s\033[0m, Age: %d, Height: %.2f\n", palmColor, t.type, t.age, t.height);
    } else if (strcmp(t.type, "pine") == 0) {
        printf("Type: %s%s\033[0m, Age: %d, Height: %.2f\n", pineColor, t.type, t.age, t.height);
    }
}

// Main function
int main() {
    int row, col;

    // Ask user for the number of rows and columns for the forest
    printf("Enter the number of rows: ");
    scanf("%d", &row);
    printf("Enter the number of columns: ");
    scanf("%d", &col);

    // Dynamically allocate memory for the forest (2D array of tree structures)
    struct tree** forest = (struct tree**)malloc(row * sizeof(struct tree*));
    for (int i = 0; i < row; i++) {
        forest[i] = (struct tree*)malloc(col * sizeof(struct tree));
    }

    // Initialize the forest with values
    initializeforest(forest, row, col);

    // Print the forest details (with colors)
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("Tree[%d][%d] -> ", i, j);
            printTree(forest[i][j]);  // Call the function to print tree details with color
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < row; i++) {
        free(forest[i]);
    }
    free(forest);

    return 0;
}
