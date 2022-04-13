#include <stdio.h>
#include"ascii_counter.h"



int main(int argc, char* argv[])
{
    int rc = 0;
    char *data = NULL;


    // есть входной аргумент
    if (argc > 1) 
    {
        data = ascii_parse(argv[1], &rc);
        if (rc == ASCII_OK) {
            printf("input:%s output:%s\n", argv[1], data);
            free(data);
        }
        else
            printf("rc:%d", rc);
    }
    else 
    {
        printf("no input data...\n");
    }

    return 0;
}
