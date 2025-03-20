#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Agregar código aquí.
    int result = 0;
    if(argc > 1){
        for(int i = 0; i < argc; i++){
            result += atoi(argv[i]);
        }
    } else {
        int c;
        result = 0;
        while ((c = getchar()) != EOF) {
            result += atoi((char *)&c);
        }
    } 
    printf("%d\n",result);
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
