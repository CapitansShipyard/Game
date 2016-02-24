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
    int IXArray[32];
public:    
    void Reset();
    int GetPC();
    void SetPC(word arg);
    void SetIX(word arg);
    string GetHex(byte p);
    int Execute(byte b1, byte b2, byte b3);    
    word GetAR()
    {return ar;}
    int GetIXArrayValue(byte index)
    {return IXArray[index];}
    void SetIXArray(int* IXArr)
    {memcpy(IXArray, IXArr,sizeof(int)*32);}
    int AngleToWall();
    int AngleToEnemy();
    void SetRandpointer(word pPtr)
    {randpointer = pPtr;}
    word GetRND();

    unsigned int DNAUsage;//debugging
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
    byte dna[_DNASIZE];
    VPU vpu;
public:    
    Fighter();
    Coord GetCoord()
    {return(MyCoord);}
    void SetCoord(Coord a)
    {MyCoord=a;}
    Action GetAction(Arena a);    
    void SetConstTable(int* ptrCT)
    {vpu.SetIXArray(ptrCT);}
    void SetDNA(ptrbyte pDNA)
    {memcpy(dna, pDNA, _DNASIZE);}
    void ResetVPU()
    {vpu.Reset();}
    unsigned int GetDNAUsage()
    {return vpu.DNAUsage;}
};

#endif // FIGHTER_H
