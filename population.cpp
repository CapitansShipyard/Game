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



void Population::Breed(Person *p1, Person *p2, Person *p3, Person *p4, int mutation, int selectorCross)
{
    //скрещивание происходит блоками по три байта
    ptrbyte ptr1 = p1->GetDNA();
    ptrbyte ptr2 = p2->GetDNA();
    ptrbyte ptrres1 = new byte[_DNASIZE];
    ptrbyte ptrres2 = new byte[_DNASIZE];
    switch (selectorCross)
    {
    case 5:
    {
        if(rand()%2 == 0)
        {
            selectorCross = 1;
        } else
        {
            selectorCross = 4;
        }
    }
    case 6:
    {
        if(rand()%2 == 0)
        {
            selectorCross = 2;
        } else
        {
            selectorCross = 4;
        }
    }
    case 7:
    {
        int flag = rand()%3;
        switch (flag)
        {
        case 0:
        {
            selectorCross = 1;
            break;
        }
        case 1:
        {
            selectorCross = 2;
            break;
        }
        case 2:
        {
            selectorCross = 4;
            break;
        }
        }
    }
    case 1:
        {
        unsigned int splitpoint=(rand()%(_DNASIZE/3-1)+1)*3; //перестраховался на случай если ДНК будет больше 32768
            for (unsigned int i=0;i<(_DNASIZE-1);i+=3)
            {
                if (splitpoint<i)
                {
                    ptrres1[i]   = ptr1[i];
                    ptrres1[i+1] = ptr1[i+1];
                    ptrres1[i+2] = ptr1[i+2];
                    ptrres2[i]   = ptr2[i];
                    ptrres2[i+1] = ptr2[i+1];
                    ptrres2[i+2] = ptr2[i+2];
                }
                else
                {
                    ptrres1[i]   = ptr2[i];
                    ptrres1[i+1] = ptr2[i+1];
                    ptrres1[i+2] = ptr2[i+2];
                    ptrres2[i]   = ptr1[i];
                    ptrres2[i+1] = ptr1[i+1];
                    ptrres2[i+2] = ptr1[i+2];
                }
                if ((rand()%100)<mutation)
                {
                    ptrres1[i]   = rand()%256;
                    ptrres1[i+1] = rand()%256;
                    ptrres1[i+2] = rand()%256;
                    ptrres2[i]   = rand()%256;
                    ptrres2[i+1] = rand()%256;
                    ptrres2[i+2] = rand()%256;
                }
                break;
            }
        }
    case 2:
        {
            unsigned int splitpoint1=(rand()%(_DNASIZE/3-1)+1)*3;
            unsigned int splitpoint2=(rand()%(_DNASIZE/3-1)+1)*3;
            if (splitpoint1>splitpoint2)
            {
                unsigned int temp = splitpoint2;
                splitpoint2 = splitpoint1;
                splitpoint1 = temp;
            }
            for (unsigned int i=0;i<(_DNASIZE-1);i+=3)
            {
                if(i<splitpoint1 || i>splitpoint2)
                {
                    ptrres1[i]   = ptr1[i];
                    ptrres1[i+1] = ptr1[i+1];
                    ptrres1[i+2] = ptr1[i+2];
                    ptrres2[i]   = ptr2[i];
                    ptrres2[i+1] = ptr2[i+1];
                    ptrres2[i+2] = ptr2[i+2];
                }
                else
                {
                    ptrres1[i]   = ptr2[i];
                    ptrres1[i+1] = ptr2[i+1];
                    ptrres1[i+2] = ptr2[i+2];
                    ptrres2[i]   = ptr1[i];
                    ptrres2[i+1] = ptr1[i+1];
                    ptrres2[i+2] = ptr1[i+2];
                }
                if ((rand()%100)<mutation)
                {
                    ptrres1[i]   = rand()%256;
                    ptrres1[i+1] = rand()%256;
                    ptrres1[i+2] = rand()%256;
                    ptrres2[i]   = rand()%256;
                    ptrres2[i+1] = rand()%256;
                    ptrres2[i+2] = rand()%256;
                }
            }
            break;
        }
    case 4:
    {
        for (unsigned int i=0;i<(_DNASIZE-1);i+=3)
        {
            if ((rand()%100)<50)
            {
                ptrres1[i]   = ptr1[i];
                ptrres1[i+1] = ptr1[i+1];
                ptrres1[i+2] = ptr1[i+2];
                ptrres2[i]   = ptr2[i];
                ptrres2[i+1] = ptr2[i+1];
                ptrres2[i+2] = ptr2[i+2];
            }
            else
            {
                ptrres1[i]   = ptr2[i];
                ptrres1[i+1] = ptr2[i+1];
                ptrres1[i+2] = ptr2[i+2];
                ptrres2[i]   = ptr1[i];
                ptrres2[i+1] = ptr1[i+1];
                ptrres2[i+2] = ptr1[i+2];
            }
            if ((rand()%100)<mutation)
            {
                ptrres1[i]   = rand()%256;
                ptrres1[i+1] = rand()%256;
                ptrres1[i+2] = rand()%256;
                ptrres2[i]   = rand()%256;
                ptrres2[i+1] = rand()%256;
                ptrres2[i+2] = rand()%256;
            }
        }
        break;
    }
    }
    p3->SetDNA(ptrres1);
    p4->SetDNA(ptrres2);

    delete ptrres1;
    delete ptrres2;
}

Population* Population::Evolve()
{
    Population* res = new Population(playerID);

    srand(time(0));

    res->members[0]->SetDNA(this->members[0]->GetDNA());
    res->members[0]->SetFitness(0);

    Person* newperson1 = new Person;
    Person* newperson2 = new Person;

    for (unsigned int i =1;i<_POPULATION_SIZE;i++)
    {
        Breed(members[0],members[i],newperson1, newperson2, 10, 7);
        res->members[i]->SetDNA(newperson1->GetDNA());
        res->members[i]->SetFitness(0);
    }

    delete newperson1;
    delete newperson2;

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

void Population::Sort()
{
    for (int i=_POPULATION_SIZE-2; i>=0;i--)
        for (int j = _POPULATION_SIZE-2;j>=i;j--)
            if (members[j]->GetFitness()<members[j+1]->GetFitness())
            {
                Person* temp = members[j];
                members[j] = members[j+1];
                members[j+1] = temp;
            }
}
