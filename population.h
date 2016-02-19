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
    void Breed(Person* p1, Person* p2, Person *p3, int mutation);
    Population* Evolve();
    void CopyTo(Population* pDest);
    void Sort(); //сортировка по фитнесс
};

#endif // POPULATION_H
