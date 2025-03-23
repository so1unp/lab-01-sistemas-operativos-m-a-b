#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define RANDOM_BYTES 7 // Definimos la cantidad de bytes aleatorios que se van a generar
#define MAX_SIZE_TEXT_ENCRYPT 8 // Definimos el tamaño del texto encriptado

// prototipos
void decrypt_file(char *filename);

int main(int argc, char *argv[])
{
    // Agregar código aquí.
    if( argc == 2){
        decrypt_file(argv[1]);
    }
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}

void decrypt_file(char *filename){

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