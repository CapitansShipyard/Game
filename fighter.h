#ifndef FIGHTER_H
#define FIGHTER_H

#include "common.h"

class Arena;
class VPU
{
private:
    word ar;
    int pc;
    word bc;
    word de;
    word ix;
    byte f;
    //структура регистра F
    //хххххххх
    //00000PCZ
    void SetFlagC(bool C);
    void SetFlagZ(bool Z);
    void SetFlagP(bool P);
    void SetFlags();
    bool ZFlag();
    bool CFlag();
    bool PFlag();
    word GetIXValue(byte index);
    word GetWord(byte a, byte b);
    void IncPC(int step);
    char DecToHex(byte a);
public:
    word* IXArray;
    void Reset();
    int GetPC();
    void SetPC(word arg);
    void SetIX(word arg);
    string GetHex(byte p);
    int Execute(byte b1, byte b2, byte b3);
    string GetMnemonic(byte b1, byte b2, byte b3);

};

struct Action//структура действий, для оператора return (не дает возвращать несколько значений)
{
    int ActionCode;//0 для движения 1 для поворота
    int ActionRate;// принимает значения от 0 до GetMaxMove() и GetMaxAngle()
};
struct Coord//структура координат
{
    int X;
    int Y;
    int Angle;
};

class Fighter
{
private:
    Action Act;
    Coord MyCoord;
    VPU vpu;
    int PreviousAct; //будем знать что делали раньше
    int AngleToWall(Arena a);//возвращает угол убегания от ближайшей стены
    int AngleToEnemy(Fighter enemy);//возвращает угол убегания от врага
    int DesiredAngle(Arena a,Fighter enemy);//возвращает средний угол между верхними двумя
public:
    Fighter();
    Coord GetCoord();
    void SetCoord(Coord a);
    Action GetAction(Arena a,Fighter enemy);    
};

#endif // FIGHTER_H
