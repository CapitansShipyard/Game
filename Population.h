#ifndef POPULATION_H_
#define POPULATION_H_
#include "common.h"

const int razm=5;

class Population {
private:
	int PopSize;
	const char* PlayerDB;
	char* err=0;
	sqlite3 *db;
    ptrbyte ChromGen();
    void ChromWrite(int id, ptrbyte Chrom);
public:
	Population(int PopSize,const char* PlayerNick);
	~Population();
	void PopGen(int PopSize);
	void WriteFitness(int id,int fitness);
	byte* GetChrom(int id);
};

#endif /* POPULATION_H_ */
