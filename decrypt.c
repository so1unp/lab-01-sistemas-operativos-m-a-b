#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd_input = STDIN_FILENO; // Por defecto, entrada estándar
    char *input_data = NULL;     // Buffer para los datos encriptados
    off_t total_size = 0;        // Tamaño total de los datos encriptados

    // Procesar argumentos de línea de comando
    if (argc == 2)
    {
        // Si hay un argumento, es el archivo de entrada
        fd_input = open(argv[1], O_RDONLY);
        if (fd_input == -1)
        {
            perror("Error al abrir archivo de entrada");
            exit(EXIT_FAILURE);
        }
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Uso: %s [archivo_entrada]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Obtener el tamaño del archivo/datos de entrada
    struct stat st;

    if (fd_input != STDIN_FILENO)
    {
        // Si es un archivo, obtenemos su tamaño directamente
        if (fstat(fd_input, &st) == -1)
        {
            perror("Error al obtener información del archivo");
            close(fd_input);
            exit(EXIT_FAILURE);
        }
        total_size = st.st_size;

        // Leer los datos del archivo
        input_data = malloc(total_size);
        if (!input_data)
        {
            perror("Error de memoria");
            close(fd_input);
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_read = read(fd_input, input_data, total_size);
        if (bytes_read != total_size)
        {
            perror("Error al leer el archivo");
            free(input_data);
            close(fd_input);
            exit(EXIT_FAILURE);
        }

        close(fd_input);
    }
    else
    {
        // Si es entrada estándar, leemos todo a un buffer
        char buffer[4096];
        ssize_t bytes_read;
        size_t capacity = 4096;

        input_data = malloc(capacity);
        if (!input_data)
        {
            perror("Error de memoria");
            exit(EXIT_FAILURE);
        }

        while ((bytes_read = read(fd_input, buffer, sizeof(buffer))) > 0)
        {
            // Ampliar el buffer si es necesario
            if (total_size + bytes_read > capacity)
            {
                capacity *= 2;
                char *temp = realloc(input_data, capacity);
                if (!temp)
                {
                    perror("Error de memoria");
                    free(input_data);
                    exit(EXIT_FAILURE);
                }
                input_data = temp;
            }

            // Copiar los datos leídos al buffer
            memcpy(input_data + total_size, buffer, bytes_read);
            total_size += bytes_read;
        }

        if (bytes_read == -1)
        {
            perror("Error al leer de la entrada estándar");
            free(input_data);
            exit(EXIT_FAILURE);
        }
    }

    // Verificar que el tamaño sea múltiplo de 8 (cada byte original + 7 bytes aleatorios)
    if (total_size % 8 != 0)
    {
        fprintf(stderr, "Formato de datos de entrada inválido\n");
        free(input_data);
        exit(EXIT_FAILURE);
    }

    // Calcular el tamaño del mensaje original
    size_t original_size = total_size / 8;
    char *decrypted = malloc(original_size + 1); // +1 para el null-terminator
    if (!decrypted)
    {
        perror("Error de memoria");
        free(input_data);
        exit(EXIT_FAILURE);
    }

    // Desencriptar el mensaje (extraer cada 8vo byte)
    for (size_t i = 0; i < original_size; i++)
    {
        decrypted[i] = input_data[i * 8 + 7]; // Cada 8vo byte es parte del mensaje original
    }
    decrypted[original_size] = '\0'; // Agregar null-terminator

    // Escribir el mensaje desencriptado a la salida estándar
    if (write(STDOUT_FILENO, decrypted, original_size) != original_size)
    {
        perror("Error al escribir a la salida estándar");
        free(input_data);
        free(decrypted);
        exit(EXIT_FAILURE);
    }

    printf("\n");

    // Liberar memoria
    free(input_data);
    free(decrypted);

    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
