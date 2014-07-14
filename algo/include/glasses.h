
/*13 Answers
			|_|
		  |_| |_|
		|_| |_| |_|
	  |_| |_| |_| |_|
	|_| |_| |_| |_| |_|

Each cup has capacity C and once a cup gets full, it drops half extra amount to left child and half extra amount to right child

for Eg : let' first cups get 2C amount of liquid then extra amount C(2C-C) will be divided equally to left and right child cup of next level

i.e. C/2 to left child and C/2 to right child

Write a function which takes input parameter as amount of liquid poured at top (L) and height of particular cup (h) index of that cup (i) and 
it should return amount of liquid absorbed in that cup.
*/


#include<iostream>

double calculateWater(double capacity, double totalWater, int lev, int cupnumber)
{
	lev = lev + 1;
	double* arr = new double[((lev+2)*(lev+1))/2];
	for(int i = 0; i < ((lev+1)*(lev+2))/2 ; i++)
		arr[i] = 0;
	arr[0] = totalWater;
	for(int level = 0; level < (lev+1); level++)
	{
		for(int current = ((level*(level+1))/2) - level ; current < ((level*(level+1))/2) ; current++)
		{
			if(arr[current] > capacity)
			{
				int temp = current + level ;
				arr[temp] += (arr[current] - capacity)/2;
				arr[temp + 1] += (arr[current] - capacity)/2;
				arr[current] = capacity;
			}
		}
	}
	for(int i = 0; i < ((lev+1)*(lev+2))/2 ; i++)
	{
		if(arr[i] > capacity) arr[i] = capacity;
		std::cout<<arr[i]<<std::endl;
	}
	std::cout<<std::endl;
	return arr[cupnumber + (lev*(lev-1))/2];
}