#include "database.h"
#include "base64.h"

static int callback(void* pParam, int argc, char **argv, char **azColName)
{
    memcpy(pParam, argv[0], strlen(argv[0])+1); //проверить, нужен ли флаг
    return 0;
}

Database::~Database()
{
    sqlite3_close(db);
}

Database::Database()
{
    char* err=0;
    std::stringstream ss;
    ss << "genotype.db";
    string FileName = ss.str();
    const char* pFileName = FileName.c_str();

    if( sqlite3_open(pFileName, &db) )
        {std::cout<< "DB Error open/create: "<< sqlite3_errmsg(db)<<'\n';}
    else if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS nicknames (playerid INTEGER PRIMARY KEY, nickname CHAR);",0,0,&err))
        {
            std::cout<<"SQL Error: "<< err<<endl;
            sqlite3_free(err);
        }
}

bool Database::ClearTable(int PlayerID)
{
    char* err=0;
    std::stringstream ss;

    ss <<"DELETE FROM t"<<PlayerID<<";";
    string Query = ss.str();
    const char* pQuery= Query.c_str();

    if (sqlite3_exec(db,pQuery,0,0,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;;
        sqlite3_free(err);
        return false;
    }
    return true;
}

bool Database::CreateTable(int PlayerID)
{
    char* err=0;
    std::stringstream ss;
    ss <<"CREATE TABLE IF NOT EXISTS t"<<PlayerID<<" (id INTEGER PRIMARY KEY, dna CHAR, fitness INTEGER);";
    string Query = ss.str();

    const char* pQuery= Query.c_str();
    if (sqlite3_exec(db,pQuery,0,0,&err))
        {
            std::cout<<"SQL Error: "<< err<<endl;
            sqlite3_free(err);
            return false;
        }
    return true;
}

char* Database::GetNickname(int PlayerID)
{
    char* err=0;
    std::stringstream ss;
    ss <<"SELECT nickname FROM nicknames WHERE playerid='"<< PlayerID <<"';";
    string Query = ss.str();
    const char* pQuery= Query.c_str();
    char* buf = new char[_NICKNAME_MAX_LENGTH];

    if (sqlite3_exec(db,pQuery,callback,buf,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
    }

    return buf;
}

bool Database::AddPlayer(int PlayerID, char* Nickname)
{
    char* err=0;
    std::stringstream ss;
    ss << "INSERT INTO nicknames (playerid,nickname) VALUES('" << PlayerID << "','"<<Nickname<<"');";
    string Query = ss.str();
    const char* pQuery= Query.c_str();

    if (sqlite3_exec(db,pQuery,0,0,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
        return false;
    }
    return true;
}

bool Database::WriteFitness(int PlayerID, int OrdNumber, int Fitness)
{
    char* err=0;
    std::stringstream ss;
    ss <<"UPDATE t"<<PlayerID<<" SET fitness='"<< Fitness<<"' WHERE id='"<<OrdNumber<<"';";
    string Query = ss.str();
    const char* pQuery= Query.c_str();

    if (sqlite3_exec(db,pQuery,0,0,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
        return false;
    }
    return true;
}

bool Database::AddDNA(int PlayerID, int OrdNumber, ptrbyte pDNA)
{
    char* err=0;
    std::stringstream ss;

    const char* b64dna;
    ss << base64_code(pDNA, _DNASIZE);
    std::string tmp = ss.str();
    b64dna=tmp.c_str();

    ss.str(std::string());
    ss << "INSERT INTO t"<<PlayerID<<" (id,dna) VALUES('" <<OrdNumber<< "','"<<b64dna<<"');";
    string Query = ss.str();
    const char* pQuery= Query.c_str();

    if (sqlite3_exec(db,pQuery,0,0,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
        return false;
    }
    return true;

}

int Database::GetFitness(int PlayerID, int OrdNumber)
{
    char* err=0;
    std::stringstream ss;
    ss <<"SELECT fitness FROM t"<<PlayerID<<" WHERE id='"<<OrdNumber<<"';";
    string Query = ss.str();
    const char* pQuery= Query.c_str();
    char* buf = new char[16];

    if (sqlite3_exec(db,pQuery,callback,buf,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
    }

    int result = atoi(buf);
    delete(buf);
    return result;
}

bool Database::GetDNA(int PlayerID, int OrdNumber, ptrbyte Buffer)
{
    char* err=0;
    std::stringstream ss;
    ss <<"SELECT dna FROM t"<<PlayerID<<" WHERE id='"<<OrdNumber<<"';";
    string Query = ss.str();
    const char* pQuery= Query.c_str();
    ptrbyte buf = new byte[_DNASIZE*2];

    if (sqlite3_exec(db,pQuery,callback,buf,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
        return false;
    }

    ptrbyte tBuffer = base64_decode(buf, _DNASIZE*2);

    memcpy(Buffer, tBuffer, _DNASIZE);
    delete(tBuffer);
    delete(buf);

    return true;
}

bool Database::Execute(char *pSQL)
{
    char* err=0;

    if (sqlite3_exec(db,pSQL,0,0,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
        return false;
    }
    return true;
}

bool Database::GetPopulation(int PlayerID, ptrbyte Buffer)
{
    //написать процедуру
    return true;
}
