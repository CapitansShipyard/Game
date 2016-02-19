#include "service.h"

string GetMnemonic(byte b1, byte b2, byte b3)
    {
        int jump;
        stringstream ss;
        string s;
        switch(b1)
        {
        case 0:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR:"<<(int)jump;
            ss>>s;
            return s;
        case 1:
            ss <<"CP_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 2:
            return "CP_AR,BC";
        case 3:
            ss <<"CP_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 4:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR_Z:"<<(int)jump;
            ss>>s;
            return s;
        case 5:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR_NZ:"<<(int)jump;
            ss>>s;
            return s;
        case 6:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR_C:"<<(int)jump;
            ss>>s;
            return s;
        case 7:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR_NC:"<<(int)jump;
            ss>>s;
            return s;
        case 8:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR_P:"<<(int)jump;
            ss>>s;
            return s;
        case 9:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"JR_NP:"<<(int)jump;
            ss>>s;
            return s;
        case 10:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"CJNZ_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 11:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"CJZ_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 12:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"CJNC_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 13:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"CJC_AR,BC:"<<(int)jump;
            ss>>s;
            return s;
        case 14:
            jump = (b2<128)?b2:((b2-128)&191)*(-1);
            ss <<"DJNZ:"<<(int)jump;
            ss>>s;
            return s;
        case 15:
            ss <<"LD_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 16:
            ss <<"LD_BC,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 17:
            ss <<"LD_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 18:
            ss <<"ADD_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 19:
            return "ADD_AR,BC";
        case 20:
            ss <<"ADD_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 21:
            ss <<"DEC_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 22:
            return "DEC_AR,BC";
        case 23:
            ss <<"DEC_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 24:
            ss <<"MUL_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 25:
            return "MUL_AR,BC";
        case 26:
            ss <<"MUL_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 27:
            ss <<"DIV_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 28:
            return "DIV_AR,BC";
        case 29:
            ss <<"DIV_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 30:
            ss <<"RST_AR,"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 31:
            return "RST_AR,BC";
        case 32:
            ss <<"RST_AR,(IX+"<<GetWord(b2,0)<<")";
            ss>>s;
            return s;
        case 33:
            return "INC_AR";
        case 34:
            return "INC_BC";
        case 35:
            return "DEC_AR";
        case 36:
            return "DEC_BC";
        case 37:
            return "EX_AR,BC";
        case 38:
            ss <<"SEED:"<<GetWord(b2,b3);
            ss>>s;
            return s;
        case 39:
            return "LD_AR,RND";
        case 40:
            return "LD_BC,RND";
        case 41:
            return "LD_AR,ANGLE_TO_WALL";
        case 42:
            return "LD_AR,ANGLE_TO_ENEMY";
        case 43:
            return "RET_MOVE_FORWARD";
        case 44:
            return "RET_TURN";
        case 45:
            return "RET_HALT";
        case 46:
            return "RET_TURN_TO_ENEMY";
        case 47:
            return "RET_TURN_FROM_ENEMY";
        case 48:
            return "RET_TURN_FROM_WALL";
        case 49:
            return "RET_MOVE_BACKWARD";
        case 50:
            return "NOP";
        case 51:
            return "NOP";
        case 52:
            return "NOP";
        case 53:
            return "NOP";
        case 54:
            return "NOP";
        case 55:
            return "NOP";
        case 56:
            return "NOP";
        case 57:
            return "NOP";
        case 58:
            return "NOP";
        case 59:
            return "NOP";
        case 60:
            return "NOP";
        case 61:
            return "NOP";
        case 62:
            return "NOP";
        case 63:
            return "NOP";

        default:
            return "NOP";
        }
        return "NOP";

    }

