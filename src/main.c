#include <stdio.h>
#include"ascii_counter.h"

static void _swap_ptr(char** a, char** b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char* argv[])
{
    int rc = 0;
    char *data = NULL;
    char *raw_data = NULL;
    int it = (argc == 3 && ASCII_IS_NUMERIC(*argv[2]))? atoi(argv[2]): 1;

    if (argc > 1) {

        printf("%s\n", argv[1]);
        raw_data = ascii_parse(argv[1], &rc);
        printf("%s\n", raw_data);

        while (it > 0 && rc == ASCII_OK)
        {
            data = ascii_parse(raw_data, &rc);
            if (rc == ASCII_OK) {
                printf("%s\n", data);
                _swap_ptr(&data, &raw_data);
                free(data);
            }else{
                printf("error:%d\n", rc);
                break;
            }
            it--;

            usleep(55000);
        }
    }
    
    return 0;
}
