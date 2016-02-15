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
    int PlayerID;
public:
    Person* members[_POPULATION_SIZE];
    Population(int pID);
    ~Population();
    void Load();
    void Save();
    void Generate();
};

#endif // POPULATION_H
