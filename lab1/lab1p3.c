#include <stdio.h>
#include <string.h>
#include <ctype.h> // Provides "isalpha" function

#define MAX_LINE_LEN 100 // Max 100 characters per line of input file
#define MAX_WORD_LEN 20  // Max 20 characters per word in line

char* reverse_word(char* str) {
    int len = strlen(str);

    // Perform character swaps
    for (int i=0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

char* process_line(char* line) {
    // Copy line into mutable string
    static char str_in[MAX_LINE_LEN];
    sscanf(line, "%s", str_in);

    static char str_out[MAX_LINE_LEN];
    char word[MAX_WORD_LEN];
    int char_idx = 0; int word_idx = 0;
    while (str_in[char_idx] != '\0' && char_idx < MAX_LINE_LEN) {
        // Reverse & Save word when non-alphabetical char appears
        if (!isalpha(str_in[char_idx])) {
            strcat(str_out, reverse_word(word));
            // Replace '_' with ' '
            str_out[strlen(str_out)] = (str_in[char_idx] == '_' ? ' ' : str_in[char_idx]);
            memset(word, 0, sizeof(word)); // Clear word buffer
            char_idx++; word_idx = 0;
            break;
        }
        word[word_idx] = str_in[char_idx++];
    }

    return str_out;
}

int main() {
    char line[MAX_LINE_LEN];
    FILE* fp_in = fopen("lab1p3in", "r");
    FILE *fp_out = fopen("lab1p3out", "w");

    // Write each processed line to output file
    while (fgets(line, MAX_LINE_LEN, fp_in)) {
        fprintf(fp_out, "%s\n", process_line(line));
    }

    fclose(fp_in); fclose(fp_out);
    return 0;
}