#ifndef __ASCII_ID__
#define __ASCII_ID__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ASCII_INCREMENT_OVERFLOW        1
#define ASCII_OK                        0
#define ASCII_ERROR                    -1
#define ASCII_ERROR_DOUBLE_NUMERIC     -2
#define ASCII_ERROR_DOUBLE_ALPHA       -3
#define ASCII_ERROR_DOUBLE_DELIMETR    -4
#define ASCII_ERROR_MISS_DELIMETR      -5
#define ASCII_ERROR_MAX_SIZE           -6

#define ASCII_MAX_SIZE 10*2

#define ASCII_IS_DELIMITER(_x) (_x == '-')
#define ASCII_IS_NUMERIC(_x) (_x >= '0' && _x <= '9') 
#define ASCII_IS_ALPHA(_x) (_x >= 'A' && _x <= 'Z')

extern char* ascii_parse(const char *str, int *ret_buf);

#endif
