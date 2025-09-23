#include <stdio.h>

#define MAX_LINE_LEN 100
#define MAX_LINE_NUM 200

char* reverse_word(char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

int main() {
    char line[MAX_LINE_LEN], str2[MAX_LINE_NUM][MAX_LINE_LEN];
    int i=0;
    FILE* fp_in = fopen("lab1p3in", "r");
    FILE *fp_out = fopen("lab1p3out", "w");

    while (fgets(line, MAX_LINE_LEN, fp_in)) {
        sscanf(line, "%s", str2[i]);
        fprintf(fp_out, "%s\n", reverse_word(str2[i]));
    }

    fclose(fp_in); fclose(fp_out);
    return 0;
}