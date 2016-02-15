#include "service.h"

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
            ss <<"CP_AR,(IX+"<<GetWord(b2,0)<<")";
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

