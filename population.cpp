#include "population.h"
#include "database.h"

extern Database* pDB;

void GenDNA(ptrbyte pBuffer) //заполняет ДНК случайными числами
{
    ptrbyte buf = new byte[_DNASIZE];
    for (unsigned int i=0;i<_DNASIZE;i++)
        buf[i]=std::rand()%256;
    memcpy(pBuffer,buf,_DNASIZE);
    delete(buf);
}

void Population::Save()
{
    pDB->ClearTable(PlayerID);
    pDB->Execute("BEGIN TRANSACTION;");

    for (unsigned int i=0; i<_POPULATION_SIZE;i++)
    {
        pDB->AddDNA(PlayerID,i+1,members[i]->GetDNA());
        pDB->WriteFitness(PlayerID,i+1,members[i]->GetFitness());
    }
    pDB->Execute("END TRANSACTION;");
}

void Population::Load()
{
    pDB->GetPopulation(PlayerID,this);
}

void Population::Generate()
{
    ptrbyte BufDNA = new byte[_DNASIZE];

    for (unsigned int i= 0; i<_POPULATION_SIZE;i++)
    {
        members[i]->SetFitness(rand()%100);
        GenDNA(BufDNA);
        members[i]->SetDNA(BufDNA);
    }
    delete(BufDNA);
}

Population::Population(int pID):
    PlayerID(pID)
{
    for (unsigned int i= 0; i<_POPULATION_SIZE;i++)
        members[i] = new Person;
}

Population::~Population()
{
    for (unsigned int i= 0; i<_POPULATION_SIZE;i++)
        delete members[i];
}
