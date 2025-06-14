#include <stdio.h>

void concat_strings(char str1[], char str2[], int i, int j) {
if (str2[j] == '\0') {
str1[i] = '\0';
return;
}
str1[i] = str2[j];
concat_strings(str1, str2, i + 1, j + 1);
}

int main() {
char str1[100] = "Hello, ";
char str2[] = "World!";
printf("Original strings:\n");
printf("str1: %s\n", str1);
printf("str2: %s\n", str2);
concat_strings(str1, str2, strlen(str1), 0);
printf("Concatenated string: %s\n", str1);
return 0;
}