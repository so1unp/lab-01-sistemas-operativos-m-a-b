#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    int c;
    bool en_palabra = false;

    // Leer caracteres uno por uno de la entrada estándar
    while ((c = getchar()) != EOF)
    {
        // Si es un espacio, tabulación o salto de línea
        if (c == ' ' || c == '\t' || c == '\n')
        {
            // Si estábamos dentro de una palabra, la terminamos
            if (en_palabra)
            {
                printf("\n");
                en_palabra = false;
            }
        }
        // Si es un carácter que forma parte de una palabra
        else
        {
            // Imprimimos el carácter
            putchar(c);
            // Marcamos que estamos dentro de una palabra
            en_palabra = true;
        }
    }

    // Si terminamos dentro de una palabra, agregamos un salto de línea final
    if (en_palabra)
    {
        printf("\n");
    }

    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
