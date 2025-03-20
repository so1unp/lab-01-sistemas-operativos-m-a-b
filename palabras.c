#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Agregar código aquí.
    int c;
    char buffer[1024];
    int index = 0; 

    while( (c = getchar()) != EOF) {
        if(c == ' '|| c == '\t' || c == '\n'){ //Compara si es un separador
            if(index > 0){
                buffer[index] = '\0'; // Termina la palabra
                printf("%s\n", buffer);
                index = 0;
            }
        } else{
            if(index < 1023){
                buffer[index++] = (char)c;
            } else{
                fprintf(stderr, "Error\n"); // si se rebalsa
                exit(EXIT_FAILURE);
            }
        }
    }
    // Cuando llega a la ultima palabra
    if (index > 0) { 
        buffer[index] = '\0';
        printf("%s\n", buffer);
    } 
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
