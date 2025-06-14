#include<stdio.h>
#include<stdlib.h>
char** createcanvas(int rows,int col){
	char** canvas=(char**)malloc(rows* sizeof(char*));
	for(int i=0;i<rows;i++){
		canvas[i]=malloc(col* sizeof(char));
	}
	return canvas;
}
void clearcanvas(char** canvas,int rows,int col){
	for(int i=0;i<rows;i++){
		for(int j=0;j<col;j++){
			canvas[i][j]=' ';
		}
	}
}
void drawline(char** canvas,int x1,int x2,int y1,int y2){
	if(x1==x2){
		for(int i=y1;i<=y2;i++){
			canvas[i][x1]='#';
		}
	}
	else if(y1==y2){
		for(int i=x1;i<=x2;i++){
			canvas[y1][i]='#';
		}
	}
}
void drawrectangle(char** canvas,int x1,int x2,int y1,int y2){
	for(int i=x1;i<=x2;i++){
		canvas[y1][i]='#';
		canvas[y2][i]='#';
	}
		for(int i=y1;i<=y2;i++){
		canvas[x1][i]='#';
		canvas[x2][i]='#';
	}
}
void printcanvas(char** canvas,int rows,int col){
		for(int i=0;i<rows;i++){
		for(int j=0;j<col;j++){
			printf("%c",canvas[i][j]);
		}
		printf("\n");
	}
}

int main() {
    int rows, col;
    printf("Enter the number of rows for the canvas: ");
    scanf("%d", &rows);
    printf("Enter the number of columns for the canvas: ");
    scanf("%d", &col);

    char **canvas = createcanvas(rows, col);

    clearcanvas(canvas, rows, col);

    int choice;
    do {
        printf("\nCanvas Menu:\n");
        printf("1. Draw a Line\n");
        printf("2. Draw a Rectangle\n");
        printf("3. Clear Canvas\n");
        printf("4. Print Canvas\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int x1, y1, x2, y2;
        switch (choice) {
            case 1:
                printf("Enter start and end coordinates (x1 y1 x2 y2) for the line: ");
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                drawline(canvas, x1, y1, x2, y2);
                break;
            case 2:
                printf("Enter top-left and bottom-right coordinates (x1 y1 x2 y2) for the rectangle: ");
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                drawrectangle(canvas, x1, y1, x2, y2);
                break;
            case 3:
                clearcanvas(canvas, rows, col);
                printf("Canvas cleared.\n");
                break;
            case 4:
                printcanvas(canvas, rows, col);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    for (int i = 0; i < rows; i++) {
        free(canvas[i]);
    }
    free(canvas);

    return 0;
}