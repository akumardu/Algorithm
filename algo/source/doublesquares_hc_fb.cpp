#include<iostream>
#include<cmath>

#define MAX 46342

void double_squares()
{
	unsigned int square_array[MAX];
	for(int i = 0; i < MAX; i++)
		square_array[i] = i*i;
	unsigned short count = 0;
	std::cin>>count;
	unsigned int total = count;
	while(count--)
	{
		unsigned long number;
		std::cin>>number;
		unsigned long limit = (unsigned long)std::sqrt((double)number) + 1, number_count = 0,start_index = 0;
		while(start_index <= limit)
		{
			if(square_array[start_index] + square_array[limit] > number)
				limit--;
			else if(square_array[start_index] + square_array[limit] < number)
				start_index++;
			else
			{
				number_count++;
				start_index++;
				limit--;
			}
		}
		std::cout<<"Case #"<<total-count<<": "<<number_count<<std::endl;
	}
}