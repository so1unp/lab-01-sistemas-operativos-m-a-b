#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void imprimir_palabras();

int main()
{
    imprimir_palabras();
    exit(EXIT_SUCCESS);
}

void imprimir_palabras()
{
    int c;
    bool en_palabra = false;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (en_palabra)
            {
                printf("\n");
                en_palabra = false; // No se está en una palabra
            }
        }
        else
        {
            putchar(c);        // Imprimir el carácter
            en_palabra = true; // Se está dentro de una palabra
        }
    }

    if (en_palabra) // Si termina en una palabra
    {
        printf("\n");
    }
}