#include "common.h"

word GetWord(byte a, byte b)
    {
        return b*256+a;
    }

int myrandom(int n)
{
    int j = (int) (((double) n) * rand() / (RAND_MAX + 1.0));
    return j;
}
