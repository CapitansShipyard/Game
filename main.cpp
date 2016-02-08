//тестовый менеджер боя (С) 2016 Avenger
//Прямоугольное поле, два участника в виде равнобедренных треугольников
//параметры бойца: х,у координаты, угол в градусах, 0 - вправо
//за один такт боец может либо повернуться, либо передвинуться

#include <QtGui>
#include "arena.h"
#include <cmath>

const int Multiplier=4; //множитель размеров арены относительно окна
const int WindowSizeX=700;
const int WindowSizeY=500;
const int ActionInterval = 20; //интервал опроса бойцов
const int border = 28; //рамка арены

struct triangle
{
    int x1;
    int x2;
    int x3;
    int y1;
    int y2;
    int y3;
};

static Arena ar((WindowSizeX-border*2)*Multiplier,(WindowSizeY-border*2)*Multiplier,5,15);

class MyTimer : public QObject {
protected:
    QGraphicsScene* ActScene;
    QGraphicsPolygonItem* tr1;
    QGraphicsPolygonItem* tr2;

    virtual void timerEvent(QTimerEvent *)
        {
        double tAngle;
        Fighter m1 = ar.GetMemberOne();
        Action act1 = m1.GetAction(ar,ar.GetMemberTwo());
        Fighter m2 = ar.GetMemberTwo();
        Action act2 = m2.GetAction(ar,ar.GetMemberOne());
        int mX;
        int mY;
        Coord c1 = m1.GetCoord();
        Coord c2 = m2.GetCoord();
        if (act1.ActionCode==1)//поворот
        {
            c1.Angle+=act1.ActionRate;
            if (c1.Angle<0)
                c1.Angle+=360;
            m1.SetCoord(c1);
        }
        else if (act1.ActionCode==0)
        {
            tAngle = c1.Angle*0.01745329251994329576923690768489;
            mX = floor(cos(tAngle)*act1.ActionRate);
            mY = floor(sin(tAngle)*act1.ActionRate);
            c1.X+=mX;
            c1.Y-=mY;
            if (c1.X<1)
                c1.X=1;
            if (c1.Y<1)
                c1.Y=1;
            if (c1.X>(ar.GetArenaSizeX()-1))
                c1.X=ar.GetArenaSizeX()-1;
            if (c1.Y>(ar.GetArenaSizeY()-1))
                c1.Y=ar.GetArenaSizeY()-1;
            m1.SetCoord(c1);
        }

        if (act2.ActionCode==1)//поворот
        {
            c2.Angle+=act2.ActionRate;
            if (c2.Angle<0)
                c2.Angle+=360;

            m2.SetCoord(c2);
        }
        else if (act2.ActionCode==0)
        {
            tAngle= c2.Angle*0.01745329251994329576923690768489;
            mX = trunc(cos(tAngle)*act2.ActionRate);
            mY = trunc(sin(tAngle)*act2.ActionRate);
            c2.X+=mX;
            c2.Y-=mY;
            if (c2.X<1)
                c2.X=1;
            if (c2.Y<1)
                c2.Y=1;
            if (c2.X>(ar.GetArenaSizeX()-1))
                c2.X=ar.GetArenaSizeX()-1;
            if (c2.Y>(ar.GetArenaSizeY()-1))
                c2.Y=ar.GetArenaSizeY()-1;
            m2.SetCoord(c2);
        }
        ActScene->removeItem(tr1);
        ActScene->removeItem(tr2);
        delete tr1;
        delete tr2;
        QPolygonF pg;

        //нужно определить координаты точек равнобедренного треугольника, учитывая угол
        triangle tr;
        tAngle = c1.Angle*0.01745329251994329576923690768489;
        tr.x1 = c1.X-20*sin(tAngle);
        tr.y1 = c1.Y-20*cos(tAngle);
        tr.x2 = c1.X+70*cos(tAngle);
        tr.y2 = c1.Y-70*sin(tAngle);
        tr.x3 = c1.X+20*sin(tAngle);
        tr.y3 = c1.Y+20*cos(tAngle);

        pg<< QPointF(tr.x1/Multiplier+border,tr.y1/Multiplier+border)
          <<QPointF(tr.x2/Multiplier+border,tr.y2/Multiplier+border)
          <<QPointF(tr.x3/Multiplier+border,tr.y3/Multiplier+border);
        tr1 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
        pg.remove(0,3);

        tAngle = c2.Angle*0.01745329251994329576923690768489;
        tr.x1 = c2.X-20*sin(tAngle);
        tr.y1 = c2.Y-20*cos(tAngle);
        tr.x2 = c2.X+70*cos(tAngle);
        tr.y2 = c2.Y-70*sin(tAngle);
        tr.x3 = c2.X+20*sin(tAngle);
        tr.y3 = c2.Y+20*cos(tAngle);

        pg<< QPointF(tr.x1/Multiplier+border,tr.y1/Multiplier+border)
          <<QPointF(tr.x2/Multiplier+border,tr.y2/Multiplier+border)
          <<QPointF(tr.x3/Multiplier+border,tr.y3/Multiplier+border);
        tr2 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
        ar.SetMemberOne(m1);
        ar.SetMemberTwo(m2);
    }

public:
    MyTimer(QGraphicsScene* PScene, QObject* pobj = 0);
};

MyTimer::MyTimer(QGraphicsScene* PScene, QObject *pobj)
    :ActScene(PScene), QObject(pobj)
{
    QPolygonF pg;
//    pg << QPointF(30,30)<<QPointF(50,40)<<QPointF(30,50);
    tr1 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
    tr2 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
}

byte* ChromGen()
{
byte* Chrom;
Chrom = new byte[dnasize];
srand(time(0));
for (int i=0;i<dnasize;i++)
    Chrom[i]= std::rand()%256;
return Chrom;
}

int main1(int argc, char **argv)
{
    QApplication app(argc, argv);
    QGraphicsScene* scene= new QGraphicsScene(QRectF(0,0,WindowSizeX,WindowSizeY));   
    QGraphicsView view(scene);
    view.setWindowTitle("Battle manager");

    QGraphicsRectItem* pRectItem = new QGraphicsRectItem(0, scene);
    pRectItem->setPen(QPen(Qt::black));
    pRectItem->setBrush(QBrush(Qt::green));
    pRectItem->setRect(QRectF(0,0,WindowSizeX,WindowSizeY));

    QGraphicsRectItem* pRectItem2 = new QGraphicsRectItem(0, scene);
    pRectItem2->setPen(QPen(Qt::black));
    pRectItem2->setBrush(QBrush(Qt::white));
    pRectItem2->setRect(QRectF(9,9,WindowSizeX-18,WindowSizeY-18));

    Coord Coords;
    Coords.X = 10;
    Coords.Y = ar.GetArenaSizeY()/2;
    Coords.Angle =0;

    Fighter m1;
    m1.SetCoord(Coords);

    Fighter m2;
    Coords.X = ar.GetArenaSizeX()-10;
    Coords.Y = ar.GetArenaSizeY()/2;
    Coords.Angle = 180;
    m2.SetCoord(Coords);

    ar.SetMemberOne(m1);
    ar.SetMemberTwo(m2);

    view.show();

    MyTimer Timer1(scene);
    Timer1.startTimer(ActionInterval);

    return app.exec();
}

int main(int argc, char **argv)
{
   CPU cpu;

   //инициализация блока IX
   cpu.IXArray = new word [31];
   cpu.IXArray[0] = 600;
   cpu.IXArray[1] = 300;
   cpu.IXArray[2] = 30;
   cpu.IXArray[3] = 10;
   cpu.IXArray[4] = 0;
   cpu.IXArray[5] = 100;
   cpu.IXArray[6] = 150;
   for (int i = 7;i<32;i++)
       cpu.IXArray[i] = 0;



   cpu.Reset();
   byte* arr = ChromGen();

   int i = 0;
   int step = 0;
//   for (int i=0;i<dnasize;i+=3)
   while (cpu.GetPC()<dnasize)
   {
       i = cpu.GetPC();
       step++;
       if (step>10000)
          break;

      // cout<<(i/3)<<'\t'<<cpu.GetHex(arr[i]%64)<<setw(4)<<cpu.GetHex(arr[i+1])<<setw(4)
       //   <<cpu.GetHex(arr[i+2])<<'\t'<<cpu.GetMnemonic(arr[i]%64,arr[i+1],arr[i+2])<<endl;
       cpu.Execute(arr[i]%64,arr[i+1],arr[i+2]);
   }
   return(0);
}

