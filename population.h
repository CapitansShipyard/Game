#ifndef POPULATION_H
#define POPULATION_H

#include "common.h"

class Person
{
private:
    int fitness;
    byte dna[_DNASIZE];
public:
    int GetFitness()
    {return fitness;}
    void SetFitness(int param)
    {fitness = param;}
    ptrbyte GetDNA()
    {return dna;}
    void SetDNA(ptrbyte pDNA)
    {memcpy(dna, pDNA, _DNASIZE);}
};

class Population
{
private:
    int playerID;
public:
    Person* members[_POPULATION_SIZE];
    Population(int pID);
    ~Population();
    void Load();
    void Save();
    void Generate();
    void Breed(Person* p1, Person* p2, Person *p3, Person *p4, int mutation,int mutateStrength, int selectorCross);
    //selectorCross принимает значения 1,2,4,5,6,7. Защиту от дурака не делал.
    //mutateStrength пока не реализована.
    Population* Evolve(int eliteCount, int luckersCount);
    //luckersCount не реализована. не знаю как выбрать максимально не похожую днк на днк лидера
    void CopyTo(Population* pDest);
    void Sort(); //сортировка по фитнесс
};

#endif // POPULATION_H
