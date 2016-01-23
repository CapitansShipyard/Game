#include <cmath>

struct Action//структура действий, для оператора return (не дает возвращать несколько значений)
{
	int ActionCode;//0 для движения 1 для поворота
	int ActionRate;// принимает значения от 0 до 10
};
struct Coord//структура координат
{
	int X;
	int Y;
};
Coord operator-(Coord a,Coord b)//сделал себе перегрузку для удовства
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
	return(std::sqrt(std::pow(a.X,2)+std::pow(a.Y,2)));
}
class Arena //мое представление класса Arena, чтоб проверить синтаксис
{
private:
public:
	int GetMaxAngle()
	{return(0);}
	int GetMaxMove()
	{return(0);}
	int GetArenaSizeX()
	{return(0);}
	int GetArenaSizeY()
	{return(0);}
	int GetCoordX()
	{return(0);}
	int GetCoordY()
	{return(0);}
	int GetAngle()
	{return(0);}
};
class Fighter
{
private:
	Action Act;
	Coord MyCoord;
	int Angle;
	int PreviousAct; //будем знать что делали раньше
	int AngleToWall(Arena a)//возвращает угол убегания от ближайшей стены
	{
		int walls[4][2];
		int temp[2];

		walls[0][0]=MyCoord.Y; walls[0][1]=180;
		walls[1][0]=a.GetArenaSizeX()-MyCoord.X; walls[1][1]=270;
		walls[2][0]=a.GetArenaSizeY()-MyCoord.Y; walls[2][1]=0;
		walls[3][0]=MyCoord.X; walls[3][0]=90;
		for(int n=3;n>1;n--)//сортируем расстояния до стен
		{
			for(int i=0;i<n;i++)
			{
				if(walls[i][0]>walls[i+1][0])
				{
					temp[0]=walls[i+1][0]; temp[1]=walls[i+1][1];
					walls[i+1][0]=walls[1][0]; walls[i+1][1]=walls[i][1];
					walls[i][0]=temp[0]; walls[i][1]=temp[1];
				}
			}
		}
		return(walls[0][1]);//возвращаем значение угла из отсортированного списка стен
	}
	int AngleToEnemy(Fighter enemy)//возвращает угол убегания от врага
	{
		Coord vector=enemy.GetCoord()-MyCoord;
		Coord Yvector;
		Yvector.X=0; Yvector.Y=-1;
		float cosA=vector*Yvector/abs(vector)*abs(Yvector);
		int Angle=(int)(std::acos(cosA)*180.0/3.1415);
		Angle+=180;
		if(Angle>359)
		{Angle-=360;}
		return (Angle);
	}
	int DesiredAngle(Arena a,Fighter enemy)//возвращает средний угол между верхними двумя
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
		if(std::abs(Delta1)>std::abs(Delta2))
			{Angle=OppAngle;}
		return(Angle);
	}

public:
Fighter(Arena a)//объект инициализируется одним аргументом класса Arena
	{
	PreviousAct=0;
	Act.ActionCode=0;
	Act.ActionRate=0;
	MyCoord.X=a.GetCoordX();
	MyCoord.Y=a.GetCoordY();
	Angle=a.GetAngle();
	}
Coord GetCoord()
	{
	return(MyCoord);
	}
void SetCoord(Arena a)
{
	MyCoord.X=a.GetCoordX();
	MyCoord.Y=a.GetCoordY();
}
Action GetAction(Arena a,Fighter enemy)
{
	MyCoord.X=a.GetCoordX();//перед расчетом действий обновляем свое состояние из арены
	MyCoord.Y=a.GetCoordY();//узкое место. данные о враге буду получать те, которые записаны
	Angle=a.GetAngle();		/*в нем, а не корректные из менеджера добавил метод SetCoord(Arena a)
	 вызываешь его у противника для актуализации данных о его положении,
	  перед выполнением метода GetAction() у бойца, которого обсчитываешь*/
	if(PreviousAct==0)
	{
		int DeltaAngle=0;
		DeltaAngle=DesiredAngle(a,enemy)-Angle;
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
};
int main()
{
return(0);
}
