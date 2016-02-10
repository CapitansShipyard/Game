#ifndef COMMON_H
#define COMMON_H

//все объявления используемых внешних библиотек и типов писать сюда
//общие константы также тут
//файл следует использовать в каждом заголовочном файле

#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>

using namespace std;
const int _DNASIZE=30000;
typedef int16_t word;
typedef unsigned char byte;
typedef word* ptrword;
static const double Pi = 3.14159265358979323846264338327950288419717;

#endif // COMMON_H
