#include "Population.h"

int main()
{
    srand(time(0));
	const char* Nick="Dipod";
	Population a(10,Nick);
	a.WriteFitness(101,9658);
    ptrbyte buffer= new byte[razm];
    a.GetChrom(102,buffer);
    for (int i =0;i<razm;i++)
        cout<<(int)buffer[i]<<"  ";
    cout<<endl;
	return 0;
}

