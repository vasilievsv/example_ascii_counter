#include "minunit.h"
#include "ascii_counter.h"


static int rc = 0;
static char *buff = NULL;

MU_TEST(test_reference_data) {

    buff = ascii_parse("B1", &rc);
    mu_check(rc == ASCII_OK);
    mu_assert_string_eq("B2", buff);
    free(buff);

    buff = ascii_parse("Z9", &rc);
    mu_check(rc == ASCII_OK);
    mu_assert_string_eq("B1-B1", buff);
    free(buff);

    buff = ascii_parse("B1-B1", &rc);
    mu_check(rc == ASCII_OK);
    mu_assert_string_eq("B1-B2", buff);
    free(buff);

    buff = ascii_parse("B1-Z9", &rc);
    mu_check(rc == ASCII_OK);
    mu_assert_string_eq("B2-B1", buff);
    free(buff);
}

MU_TEST(test_size_policy) 
{
    buff = ascii_parse("B1-B1-B1-B1-B1-B1-B1-B1-B1-B1", &rc);
    mu_check(rc == ASCII_OK);
    mu_assert_string_eq("B1-B1-B1-B1-B1-B1-B1-B1-B1-B2", buff);
    free(buff);

    buff = ascii_parse("B1-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9", &rc);
    mu_check(rc == ASCII_OK);
    mu_assert_string_eq("B2-B1-B1-B1-B1-B1-B1-B1-B1-B1", buff);
    free(buff);

    buff = ascii_parse("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);
    free(buff);
}


int main()
{
    MU_RUN_TEST(test_reference_data);
    MU_RUN_TEST(test_size_policy);
    MU_REPORT();
    return MU_EXIT_CODE;
}