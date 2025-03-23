#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define RANDOM_BYTES 7 // Definimos la cantidad de bytes aleatorios que se van a generar
#define MAX_SIZE_TEXT_ENCRYPT 8 // Definimos el tamaño del texto encriptado

// prototipos
void encrypt_text(char *message);

void encrypt_file(char *filename);

void encrypt_file_more_text(char *filename, char *message);

void show_message_encrypt(char *message_encrypt);

int main(int argc, char *argv[])
{
    srand((unsigned int) time(NULL)); // inicalizamos la semilla para el random

    if(argc == 2){
        int fileopen = open(argv[1], O_RDONLY);
        if(fileopen != -1){
            close(fileopen);
            encrypt_file(argv[1]); // si es un archivo
        } else{
            encrypt_text(argv[1]);// si es un texto
        }
        
    } else if(argc == 3){
        encrypt_file_more_text(argv[1], argv[2]); //si es un archivo mas el texto
    }
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}

void encrypt_text(char *message){


    char random[MAX_SIZE_TEXT_ENCRYPT];

    while(*message != '\0'){
        for(int i = 0; i < RANDOM_BYTES; i++){
            random[i] = (char) (rand() % (126 - 32 + 1)) + 32; // generamos un byte aleatorio
        }
        random[7] = *message;
        
        show_message_encrypt(random);

        message++; // avanzamos al siguiente caracter
    } 
    printf("\n"); 
}

void encrypt_file(char *filename){
    int file = open(filename,O_RDONLY);

    if (file == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    
    char random[MAX_SIZE_TEXT_ENCRYPT];
    char buffer[1024];
    ssize_t readed;

    while((readed = read(file, buffer, sizeof(buffer))) > 0){
        for(ssize_t i = 0; i < readed; i++){
            for(int j = 0; j < RANDOM_BYTES; j++){
                random[j] = (char) (rand() % (126 - 32 + 1)) + 32; // generamos un byte aleatorio 
            }
            random[7] = buffer[i];
            show_message_encrypt(random);
        }
    }
    printf("\n");
    close(file);
}

void encrypt_file_more_text(char *filename, char *message){
    (void) filename;
    (void) message;
}

void show_message_encrypt(char *message_encrypt){

    for(int i = 0; i < MAX_SIZE_TEXT_ENCRYPT; i++){
        printf("%c", message_encrypt[i]);
    }
}

