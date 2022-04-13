#include "minunit.h"
#include "ascii_counter.h"


static int rc = 0;
static char *buff = NULL;

MU_TEST(test_reference_error) {
    
    buff = ascii_parse("00", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("AA", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("Z0", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("0Z", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);
}


MU_TEST(test_wrong_delimiter) {

    buff = ascii_parse("F1--G1", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("-F1G1", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("F1G1-", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("F1G1", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);
}

MU_TEST(test_wrong_size)
{
    buff = ascii_parse(NULL, &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);

    buff = ascii_parse("Z", &rc);
    mu_check(buff == NULL);
    mu_check(rc < 0);
    free(buff);
}

int main()
{
    MU_RUN_TEST(test_reference_error);
    MU_RUN_TEST(test_wrong_delimiter);
    MU_RUN_TEST(test_wrong_size);
    MU_REPORT();
    return MU_EXIT_CODE;
}