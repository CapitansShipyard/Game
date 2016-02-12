
#include "Population.h"
#include <iostream>
#include <cstdlib>
#include <sqlite3.h>
#include <cstring>
#include <sstream>
char* HexChrom=new char[razm*2];
void Population::HexToDec(char* HexChrom)
{
    int a,b;
    int temp;
    for(int i=0;i<razm*2;i+=2)
    {
    a = HexChrom[i];
    b = HexChrom[i+1];
    switch(a)
        {
        case '0':
            {temp=0;
            break;}
        case '1':
            {temp=16;
            break;}
        case '2':
            {temp=32;
            break;}
        case '3':
            {temp=48;
            break;}
        case '4':
            {temp=64;
            break;}
        case '5':
            {temp=80;
            break;}
        case '6':
            {temp=96;
            break;}
        case '7':
            {temp=112;
            break;}
        case '8':
            {temp=128;
            break;}
        case '9':
            {temp=144;
            break;}
        case 'A':
            {temp=160;
            break;}
        case 'B':
            {temp=176;
            break;}
        case 'C':
            {temp=192;
            break;}
        case 'D':
            {temp=208;
            break;}
        case 'E':
            {temp=224;
            break;}
        case 'F':
            {temp=240;
            break;}
        }
    switch(b)
        {
        case '1':
            {temp+=1;
            break;}
        case '2':
            {temp+=2;
            break;}
        case '3':
            {temp+=3;
            break;}
        case '4':
            {temp+=4;
            break;}
        case '5':
            {temp+=5;
            break;}
        case '6':
            {temp+=6;
            break;}
        case '7':
            {temp+=7;
            break;}
        case '8':
            {temp+=8;
            break;}
        case '9':
            {temp+=9;
            break;}
        case 'A':
            {temp+=10;
            break;}
        case 'B':
            {temp+=11;
            break;}
        case 'C':
            {temp+=12;
            break;}
        case 'D':
            {temp+=13;
            break;}
        case 'E':
            {temp+=14;
            break;}
        case 'F':
            {temp+=15;
            break;}
        }
        Population::Chrom[i/2]=temp;
    }
}
static int callback(void* HexChrom, int argc, char **argv, char **azColName)
    {
    memcpy(HexChrom, argv[0], razm*2);
    return 0;
        }
void Population::ChromGen()
{
for (int i=0;i<razm;i++)
{
	Chrom[i]=std::rand()%256;
}
}
char Population::DecToHex(byte a)
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
void Population::ChromWrite(int id)
{
	std::stringstream ss;
	const char* sql;
	const char* FFchrom;
	for (int i=0;i<razm;i++)
	{
		ss << DecToHex(Chrom[i]/16)<< DecToHex(Chrom[i]%16);
	}
	std::string tmp = ss.str();
	FFchrom=tmp.c_str();
	ss.str(std::string());
	ss << "INSERT INTO population (id,chrom) VALUES('" << id << "','"<<FFchrom<<"');";
	tmp = ss.str();
	sql=tmp.c_str();
	if (sqlite3_exec(db, sql,0,0,&err))
	{
		std::cout<<"Ошибка SQL: "<< err<<'\n';
		sqlite3_free(err);
	}

}
void Population::PopGen(int i)
{
	int id = 100;
	while(i>0)
	{
		ChromGen();
		ChromWrite(id);
		id++;
		i--;
	}
}
Population::Population(int PopSize,const char* PlayerNick)
{
	Population::PopSize=PopSize;
	std::stringstream ss;
	ss << PlayerNick << ".db";
	const std::string tmp = ss.str();
	PlayerDB=tmp.c_str();
	if( sqlite3_open(PlayerDB, &db) )
		{std::cout<< "Ошибка открытия/создания БД: "<< sqlite3_errmsg(db)<<'\n';}
	else if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS population (id INTEGER PRIMARY KEY, chrom CHAR, fitness INTEGER);",0,0,&err))
		{
			std::cout<<"Ошибка SQL: "<< err<<'\n';
			sqlite3_free(err);
		}
	PopGen(PopSize);
}
void Population::WriteFitness(int id,int fitness)
{
	std::stringstream ss;
	ss <<"UPDATE population SET fitness='"<< fitness<<"' WHERE id='"<<id<<"';";
	const std::string tmp = ss.str();
	const char* sql=tmp.c_str();
	if (sqlite3_exec(db,sql,0,0,&err))
	{
	std::cout<<"Ошибка SQL: "<< err<<'\n';
	sqlite3_free(err);
	}
}

byte* Population::GetChrom(int id)
{
	std::stringstream ss;
	ss <<"SELECT chrom FROM population WHERE id='"<< id <<"';";
	std::string tmp = ss.str();
	const char* sql=tmp.c_str();
    if (sqlite3_exec(db,sql,callback,HexChrom,&err))
	{
	std::cout<<"Ошибка SQL: "<< err<<'\n';
	sqlite3_free(err);
	}
	ss.str(std::string());
    HexToDec(HexChrom);
	return(Chrom);
}
Population::~Population()
{
	sqlite3_close(db);
}
