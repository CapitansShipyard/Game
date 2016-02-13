#include "Population.h"
#include "base64.h"

static int callback(void* HexChrom, int argc, char **argv, char **azColName)
    {
        memcpy(HexChrom, argv[0], razm*2);
        return 0;
    }

ptrbyte Population::ChromGen()
{
    ptrbyte buf = new byte[razm];
    for (int i=0;i<razm;i++)
        buf[i]=std::rand()%256;
    return buf;
}

void Population::ChromWrite(int id, ptrbyte Chrom)
{
    char* err=0;
    std::stringstream ss;
	const char* sql;
	const char* FFchrom;
    ss << base64_code(Chrom, razm);

	std::string tmp = ss.str();
	FFchrom=tmp.c_str();
	ss.str(std::string());
	ss << "INSERT INTO population (id,chrom) VALUES('" << id << "','"<<FFchrom<<"');";
	tmp = ss.str();
	sql=tmp.c_str();
	if (sqlite3_exec(db, sql,0,0,&err))
	{
        std::cout<<"SQL Error: "<< err<<endl;
		sqlite3_free(err);
	}

}
void Population::PopGen()
{
	int id = 100;
    ptrbyte buffer;
    for (int i =0;i<PopSize;i++)
	{
        buffer = ChromGen();
        ChromWrite(id,buffer);
		id++;
	}
    delete(buffer);
}
Population::Population(int pSize, const char* PlayerNick)
{
    char* err=0;
    PopSize=pSize;
	std::stringstream ss;
	ss << PlayerNick << ".db";
    string FileName = ss.str();
    const char* pFileName = FileName.c_str();

    if( sqlite3_open(pFileName, &db) )
        {std::cout<< "DB Error open/create: "<< sqlite3_errmsg(db)<<'\n';}
	else if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS population (id INTEGER PRIMARY KEY, chrom CHAR, fitness INTEGER);",0,0,&err))
		{
            std::cout<<"SQL Error: "<< err<<endl;
			sqlite3_free(err);
		}
    ClearDB();
    PopGen();
}
void Population::WriteFitness(int id,int fitness)
{
    char* err=0;
	std::stringstream ss;
	ss <<"UPDATE population SET fitness='"<< fitness<<"' WHERE id='"<<id<<"';";
    string Query = ss.str();
    const char* pQuery= Query.c_str();

    if (sqlite3_exec(db,pQuery,0,0,&err))
	{
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
	}
}

void Population::GetChrom(int id, ptrbyte pBuf)
{
    char* err=0;
    std::stringstream ss;
	ss <<"SELECT chrom FROM population WHERE id='"<< id <<"';";
    string Query = ss.str();
    const char* pQuery= Query.c_str();
    ptrbyte Chrom = new byte[razm*2];

    if (sqlite3_exec(db,pQuery,callback,Chrom,&err))
	{
        std::cout<<"SQL Error: "<< err<<endl;
        sqlite3_free(err);
	}

    ptrbyte buffer = base64_decode(Chrom, razm*2);
    memcpy(pBuf, buffer, razm);
    delete(buffer);
    delete(Chrom);

}

void Population::ClearDB()
{
    char* err=0;
    std::stringstream ss;
    ss <<"DELETE FROM population;";
    string Query = ss.str();
    const char* pQuery= Query.c_str();

    if (sqlite3_exec(db,pQuery,0,0,&err))
    {
        std::cout<<"SQL Error: "<< err<<endl;;
        sqlite3_free(err);
    }

}

Population::~Population()
{
	sqlite3_close(db);
}
