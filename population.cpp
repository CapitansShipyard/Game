#include "population.h"
#include "database.h"

extern Database* pDB;

int myrandom(int n)
{
    int j = (int) (((double) n) * rand() / (RAND_MAX + 1.0));
    return j;
}

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
    pDB->ClearTable(playerID);
    pDB->Execute("BEGIN TRANSACTION;");

    for (unsigned int i=0; i<_POPULATION_SIZE;i++)
    {
        pDB->AddDNA(playerID,i+1,members[i]->GetDNA());
        pDB->WriteFitness(playerID,i+1,members[i]->GetFitness());
    }
    pDB->Execute("END TRANSACTION;");
}

void Population::Load()
{
    pDB->GetPopulation(playerID,this);
}

void Population::Generate()
{
    ptrbyte BufDNA = new byte[_DNASIZE];

    for (unsigned int i= 0; i<_POPULATION_SIZE;i++)
    {
        members[i]->SetFitness(0);
        GenDNA(BufDNA);
        members[i]->SetDNA(BufDNA);
    }
    delete(BufDNA);
}

Population::Population(int pID):
    playerID(pID)
{
    for (unsigned int i= 0; i<_POPULATION_SIZE;i++)
        members[i] = new Person;
}

Population::~Population()
{
    for (unsigned int i= 0; i<_POPULATION_SIZE;i++)
        delete members[i];
}

void Population::Breed(Person *p1, Person *p2, Person *p3, int mutation)
{
    //первый партнер имеет более высокий приоритет над вторым.
    //скрещивание происходит блоками по три байта
    //приоритет надо подобрать
    ptrbyte ptr1 = p1->GetDNA();
    ptrbyte ptr2 = p2->GetDNA();
    ptrbyte ptrres = new byte[_DNASIZE];
    const int priority = 60; //приоритет

    for (unsigned int i=0;i<(_DNASIZE-1);i+=3)
    {
        if ((rand()%100)<priority)
        {
            ptrres[i] = ptr1[i];
            ptrres[i+1] = ptr1[i+1];
            ptrres[i+2] = ptr1[i+2];
        }
        else
        {
            ptrres[i] = ptr2[i];
            ptrres[i+1] = ptr2[i+1];
            ptrres[i+2] = ptr2[i+2];
        }
        if ((rand()%100)<mutation)
        {
            ptrres[i] = rand()%256;
            ptrres[i+1] = rand()%256;
            ptrres[i+2] = rand()%256;
        }
    }

    p3->SetDNA(ptrres);
    delete ptrres;

}

Population* Population::Evolve()
{
    Population* res = new Population(playerID);

    srand(time(0));

    res->members[0]->SetDNA(this->members[0]->GetDNA());
    res->members[0]->SetFitness(0);

    Person* newperson = new Person;

    for (unsigned int i =1;i<_POPULATION_SIZE;i++)
    {
        Breed(members[0],members[i],newperson,10);
        res->members[i]->SetDNA(newperson->GetDNA());
        res->members[i]->SetFitness(0);
    }

    delete newperson;

    return res;
}

void Population::CopyTo(Population *pDest)
{
    for (unsigned int i= 0;i<_POPULATION_SIZE;i++)
    {
        pDest->members[i]->SetFitness(this->members[i]->GetFitness());
        pDest->members[i]->SetDNA(this->members[i]->GetDNA());
    }
}
