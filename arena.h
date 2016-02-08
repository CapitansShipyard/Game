#ifndef ARENA_H
#define ARENA_H

#include "fighter.h"

class Arena
{
private:
    int sizeX;
    int sizeY;
    int MaxAngle;
    int MaxMove;
    Fighter Member1;
    Fighter Member2;
public:
    Arena(int pX, int pY, int MAngle, int MMove):
        sizeX(pX), sizeY(pY), MaxAngle(MAngle), MaxMove(MMove)
    {}
    ~Arena()
    {}
    int GetArenaSizeX()
    {return sizeX;}
    int GetArenaSizeY()
    {return sizeY;}
    int GetMaxAngle()
    {return MaxAngle;}
    int GetMaxMove()
    {return MaxMove;}
    void SetArenaSizeX(int param)
    {sizeX = param;}
    void SetArenaSizeY(int param)
    {sizeY = param;}
    void SetMaxAngle(int param)
    {MaxAngle = param;}
    void SetMaxMove(int param)
    {MaxMove = param;}
    void SetMemberOne(Fighter param)
    {Member1 = param;}
    void SetMemberTwo(Fighter param)
    {Member2 = param;}
    Fighter GetMemberOne()
    {return Member1;}
    Fighter GetMemberTwo()
    {return Member2;}
};
#endif // ARENA_H
