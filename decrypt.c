#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define RANDOM_BYTES 7 // Definimos la cantidad de bytes aleatorios que se van a generar
#define MAX_SIZE_TEXT_ENCRYPT 8 // Definimos el tamaño del texto encriptado

// prototipos
void descrypt_text(char *message);

void descrypt_file(char *filename);

int main(int argc, char *argv[])
{
    if(argc == 2){
        int fileopen = open(argv[1], O_RDONLY);
        if(fileopen != -1){
            close(fileopen);
            descrypt_file(argv[1]); // si es un archivo
        } else{
            descrypt_text(argv[1]);// si es un texto
        } 
    }
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
/*
* Función que desencripta un texto
*/
void descrypt_text(char *message){
    char descrypt_arr[1024];
    int index = 0;

    while(*message != '\0'){
        descrypt_arr[index++] = message[MAX_SIZE_TEXT_ENCRYPT];
        printf("%c",message[MAX_SIZE_TEXT_ENCRYPT]);
        message += MAX_SIZE_TEXT_ENCRYPT;
    }

    descrypt_arr[index] ='\0';
    printf("\n");

    printf("%s",descrypt_arr);

    printf("\n");
}

void descrypt_file(char *filename){

    // abrimos el archivo
    int file = open(filename,O_RDONLY);
    
    char buffer[1024];
    ssize_t readed;
    while ((readed = read(file, buffer, MAX_SIZE_TEXT_ENCRYPT)) > 0) {
        if (readed == MAX_SIZE_TEXT_ENCRYPT) { // Si se lee un bloque completo
            printf("%c", buffer[7]); // Extraemos el ultimo byte
        }
    }
    
    printf("\n");
    close(file);
}