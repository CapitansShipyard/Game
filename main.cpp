#include "database.h"
#include "population.h"

Database* pDB = new Database;

int main()
{
    srand(time(0));
    //////////////////////////
    //ТЕСТОВЫЙ МОДУЛЬ////
    /////////////////////////

    Population* p = new Population(1);
//    p->Generate();
  //  p->Save();
//    pDB->AddPlayer(2,"It is a Test Nick Name");
//    cout<<pDB->GetNickname(1)<<endl;

    p->Load();
    for (unsigned int i=0;i<_POPULATION_SIZE;i++)
    {
        cout<<p->members[i]->GetFitness()<<endl;
    }

  /*  pDB->Execute("BEGIN TRANSACTION;");
    pDB->ClearTable(1);
    for (int i = 0;i<100;i++)
    {
       ptrbyte DNA = DNAGen();
       pDB->AddDNA(1,i,DNA);
       delete(DNA);
       pDB->WriteFitness(1,i,std::rand()%256);
    }
    pDB->Execute("END TRANSACTION;");
//    ptrbyte buffer= new byte[_DNASIZE];
//    pDB->GetDNA(1,3,buffer);
//    for (unsigned int i =0;i<_DNASIZE;i++)
//        cout<<(int)buffer[i]<<"  ";
//    cout<<endl;
*/
    delete(pDB);
    delete(p);
	return 0;
}

