#include<iostream>


void factorial_cc()
{
	unsigned int count = 0;
	std::cin>>count;
	while(count--)
	{
		unsigned long number;
		std::cin>>number;
		unsigned long powof5 = 5;
		unsigned long numberOfZeroes = 0;
		while(number >= powof5)
		{
			numberOfZeroes += number/powof5;
			powof5 *= 5;
		}
		printf("%d\n",numberOfZeroes);
	}
}