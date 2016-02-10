//тестовый менеджер боя (С) 2016 Avenger
//Прямоугольное поле, два участника в виде равнобедренных треугольников
//параметры бойца: х,у координаты, угол в градусах, 0 - вправо
//за один такт боец может либо повернуться, либо передвинуться

#include <QtGui>
#include "arena.h"

const int Multiplier=4; //множитель размеров арены относительно окна
const int WindowSizeX=700;
const int WindowSizeY=500;
const int ActionInterval = 10; //интервал опроса бойцов
const int border = 28; //рамка арены
word* IXArray1;
word* IXArray2;

int sign(int n)
{
 return (n>=0)-(n<=0);
}

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

byte* ChromGen()
{
byte* Chrom;
Chrom = new byte[_DNASIZE];
srand(time(0));
for (int i=0;i<_DNASIZE;i++)
    Chrom[i]= std::rand()%256;
return Chrom;
}

class MyTimer : public QObject {
protected:
    QGraphicsScene* ActScene;
    QGraphicsPolygonItem* tr1;
    QGraphicsPolygonItem* tr2;

    virtual void timerEvent(QTimerEvent *)
        {
        double tAngle;
        int mX;
        int mY;
        int movement;

        Fighter m1 = ar.GetMemberOne();
        Fighter m2 = ar.GetMemberTwo();
        Coord c1 = m1.GetCoord();
        Coord c2 = m2.GetCoord();

        IXArray1[5] = c1.X;
        IXArray1[6] = c1.Y;
        IXArray1[7] = c2.X;
        IXArray1[8] = c2.Y;
        m1.SetConstTable(IXArray1);

        IXArray2[5] = c2.X;
        IXArray2[6] = c2.Y;
        IXArray2[7] = c1.X;
        IXArray2[8] = c1.Y;
        m1.SetConstTable(IXArray1);

        Action act1 = m1.GetAction(ar,ar.GetMemberTwo());
        Action act2 = m2.GetAction(ar,ar.GetMemberOne());

        if (act1.ActionCode==1)//поворот
        {
            if (act2.ActionRate<=ar.GetMaxAngle())
                c2.Angle+=act2.ActionRate;
            else
                c2.Angle+=(ar.GetMaxAngle()*sign(act2.ActionRate));
            if (c1.Angle<0)
                c1.Angle+=360;
            m1.SetCoord(c1);
        }
        else if (act1.ActionCode==0)
        {
            if (act1.ActionRate<=ar.GetMaxMove())
                movement = act1.ActionRate;
            else
                movement = ar.GetMaxMove();
            tAngle = c1.Angle*0.01745329251994329576923690768489;
            mX = floor(cos(tAngle)*movement);
            mY = floor(sin(tAngle)*movement);
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
        else if (act1.ActionCode==2)//halt
        {//do nothing
        }

        if (act2.ActionCode==1)//поворот
        {
            if (act2.ActionRate<=ar.GetMaxAngle())
                c2.Angle+=act2.ActionRate;
            else
                c2.Angle+=(ar.GetMaxAngle()*sign(act2.ActionRate));
            if (c2.Angle<0)
                c2.Angle+=360;

            m2.SetCoord(c2);
        }
        else if (act2.ActionCode==0)
        {
            if (act2.ActionRate<=ar.GetMaxMove())
                movement = act2.ActionRate;
            else
                movement = ar.GetMaxMove();

            tAngle= c2.Angle*0.01745329251994329576923690768489;
            mX = trunc(cos(tAngle)*movement);
            mY = trunc(sin(tAngle)*movement);
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
        else if (act2.ActionCode==2)//halt
        {//do nothing
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
        ar.IncTickCount();
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

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QGraphicsScene* scene= new QGraphicsScene(QRectF(0,0,WindowSizeX,WindowSizeY));   
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QGraphicsView view(scene);
    view.setWindowTitle("Battle manager");
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QGraphicsRectItem* pRectItem = new QGraphicsRectItem(0, scene);
    pRectItem->setPen(QPen(Qt::black));
    pRectItem->setBrush(QBrush(Qt::green));
    pRectItem->setRect(QRectF(0,0,WindowSizeX,WindowSizeY));

    QGraphicsRectItem* pRectItem2 = new QGraphicsRectItem(0, scene);
    pRectItem2->setPen(QPen(Qt::black));
    pRectItem2->setBrush(QBrush(Qt::white));
    pRectItem2->setRect(QRectF(9,9,WindowSizeX-18,WindowSizeY-18));

    Coord CoordsM1;
    CoordsM1.X = 10;
    CoordsM1.Y = ar.GetArenaSizeY()/2;
    CoordsM1.Angle =0;

    Coord CoordsM2;
    CoordsM2.X = ar.GetArenaSizeX()-10;
    CoordsM2.Y = ar.GetArenaSizeY()/2;
    CoordsM2.Angle = 180;

    Fighter m1;
    m1.SetCoord(CoordsM1);
    byte* dna1 = ChromGen();
    m1.SetDNA(dna1);

    IXArray1 = new word [31];
    IXArray1[0] = ar.GetArenaSizeX();
    IXArray1[1] = ar.GetArenaSizeY();
    IXArray1[2] = ar.GetMaxAngle();
    IXArray1[3] = ar.GetMaxMove();
    IXArray1[4] = 0;
    IXArray1[5] = CoordsM1.X;
    IXArray1[6] = CoordsM1.Y;
    IXArray1[7] = CoordsM2.X;
    IXArray1[8] = CoordsM2.Y;
    for (int i = 9;i<32;i++)
      IXArray1[i] = 0;

    m1.SetConstTable(IXArray1);

    Fighter m2;
    m2.SetCoord(CoordsM2);
    byte* dna2 = ChromGen();
    m2.SetDNA(dna2);

    IXArray2 = new word [31];
    IXArray2[0] = ar.GetArenaSizeX();
    IXArray2[1] = ar.GetArenaSizeY();
    IXArray2[2] = ar.GetMaxAngle();
    IXArray2[3] = ar.GetMaxMove();
    IXArray2[4] = 0;
    IXArray2[5] = CoordsM2.X;
    IXArray2[6] = CoordsM2.Y;
    IXArray2[7] = CoordsM1.X;
    IXArray2[8] = CoordsM1.Y;
    for (int i = 9;i<32;i++)
      IXArray2[i] = 0;

    m2.SetConstTable(IXArray2);

    ar.SetMemberOne(m1);
    ar.SetMemberTwo(m2);

    view.show();

    MyTimer Timer1(scene);
    Timer1.startTimer(ActionInterval);

    return app.exec();
}

