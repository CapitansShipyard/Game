#include <cmath>
#include "arena.h"
#include <cstdlib>

Coord operator-(Coord a,Coord b)//сделал себе перегрузку для удобства
{
    Coord c;
    c.X=a.X-b.X;
    c.Y=a.Y-b.Y;
    return(c);
}
float operator*(Coord a,Coord b)
{
    float c;
    c=a.X*b.X+a.Y*b.Y;
    return(c);
}

float abs(Coord a)
{
	return((float)(std::sqrt(std::pow(a.X,2)+std::pow(a.Y,2))));
}

int Fighter::AngleToWall(Arena a)//возвращает угол убегания от ближайшей стены
{
    int walls[4][2];
    int temp[2];

    walls[0][0]=MyCoord.Y; walls[0][1]=270;
    walls[1][0]=a.GetArenaSizeX()-MyCoord.X; walls[1][1]=180;
    walls[2][0]=a.GetArenaSizeY()-MyCoord.Y; walls[2][1]=90;
    walls[3][0]=MyCoord.X; walls[3][1]=0;
    for(int n=3;n>0;n--)//сортируем расстояния до стен
    {
        for(int i=0;i<n;i++)
        {
            if(walls[i][0]>walls[i+1][0])
            {
                temp[0]=walls[i+1][0]; temp[1]=walls[i+1][1];
                walls[i+1][0]=walls[i][0]; walls[i+1][1]=walls[i][1];
                walls[i][0]=temp[0]; walls[i][1]=temp[1];
            }
        }
    }
    return(walls[0][1]);//возвращаем значение угла из отсортированного списка стен
}

int Fighter::AngleToEnemy(Fighter enemy)//возвращает угол убегания от врага
{
    Coord vector=enemy.GetCoord()-MyCoord;
    Coord Yvector;
    vector.Y *=-1;
    Yvector.X=1; Yvector.Y=0;
    float cosA=(vector*Yvector)/(abs(vector)*abs(Yvector));
    int Angle=(int)(std::acos(cosA)*180.0/3.1415);
    if (vector.Y>0)
       Angle=360-Angle;
    Angle+=180;

    if(Angle>359)
      Angle=Angle-360;
    return (Angle);
}

int Fighter::DesiredAngle(Arena a,Fighter enemy)//возвращает средний угол между верхними двумя
{
    int FirstAngle=AngleToEnemy(enemy);
    int SecondAngle=AngleToWall(a);
    int Angle=(FirstAngle+SecondAngle)/2;
    int Delta1; int Delta2;
    int OppAngle=Angle-180;
    if (OppAngle<0)
        {OppAngle+=360;}
    Delta1=Angle-FirstAngle;
    Delta2=OppAngle-FirstAngle;
    if((std::abs(Delta1)>std::abs(Delta2))||(rand()%100<30))
        {Angle=OppAngle;}
    return(Angle);
}

Fighter::Fighter()
	{
	PreviousAct=0;
	Act.ActionCode=0;
	Act.ActionRate=0;
	MyCoord.X=0;
	MyCoord.Y=0;
	MyCoord.Angle=0;
	}
Coord Fighter::GetCoord()
	{
	return(MyCoord);
	}
void Fighter::SetCoord(Coord a)
{
	MyCoord=a;
}
Action Fighter::GetAction(Arena a,Fighter enemy)
{
	if(PreviousAct==0)
	{
		int DeltaAngle=0;
		DeltaAngle=DesiredAngle(a,enemy)-MyCoord.Angle;
		if(DeltaAngle<-180)
		{DeltaAngle+=360;}
		if(DeltaAngle>180)
		{DeltaAngle-=360;}
		if(DeltaAngle<0 && -DeltaAngle>a.GetMaxAngle())
		{DeltaAngle=-a.GetMaxAngle();}
		if(DeltaAngle>0 && DeltaAngle>a.GetMaxAngle())
		{DeltaAngle=a.GetMaxAngle();}
		if(fabs(DeltaAngle)<5)
		{
			PreviousAct=0;
			Act.ActionCode=0;
			Act.ActionRate=a.GetMaxMove();
		}
		else
		{
			PreviousAct=1;
			Act.ActionCode=1;
			Act.ActionRate=DeltaAngle;
		}
	}
	else
	{
		PreviousAct=0;
		Act.ActionCode=0;
		Act.ActionRate=a.GetMaxMove();//пускай газует на полную
	}
	return (Act);
}
