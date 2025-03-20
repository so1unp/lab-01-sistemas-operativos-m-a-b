#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // Inicializar generador de números aleatorios
    srand(time(NULL));

    int fd_output = STDOUT_FILENO; // Por defecto, salida estándar
    char *message = NULL;
    int message_length = 0;

    if (argc == 2)
    {
        // Sólo mensaje, salida a stdout
        message = argv[1];
        message_length = strlen(message);
    }
    else if (argc == 3)
    {
        // Archivo de salida y mensaje
        fd_output = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_output == -1)
        {
            perror("Error al abrir archivo de salida");
            exit(EXIT_FAILURE);
        }
        message = argv[2];
        message_length = strlen(message);
    }
    else
    {
        // Leer desde entrada estándar
        int capacity = 128;
        message = malloc(capacity);
        if (!message)
        {
            perror("Error de memoria");
            exit(EXIT_FAILURE);
        }

        int c;
        while ((c = getchar()) != EOF)
        {
            if (message_length >= capacity - 1)
            {
                capacity *= 2;
                message = realloc(message, capacity);
                if (!message)
                {
                    perror("Error de memoria");
                    exit(EXIT_FAILURE);
                }
            }
            message[message_length++] = c;
        }

        if (message_length == 0)
        {
            fprintf(stderr, "No se proporcionó ningún mensaje\n");
            free(message);
            exit(EXIT_FAILURE);
        }
    }

    // Encriptar el mensaje: cada byte original precedido por 7 bytes aleatorios
    unsigned char *encrypted = malloc(message_length * 8);
    if (!encrypted)
    {
        perror("Error de memoria");
        if (argc == 1)
            free(message);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < message_length; i++)
    {
        // Generar 7 bytes aleatorios
        for (int j = 0; j < 7; j++)
        {
            encrypted[i * 8 + j] = rand() % 256;
        }
        // Colocar el byte original después de los 7 bytes aleatorios
        encrypted[i * 8 + 7] = message[i];
    }

    // Escribir el mensaje encriptado
    if (write(fd_output, encrypted, message_length * 8) != message_length * 8)
    {
        perror("Error al escribir");
        if (argc == 1)
            free(message);
        free(encrypted);
        exit(EXIT_FAILURE);
    }

    // Cerrar archivo si no es stdout
    if (fd_output != STDOUT_FILENO)
    {
        close(fd_output);
    }

    // Liberar memoria
    if (argc == 1)
        free(message);
    free(encrypted);

    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
