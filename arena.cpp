//тестовый менеджер боя (С) 2016 Avenger
//Прямоугольное поле, два участника в виде равнобедренных треугольников
//параметры бойца: х,у координаты, угол в градусах, 0 - вправо
//за один такт боец может либо повернуться, либо передвинуться

#include "arena.h"
#include "population.h"
#include "database.h"

const int _MULTIPLIER=4; //множитель размеров арены относительно окна
const int _WINDOW_SIZE_X=700;
const int _WINDOW_SIZE_Y=500;
const int _ACTION_INTERVAL = 3; //интервал опроса бойцов
const int _BORDER = 35; //рамка арены

Database* pDB = new Database;
int TimerID;
static Population* p = new Population(1);
static unsigned int counter;

static Fighter* m1 = new Fighter;
static Fighter* m2 = new Fighter;



int sign(int n)
{    
 return (n<=32767)-(n>=32767);
}

Arena ar((_WINDOW_SIZE_X-_BORDER*2)*_MULTIPLIER,(_WINDOW_SIZE_Y-_BORDER*2)*_MULTIPLIER,5,20);

QLabel *TickLabel;
QLabel *Score1Label;
QLabel *Score2Label;

void MyTimer::timerEvent(QTimerEvent *)
        {
        double tAngle;
        int mX;
        int mY;
        int movement;

        Fighter* m1 = ar.GetMemberOne();
        Fighter* m2 = ar.GetMemberTwo();
        Coord c1 = m1->GetCoord();
        Coord c2 = m2->GetCoord();

        ptrword IXArray1 = new word[32];
        IXArray1[_IX_MY_COORD_X] = c1.X;
        IXArray1[_IX_MY_COORD_Y] = c1.Y;
        IXArray1[_IX_ENEMY_COORD_X] = c2.X;
        IXArray1[_IX_ENEMY_COORD_Y] = c2.Y;
        IXArray1[_IX_ARENA_TICK_COUNT] = ar.GetBattleTime();
        m1->SetConstTable(IXArray1);

        ptrword IXArray2 = new word[32];
        IXArray2[_IX_MY_COORD_X] = c2.X;
        IXArray2[_IX_MY_COORD_Y] = c2.Y;
        IXArray2[_IX_ENEMY_COORD_X] = c1.X;
        IXArray2[_IX_ENEMY_COORD_Y] = c1.Y;
        IXArray1[_IX_ARENA_TICK_COUNT] = ar.GetBattleTime();
        m1->SetConstTable(IXArray1);

        delete(IXArray1);
        delete(IXArray2);

        double score1 =0;

        Action act1 = m1->GetAction(ar);
      //  Action act2 = m2->GetAction(ar);

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
            m1->SetCoord(c1);
            score1+=0.0002;
        }
        else if (act1.ActionCode==_ACTION_MOVE)
        {            
            if (abs(act1.ActionRate)<=ar.GetMaxMove())
                movement = act1.ActionRate;
            else
                movement = ar.GetMaxMove()*sign(act1.ActionRate);
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
            m1->SetCoord(c1);
            score1+=0.0002;
        }
        else if (act1.ActionCode==_ACTION_HALT)
        {//do nothing
        }

        ar.SetScoreOne(ar.GetScoreOne()+score1);
        ////ОЧКИ ЗА АКТИВНОСТЬ НА АРЕНЕ


  /*      if (act2.ActionCode==_ACTION_TURN)
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
            m2->SetCoord(c2);
        }
        else if (act2.ActionCode==_ACTION_MOVE)
        {
            if (abs(act2.ActionRate)<=ar.GetMaxMove())
                movement = act2.ActionRate;
            else
                movement = ar.GetMaxMove()*sign(act2.ActionRate);

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
            m2->SetCoord(c2);
        }
        else if (act2.ActionCode==_ACTION_HALT)
        {//do nothing
        }
*/
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

        //посчитаем очки
        double distance = hypot((c1.X-c2.X),(c1.Y-c2.Y));
        score1 = 1/distance;
        double score2 = score1; //пока так
        ar.SetScoreOne(ar.GetScoreOne()+score1);
        ar.SetScoreTwo(ar.GetScoreTwo()+score2);
        Score1Label->setText(QString::number(ar.GetScoreOne(),'f',5));
     //   Score2Label->setText(QString::number(ar.GetScoreTwo(),'f',5));
        ar.IncTickCount();
        TickLabel->setText("Tick: "+QString::number(ar.GetBattleTime()));
        if (ar.GetBattleTime()==1000)
        {
            this->killTimer(TimerID);
            p->members[counter-1]->SetFitness(trunc(ar.GetScoreOne()*10000));
            cout<<"Fitness = "<<p->members[counter-1]->GetFitness()<<endl;
            cout<<"DNA usage(%) = "<<(int)((m1->GetDNAUsage()*100)/_DNASIZE)<<endl;
            ar.Initialization(this);
        }
    }

MyTimer::MyTimer(QGraphicsScene* PScene, QObject *pobj)
    :ActScene(PScene), QObject(pobj)
{
    QPolygonF pg;
//    pg << QPointF(30,30)<<QPointF(50,40)<<QPointF(30,50);
    tr1 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
    tr2 = ActScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
}

void Arena::Initialization(MyTimer* Timer)
{
    if (counter==_POPULATION_SIZE)
    {
        p->Save();
        return;
    }

    Coord CoordsM1;
    CoordsM1.X = 10;
    CoordsM1.Y = GetArenaSizeY()/2;
    CoordsM1.Angle =0;


    //ТЕСТЫ С НЕПОДВИЖНОЙ МИШЕНЬЮ
    Coord CoordsM2;
    CoordsM2.X = GetArenaSizeX()/2;
    CoordsM2.Y = GetArenaSizeY()/2-700;
    CoordsM2.Angle = 180;

    Fighter* m1 = ar.GetMemberOne();
    Fighter* m2 = ar.GetMemberTwo();

    m1->SetCoord(CoordsM1);
    m1->ResetVPU();

    ptrbyte pDNA = p->members[counter]->GetDNA();

    m1->SetDNA(pDNA);

    cout<<counter<<endl;

    ptrword IXArray1 = new word [32];
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

    m1->SetConstTable(IXArray1);

    m2->SetCoord(CoordsM2);
    m2->ResetVPU();

    m2->SetDNA(pDNA);

    ptrword IXArray2 = new word [32];
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

    m2->SetConstTable(IXArray2);
    TickCount =0;
    SetMemberOne(m1);
    SetMemberTwo(m2);
    SetScoreOne(0);
    SetScoreTwo(0);

    delete(IXArray1);
    delete(IXArray2);
    counter++;

    TimerID = Timer->startTimer(_ACTION_INTERVAL);

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

    Score1Label = new QLabel("000000000000");
    Score1Label->setAlignment(Qt::AlignCenter);
    Score1Label->move(50,3);
    Score1Label->setStyleSheet("background-color: yellow");
    scene->addWidget(Score1Label);

    Score2Label = new QLabel("000000000000");
    Score2Label->setAlignment(Qt::AlignCenter);
    Score2Label->move(_WINDOW_SIZE_X-120,3);
    Score2Label->setStyleSheet("background-color: yellow");
    scene->addWidget(Score2Label);

    view.show();

 //   srand(time(0));
    ///THIS BLOCK IS FOR TEST PURPOSES ONLY!!!!
//    pDB->AddPlayer(1, "Test");
//
//    pDB->CreateTable(1);
//      p->Generate();
    p->Load();
    p->Sort();
    for (unsigned int i = 0; i<_POPULATION_SIZE; i++)
        cout<<p->members[i]->GetFitness()<<endl;
//    p->Save();
    //  p->Load();

//    p->Save();
//    Population* pNew = p->Evolve(1,0);
//    pNew->Save();
//    pNew->CopyTo(p);
 //   delete pNew;
//    p->Load();
    /////END OF BLOCK

    counter = 0;

    ar.SetMemberOne(m1);
    ar.SetMemberTwo(m2);

    MyTimer* Timer1 = new MyTimer(scene);

//    ar.Initialization(Timer1);

    return app.exec();
}

