#include<iostream>
#include<string>
#include<algorithm>

#ifndef MISC_SMALL_H
#define MISC_SMALL_H

typedef unsigned int uint;

//Program to convert decimal to anybase
std::string convert_anybase(long n, int base)
{
	std::string result;
	std::string basLetter = "0123456789abcdefghijklmnopqrstuvwxyz";
	int m = 0;
	while(n)
	{
		m = n % base;
		result.push_back(basLetter[m]);
		n = n/base;
	}
	std::reverse(result.begin(),result.end());
#ifdef DEBUG
	std::cout<<"Result String: "<<result<<std::endl;
#endif
	return result;
}

//Sign of an integer
int sign_am(int n)
{
	return 1 & n>>(sizeof(int)*CHAR_BIT - 1);
}

//Absolute value of an integer
int abs_am(int n)
{
	int mask = n>>(sizeof(int)*CHAR_BIT - 1);
	int r = (n ^ mask);
	r = r - mask;
	return r;
}

//Min of two values
int min_am(int x, int y)
{
	return y + ((x-y)&(x-y)>>(sizeof(int)*CHAR_BIT - 1));
}

//Max of two values
int max_am(int x, int y)
{
	return x - ((x-y)&(x-y)>>(sizeof(int)*CHAR_BIT - 1));
}

//Power of two (zero is not power of two)
bool power_of2(int v)
{
	return !(v & (v-1)) && v;
}

//Check set bit
bool setCheckBit(int n, int pos)
{
	int x = ~(1<<pos);
	return ((n&x) == n);
}

//Add 1 to a number without using +
// a + b = ((a&b)<<1) + (a^b)
// a + b =  carry     + sum
int add_1(int x)
{
	int m = 1;
	while(x & m) // while there is carry
	{
		x = x ^ m; // calculate sum
		m = m << 1; // same as carry
	}
	x = x ^ m;
	return x;
}

//Sub 1 to a number without using -
// a + b = ((a&b)<<1) + (a^b)
// a + b =  carry     + sum
int sub_1(int x)
{
	int m = 1;
	while(!(x & m)) // while there is carry
	{
		x = x ^ m; // calculate sum
		m = m << 1; // same as carry
	}
	x = x ^ m;
	return x;
}

// Swap two values
template<typename T>
void swap(T& one, T& two)
{
	T temp = one;
	one = two;
	two = temp;
}

int powof(int x, int y)
{
	if(y == 0)
		return 1;
	int temp = powof(x,y/2);
	if(y % 2 == 0)
		return temp * temp;
	else
		return temp * temp * x;
}

void printallsubset(int* arr, int n)
{
	unsigned long c = 1<<n;
	for(unsigned long i = 0; i < c; i++)
	{
		unsigned long temp = i;
		int* elem = arr;
		std::cout<<"set : ";
		while(temp > 0)
		{
			if(temp & 1)
			std::cout<<*elem<<" ";
			temp = temp >> 1;
			
			elem++;
		}
		std::cout<<std::endl;
	}

}


void* aligned_malloc(unsigned int req, unsigned int alignment)
{
	int offset = alignment - 1 + sizeof(void*);
	void* p1 = (void *) malloc(req + offset);
	if(p1 == NULL)
		return p1;
	void **p2 = (void**)(((int)p1 + offset) & ~(alignment - 1));
	p2[-1] = p1;
	return p2;
}

void aligned_free(void* p)
{
	free(((void**)p)[-1]);
}

int** my2DAlloc(int rows, int cols)
{
	int header = rows * sizeof(int*);
	int data = rows * cols * sizeof(int);
	int** retVal = (int**)malloc(header + data);
	int* buf = (int*)(retVal + rows);
	
	for(int i = 0; i < cols; i++)
		retVal[i] = buf + i * cols;
	return retVal;
}

void next_permutation(char*arr, int n, bool lesstohigh)
{
	int j = n-2;
	for(;j >= 0; j--)
	{
		if((lesstohigh && arr[j] < arr [j+1]) || (!lesstohigh && arr[j]>arr[j+1]))
			break;
	}
	if(j < 0)
		return;
	int k = n-1;
	for(;k>j;k--)
	{
		if((lesstohigh && arr[k] > arr[j]) || (!lesstohigh && arr[k] < arr[j]))
			break;
	}
	char temp = arr[k];
	arr[k] = arr[j];
	arr[j] = temp;
	for(k = n-1; j < k; j++,k--)
	{
		char temp = arr[k];
		arr[k] = arr[j];
		arr[j] = temp;
	}
}

void permutation_with_rep(char* arr, int n)
{
	std::sort(arr,arr+n-1);
	std::cout<<arr<<std::endl;
	while(true)
	{
		int j = n-2;
		for(; j >=0 ; j--)
		{
			if(arr[j] < arr[j+1])
				break;
		}
		if(j < 0 )
			break;
		int k = n-1;
		for(;k>j;k--)
		{
			if(arr[k] > arr[j])
				break;
		}
		char temp = arr[k];
		arr[k] = arr[j];
		arr[j] = temp;
		j++;
		for(k=n-1;j<k;j++,k--)
		{
			char temp = arr[k];
			arr[k] = arr[j];
			arr[j] = temp;
		}
		std::cout<<arr<<std::endl;
	}
}

#endif





