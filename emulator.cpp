#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

using namespace std;
const int dnasize=600;

typedef int16_t word;
typedef unsigned char byte;

class CPU
{
private:
    word ar;
    int pc;
    word bc;
    word de;
    word ix;
    byte f;
    //структура регистра F
    //хххххххх
    //00000PCZ
    void SetFlagC(bool C)
    {
        if (C)
            f = f|2;
        else
            f = f&253;
    }
    void SetFlagZ(bool Z)
    {
        if (Z)
            f = f|1;
        else
            f = f&254;
    }
    void SetFlagP(bool P)
    {
        if (P)
            f = f|4;
        else
            f = f&251;
    }
    void SetFlags()
    {
        SetFlagC(0);
        if (ar==0)
            SetFlagZ(1);
        else
            SetFlagZ(0);
        //добавить установку флага P

    }
    bool ZFlag()
    {
        if ((f&1)==0)
            return false;
        else
            return true;
    }
    bool CFlag()
    {
        if ((f&2)==0)
            return false;
        else
            return true;
    }
    bool PFlag()
    {
        if ((f&4)==0)
            return false;
        else
            return true;
    }

    word GetIXValue(byte index)
    {
        return index;//дописать выборку из массива
    }

    word GetWord(byte a, byte b)
    {
        return b*256+a;
    }
    void IncPC(int step)
    {
        step*=3;
        pc+=step;
        if (pc>dnasize)
            pc=0;
        if (pc<0)
            pc=0;
    }
    char DecToHex(byte a)
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

public:
    void SetPC(word arg)
    {pc = arg;}
    void SetIX(word arg)
    {ix = arg;}
    string GetHex(byte p)
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

    int Execute(byte b1, byte b2, byte b3)    
    {
        word jump;
        word temp;
        int test;
        switch(b1)
        {
        case 0:
            IncPC(1);
        case 1:
            jump = (b2<128)?b2:(b2-128)*(-1);
            IncPC(jump);
        case 2:
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
        case 3:
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
        case 4:
            temp = (de-ar);
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
        case 5:
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
        case 6:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (ZFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 7:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (!ZFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 8:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (CFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 9:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (!CFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 10:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (PFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 11:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (!PFlag())
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 12:
            jump = (b2<128)?b2:(b2-128)*(-1);
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
        case 13:
            jump = (b2<128)?b2:(b2-128)*(-1);
            temp = (de-ar);
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

        case 14:
            jump = (b2<128)?b2:(b2-128)*(-1);
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
        case 15:
            jump = (b2<128)?b2:(b2-128)*(-1);
            temp = (de-ar);
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
        case 16:
            jump = (b2<128)?b2:(b2-128)*(-1);
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
        case 17:
            jump = (b2<128)?b2:(b2-128)*(-1);
            temp = (de-ar);
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
        case 18:
            jump = (b2<128)?b2:(b2-128)*(-1);
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
        case 19:
            jump = (b2<128)?b2:(b2-128)*(-1);
            temp = (de-ar);
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
        case 20:
            jump = (b2<128)?b2:(b2-128)*(-1);
            if (jump>0)
                jump*=-1;
            bc--;
            if ((bc%256)!=0)
            {
                IncPC(jump);
            }
            else
                IncPC(1);
        case 21:
            ar = GetWord(b2,b3);
            SetFlags();
            IncPC(1);
        case 22:
            bc= GetWord(b2,b3);
            IncPC(1);
        case 23:
            de= GetWord(b2,b3);
            IncPC(1);
        case 24:
            ar = GetIXValue(b2);
            SetFlags();
            IncPC(1);
        case 25:
            temp =GetWord(b2,b3);
            ar+=temp;
            SetFlags();
            test = ar+temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 26:
            ar+=bc;
            SetFlags();
            test = ar+bc;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 27:
            ar+=de;
            SetFlags();
            test = ar+bc;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 28:
            temp =GetIXValue(b2);
            ar+=temp;
            SetFlags();
            test = ar+temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 29:
            temp = GetWord(b2,b3);
            ar-=temp;
            SetFlags();
            test = ar-temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 30:
            ar-=bc;
            SetFlags();
            test = ar-bc;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 31:
            ar-=de;
            SetFlags();
            test = ar-de;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 32:
            temp = GetIXValue(b2);
            ar-=temp;
            SetFlags();
            test = ar-temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 33:
            temp =GetWord(b2,b3);
            ar*=temp;
            SetFlags();
            test = ar*temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 34:
            ar*=bc;
            SetFlags();
            test = ar*de;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 35:
            ar*=de;
            SetFlags();
            test = ar*de;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 36:
            temp =GetIXValue(b2);
            ar*=temp;
            SetFlags();
            test = ar*temp;
            if ((test>32767)||(test<-32767))
                 SetFlagC(true);
            IncPC(1);
        case 37:
            temp = GetWord(b2,b3);
            ar/=temp;
            SetFlags();
            IncPC(1);
        case 38:
            ar/=bc;
            SetFlags();
            IncPC(1);
        case 39:
            ar/=de;
            SetFlags();
            IncPC(1);
        case 40:
            temp = GetIXValue(b2);
            ar/=temp;
            SetFlags();
            IncPC(1);
        case 41:
            temp= GetWord(b2,b3);
            ar%=temp;
            SetFlags();
            IncPC(1);
        case 42:
            ar%=bc;
            SetFlags();
            IncPC(1);
        case 43:
            ar%=bc;
            SetFlags();
            IncPC(1);
        case 44:
            temp = GetIXValue(b2);
            ar%=temp;
            SetFlags();
            IncPC(1);
        case 45:
            test = ar;
            ar++;
            SetFlags();
            if (ar<test)
                SetFlagC(1);
            IncPC(1);
        case 46:
            bc++;
            IncPC(1);
        case 47:
            de++;
            IncPC(1);
        case 48:
            test = ar;
            ar--;
            SetFlags();
            if (ar>test)
                SetFlagC(1);
            IncPC(1);
        case 49:
            bc--;
            IncPC(1);
        case 50:
            de--;
            IncPC(1);
        case 51:
            temp = ar;
            ar = bc;
            bc = temp;
            SetFlags();
            IncPC(1);
        case 52:
            temp = ar;
            ar = de;
            de = temp;
            SetFlags();
            IncPC(1);
        case 53:
            temp = bc;
            de = bc;
            bc = temp;
            SetFlags();
            IncPC(1);
        case 54:
            srand(GetWord(b2,b3));
            IncPC(1);
        case 55:
            ar = rand();
            SetFlags();
            IncPC(1);
        case 56:
            bc= rand();
            IncPC(1);
        case 57:
            de=rand();
            IncPC(1);
/*        case 58:
            return "LD_AR,ANGLE_TO_WALL";
        case 59:
            return "LD_AR,ANGLE_TO_ENEMY";
        case 60:
            return "RET_MOVE";
        case 61:
            return "RET_TURN";
        case 62:
            return "RET_HALT";
        case 63:
            return "RET_SOMETHING";
*/        default:
            IncPC(1);
        }
        return 0;
    }
    string GetMnemonic(byte b1, byte b2, byte b3)
    {
        int jump;
        stringstream ss;
        string s;
        switch(b1)
        {
        case 0:
            return "NOP";
        case 1:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR:"<<(int)jump;
            ss>>s;
            return s;
        case 2:
            ss <<"CP_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 3:
            return "CP_AR,BC";
        case 4:
            return "CP_AR,DE";
        case 5:
            ss <<"CP_AR,(IX+"<<b2<<")";
            ss>>s;
            return s;
        case 6:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR_Z:"<<(int)jump;
            ss>>s;
            return s;
        case 7:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR_NZ:"<<(int)jump;
            ss>>s;
            return s;
        case 8:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR_C:"<<(int)jump;
            ss>>s;
            return s;
        case 9:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR_NC:"<<(int)jump;
            ss>>s;
            return s;
        case 10:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR_P:"<<(int)jump;
            ss>>s;
            return s;
        case 11:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"JR_NP:"<<(int)jump;
            ss>>s;
            return s;
        case 12:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJNZ_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 13:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJNZ_AR,DE:"<<(int)jump;
            ss>>s;
            return s;
        case 14:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJZ_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 15:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJZ_AR,DE:"<<(int)jump;
            ss>>s;
            return s;
        case 16:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJNC_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 17:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJNC_AR,DE:"<<(int)jump;
            ss>>s;
            return s;
        case 18:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJC_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 19:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"CJC_AR,DE:"<<(int)jump;
            ss>>s;
            return s;
        case 20:
            jump = (b2<128)?b2:(b2-128)*(-1);
            ss <<"DJNZ:"<<(int)jump;
            ss>>s;
            return s;
        case 21:
            ss <<"LD_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 22:
            ss <<"LD_BC,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 23:
            ss <<"LD_DE,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 24:
            ss <<"LD_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 25:
            ss <<"ADD_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 26:
            return "ADD_AR,BC";
        case 27:
            return "ADD_AR,DE";
        case 28:
            ss <<"ADD_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 29:
            ss <<"DEC_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 30:
            return "DEC_AR,BC";
        case 31:
            return "DEC_AR,DE";
        case 32:
            ss <<"DEC_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 33:
            ss <<"MUL_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 34:
            return "MUL_AR,BC";
        case 35:
            return "MUL_AR,DE";
        case 36:
            ss <<"MUL_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 37:
            ss <<"DIV_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 38:
            return "DIV_AR,BC";
        case 39:
            return "DIV_AR,DE";
        case 40:
            ss <<"DIV_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 41:
            ss <<"RST_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 42:
            return "RST_AR,BC";
        case 43:
            return "RST_AR,DE";
        case 44:
            ss <<"RST_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 45:
            return "INC_AR";
        case 46:
            return "INC_BC";
        case 47:
            return "INC_DE";
        case 48:
            return "DEC_AR";
        case 49:
            return "DEC_BC";
        case 50:
            return "DEC_DE";
        case 51:
            return "EX_AR,BC";
        case 52:
            return "EX_AR,DE";
        case 53:
            return "EX_BC,DE";
        case 54:
            ss <<"SEED:"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 55:
            return "LD_AR,RND";
        case 56:
            return "LD_BC,RND";
        case 57:
            return "LD_DE,RND";
        case 58:
            return "LD_AR,ANGLE_TO_WALL";
        case 59:
            return "LD_AR,ANGLE_TO_ENEMY";
        case 60:
            return "RET_MOVE";
        case 61:
            return "RET_TURN";
        case 62:
            return "RET_HALT";
        case 63:
            return "RET_SOMETHING";

        default:
            return "NOP";
        }
        return "NOP";

    }

};

byte* ChromGen()
{
byte* Chrom;
Chrom = new byte[dnasize];
for (int i=0;i<dnasize;i++)
    Chrom[i]= std::rand()%256;
return Chrom;
}

int main()
{
   CPU cpu;
   byte* arr = ChromGen();
   for (int i=0;i<dnasize;i+=3)
   {
       cout<<(i/3)<<'\t'<<cpu.GetHex(arr[i]%64)<<setw(4)<<cpu.GetHex(arr[i+1])<<setw(4)
          <<cpu.GetHex(arr[i+2])<<'\t'<<cpu.GetMnemonic(arr[i]%64,arr[i+1],arr[i+2])<<endl;
   }

}
