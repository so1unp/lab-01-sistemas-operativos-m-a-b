#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumar_argumentos(int argc, char *argv[]);
int sumar_entrada_estandar();

int main(int argc, char *argv[])
{
    int sum = 0;

    if (argc > 1)
    {
        sum = sumar_argumentos(argc, argv);
    }
    else
    {
        sum = sumar_entrada_estandar();
    }

    printf("La suma es: %d\n", sum); // Imprimir la suma

    exit(EXIT_SUCCESS);
}

// Función para sumar los argumentos de la línea de comandos
int sumar_argumentos(int argc, char *argv[])
{
    int sum = 0;
    for (int i = 1; i < argc; i++)
    {
        sum += atoi(argv[i]);
    }
    return sum;
}

// Función para sumar números desde la entrada estándar
int sumar_entrada_estandar()
{
    int sum = 0;
    char buffer[256];
    int index = 0;
    int n = getchar(); // Leer el primer carácter

    while (n != EOF) // Leer línea por línea hasta EOF
    {
        if (n == '\n' || n == ' ' || n == '\t')
        {
            buffer[index] = '\0'; // Terminar la cadena
            if (index > 0)
            {                        // Verificar que hay algo que sumar
                sum += atoi(buffer); // Convertir a entero y sumar
            }
            index = 0; // Reiniciar índice para la siguiente línea
        }
        else
        {
            buffer[index++] = (char)n; // Almacenar el carácter
        }

        n = getchar(); // Leer el siguiente carácter
    }

    // Procesar el último número si quedó algo en el buffer
    if (index > 0)
    {
        buffer[index] = '\0';
        sum += atoi(buffer);
    }

    return sum;
}