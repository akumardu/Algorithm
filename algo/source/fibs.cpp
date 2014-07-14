#include<iostream>
#include<vector>

long fibs_iterative(long n)
{
	long a = 0,b = 1,i = 0;
	while(i++ < n)
	{
		a = a + b;
		b = a - b;
	}
	return a;
}

bool is_prime(long n)
{
	long i = 1;
	while(i++<n/2)
		if( n % i == 0)
			return false;
	return true;
}

long fibs_prime_greater(long n)
{
	long a = 0, b = 1;
	while(true)
	{
		a = a + b;
		b = a - b;
		if(a > n && is_prime(a))
			return a;
	}
	return a;
}

long sum_prime_divisors(long n)
{
	long i = 1,sum = 0;
	while(i++ < n/2)
	{
		if(n % i == 0 && is_prime(i))
			sum += i;
	}
	return sum;
}

long sum_of_subsets = 0;

void combo(std::vector<int> vec1, std::vector<int> src)
{
	if(src.size() > 1)
	{
		int temp = src[0];
		src.erase(src.begin());
		vec1.push_back(temp);
		if(vec1.size() > 1)
		{
			int sum = 0;
			for(unsigned int i = 0; i < vec1.size(); i++)
				sum += vec1[i];
			for(unsigned int i = 0; i < src.size(); i++)
				if(sum == src[i])
					sum_of_subsets++;
		}
		combo(vec1,src);
		vec1.pop_back();
		combo(vec1,src);
	}
}

long subsets_of_sums()
{
	std::vector<int> vec;
	std::vector<int> assoc;
	long sum = 0;
	int temp = -1, i = 1;
	while(temp != 0)
	{
		std::cin>>temp;
		if(!temp)
			break;
		vec.push_back(temp);
	}
	combo(assoc,vec);
	return sum_of_subsets;
}

long fibs_logarithmic(long n)
{
	long a_t=1,b_t=0,d_t=1; // identity matrix 
	/*
	1 0
	0 1
	*/
	long a_y=0,b_y=1,d_y=1; // fibonacci matrix
	/*
	0 1
	1 1
	*/
	while(n)
	{
		if(n & 1)
		{
			long a = a_t * a_y + b_t * b_y;
			long b = a_t * b_y + b_t * d_y;
			long d = b_t * b_y + d_t * d_y;

			a_t = a;
			b_t = b;
			d_t = d;
		}
		
		long a = a_y * a_y + b_y * b_y;
		long b = a_y * b_y + b_y * d_y;
		long d = b_y * b_y + d_y * d_y;

		a_y = a;
		b_y = b;
		d_y = d;

		n >>= 1;
	}
	return b_t;
}