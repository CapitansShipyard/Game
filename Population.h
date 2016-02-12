#ifndef POPULATION_H_
#define POPULATION_H_
typedef struct sqlite3 sqlite3;
const int razm=5;
typedef unsigned char byte;
class Population {
private:
	int PopSize;
	const char* PlayerDB;
	char* err=0;
	sqlite3 *db;
	byte Chrom[razm];
	void ChromGen();
	void ChromWrite(int id);
	char DecToHex(byte a);
	void HexToDec(char* HexChrom);
public:
	Population(int PopSize,const char* PlayerNick);
	~Population();
	void PopGen(int PopSize);
	void WriteFitness(int id,int fitness);
	byte* GetChrom(int id);
};

#endif /* POPULATION_H_ */
