#include <stdio.h>

#define MAX_LINE_LEN 100
#define MAX_LINE_NUM 200

int main() {
    char line[MAX_LINE_LEN], str2[MAX_LINE_NUM][MAX_LINE_LEN];
    int i=0;
    FILE* fp_in = fopen("lab1p3in", "r");
    FILE *fp_out = fopen("lab1p3out", "w");

    while (fgets(line, MAX_LINE_LEN, fp_in)) {
        sscanf(line, "%s", str2[i]);
        fprintf(fp_out, "%s\n", str2[i]);
    }

    fclose(fp_in); fclose(fp_out);
    return 0;
}