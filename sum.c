#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    // Agregar código aquí.
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            sum += atoi(argv[i]);
        }
    }
    else
    {
        int num = 0;
        do
        {
            num = getchar();
            sum += atoi((char *)&num);
        } while (num != EOF);
        }
    printf("La suma es: %d\n", sum);
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
