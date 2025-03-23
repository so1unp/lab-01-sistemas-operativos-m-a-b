#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void decrypt_from_command_line(char *message) {
    char word[100] = {};
    int j = 0;

    for (int i = 0; message[i] != '\0'; i++) {
        if ((i + 1) % 8 == 0) {
            word[j] = message[i];
            j++;
        }
    }

    word[j] = '\0';

    printf("%s\n", word);
}

void decrypt_from_file(char *filename) {
    int exit = open(filename, O_RDONLY);
    if (exit == -1) {
        perror("Error al abrir el archivo");
        return;
    }

    int word_buffer[8];
    int readed;
    while ((readed = read(exit, word_buffer, sizeof(word_buffer))) > 0) {
        printf("%c", word_buffer[7]);
    }

    if (readed == -1) {
        perror("Error al leer el archivo");
    }

    close(exit);
}

int main(int argc, char *argv[])
{
    int exit = open(argv[1], O_RDONLY);
    if (exit == -1) {
        decrypt_from_command_line(argv[1]);
        
    } else {
        decrypt_from_file(argv[1]);
    }
}


