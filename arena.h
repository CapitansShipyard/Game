#ifndef ARENA_H
#define ARENA_H

#include "common.h"
#include "fighter.h"
#include <QtGui>

class MyTimer : public QObject {
protected:
    QGraphicsScene* ActScene;
    QGraphicsPolygonItem* tr1;
    QGraphicsPolygonItem* tr2;

    virtual void timerEvent(QTimerEvent *);

public:
    MyTimer(QGraphicsScene* PScene, QObject* pobj = 0);
};


struct triangle
{
    int x1;
    int x2;
    int x3;
    int y1;
    int y2;
    int y3;
};

class Arena
{
private:
    int sizeX;
    int sizeY;
    int MaxAngle;
    int MaxMove;
    int TickCount;
    float Score1;
    float Score2;
    Fighter* Member1;
    Fighter* Member2;
public:
    Arena(int pX, int pY, int MAngle, int MMove):
        sizeX(pX), sizeY(pY), MaxAngle(MAngle), MaxMove(MMove), TickCount(0)
    {}
    ~Arena()
    {}
    void Initialization(MyTimer *Timer);
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
    void SetMemberOne(Fighter* param)
    {Member1 = param;}
    void SetMemberTwo(Fighter* param)
    {Member2 = param;}
    Fighter* GetMemberOne()
    {return Member1;}
    Fighter* GetMemberTwo()
    {return Member2;}
    void IncTickCount()
    {TickCount++;}
    int GetBattleTime()
    {return TickCount;}
    void SetScoreOne(float score)
    {Score1 = score;}
    void SetScoreTwo(float score)
    {Score2 = score;}
    float GetScoreOne()
    {return Score1;}
    float GetScoreTwo()
    {return Score2;}
};
#endif // ARENA_H
