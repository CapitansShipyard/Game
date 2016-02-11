//тестовый менеджер боя (С) 2016 Avenger
//Прямоугольное поле, два участника в виде равнобедренных треугольников
//параметры бойца: х,у координаты, угол в градусах, 0 - вправо
//за один такт боец может либо повернуться, либо передвинуться

#include <QtGui>
#include "arena.h"

const int _MULTIPLIER=4; //множитель размеров арены относительно окна
const int _WINDOW_SIZE_X=700;
const int _WINDOW_SIZE_Y=500;
const int _ACTION_INTERVAL = 5; //интервал опроса бойцов
const int _BORDER = 35; //рамка арены

word* IXArray1;
word* IXArray2;

int sign(int n)
{    
 return (n<=32767)-(n>=32767);
}

Arena ar((_WINDOW_SIZE_X-_BORDER*2)*_MULTIPLIER,(_WINDOW_SIZE_Y-_BORDER*2)*_MULTIPLIER,5,15);

QLabel *TickLabel;

byte* ChromGen()
{
byte* Chrom;
Chrom = new byte[_DNASIZE];
for (unsigned int i=0;i<_DNASIZE;i++)
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

        IXArray1[_IX_MY_COORD_X] = c1.X;
        IXArray1[_IX_MY_COORD_Y] = c1.Y;
        IXArray1[_IX_ENEMY_COORD_X] = c2.X;
        IXArray1[_IX_ENEMY_COORD_Y] = c2.Y;
        IXArray1[_IX_ARENA_TICK_COUNT] = ar.GetBattleTime();
        m1.SetConstTable(IXArray1);

        IXArray2[_IX_MY_COORD_X] = c2.X;
        IXArray2[_IX_MY_COORD_Y] = c2.Y;
        IXArray2[_IX_ENEMY_COORD_X] = c1.X;
        IXArray2[_IX_ENEMY_COORD_Y] = c1.Y;
        IXArray1[_IX_ARENA_TICK_COUNT] = ar.GetBattleTime();
        m1.SetConstTable(IXArray1);

        Action act1 = m1.GetAction(ar);
        Action act2 = m2.GetAction(ar);

        if (act1.ActionCode==_ACTION_TURN)
        {
            if (abs(act1.ActionRate)<=ar.GetMaxAngle())
                c1.Angle+=act1.ActionRate;
            else
                c1.Angle+=(ar.GetMaxAngle()*sign(act1.ActionRate));
            if (c1.Angle<0)
                c1.Angle+=360;
            if (c1.Angle>=360)
                c1.Angle-=360;
            m1.SetCoord(c1);
        }
        else if (act1.ActionCode==_ACTION_MOVE)
        {
            if (act1.ActionRate<=ar.GetMaxMove())
                movement = act1.ActionRate;
            else
                movement = ar.GetMaxMove();
            tAngle = c1.Angle*_180_DIV_PI;
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
        else if (act1.ActionCode==_ACTION_HALT)
        {//do nothing
        }

        if (act2.ActionCode==_ACTION_TURN)
        {
            if (abs(act2.ActionRate)<=ar.GetMaxAngle())
                c2.Angle+=act2.ActionRate;
            else
                c2.Angle+=(ar.GetMaxAngle()*sign(act2.ActionRate));
            if (c2.Angle<0)
                c2.Angle+=360;
            if (c2.Angle>=360)
                c2.Angle-=360;
 //           cout<<act2.ActionRate<<endl;
            m2.SetCoord(c2);
        }
        else if (act2.ActionCode==_ACTION_MOVE)
        {
            if (act2.ActionRate<=ar.GetMaxMove())
                movement = act2.ActionRate;
            else
                movement = ar.GetMaxMove();

            tAngle= c2.Angle*_180_DIV_PI;
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
        else if (act2.ActionCode==_ACTION_HALT)
        {//do nothing
        }

        ActScene->removeItem(tr1);
        ActScene->removeItem(tr2);
        delete tr1;
        delete tr2;
        QPolygonF pg;

        //нужно определить координаты точек равнобедренного треугольника, учитывая угол
        triangle tr;
        tAngle = c1.Angle*_180_DIV_PI;
        tr.x1 = c1.X-20*sin(tAngle);
        tr.y1 = c1.Y-20*cos(tAngle);
        tr.x2 = c1.X+70*cos(tAngle);
        tr.y2 = c1.Y-70*sin(tAngle);
        tr.x3 = c1.X+20*sin(tAngle);
        tr.y3 = c1.Y+20*cos(tAngle);

        pg<< QPointF(tr.x1/_MULTIPLIER+_BORDER,tr.y1/_MULTIPLIER+_BORDER)
          <<QPointF(tr.x2/_MULTIPLIER+_BORDER,tr.y2/_MULTIPLIER+_BORDER)
          <<QPointF(tr.x3/_MULTIPLIER+_BORDER,tr.y3/_MULTIPLIER+_BORDER);
        tr1 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
        pg.remove(0,3);

        tAngle = c2.Angle*_180_DIV_PI;
        tr.x1 = c2.X-20*sin(tAngle);
        tr.y1 = c2.Y-20*cos(tAngle);
        tr.x2 = c2.X+70*cos(tAngle);
        tr.y2 = c2.Y-70*sin(tAngle);
        tr.x3 = c2.X+20*sin(tAngle);
        tr.y3 = c2.Y+20*cos(tAngle);

        pg<< QPointF(tr.x1/_MULTIPLIER+_BORDER,tr.y1/_MULTIPLIER+_BORDER)
          <<QPointF(tr.x2/_MULTIPLIER+_BORDER,tr.y2/_MULTIPLIER+_BORDER)
          <<QPointF(tr.x3/_MULTIPLIER+_BORDER,tr.y3/_MULTIPLIER+_BORDER);
        tr2 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
        ar.SetMemberOne(m1);
        ar.SetMemberTwo(m2);
        ar.IncTickCount();
        TickLabel->setText("Tick: "+QString::number(ar.GetBattleTime()));
        if (ar.GetBattleTime()==1000)
            ar.Initialization();
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

void Arena::Initialization()
{
    srand(time(0));
    Coord CoordsM1;
    CoordsM1.X = 10;
    CoordsM1.Y = GetArenaSizeY()/2;
    CoordsM1.Angle =0;

    Coord CoordsM2;
    CoordsM2.X = GetArenaSizeX()-10;
    CoordsM2.Y = GetArenaSizeY()/2;
    CoordsM2.Angle = 180;

    Fighter m1;
    m1.SetCoord(CoordsM1);
    byte* dna1 = ChromGen();
    m1.SetDNA(dna1);

    IXArray1 = new word [31];
    IXArray1[_IX_ARENA_SIZE_X] = GetArenaSizeX();
    IXArray1[_IX_ARENA_SIZE_Y] = GetArenaSizeY();
    IXArray1[_IX_ARENA_MAX_ANGLE] = GetMaxAngle();
    IXArray1[_IX_ARENA_MAX_MOVE] = GetMaxMove();
    IXArray1[_IX_ARENA_TICK_COUNT] = 0;
    IXArray1[_IX_MY_COORD_X] = CoordsM1.X;
    IXArray1[_IX_MY_COORD_Y] = CoordsM1.Y;
    IXArray1[_IX_ENEMY_COORD_X] = CoordsM2.X;
    IXArray1[_IX_ENEMY_COORD_Y] = CoordsM2.Y;
    for (int i = 9;i<32;i++)
      IXArray1[i] = 0;

    m1.SetConstTable(IXArray1);

    Fighter m2;
    m2.SetCoord(CoordsM2);
    byte* dna2 = ChromGen();
    m2.SetDNA(dna2);

    IXArray2 = new word [31];
    IXArray2[_IX_ARENA_SIZE_X] = GetArenaSizeX();
    IXArray2[_IX_ARENA_SIZE_Y] = GetArenaSizeY();
    IXArray2[_IX_ARENA_MAX_ANGLE] = GetMaxAngle();
    IXArray2[_IX_ARENA_MAX_MOVE] = GetMaxMove();
    IXArray2[_IX_ARENA_TICK_COUNT] = 0;
    IXArray2[_IX_MY_COORD_X] = CoordsM2.X;
    IXArray2[_IX_MY_COORD_Y] = CoordsM2.Y;
    IXArray2[_IX_ENEMY_COORD_X] = CoordsM1.X;
    IXArray2[_IX_ENEMY_COORD_Y] = CoordsM1.Y;
    for (int i = 9;i<32;i++)
      IXArray2[i] = 0;

    m2.SetConstTable(IXArray2);
    TickCount =0;
    SetMemberOne(m1);
    SetMemberTwo(m2);

}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QGraphicsScene* scene= new QGraphicsScene(QRectF(0,0,_WINDOW_SIZE_X,_WINDOW_SIZE_Y));
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QGraphicsView view(scene);

    view.setWindowTitle("Battle manager");
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QGraphicsRectItem* pRectItem = new QGraphicsRectItem(0, scene);
    pRectItem->setPen(QPen(Qt::black));
    pRectItem->setBrush(QBrush(Qt::green));
    pRectItem->setRect(QRectF(0,0,_WINDOW_SIZE_X,_WINDOW_SIZE_Y));

    QGraphicsRectItem* pRectItem2 = new QGraphicsRectItem(0, scene);
    pRectItem2->setPen(QPen(Qt::black));
    pRectItem2->setBrush(QBrush(Qt::cyan));
    pRectItem2->setRect(QRectF(20,20,_WINDOW_SIZE_X-40,_WINDOW_SIZE_Y-40));

    TickLabel = new QLabel("0000000000");
    TickLabel->setAlignment(Qt::AlignHCenter);
    TickLabel->move(_WINDOW_SIZE_X/2-45,3);
    TickLabel->setStyleSheet("background-color: yellow");

    scene->addWidget(TickLabel);

    view.show();

    ar.Initialization();

    MyTimer Timer1(scene);
    Timer1.startTimer(_ACTION_INTERVAL);

    return app.exec();
}

