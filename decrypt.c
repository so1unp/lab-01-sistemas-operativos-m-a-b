#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void decrypt_from_command_line(char *message) {

    char word[100] = {};
    int j = 0;

    for (int i = 0; message[i] != '\0'; i++) {
        
        if ((i+1) % 8 == 0) {
            word[j] = message[i];
            j++;
        }

    }

    for (int i = 0; i < 8; i++) {
        printf("%c", word[i]);
    }

}

void decrypt_from_file(char *filename) {
    char word[100] = {};
    char buffer[1024];
    int j = 0;
    int exit = open(filename, O_RDONLY);
    int readed = 0;

    // while((readed = read(exit,buffer,sizeof(buffer))) > 0)
    // {   
    //     if ((readed+1) % 8 == 0) {
    //         if (j < sizeof(word) - 1) {
    //             word[j] = buffer[readed];
    //             j++;
    //         }
    //     }
    // }

    while ((readed = read(exit, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < readed; i++) {
            if ((i+1) % 8 == 0) {
                if (j < (sizeof(word) - 1)) {
                    word[j] = buffer[i];
                    j++;
                }
            }
        }
    }
    
    for (int i = 0; i < 8; i++) {
        printf("%c", word[i]);
    }

    close(exit);
}

int main(int argc, char *argv[])
{
    
    // if (argc == 2) {
    //     decrypt_from_command_line(argv[1]);
    // } else {
    decrypt_from_file(argv[1]);
    // }


    exit(EXIT_SUCCESS);
}


