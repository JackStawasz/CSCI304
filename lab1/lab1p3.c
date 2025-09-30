#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Main Function
*  Purpose: Controls program, given the input file, reverses and capitalizes all words while keeping nonalphanumeric characters the same.
*  Input: lab1p3in, the file to be encoded.
*  Output: Returns exit status, and lab1p3out, the encoded file.
*/
int main (int argc, char **argv) {
    char output[100];
    char *poutput = output;
    char tempWord[100];
    char *ptempWord = tempWord;
    char *pwordStart = tempWord;
    char ch;

    // Open file and make sure it exists.
    FILE *fileIn = fopen("lab1p3in", "r");
    if (!fileIn) {
        return EXIT_FAILURE;
    }
    
    // Moves through every single character of the file to encrypt the message.
    while ((ch = fgetc(fileIn)) != EOF) {
        // Check to see if the character is alphabetic or not to know whether or not we need to reverse it.
        if (isalpha(ch)) {
            // Add the character to a temporary buffer that we will reverse once we ahve read the full word.
            *ptempWord = toupper(ch);
            ptempWord++;
        } else {
            // Go through the temporary buffer and reverse the word, then adding the nonalphabetic symbol afterwards.
            while (ptempWord > pwordStart) {
                ptempWord--;
                *poutput = *ptempWord;
                poutput++;
            }

            // Treat underscores as spaces internally.
            if (ch == '_') {
                ch = ' ';
            }

            // Append the nonalphabetic character to the output.
            *poutput = ch;
            poutput++;
        }
    }
    
    // Perform one extra loop of reversing the word to account for a word being right before EOF and add a terminating character.
    while (ptempWord > pwordStart) {
        ptempWord--;
        *poutput++ = *ptempWord;
        poutput++;
    }

    *poutput = '\0';
    
    // Write to the output file, making sure we are allowed to, then close out the opened files.
    FILE *fOut = fopen("lab1p3out", "w");
    if (!fOut) {
        fclose(fileIn);
        return EXIT_FAILURE;
    }
    fprintf(fOut, "%s", output);
    fclose(fileIn);
    fclose(fOut);
    return EXIT_SUCCESS;
}