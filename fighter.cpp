#include "arena.h"
#include "service.h"

word VPU::GetRND()
{
    word res = GetWord(randarray[randpointer],0);
    randpointer++;

    return res;
}

void VPU::SetFlagC(bool C)
    {
        if (C)
            f = f|2;
        else
            f = f&253;
    }
void VPU::SetFlagZ(bool Z)
    {
        if (Z)
            f = f|1;
        else
            f = f&254;
    }
void VPU::SetFlagP(bool P)
    {
        if (P)
            f = f|4;
        else
            f = f&251;
    }
void VPU::SetFlags()
    {
        SetFlagC(0);
        if (ar==0)
            SetFlagZ(1);
        else
            SetFlagZ(0);
        SetFlagP(1);
        //добавить установку флага P

    }
bool VPU::ZFlag()
    {
        if ((f&1)==0)
            return false;
        else
            return true;
    }
bool VPU::CFlag()
    {
        if ((f&2)==0)
            return false;
        else
            return true;
    }
bool VPU::PFlag()
    {
        if ((f&4)==0)
            return false;
        else
            return true;
    }

word VPU::GetIXValue(byte index)
    {
        byte temp=index|31;
        return IXArray[temp];
    }

void VPU::IncPC(int step)
    {
        step*=3;
        pc+=step;
        if (pc>_DNASIZE)
            pc=0;
    }
char VPU::DecToHex(byte a)
    {
    switch(a)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    }
    return '0';
    }

void VPU::Reset()
    {
        ar = 0;
        bc = 0;
        ix = 0;
        pc = 0;
        f = 0;
        SetFlags();
        srand(1);
        for (int i = 0;i<65536;i++)
           randarray[i] = rand()%256;
        randpointer = 0;
        DNAUsage = 0;
    }
int VPU::GetPC()
    {return pc;}
void VPU::SetPC(word arg)
    {pc = arg;}
void VPU::SetIX(word arg)
    {ix = arg;}
string VPU::GetHex(byte p)
    {
        int a = p/16;
        int b = p%16;
        char ca = DecToHex(a);
        char cb = DecToHex(b);
        stringstream ss;
        ss<<ca<<cb;
        string s;
        ss>>s;
        return s;
    }

int VPU::Execute(byte b1, byte b2, byte b3)
    {
        word jump;
        word temp;
        int test;
        switch(b1)
        {
        case 0:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            IncPC(jump);
            break;
        case 1:
            temp = (GetWord(b2,b3)-ar);
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            IncPC(1);
            break;
        case 2:
            temp = (bc-ar);
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            IncPC(1);
            break;
        case 3:
            temp = GetIXValue(b2);
            temp-=ar;
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            IncPC(1);
            break;
        case 4:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            if (ZFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 5:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            if (!ZFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 6:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            if (CFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 7:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            if (!CFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 8:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            if (PFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 9:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            if (!PFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 10:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            temp = (bc-ar);
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            if (!ZFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 11:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            temp = (bc-ar);
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            if (ZFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 12:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            temp = (bc-ar);
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            if (!CFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 13:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            temp = (bc-ar);
            if (temp==0)
            {
                SetFlagZ(1);
                SetFlagC(0);
            }
            else if (temp>0)
            {
                SetFlagZ(0);
                SetFlagC(0);
            }
            else
            {
                SetFlagZ(0);
                SetFlagC(1);
            }
            if (CFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 14:
            jump = (b2<128)?(b2&&63):((b2-128)&191)*(-1);
            if (jump>0)
                jump*=-1;
            bc--;
            if ((bc%256)!=0)
            {
                IncPC(jump);
            }
            else
                IncPC(1);
            break;
        case 15:
            ar = GetWord(b2,b3);
            SetFlags();
            IncPC(1);
            break;
        case 16:
            bc= GetWord(b2,b3);
            IncPC(1);
            break;
        case 17:
            ar = GetIXValue(b2);
            SetFlags();
            IncPC(1);
            break;
        case 18:
            temp =GetWord(b2,b3);
            ar+=temp;
            SetFlags();
            test = ar+temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 19:
            ar+=bc;
            SetFlags();
            test = ar+bc;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 20:
            temp =GetIXValue(b2);
            ar+=temp;
            SetFlags();
            test = ar+temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 21:
            temp = GetWord(b2,b3);
            ar-=temp;
            SetFlags();
            test = ar-temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 22:
            ar-=bc;
            SetFlags();
            test = ar-bc;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 23:
            temp = GetIXValue(b2);
            ar-=temp;
            SetFlags();
            test = ar-temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 24:
            temp =GetWord(b2,b3);
            ar*=temp;
            SetFlags();
            test = ar*temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 25:
            ar*=bc;
            SetFlags();
            test = ar*bc;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 26:
            temp =GetIXValue(b2);
            ar*=temp;
            SetFlags();
            test = ar*temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
            break;
        case 27:
            temp = GetWord(b2,b3);
            ar/=temp;
            SetFlags();
            IncPC(1);
            break;
        case 28:
            if (bc!=0)
                ar/=bc;
            SetFlags();
            IncPC(1);
            break;
        case 29:
            temp = GetIXValue(b2);
            if (temp!=0)
                ar/=temp;
            SetFlags();
            IncPC(1);
            break;
        case 30:
            temp= GetWord(b2,b3);
            if (temp!=0)
                ar=ar%temp;
            SetFlags();
            IncPC(1);
            break;
        case 31:
            if (bc!=0)
                ar=ar%bc;
            SetFlags();
            IncPC(1);
            break;
        case 32:
            temp = GetIXValue(b2);
            if (temp!=0)
                ar=ar%temp;
            SetFlags();
            IncPC(1);
            break;
        case 33:
            test = ar;
            ar++;
            SetFlags();
            if (ar<test)
                SetFlagC(1);
            IncPC(1);
            break;
        case 34:
            bc++;
            IncPC(1);
            break;
        case 35:
            test = ar;
            ar--;
            SetFlags();
            if (ar>test)
                SetFlagC(1);
            IncPC(1);
            break;
        case 36:
            bc--;
            IncPC(1);
            break;
        case 37:
            temp = ar;
            ar = bc;
            bc = temp;
            SetFlags();
            IncPC(1);
            break;
        case 38:
            SetRandpointer(GetWord(b2,b3));
            IncPC(1);
            break;
        case 39:
            ar = GetRND();
            SetFlags();
            IncPC(1);
            break;
        case 40:
            bc= GetRND();
            IncPC(1);
            break;
        case 41:
            ar = AngleToWall();
            IncPC(1);
            break;
        case 42:
            ar = AngleToEnemy();
            IncPC(1);
            break;
        case 43:
            IncPC(1);
            return(1);
        case 44:
            IncPC(1);
            return(2);
        case 45:
            IncPC(1);
            return(3);
        case 46:
            IncPC(1);
            return(4);//turn to enemy
        case 47:
            IncPC(1);
            return(5);//turn from enemy
        case 48:
            IncPC(1);
            return(6);//turn from wall
        case 49:
            IncPC(1);
            return(7);//move backward
        case 50:
            IncPC(1);
            break;
        case 51:
            IncPC(1);
            break;
        case 52:
            IncPC(1);
            break;
        case 53:
            IncPC(1);
            break;
        case 54:
            IncPC(1);
            break;
        case 55:
            IncPC(1);
            break;
        case 56:
            IncPC(1);
            break;
        case 57:
            IncPC(1);
            break;
        case 58:
            IncPC(1);
            break;
        case 59:
            IncPC(1);
            break;
        case 60:
            IncPC(1);
            break;
        case 61:
            IncPC(1);
            break;
        case 62:
            IncPC(1);
            break;
        case 63:
            IncPC(1);
            break;
        default:
            IncPC(1);
        }
        return 0;
    }

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

float absVect(Coord a)
{
    return((float)(std::sqrt(std::pow(a.X,2)+std::pow(a.Y,2))));
}

int VPU::AngleToWall()//возвращает угол от стены
{
    int walls[4][2];
    int temp[2];
    Coord MyCoord;
    MyCoord.X = GetIXArrayValue(_IX_MY_COORD_X);
    MyCoord.Y = GetIXArrayValue(_IX_MY_COORD_Y);

    walls[0][0]=MyCoord.Y; walls[0][1]=270;
    walls[1][0]=GetIXArrayValue(0)-MyCoord.X; walls[1][1]=180;
    walls[2][0]=GetIXArrayValue(1)-MyCoord.Y; walls[2][1]=90;
    walls[3][0]=MyCoord.X; walls[3][1]=0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3-i; j++)
           if(walls[j][0]>walls[j+1][0])
            {
                temp[0]=walls[j+1][0]; temp[1]=walls[j+1][1];
                walls[j+1][0]=walls[j][0]; walls[j+1][1]=walls[j][1];
                walls[j][0]=temp[0]; walls[j][1]=temp[1];
            }

    return(walls[0][1]);//возвращаем значение угла из отсортированного списка стен
}

int VPU::AngleToEnemy()//возвращает угол К врагу
{
    Coord ECoords;
    Coord MyCoord;
    MyCoord.X = GetIXArrayValue(_IX_MY_COORD_X);
    MyCoord.Y = GetIXArrayValue(_IX_MY_COORD_Y);
    ECoords.X = GetIXArrayValue(_IX_ENEMY_COORD_X);
    ECoords.Y = GetIXArrayValue(_IX_ENEMY_COORD_Y);

    Coord vector=ECoords-MyCoord;
    Coord Xvector;
    Xvector.X=1; Xvector.Y=0;
    float cosA=(vector*Xvector)/(absVect(vector)*absVect(Xvector));
    int Angle=trunc(std::acos(cosA)*180.0/_PI);
    if (vector.Y>0)
       Angle=360-Angle;//т.к. косинус определен на промежутке от 0 до 180

    return (Angle);
}

Fighter::Fighter()
	{
    Act.ActionCode=_ACTION_HALT;
	Act.ActionRate=0;
	MyCoord.X=0;
	MyCoord.Y=0;
	MyCoord.Angle=0;
    vpu.Reset();
	}

Action Fighter::GetAction(Arena a)
{
    //основная процедура исполняемого кода бойца
    //процессор должен быть настроен, выполнение продолжается с момента последнего прерывания
    //должна быть реализована защита от зависания

    unsigned int i = 0;
    unsigned int step = 0;
    int RetCode;
    bool stop=false;
    int temp;

    Act.ActionCode = _ACTION_HALT;
    Act.ActionRate = 0;

  /*  if (a.GetBattleTime() == 0)
    {
            cout<<"ar="<<vpu.GetAR()<<", bc="<<vpu.bc<<" f="<<vpu.f<<", pc="<<vpu.GetPC()<<endl;
    }*/
    while ((step<_VPU_MAX_STEPS)&&(!stop))//настроить
    {
        i = vpu.GetPC();
        if (vpu.DNAUsage<i)
            vpu.DNAUsage = i;
        step++;

//        cout<<(i/3)<<'\t'<<vpu.GetHex(dna[i]%64)<<setw(4)<<vpu.GetHex(dna[i+1])<<setw(4)
//           <<vpu.GetHex(dna[i+2])<<'\t'<<GetMnemonic(dna[i]%64,dna[i+1],dna[i+2])<<'\t'<<vpu.GetAR()<<endl;
        RetCode = vpu.Execute(dna[i]%64,dna[i+1],dna[i+2]);
        switch(RetCode)
        {
        case 1:
            Act.ActionCode = _ACTION_MOVE;
            Act.ActionRate = abs((vpu.GetAR()&63));
            stop = true;
            break;
        case 2:
            Act.ActionCode = _ACTION_TURN;
            if (vpu.GetAR()<0)
               Act.ActionRate = (vpu.GetAR()&255)*(-1);
            else
               Act.ActionRate = (vpu.GetAR()&255);
            stop = true;
            break;
        case 3:
            Act.ActionCode = _ACTION_HALT;
            Act.ActionRate = 0;
            stop = true;
            break;
        case 4:
            Act.ActionCode = _ACTION_TURN;
            temp = MyCoord.Angle-vpu.AngleToEnemy();
            if (temp>180)
                temp = (360-temp)*(-1);
            Act.ActionRate = temp;
            stop = true;
            break;
        case 5:
            Act.ActionCode = _ACTION_TURN;
            temp = MyCoord.Angle-vpu.AngleToWall();
            temp+=180;
            if (temp>360)
                temp-=360;
            if (temp>180)
                temp = (360-temp)*(-1);
            Act.ActionRate = temp;
            stop = true;
            break;
        case 6:
            Act.ActionCode = _ACTION_TURN;
            temp = MyCoord.Angle-vpu.AngleToWall();
            if (temp>180)
                temp = (360-temp)*(-1);
            Act.ActionRate = temp;
            stop = true;
            break;
        case 7:
            Act.ActionCode = _ACTION_MOVE;
            Act.ActionRate = abs(vpu.GetAR()&63)*(-1);
            stop = true;
            break;

        }
    }

	return (Act);
}
