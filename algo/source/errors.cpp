#include <cstdio>
#include <cstdlib>
#include <iostream>

void bus_error_example()
{
	int* it = (int*) malloc(2* sizeof(int));
	char* ct = (char*)it;
	ct++;
	it = (int*)ct;
	*it = 100;
	std::cout<<*it<<std::endl;
}
// Adding another useless command
// World