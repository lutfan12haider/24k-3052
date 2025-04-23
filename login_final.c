#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

char fusername[30];
void registration() {
    char username[30];
    char password[30];
    
    FILE *file = fopen("user.txt", "a");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\t\tError opening file for registration.\n");
        return;
    }
    
    printf("\t\t\t\t\t\t\t\t\t\t\t\tPlease Enter Your UserName: \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t");
    scanf("%s", username);
    
    printf("\t\t\t\t\t\t\t\t\t\t\t\tPlease Enter Your Password: \n");
    char ch;
    int i = 0;
    char npassword[30];
    printf("\t\t\t\t\t\t\t\t\t\t\t\t");
    
    while ((ch = getch()) != '\r') {  
        if (ch == '\b') {  
            if (i > 0) {
                i--;
                printf("\b \b");  
            }
        } else {
            password[i++] = ch;
            printf("*"); 
        }
    }
    password[i] = '\0'; 
    
    printf("\n");

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("\t\t\t\t\t\t\t\t\t\t\t\tUser registered successfully\n");
}

int login() {
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\t\t\t\t\t\tError opening file for login.\n");
        return 1;
    }
    int i=0;
    char username[30], password[30], fpassword[30],ch;
    
    printf("\t\t\t\t\t\t\t\t\t\t\t\tEnter Username: \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t");
    scanf("%s", username);
    
    printf("\t\t\t\t\t\t\t\t\t\t\t\tEnter Password: \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t");
     while ((ch = getch()) != '\r') {  
        if (ch == '\b') {  
            if (i > 0) {
                i--;
                printf("\b \b");  
            }
        } else {
            password[i++] = ch;
            printf("*"); 
        }
    }
    password[i] = '\0'; 
    
    printf("\n");
    
    while (fscanf(file, "%s %s", fusername, fpassword) != EOF) {
        if (strcmp(username, fusername) == 0 && strcmp(password, fpassword) == 0) {
            fclose(file);
            return 1;
        }
    }
    
    printf("\t\t\t\t\t\t\t\t\t\t\t\tIncorrect Username or Password\n");
    fclose(file);
    return 0;
}

void log() {
    int choice, l;
    int login_count = 0;
    
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tWelcome to Fast University\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\tPlease Enter Your Desired Choice\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t1 To Login\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t2 To Create New Account\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: {
            int l = login();
            if (l == 1) {
                login_count = 0;
                system("cls");  
                printf("\t\t\t\t\t\t\t\t\t\t\t\tLogin successful. Welcome %s\n", fusername);
            } else {
                login_count++;
                if (login_count >= 3) {
                    printf("Too many failed login attempts\n");
                    exit(0);
                }
                printf("Login failed! Please try again.\n");
                system("cls");  
            }
            break;
        }
        case 2: {
            registration();
            break;
        }
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

int main() {
    log();
}

