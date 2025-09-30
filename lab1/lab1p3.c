#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Main Function
*  Purpose: Controls program, given the input file, reverses and capitalizes all words while keeping nonalphanumeric characters the same.
*  Input: lab1p3in, the file to be encoded.
*  Output: Returns exit status, and lab1p3out, the encoded file.
*/
int main (void) {
    char output[100];
    char *poutput = output;
    char tempword[100];
    char *ptempword = tempword;
    char *pwordstart = tempword;
    char ch;

    // Open file and make sure it exists.
    FILE *fpin = fopen("lab1p3in", "r");
    if (!fpin) {
        return EXIT_FAILURE;
    }
    
    // Moves through every single character of the file to encrypt the message.
    while ((ch = fgetc(fpin)) != EOF) {
        // Check to see if the character is alphanumeric or not to know whether or not we need to reverse it.
        if (isalnum(ch)) {
            // Add the character to a temporary buffer that we will reverse once we ahve read the full word.
            *ptempword = toupper(ch);
            ptempword++;
        } else {
            // Go through the temporary buffer and reverse the word, then adding the nonalphanumeric symbol afterwards.
            while (ptempword > pwordstart) {
                ptempword--;
                *poutput = *ptempword;
                poutput++;
            }
            if (ch == '_') {
                ch = ' ';
            }
            *poutput = toupper(ch);
            poutput++;
   
        }
       
    }
    
    // Perform one extra loop of reversing the word to account for a word being right before EOF and add a terminating character.
    while (ptempword > pwordstart) {
        ptempword--;
        *poutput++ = *ptempword;
    }

    *poutput = '\0';
    
    // Write to the output file, making sure we are allowed to, then close out the opened files.
    FILE *fpout = fopen("lab1p3out", "w");
    if (!fpout) {
        fclose(fpin);
        return EXIT_FAILURE;
    }
    fprintf(fpout, "%s", output);
    fclose(fpin);
    fclose(fpout);
    return EXIT_SUCCESS;
}