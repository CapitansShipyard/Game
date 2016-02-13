#ifndef POPULATION_H_
#define POPULATION_H_
#include "common.h"

const int razm=8; //должен быть кратным 4! (требование преобразования Base64)

class Population {
private:
	int PopSize;
	sqlite3 *db;
    ptrbyte ChromGen();
    void ChromWrite(int id, ptrbyte Chrom);
    void ClearDB();
public:
    Population(int pSize,const char* PlayerNick);
	~Population();
    void PopGen();
	void WriteFitness(int id,int fitness);
    void GetChrom(int id, ptrbyte pBuf);
};

#endif /* POPULATION_H_ */
