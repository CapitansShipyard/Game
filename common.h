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

typedef int16_t word;
typedef unsigned char byte;
typedef word* ptrword;
typedef byte* ptrbyte;

const unsigned int _DNASIZE=30000; //размер ДНК в байтах, кратно 3 (<32768 на данный момент)
const unsigned int _VPU_MAX_STEPS = 10000; //Защита от зависания VPU
const double _PI = 3.14159265358979323846264338327950288419717;
const double _180_DIV_PI = 0.01745329251994329576923690768489;

//константы, относящиеся к индексному массиву IX
const byte _IX_ARENA_SIZE_X = 0;
const byte _IX_ARENA_SIZE_Y = 1;
const byte _IX_ARENA_MAX_ANGLE = 2;
const byte _IX_ARENA_MAX_MOVE = 3;
const byte _IX_ARENA_TICK_COUNT = 4;
const byte _IX_MY_COORD_X = 5;
const byte _IX_MY_COORD_Y = 6;
const byte _IX_ENEMY_COORD_X = 7;
const byte _IX_ENEMY_COORD_Y = 8;

//константы, относящиеся к типам действий
const byte _ACTION_MOVE = 0;
const byte _ACTION_TURN = 1;
const byte _ACTION_HALT = 2;

#endif // COMMON_H
