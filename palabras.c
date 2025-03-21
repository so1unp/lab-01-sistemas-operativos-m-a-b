#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int input;
    bool is_word = false;
    
    while ((input = getchar()) != EOF) {
        if (input == ' ' || input == '\t' || input == '\n') {
            if (is_word) {
                printf("\n");
                is_word = false;
            }
        } else {
            putchar(input);
            is_word = true;
        }
    }

    exit(EXIT_SUCCESS);
}
