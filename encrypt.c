#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFER_SIZE 4096        /* Tamaño del buffer (4KB) */
#define RANDOM_BYTES_POR_CHAR 7 /* Número de bytes aleatorios por cada carácter */

int leer_de_stdin(char *buffer, int max_size);
int encriptar_mensaje(char *message, int message_length, unsigned char *encrypted);
int escribir_a_output(int fd, unsigned char *data, int size);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int fd_output = STDOUT_FILENO;                                           /* Por defecto, salida estándar */
    char message_buffer[BUFFER_SIZE];                                        /* Buffer para el mensaje */
    int message_length = 0;                                                  /* Longitud del mensaje */
    unsigned char encrypted_data[BUFFER_SIZE * (RANDOM_BYTES_POR_CHAR + 1)]; /* Buffer para el mensaje encriptado */
    int encrypted_size = 0;                                                  /* Tamaño del mensaje encriptado */

    switch (argc)
    {
    case 1: /* Sin argumentos: leer de stdin */
        message_length = leer_de_stdin(message_buffer, BUFFER_SIZE);
        encrypted_size = encriptar_mensaje(message_buffer, message_length, encrypted_data);
        break;

    case 2: /* Un argumento: bin/encrypt "mensaje" */
        encrypted_size = encriptar_mensaje(argv[1], strlen(argv[1]), encrypted_data);
        break;

    case 3: /* Dos argumentos: bin/encrypt archivo.msg "mensaje" */
        /* Abrir archivo de salida en modo escritura, si no existe se crea y si existe se vacia. Con permisos (P:l/e, G:l, O:l = 0644)*/
        fd_output = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_output == -1)
        {
            write(STDERR_FILENO, "Error al abrir archivo de salida\n", 33);
            exit(EXIT_FAILURE);
        }

        encrypted_size = encriptar_mensaje(argv[2], strlen(argv[2]), encrypted_data);
    }

    /* Escribir datos encriptados */
    if (escribir_a_output(fd_output, encrypted_data, encrypted_size) != 0)
    {
        /* Error al escribir, salir */
        if (fd_output != STDOUT_FILENO)
        {
            close(fd_output);
        }
        exit(EXIT_FAILURE);
    }

    /* Cerrar archivo si no es stdout */
    if (fd_output != STDOUT_FILENO)
    {
        close(fd_output);
    }

    /* Terminar programa con éxito */
    exit(EXIT_SUCCESS);
}

/*
 * Función: leer_de_stdin
 * -------------------------
 * Lee un mensaje desde la entrada estándar (stdin).
 *
 * Parámetros:
 *   buffer - Buffer donde se almacenará el mensaje leído
 *   max_size - Tamaño máximo del buffer
 *
 * Retorna: Longitud del mensaje leído
 */
int leer_de_stdin(char *buffer, int max_size)
{
    int length = 0;
    int c;

    /* Leer caracteres hasta encontrar EOF (Ctrl+D) o llenar el buffer */
    while ((c = getchar()) != EOF && length < max_size - 1)
    {
        /* Almacenar el carácter leído */
        buffer[length++] = c;
    }

    /* Verificar que se haya leído algún dato */
    if (length == 0)
    {
        write(STDERR_FILENO, "Error: No se proporcionó ningún mensaje\n", 40);
        exit(EXIT_FAILURE);
    }

    /* Verificar si el buffer se llenó completamente */
    if (length >= max_size - 1 && c != EOF)
    {
        write(STDERR_FILENO, "Advertencia: El mensaje es demasiado largo y será truncado\n", 58);

        /* Leer y descartar el resto de la entrada */
        while (getchar() != EOF)
            ;
    }

    return length;
}

/*
 * Función: encriptar_mensaje
 * ------------------------
 * Encripta un mensaje añadiendo 7 bytes aleatorios antes de cada byte del mensaje.
 *
 * Parámetros:
 *   message - Buffer con el mensaje original
 *   message_length - Longitud del mensaje original
 *   encrypted - Buffer donde se almacenará el mensaje encriptado
 *
 * Retorna: Tamaño del mensaje encriptado en bytes
 */
int encriptar_mensaje(char *message, int message_length, unsigned char *encrypted)
{
    /* Encriptar cada byte del mensaje */
    for (int i = 0; i < message_length; i++)
    {
        /* Posición base para este carácter en el mensaje encriptado */
        int base_pos = i * (RANDOM_BYTES_POR_CHAR + 1);

        /* Generar RANDOM_BYTES_POR_CHAR bytes aleatorios */
        for (int j = 0; j < RANDOM_BYTES_POR_CHAR; j++)
        {
            encrypted[base_pos + j] = rand() % 256;
        }

        /* Añadir el byte original después de los bytes aleatorios */
        encrypted[base_pos + RANDOM_BYTES_POR_CHAR] = message[i];
    }

    /* Retornar el tamaño del mensaje encriptado */
    return message_length * (RANDOM_BYTES_POR_CHAR + 1);
}

/*
 * Función: escribir_a_output
 * ------------------------
 * Escribe los datos encriptados al descriptor de archivo especificado.
 *
 * Parámetros:
 *   fd - Archivo donde escribir
 *   data - Datos a escribir
 *   size - Tamaño de los datos en bytes
 *
 * Retorna: 0 en caso de éxito, -1 en caso de error
 */
int escribir_a_output(int fd, unsigned char *data, int size)
{
    int bytes_written = write(fd, data, size);

    if (bytes_written != size)
    {
        write(STDERR_FILENO, "Error al escribir datos\n", 24);
        return -1;
    }

    return 0;
}