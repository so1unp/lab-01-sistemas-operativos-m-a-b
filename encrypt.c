#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

void encrypt_command_line(char *message) {

    srand(time(0));
    int randoms[8];

    for (int i = 0; message[i] != '\0'; i++) { // \0 es caracter nulo, recorre el string hasta encontrar uno
        
        for (int j = 0; j < 7; j++) {
            randoms[j] = (rand() % (126 - 32 + 1)) + 32;
        }
        randoms[7] = message[i];
        for (int j = 0; j < 8; j++) {
            printf("%c", randoms[j]);
        }
    }

}

void encrypt_and_save_in_file(char *filename, char *message) {
    int exit = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    srand(time(0));
    int randoms[8];

    for (int i = 0; message[i] != '\0'; i++) { // \0 es caracter nulo, recorre el string hasta encontrar uno
        
        for (int j = 0; j < 7; j++) {
            randoms[j] = (rand() % (126 - 32 + 1)) + 32;
        }
        randoms[7] = message[i];
        write(exit, randoms, sizeof(randoms));
        
    }

    close(exit);
}

int main(int argc, char *argv[]) {

    if (argc == 2) {
        encrypt_command_line(argv[1]);
    } else {
        encrypt_and_save_in_file(argv[1], argv[2]);
    }

    return EXIT_SUCCESS;
}

