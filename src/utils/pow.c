#include "./includes.h"
#include "./utils.h"

int pow(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return pow(x, y/2)*pow(x, y/2);
    else
        return x*pow(x, y/2)*pow(x, y/2);
}