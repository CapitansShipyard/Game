#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"

class Population;

class Database
{
private:
    sqlite3* db;
public:
    Database();
    ~Database();
    bool ClearTable(int PlayerID); //очистка таблицы игрока
    bool CreateTable(int PlayerID); //создание таблицы игрока
    char* GetNickname(int PlayerID); //получить ник по ИД
    bool AddPlayer(int PlayerID, char* Nickname); //добавить игрока в таблицу сопоставления
    bool WriteFitness(int PlayerID, int OrdNumber, int Fitness); //записать значение фитнесс-функции в строке
    bool AddDNA(int PlayerID, int OrdNumber, ptrbyte pDNA); //добавить строку с ДНК
    int GetFitness(int PlayerID, int OrdNumber); //получить значение фитнесс-функции в строке
    bool GetDNA(int PlayerID, int OrdNumber, ptrbyte Buffer); //получить значение ДНК из строки
    bool Execute(const char* pSQL); //выполнить команду SQL
    bool GetPopulation(int PlayerID, Population *Pop); //получить популяцию игрока целиком, вместе с фитнесс
};

#endif // DATABASE_H
