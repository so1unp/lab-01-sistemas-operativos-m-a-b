#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char *argv[])
// {
//     int result = 0;
//     int input;
//     int buffer[] = {};

//     if (argc > 1)
//     {
//         for (int i = 0; i < argc; i++)
//         {
//             result += atoi(argv[i]);
//         }
//         printf("%d",result);
//     } else {
//         input = getchar();
//         while (input != EOF)
//         {
//             result += atoi((char *)&input);
//             input = getchar();
//         }
//         printf("%d",result);
//     }

//     exit(EXIT_SUCCESS);

// }
int main(int argc, char *argv[])
{
    int result = 0;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)\
        {
            result += atoi(argv[i]);
        }
        printf("%d\n", result);
    }
    else
    {
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            result += atoi(buffer);
        }
        printf("%d\n", result);
    }

    return 0;
}



