#ifndef FIGHTER_H
#define FIGHTER_H

class Arena;

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
