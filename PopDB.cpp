#include "Population.h"
#include "database.h"

ptrbyte DNAGen()
{
    ptrbyte buf = new byte[_DNASIZE];
    for (unsigned int i=0;i<_DNASIZE;i++)
        buf[i]=std::rand()%256;
    return buf;
}

int main()
{
    srand(time(0));
    //////////////////////////
    //ТЕСТОВЫЙ МОДУЛЬ////
    /////////////////////////
    Database* pDB = new Database;
//    pDB->AddPlayer(2,"It is a Test Nick Name");
//    cout<<pDB->GetNickname(1)<<endl;

    pDB->Execute("BEGIN TRANSACTION;");
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

    delete(pDB);
	return 0;
}

