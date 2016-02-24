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
static const int _FAST_CALC = 0;//режим быстрого просчета или 0 - с визуализацией

Database* pDB = new Database;
int TimerID;
static Population* p = new Population(1);
static unsigned int counter;

static Fighter* m1 = new Fighter;
static Fighter* m2 = new Fighter;

static Arena* ar = new Arena;

QLabel *TickLabel;
QLabel *Score1Label;
QLabel *Score2Label;

void FillIXArray(Fighter* f1, Fighter* f2, Arena* a) //заполняет массив констант участника f1
{
    int* IXArray = new int [32];
    IXArray[_IX_ARENA_SIZE_X] = a->GetArenaSizeX();
    IXArray[_IX_ARENA_SIZE_Y] = a->GetArenaSizeY();
    IXArray[_IX_ARENA_MAX_ANGLE] = a->GetMaxAngle();
    IXArray[_IX_ARENA_MAX_MOVE] = a->GetMaxMove();
    IXArray[_IX_MY_COORD_X] = f1->GetCoord().X;
    IXArray[_IX_MY_COORD_Y] = f1->GetCoord().Y;
    IXArray[_IX_ENEMY_COORD_X] = f2->GetCoord().X;
    IXArray[_IX_ENEMY_COORD_Y] = f2->GetCoord().Y;
    IXArray[_IX_ARENA_TICK_COUNT] = a->GetBattleTime();
    for (int i = 9;i<32;i++)
      IXArray[i] = 0;
    f1->SetConstTable(IXArray);
    delete IXArray;
}

void MyTimer::timerEvent(QTimerEvent *)
        {
        double tAngle;
        int mX;
        int mY;
        int movement;

        m1 = ar->GetMemberOne();
        m2 = ar->GetMemberTwo();
        Coord c1 = m1->GetCoord();
        Coord c2 = m2->GetCoord();

        FillIXArray(m1,m2,ar);
        FillIXArray(m2,m1,ar);

        double score1 =0;

        Action act1 = m1->GetAction(ar);
      //  Action act2 = m2->GetAction(ar);

        if (act1.ActionCode==_ACTION_TURN)
        {            
            if (abs(act1.ActionRate)<=ar->GetMaxAngle())
                movement = act1.ActionRate;
            else
                movement = (ar->GetMaxAngle()*sign(act1.ActionRate));
            c1.Angle+=movement;
            if (c1.Angle<0)
                c1.Angle+=360;
            if (c1.Angle>=360)
                c1.Angle-=360;
            m1->SetCoord(c1);
            score1+=0.0002;
        }
        else if (act1.ActionCode==_ACTION_MOVE)
        {            
            if (abs(act1.ActionRate)<=ar->GetMaxMove())
                movement = act1.ActionRate;
            else
                movement = ar->GetMaxMove()*sign(act1.ActionRate);
            tAngle = c1.Angle*_180_DIV_PI;
            mX = floor(cos(tAngle)*movement);
            mY = floor(sin(tAngle)*movement);
            c1.X+=mX;
            c1.Y-=mY;
            if (c1.X<1)
                c1.X=1;
            if (c1.Y<1)
                c1.Y=1;
            if (c1.X>(ar->GetArenaSizeX()-1))
                c1.X=ar->GetArenaSizeX()-1;
            if (c1.Y>(ar->GetArenaSizeY()-1))
                c1.Y=ar->GetArenaSizeY()-1;
            m1->SetCoord(c1);
            score1+=0.0002;
        }
        else if (act1.ActionCode==_ACTION_HALT)
        {//do nothing
        }

        ar->SetScoreOne(ar->GetScoreOne()+score1);
        ////ОЧКИ ЗА АКТИВНОСТЬ НА АРЕНЕ


  /*      if (act2.ActionCode==_ACTION_TURN)
        {
            if (abs(act2.ActionRate)<=ar.GetMaxAngle())
                movement = act2.ActionRate;
            else
                movement = (ar.GetMaxAngle()*sign(act2.ActionRate));
            c2.Angle+=movement;
            if (c2.Angle<0)
                c2.Angle+=360;
            if (c2.Angle>=360)
                c2.Angle-=360;
            m2->SetCoord(c2);
            score2+=0.0002;
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
        ar->SetMemberOne(m1);
        ar->SetMemberTwo(m2);

        ar->ReDraw();

        double distance = hypot((c1.X-c2.X),(c1.Y-c2.Y));
        score1 = 1/distance;
        double score2 = score1; //пока так

        Score1Label->setText(QString::number(ar->GetScoreOne(),'f',5));
     //   Score2Label->setText(QString::number(ar.GetScoreTwo(),'f',5));
        ar->SetScoreOne(ar->GetScoreOne()+score1);
        ar->SetScoreTwo(ar->GetScoreTwo()+score2);

        ar->IncTickCount();
        TickLabel->setText("Tick: "+QString::number(ar->GetBattleTime()));
        if (ar->GetBattleTime()==_BATTLE_TIME)
        {
            this->killTimer(TimerID);
            p->members[counter-1]->SetFitness(trunc(ar->GetScoreOne()*10000));
            cout<<"Fitness = "<<p->members[counter-1]->GetFitness()<<endl;
            cout<<"DNA usage(%) = "<<(int)((m1->GetDNAUsage()*100)/_DNASIZE)<<endl;
            ar->Initialization(this);
        }
    }

void Arena::Prepare()
{
    SetArenaSizeX((_WINDOW_SIZE_X-_BORDER*2)*_MULTIPLIER);
    SetArenaSizeY((_WINDOW_SIZE_Y-_BORDER*2)*_MULTIPLIER);
    SetMaxAngle(5);
    SetMaxMove(20);
    TickCount = 0;

    QPolygonF pg;
    tr1 = ArScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
    tr2 = ArScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
}

void Arena::ReDraw()
{
    Coord c1 = GetMemberOne()->GetCoord();
    Coord c2 = GetMemberTwo()->GetCoord();

    double tAngle;
    ArScene->removeItem(tr1);
    ArScene->removeItem(tr2);
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
    tr1 = ArScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
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
    tr2 = ArScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));

}

void Arena::Simulate()
{
    double tAngle;
    int mX;
    int mY;
    int movement;

    do
    {
        m1 = GetMemberOne();
        m2 = GetMemberTwo();
        Coord c1 = m1->GetCoord();
        Coord c2 = m2->GetCoord();

        FillIXArray(m1,m2,this);
        FillIXArray(m2,m1,this);

        double score1 =0;

        Action act1 = m1->GetAction(this);
      //  Action act2 = m2->GetAction(ar);

        if (act1.ActionCode==_ACTION_TURN)
        {
            if (abs(act1.ActionRate)<=GetMaxAngle())
                movement = act1.ActionRate;
            else
                movement = (GetMaxAngle()*sign(act1.ActionRate));
            c1.Angle+=movement;
            if (c1.Angle<0)
                c1.Angle+=360;
            if (c1.Angle>=360)
                c1.Angle-=360;
            m1->SetCoord(c1);
            score1+=0.0002;
        }
        else if (act1.ActionCode==_ACTION_MOVE)
        {
            if (abs(act1.ActionRate)<=GetMaxMove())
                movement = act1.ActionRate;
            else
                movement = GetMaxMove()*sign(act1.ActionRate);
            tAngle = c1.Angle*_180_DIV_PI;
            mX = floor(cos(tAngle)*movement);
            mY = floor(sin(tAngle)*movement);
            c1.X+=mX;
            c1.Y-=mY;
            if (c1.X<1)
                c1.X=1;
            if (c1.Y<1)
                c1.Y=1;
            if (c1.X>(GetArenaSizeX()-1))
                c1.X=GetArenaSizeX()-1;
            if (c1.Y>(GetArenaSizeY()-1))
                c1.Y=GetArenaSizeY()-1;
            m1->SetCoord(c1);
            score1+=0.0002;
        }
        else if (act1.ActionCode==_ACTION_HALT)
        {//do nothing
        }

        SetScoreOne(GetScoreOne()+score1);
        ////ОЧКИ ЗА АКТИВНОСТЬ НА АРЕНЕ


    /*      if (act2.ActionCode==_ACTION_TURN)
        {
            if (abs(act2.ActionRate)<=GetMaxAngle())
                movement = act2.ActionRate;
            else
                movement = (GetMaxAngle()*sign(act2.ActionRate));
            c2.Angle+=movement;
            if (c2.Angle<0)
                c2.Angle+=360;
            if (c2.Angle>=360)
                c2.Angle-=360;
            m2->SetCoord(c2);
            score2+=0.0002;
        }
        else if (act2.ActionCode==_ACTION_MOVE)
        {
            if (abs(act2.ActionRate)<=GetMaxMove())
                movement = act2.ActionRate;
            else
                movement = GetMaxMove()*sign(act2.ActionRate);

            tAngle= c2.Angle*_180_DIV_PI;
            mX = trunc(cos(tAngle)*movement);
            mY = trunc(sin(tAngle)*movement);
            c2.X+=mX;
            c2.Y-=mY;
            if (c2.X<1)
                c2.X=1;
            if (c2.Y<1)
                c2.Y=1;
            if (c2.X>(GetArenaSizeX()-1))
                c2.X=GetArenaSizeX()-1;
            if (c2.Y>(GetArenaSizeY()-1))
                c2.Y=GetArenaSizeY()-1;
            m2->SetCoord(c2);
        }
        else if (act2.ActionCode==_ACTION_HALT)
        {//do nothing
        }
    */
        SetMemberOne(m1);
        SetMemberTwo(m2);

        //посчитаем очки
        double distance = hypot((c1.X-c2.X),(c1.Y-c2.Y));
        score1 = 1/distance;
        double score2 = score1; //пока так
        SetScoreOne(GetScoreOne()+score1);
        SetScoreTwo(GetScoreTwo()+score2);
        IncTickCount();
    }
    while (GetBattleTime()<_BATTLE_TIME);

    p->members[counter-1]->SetFitness(trunc(GetScoreOne()*10000));
//    cout<<counter-1<<endl;
//    cout<<"Fitness = "<<p->members[counter-1]->GetFitness()<<endl;
//    cout<<"DNA usage(%) = "<<(int)((m1->GetDNAUsage()*100)/_DNASIZE)<<endl;

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
    CoordsM2.Y = GetArenaSizeY()/2+700;
    CoordsM2.Angle = 180;

    m1 = ar->GetMemberOne();
    m2 = ar->GetMemberTwo();

    ptrbyte pDNA = p->members[counter]->GetDNA();
    m1->SetDNA(pDNA);
    m1->SetCoord(CoordsM1);
    m1->ResetVPU();

    FillIXArray(m1,m2,this);

    m2->SetDNA(pDNA);
    m2->SetCoord(CoordsM2);
    m2->ResetVPU();

    FillIXArray(m2,m1,this);

    TickCount =0;
    SetMemberOne(m1);
    SetMemberTwo(m2);
    SetScoreOne(0);
    SetScoreTwo(0);

    counter++;

    if (_FAST_CALC!=1)
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

    ar->SetScene(scene);
    ar->Prepare();
    MyTimer* Timer1 = new MyTimer;
    counter = 0;

    ar->SetMemberOne(m1);
    ar->SetMemberTwo(m2);

    //------раскомментировать для создания базы (первый запуск)-------
    //pDB->AddPlayer(1, "Test");
    //pDB->CreateTable(1);
    //----------------------------------------------------------------

    //----раскомментировать для генерации новой популяции в памяти----
    //srand(time(0));
    //p->Generate();
    //----------------------------------------------------------------

    //----раскомментировать для загрузки начальной популяции из базы--
    p->Load();
    //----------------------------------------------------------------

    if (_FAST_CALC==1) //настраивается выше в разделе объявлений
    {
        for (int j = 1;j<=50;j++)//количество популяций
        {
            counter = 0;
            Population* pNew = p->Evolve(1,0);
            pNew->CopyTo(p);
            delete pNew;

            for (unsigned int i=0;i<_POPULATION_SIZE;i++)
            {
                ar->Initialization(Timer1);
                ar->Simulate();
            }
            p->Sort();
            cout<<"Leader fitness after "<<j<<" = "<<p->members[0]->GetFitness()<<endl;
        }
        p->Save(); //сохраняется только самая последняя популяция
    }
    else
    {
        Population* pNew = p->Evolve(1,0);
        pNew->CopyTo(p);
        delete pNew;
        ar->Initialization(Timer1);
    }

    return app.exec();
}

