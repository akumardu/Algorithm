#include<iostream>
#include<string>

typedef unsigned int uint;

void longest_pallindrome()
{
	std::string inputStr;
	std::cin>>inputStr;
	uint i =0,j=1,globalMax = 0,localMax=0;
	for(uint i = 0; i < inputStr.length(); i++)
		inputStr[i] = tolower(inputStr[i]);
	while(j<inputStr.length())
	{
		if(inputStr[j] == inputStr[j-1])
		{
			localMax++;
			int localj = 1;
			while(j - localj >= 0 && j + localj < inputStr.length())
			{
				if(inputStr[j-localj] == inputStr[j+localj])
				{
					localj++;
					localMax++;
				}
				else
					break;
			}
			if(globalMax < 2*localMax)
			{
				globalMax = 2*localMax;
				i = j-localj + 1;
			}
			localMax = 0;
		}
		else if(inputStr[j-1] == inputStr[j+1])
		{
			localMax++;
			int localj = 1;
			while(j - localj -1 >=0 && j + localj + 1 < inputStr.length())
			{
				if(inputStr[j-localj -1] == inputStr[j+localj+1])
				{
					localj++;
					localMax++;
				}
				else
					break;
			}
			if(globalMax < 2*localMax + 1)
			{
				globalMax = 2 * localMax + 1;
				 i = j - localj ;
			}
			localMax = 0;
		}
		j++;
	}
	std::cout<<i<<" : "<<globalMax<<std::endl;
}