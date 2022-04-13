#include "minunit.h"
#include "ascii_counter.h"


static int rc = 0;
static char *buff = NULL;

MU_TEST(test_fuzz_data) {

    buff = ascii_parse("?????", &rc);
    mu_check(rc < 0);
    mu_check(buff == NULL);
}


int main()
{
    MU_RUN_TEST(test_fuzz_data);
    MU_REPORT();
    return MU_EXIT_CODE;
}