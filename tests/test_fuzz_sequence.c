#include "minunit.h"
#include "ascii_counter.h"


static int rc = 0;
static char *buff = NULL;

MU_TEST(test_fuzz_data) {

    buff = ascii_parse("?????", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);
}

MU_TEST(test_fuzz_boundary) {

    buff = ascii_parse("A1", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);

    buff = ascii_parse("B0", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);

    buff = ascii_parse("-B1", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);

    buff = ascii_parse("B1-", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);

    buff = ascii_parse("ZZ", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);

    buff = ascii_parse("11", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);
}

MU_TEST(test_fuzz_overflow) {

    buff = ascii_parse("B1-B1-B1-B1-B1-B1-B1-B1-B1-B1-B1", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);

    buff = ascii_parse("F1G", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);
}


int main()
{
    MU_RUN_TEST(test_fuzz_data);
    MU_RUN_TEST(test_fuzz_boundary);
    MU_RUN_TEST(test_fuzz_overflow);
    MU_REPORT();
    return MU_EXIT_CODE;
}
