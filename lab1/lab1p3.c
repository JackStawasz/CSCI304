#include <stdio.h>
#include <string.h>
#include <ctype.h> // Provides "isalpha" function

#define MAX_LINE_LEN 100 // Max 100 characters per line of input file
#define MAX_WORD_LEN 20  // Max 20 characters per word in line

char* process_word(char* str) {
    int len = strlen(str);

    // Perform character swaps
    for (int i=0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = toupper(str[len - i - 1]);
        str[len - i - 1] = temp;
    }

    // Capitalize letters
    for (int i=0; i < len; i++) {
        str[i] = toupper(str[i]);
    }
    
    return str;
}

char* process_line(char* line) {
    static char str_out[MAX_LINE_LEN];
    str_out[0] = '\0';
    char word[MAX_WORD_LEN];
    int char_idx = 0; int word_idx = 0;
    while (line[char_idx] != '\0' && char_idx < MAX_LINE_LEN) {
        if (isalpha(line[char_idx])) { // Save letter to word
            word[word_idx++] = line[char_idx++];
        } else { // Save reversed word to output
            word[word_idx] = '\0';
            strcat(str_out, process_word(word));
            // Replace '_' with ' '
            str_out[strlen(str_out)] = (line[char_idx] == '_' ? ' ' : line[char_idx]);
            memset(word, 0, sizeof(word)); // Clear word buffer
            char_idx++; word_idx = 0;
        }
    }

    // Append any remaining word
    if (word_idx > 0) {
        word[word_idx] = '\0';
        strcat(str_out, process_word(word));
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