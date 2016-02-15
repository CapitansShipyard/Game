#ifndef FIGHTER_H
#define FIGHTER_H

#include "common.h"

class Arena;

class VPU
{
private:
    word ar;
    unsigned int pc;
    word bc;
    word de;
    word ix;
    byte f;
    word randpointer;
    byte randarray[65536];
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
    void IncPC(int step);
    char DecToHex(byte a);
    word* IXArray;
public:    
    void Reset();
    int GetPC();
    void SetPC(word arg);
    void SetIX(word arg);
    string GetHex(byte p);
    int Execute(byte b1, byte b2, byte b3);    
    word GetAR()
    {return ar;}
    word GetIXArrayValue(byte index)
    {return IXArray[index];}
    void SetIXArray(word* IXArr)
    {IXArray = IXArr;}
    int AngleToWall();
    int AngleToEnemy();
    void SetRandpointer(word pPtr)
    {randpointer = pPtr;}
    word GetRND();
};

struct Action//структура действий, для оператора return (не дает возвращать несколько значений)
{
    int ActionCode;
    int ActionRate;
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
    byte dna[_DNASIZE];
public:
    Fighter();
    Coord GetCoord()
    {return(MyCoord);}
    void SetCoord(Coord a)
    {MyCoord=a;}
    Action GetAction(Arena a);    
    void SetConstTable(word* ptrCT)
    {vpu.SetIXArray(ptrCT);}
    void SetDNA(ptrbyte pDNA)
    {memcpy(dna, pDNA, _DNASIZE);}
    void ResetVPU()
    {vpu.Reset();}
};

#endif // FIGHTER_H
