#include <iostream>
#include "Population.h"
int main()
{
	const char* Nick="Dipod";
	Population a(10,Nick);
	a.WriteFitness(101,9658);
	a.GetChrom(102);
	std::cin.get();
	std::cout<<"я могу выводить сообщения";
	return 0;
}
