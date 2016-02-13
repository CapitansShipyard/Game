#ifndef BASE64_H
#define BASE64_H

#include "common.h"

const static char base64ABC[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char * base64_code (unsigned char * S, int SIZE);
unsigned char * base64_decode (unsigned char * S, int SIZE);

#endif // BASE64_H
