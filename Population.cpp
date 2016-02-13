#include "Population.h"

//-------------!!Преобразование Base64-----------------
#define S_(a) S[n * 3 + a]
#define S__(a,b) (S[n * 3 + a] & b)
#define S__l(a,b,c) ((S[n * 3 + a] & b) << c)
#define B1 buffer[n * 4] = base64ABC[ (S_(0) >> 2) ];
#define B2 buffer[n * 4 + 1] = base64ABC [ (S__l(0,0x3,4)) | S_(1) >> 4 ];
#define B3 buffer[n * 4 + 2] = base64ABC [ S__l(1,0x0F,2) | S_(2) >> 6];
#define B4 buffer[n * 4 + 3] = base64ABC [ S__(2,0x3F) ];

unsigned char * base64_code (unsigned char * S, int SIZE = 0)
{
    uchar_t c, *buffer;
    int n;

    c = (SIZE == 0) ? strlen ((const char *) S) % 3 : SIZE % 3;
    SIZE = (SIZE == 0) ? strlen ((const char *) S) / 3 : SIZE / 3;

    buffer = new uchar_t [SIZE * 4 + 5];

    for (n = 0; n <    SIZE; n++)
    { B1; B2; B3; B4; }

    switch (c)
    {
    case 1:
        B1; B2;
        buffer[n * 4 + 2] = '=';
        buffer[n * 4 + 3] = '=';
        n++;
        break;
    case 2:
        B1; B2; B3;
        buffer[n * 4 + 3] = '=';
        n++;
        break;
    }
    buffer[n * 4] = 0;
  //  printf ("%s---\n", buffer);
    return buffer;
}

#define BASE64(a) ((unsigned char) (strchr (base64ABC, S[n * 4 + a]) - base64ABC))
unsigned char *
base64_decode (unsigned char * S, int SIZE = 0)
{
    unsigned char * ptr;
    int n;

    if (SIZE % 4)
        return NULL;

    SIZE = SIZE ? SIZE / 4 : strlen ((const char *) S) / 4;
    ptr = new unsigned char [SIZE * 4 + 5];

    for (n = 0; n < SIZE; n++)
    {
        ptr[n * 3] = (BASE64(0) << 2) | ( BASE64(1) >> 4);
        if (S[n * 4 +2] != '=')
        {
            ptr[n * 3 + 1] = ((BASE64(1) & 0x0F) << 4) | (BASE64(2) >> 2);
            if (S[n * 4 + 3] != '=')
                ptr[n * 3 + 2] = ((BASE64(2) & 0x03) << 6) | BASE64 (3);
            else
                ptr[n * 3 + 2] = 0;
        }
        else
            ptr[n * 3 +1] = 0;
    }

    n++;
    ptr [n * 3] = 0;
    return ptr;
}
//-------------!!Преобразование Base64-----------------

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
        std::cout<<"SQL Error: "<< err<<endl;;
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
