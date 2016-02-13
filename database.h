#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"

class Database
{
private:
    sqlite3* db;
public:
    Database();
    ~Database();
    bool ClearTable(int PlayerID);
    bool CreateTable(int PlayerID);
    char* GetNickname(int PlayerID);
    bool AddPlayer(int PlayerID, char* Nickname);
    bool WriteFitness(int PlayerID, int OrdNumber, int Fitness);
    bool AddDNA(int PlayerID, int OrdNumber, ptrbyte pDNA);
    int GetFitness(int PlayerID, int OrdNumber);
    bool GetDNA(int PlayerID, int OrdNumber, ptrbyte Buffer);
    bool Execute(char* pSQL);
    bool GetPopulation(int PlayerID, ptrbyte Buffer);
};

#endif // DATABASE_H
