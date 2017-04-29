#include "./includes.h"
#include "./utils.h"


int
startsWith(const char * pre, const char * str)
{
    size_t lenpre = strlen(pre),
      lenstr      = strlen(str);

    if (lenstr >= lenpre && strncmp(pre, str, lenpre) == 0) {
        return 1;
    }

    return 0;
}
