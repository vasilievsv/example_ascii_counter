#include "ascii_counter.h"

static char *_strdup2(const char *src) 
{
    size_t len = strlen(src) + 1;
    char *dst = malloc(len);
    
    if (dst == NULL) 
        return NULL;
    memcpy(dst, src, len);

    return dst;
}

static inline int ascii_increment_alpha(char *ch)
{
    if (*ch >= 'B' && *ch <= 'Z')
    {
        (*ch)++;
        if (*ch > 'Z') {
            *ch = 'B';
            return ASCII_INCREMENT_OVERFLOW;
        };

        return 0;
    }

    return ASCII_ERROR;
}

static inline int ascii_increment_numeric(char *ch)
{
    if (*ch >= '1' && *ch <= '9') {

        (*ch)++;
        if (*ch > '9') {
            *ch = '1';
            return ASCII_INCREMENT_OVERFLOW;
        };

        return 0;
    }

    return ASCII_ERROR;
}

char* ascii_realloc_buff(char* buff)
{
    static const char *tmp_token = "B1-";
    static int tmp_token_len     = 3;

    if (buff == NULL) 
        return;

    int buff_len = strlen(buff);

    char *new_buff = (char*)malloc(buff_len + tmp_token_len + 1); // + zero
    if (new_buff == NULL) 
        return NULL;

    memcpy(new_buff,tmp_token, tmp_token_len);
    memcpy(new_buff + tmp_token_len, buff, buff_len);
    //swap
    free((void*)buff);
    buff = new_buff;
}

static int ascii_check_policy(const char *str)
{
    size_t i = 0;
    size_t errcnt = 0;
    size_t lencnt = 0;
    size_t delimiter_cnt=0;

    while (str[i] != '\0') {

        //считаем разделители
        if (str[i] == '-') {
            errcnt++;
            delimiter_cnt++;
        }
        else
            errcnt = 0;
        // проверка двух разделителей подряд 
        if (errcnt > 1) 
            goto fail;
        //подсчет размера строки без терминирующего нуля
        i++; 
    }

    // слишком короткий
    if(i<=1)
        goto fail;
    // превышение ограничения (минус разделители)
    if((i-delimiter_cnt) > ASCII_MAX_SIZE)
        goto fail;
    //  нет разделителей и больше двух симовлов 
    if(delimiter_cnt==0 && i>2) 
        goto fail;
    // проверка разделителя на границах
    if (str[0] == '-' || str[i-1] == '-') 
        goto fail;

    return ASCII_OK;
fail:
    return ASCII_ERROR;
}

int ascii_validate_token(char h_symbol, char l_symbol, int* cnt)
{
    if(ASCII_IS_NUMERIC(h_symbol) || h_symbol=='A')
        return ASCII_ERROR;

    if(ASCII_IS_ALPHA(l_symbol) || l_symbol == '0')
        return ASCII_ERROR;

    if (ASCII_IS_NUMERIC(h_symbol) && ASCII_IS_NUMERIC(l_symbol))
        return ASCII_ERROR;

    if (ASCII_IS_ALPHA(h_symbol) && ASCII_IS_ALPHA(l_symbol))
        return ASCII_ERROR;

    if (ASCII_IS_NUMERIC(h_symbol) && ASCII_IS_ALPHA(l_symbol))
        return ASCII_ERROR;

    return ASCII_OK;
}

char *ascii_parse(const char *str, int *last_code)
{
    int ret_code    = ASCII_ERROR;
    char *ret_data   = NULL;

    if (str == NULL) 
        goto fail;

    int str_len         = (int)strlen(str);
    volatile int offset = str_len;
    int pair_cnt    = 0;
    
    ret_data = _strdup2(str);
    if (ret_data == NULL) 
        goto fail;
    
    // Проврека основных ограничений
    ret_code = ascii_check_policy(str);
    if (ret_code < 0)
        goto fail;

    // Обход с конца массива
    while (offset > 0) {

        char h_symbol = *(ret_data + offset - 2); // symbol high - alpha
        char l_symbol = *(ret_data + offset - 1); // symbol low  - numeric
        
        // Пропуск разделителя
        if (ASCII_IS_DELIMITER(h_symbol) || ASCII_IS_DELIMITER(l_symbol)) {
            offset -= 1;
            continue;
        }

        // Валидация символов
        ret_code = ascii_validate_token(h_symbol, l_symbol, NULL);
        if (ret_code < 0){
            goto fail;
        }

        // Инкремент ASCII
        if (ascii_increment_numeric(&l_symbol) == ASCII_INCREMENT_OVERFLOW
            && ascii_increment_alpha(&h_symbol) == ASCII_INCREMENT_OVERFLOW)
        {
            *(ret_data + offset - 1) = l_symbol;
            *(ret_data + offset - 2) = h_symbol;
            // подсчет символов
            pair_cnt += 2;

            // Конец последовательности
            if ((offset - 2) == 0){
                if (pair_cnt >= ASCII_MAX_SIZE)
                {
                    ret_code = ASCII_ERROR_MAX_SIZE;
                    goto fail;
                }

                //выделяем память под новый элемент
                ret_data = ascii_realloc_buff(ret_data);
                if(ret_data == NULL) 
                    goto fail;
            }

            offset -= 2;
            continue;
        }

        *(ret_data + offset - 1) = l_symbol;
        *(ret_data + offset - 2) = h_symbol;
        // условие выхода
        offset = 0;
    }

    *last_code = ret_code;
    return ret_data;
fail:
    *last_code = ret_code;
    free(ret_data);
    return NULL;
}