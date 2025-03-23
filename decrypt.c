#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFER_SIZE 4096        /* Tamaño del buffer para lectura (4KB) */
#define RANDOM_BYTES_POR_CHAR 7 /* Número de bytes aleatorios por cada carácter */

int leer_de_archivo(int fd, char *buffer, int size);
int leer_de_stdin(char *buffer, int max_size);
int decriptar_mensaje(char *encrypted, int encrypted_size, char *decrypted);
int escribir_a_output(int fd, char *data, int size);

int main(int argc, char *argv[])
{
    int fd_input = STDIN_FILENO;        /* Por defecto, entrada estándar */
    char input_buffer[BUFFER_SIZE * 8]; /* Buffer para los datos encriptados */
    int total_size = 0;                 /* Tamaño total de los datos encriptados */

    switch (argc)
    {
    case 1: /* Sin argumentos: leer de stdin */
        total_size = leer_de_stdin(input_buffer, sizeof(input_buffer));
        if (total_size == -1)
        {
            exit(EXIT_FAILURE);
        }
        break;

    case 2: /* Un argumento: bin/decrypt "mensaje" */
        /* Si hay un argumento, es el archivo de entrada */
        fd_input = open(argv[1], O_RDONLY);
        if (fd_input == -1)
        {
            write(STDERR_FILENO, "Error al abrir archivo de entrada\n", 35);
            exit(EXIT_FAILURE);
        }

        /* Obtener el tamaño del archivo */
        struct stat st;
        if (fstat(fd_input, &st) == -1)
        {
            write(STDERR_FILENO, "Error al obtener información del archivo\n", 42);
            close(fd_input);
            exit(EXIT_FAILURE);
        }

        total_size = st.st_size;

        /* Verificar que el tamaño no exceda el buffer */
        if (total_size > sizeof(input_buffer))
        {
            write(STDERR_FILENO, "Error: Archivo demasiado grande\n", 33);
            close(fd_input);
            exit(EXIT_FAILURE);
        }

        /* Leer los datos del archivo */
        if (leer_de_archivo(fd_input, input_buffer, total_size) != 0)
        {
            close(fd_input);
            exit(EXIT_FAILURE);
        }

        close(fd_input);
        break;

    default:
        write(STDERR_FILENO, "Uso: decrypt [archivo_entrada] / decrypt\n", 42);
        exit(EXIT_FAILURE);
    }

    /* Buffer para el mensaje desencriptado */
    char decrypted_data[BUFFER_SIZE];

    /* Desencriptar el mensaje */
    int decrypted_size = decriptar_mensaje(input_buffer, total_size, decrypted_data);
    if (decrypted_size == -1)
    {
        exit(EXIT_FAILURE);
    }

    /* Escribir mensaje desencriptado a la salida estándar */
    if (escribir_a_output(STDOUT_FILENO, decrypted_data, decrypted_size) != 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Terminar programa con éxito */
    exit(EXIT_SUCCESS);
}

/*
 * Función: leer_de_archivo
 * -----------------------
 * Lee datos desde un archivo específico.
 *
 * Parámetros:
 *   fd - Descriptor del archivo a leer
 *   buffer - Puntero donde se almacenarán los datos leídos
 *   size - Tamaño exacto a leer
 *
 * Retorna: 0 en caso de éxito, -1 en caso de error
 */
int leer_de_archivo(int fd, char *buffer, int size)
{
    ssize_t bytes_read = read(fd, buffer, size);

    if (bytes_read != size)
    {
        write(STDERR_FILENO, "Error al leer el archivo\n", 25);
        return -1;
    }

    return 0;
}

/*
 * Función: leer_de_stdin
 * ------------------------
 * Lee todos los datos disponibles desde la entrada estándar usando getchar().
 *
 * Parámetros:
 *   buffer - Puntero al buffer donde se almacenarán los datos
 *   max_size - Tamaño máximo del buffer
 *
 * Retorna: Número de bytes leídos o -1 en caso de error
 */
int leer_de_stdin(char *buffer, int max_size)
{
    int total = 0;
    int c;

    /* Leer caracteres hasta encontrar EOF (Ctrl+D) */
    while ((c = getchar()) != EOF)
    {
        /* Verificar si hay espacio en el buffer */
        if (total >= max_size)
        {
            write(STDERR_FILENO, "Error: Datos de entrada demasiado grandes\n", 42);
            return -1;
        }

        /* Almacenar el carácter leído */
        buffer[total++] = c;
    }

    /* Verificar que se haya leído algún dato */
    if (total == 0)
    {
        write(STDERR_FILENO, "Error: No se proporcionaron datos de entrada\n", 46);
        return -1;
    }

    return total;
}

/*
 * Función: decriptar_mensaje
 * ------------------------
 * Desencripta un mensaje extrayendo cada byte original (cada 8vo byte).
 *
 * Parámetros:
 *   encrypted - Buffer con los datos encriptados
 *   encrypted_size - Tamaño de los datos encriptados
 *   decrypted - Buffer donde se almacenará el mensaje desencriptado
 *
 * Retorna: Tamaño del mensaje desencriptado
 */
int decriptar_mensaje(char *encrypted, int encrypted_size, char *decrypted)
{
    /* Verificar que el tamaño sea múltiplo de la cantidad de bytes por carácter + 1 */
    if (encrypted_size % (RANDOM_BYTES_POR_CHAR + 1) != 0)
    {
        write(STDERR_FILENO, "Formato de datos de entrada inválido\n", 38);
        return -1;
    }

    /* Calcular el tamaño del mensaje original */
    int original_size = encrypted_size / (RANDOM_BYTES_POR_CHAR + 1);

    /* Extraer cada byte original (cada RANDOM_BYTES_POR_CHAR + 1 byte) */
    for (int i = 0; i < original_size; i++)
    {
        decrypted[i] = encrypted[i * (RANDOM_BYTES_POR_CHAR + 1) + RANDOM_BYTES_POR_CHAR];
    }

    return original_size;
}

/*
 * Función: escribir_a_output
 * ------------------------
 * Escribe datos al descriptor de archivo especificado.
 *
 * Parámetros:
 *   fd - Archivo donde escribir
 *   data - Datos a escribir
 *   size - Tamaño de los datos en bytes
 *
 * Retorna: 0 en caso de éxito, -1 en caso de error
 */
int escribir_a_output(int fd, char *data, int size)
{
    int bytes_escritos = write(fd, data, size);

    if (bytes_escritos != size)
    {
        write(STDERR_FILENO, "Error al escribir datos\n", 24);
        return -1;
    }

    write(STDOUT_FILENO, "\n", 1); // Añadir nueva línea al final

    return 0;
}