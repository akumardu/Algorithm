#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<bitset>
#include<set>
#include<math.h>
#include "graph.h"
#include<functional>

using namespace std;

namespace euler
{
	void program_1()
	{
		int result = 0;
		for(int i = 2; i <1000; i++)
		{
			if((i % 3 == 0 )|| (i % 5 == 0))
				result += i;
		}
		std::cout<<result<<std::endl;
	}

	void program_2()
	{
		long fib = 0,result = 0, a = 1, b = 0;
		while(fib < 4000000)
		{
			fib = a + b;
			if(fib %2 == 0)
				result += fib;
			b = a;
			a = fib;
		}
		std::cout<<result<<std::endl;
	}
	void find_primes(long* primes, long *leng)
	{
		primes[0] = 2;
		primes[1] = 3;
		long len = 2;
		bool isPrime = true;
		for(long i = 5 ; i < 2050000; i++)
		{
			isPrime = true;
			for( int j = 0; j < len; j++)
			{
				if(i % primes[j] == 0)
				{
					isPrime = false;
					break;
				}
			}
			if(isPrime)
			{
				primes[len] = i;
				len++;
				if(len >= *leng)
				{
					std::cout<<"i : " << i<<std::endl;
					return;
				}
			}
		}
		std::cout<<"len : "<<len<<std::endl;
		len--;
		*leng = len;
	}
	void program_3()
	{
		long long num = 600851475143;
		long* primes = new long[400];
		long leng = 400;
		find_primes(primes, &leng);
		std::cout<<"Largest Prime found: "<<primes[leng - 1]<<std::endl;
		long long i = 0, result = 0;
		for(; i < leng; i++)
		{
			if( num % primes[i] == 0)
			{
				result = i;
				break;
			}
		}
		std::cout<<result;
	}
	bool is_Prime(long long prime)
	{
		if(prime == 2 || prime == 3) return true;
		for( int i = 2; i <= prime / 2; i++)
		{
			if( prime % i == 0)
				return false;
		}
		return true;
	}
	void program_3_another()
	{
		long long num = 600851475143;
		
		for( long long i = 2; i <= num ; i++)
		{
			if(num < i)
			{
				std::cout<<"WTF"<<std::endl;
				return;
			}
			if(num % i == 0)
			{
				num = num / i;
				if(is_Prime(i))
				{
					std::cout<<i<<std::endl;
					//return;
				}
			}
		}
		std::cout<<"End"<<std::endl;
	}

	bool is_Pallindrome(long long x)
	{
		long long comp = x;
		long long y = 0;
		while(x>0)
		{
			y = y*10 + x%10;
			x = x/10;
		}
		return comp == y;
	}
	
	void program_4()
	{
		long max = 0;
		for(int i = 999; i > 100; i--)
		{
			for(int j = 999; j > 100; j--)
			{
				if(is_Pallindrome(i*j))
				{
					if(max < (i* j))
						max = i*j;
					//return;
				}
			}
		}
		std::cout<<max<<std::endl;
	}

	void program_5()
	{
		long num = 20;
		long result = 1;
		for(int i = 2; i <= num; i++)
		{
			if(is_Prime(i))
			{
				int temp = i;
				while(temp < num)
					temp *= i;
				temp = temp/i;
				result *= temp;
			}
		}
		std::cout<<result<<std::endl;
	}
	void program_6()
	{
		int num = 100;
		long long result1 = 0, result2 = 0;
		for(long long i = 1; i <= num; i++)
		{
			result1 += i*i;
			result2 += i;
		}
		std::cout<<result2*result2 - result1<<std::endl;
	}

	void program_7()
	{
		long* primes = new long[11001];
		long leng = 11000;
		find_primes(primes,&leng);
		std::cout<<primes[10000]<<std::endl;
	}

	void program_8()
	{
		string input;
		std::cin>>input;
		int result = (input[0] - '0')*(input[1] - '0')*(input[2] - '0')*(input[3] - '0')*(input[4] - '0');
		int max = result;
		for(unsigned int i = 5; i < input.length(); i++)
		{
			if(input[i - 5] != '0')
				result = result / (input[i-5] - '0');
			else
			{
				result = (input[i - 1] - '0')*(input[i - 2] - '0')*(input[i - 3] - '0')*(input[i - 4] - '0');
			}
			result = result * (input[i] - '0');
			if(max < result)
				max = result;
		}
		std::cout<<max<<std::endl;
	}

	void program_9()
	{
		int z=1;
		for(int y = 1; y < 1000; y++)
		{
			for(int x = 1; x < 1000; x++)
			{
				z = 1000 - x - y;
				if(z <= x || z <= y)
					continue;
				if(z*z == (x*x + y*y))
				{
					std::cout<<x*y*z<<std::endl;
					return;
				}
			}
		}
	}

	void program_10()
	{
		long* primes = new long[300000];
		long leng = 300000;
		find_primes(primes,&leng);
		long long result = 0;
		for(int i = 0 ; primes[i] < 2000000; i++)
			result += primes[i];
		std::cout<<result<<std::endl;
	}

	void program_11()
	{
		int** arr = new int*[20];
		for(int i = 0 ; i < 20; i++)
			arr[i] = new int[20];
		for(int i = 0; i < 20 ; i++)
			for(int j = 0; j < 20 ; j++)
				std::cin>>arr[i][j];
		long max = 0;
		for(int i = 0; i < 20; i++)
		{
			for(int j = 0; j < 20; j++)
			{
				long down = 1;
				if((20 - i) >= 4)
				{
					for(int k = 0; k < 4; k++)
						down = down * arr[i+k][j];
				}
				if(max < down)
					max = down;
				down = 1;
				if((20 - j) >= 4)
				{
					for(int k = 0; k < 4; k++)
						down = down * arr[i][j+k];
				}
				if(max < down)
					max = down;
				down = 1;
				if(((20 - j) >= 4) && ((20-i) >= 4))
				{
					for(int k = 0; k < 4; k++)
						down = down * arr[i+k][j+k];
				}
				if(max < down)
					max = down;
				down = 1;
				if((j >=3) && (20 - i)>=4)
				{
					for(int k = 0; k < 4; k++)
						down = down * arr[i+k][j-k];
				}
				if(max < down)
					max = down;
			}
		}
		std::cout<<max<<std::endl;

	}

	void program_12()
	{
		unsigned long long num = 2;
		while(true)
		{
			unsigned long long tri = (num*(num+1))/2;
			int divisors = 1;
			unsigned long long temptri = tri;
			for(unsigned long long i = 2; i <= temptri/2 + 1; i++)
			{
				if(tri%i == 0)
				{
					int temp = 0;
					while(tri%i == 0)
					{
						tri = tri/i;
						temp++;
					}
					divisors = divisors * (temp+1);
					if(tri == 1)
						break;
				}
			}
			if(divisors>500)
			{
				std::cout<<num<<std::endl;
				return;
			}
			num++;
		}
	}

	void program_14()
	{
		int* chain = new int[1000000];
		std::memset(chain,0,1000000*sizeof(int));
		chain[1] = 1;
		for(int i = 2; i < 1000000; i++)
		{
			if((i & (i - 1)) == 0)
			{
				chain[i] = chain[i/2] + 1;
				continue;
			}
			long temp = 0, tempi = i;
			while(chain[tempi] == 0)
			{
				if(tempi%2 == 0)
					tempi = tempi/2;
				else
					tempi = 3*tempi + 1;
				temp++;
				while(tempi > 1000000)
				{
					if(tempi%2 == 0)
						tempi = tempi/2;
					else
						tempi = 3*tempi + 1;
					temp++;
				}
			}

			temp = temp + chain[tempi];
			chain[i] = temp;
		}
		int max = 0, num = 0;
		for(int i = 2; i < 1000000; i++)
			if(max < chain[i])
			{
				max = chain[i];
				num = i;
			}
		std::cout<<num<<std::endl;
	}

	void program_16()
	{
		std::vector<int> vect;
		vect.push_back(2);
		for(int i = 1; i < 1000; i++)
		{
			int carry = 0,temp = 0;
			for(unsigned int j = 0; j < vect.size(); j++)
			{
				temp = vect[j];
				vect[j] = (vect[j] * 2 + carry) % 10;
				carry = (temp * 2 + carry) / 10;
			}
			if(carry)
				vect.push_back(carry);
		}
		int result = 0;
		for(unsigned int i = 0; i < vect.size(); i++)
			result += vect[i];
		std::cout<<result<<std::endl;
	}

	void program_18()
	{
		int** arr = new int*[100];
		for(int i = 0; i < 100; i++)
			arr[i] = new int[100];
		for(int i = 0;i < 100; i++)
		{
			int j = 0;
			for(; j <= i; j++)
			{
				std::cin>>arr[i][j];
			}
		}
		for(int i = 98;i >= 0; i--)
		{
			int j = 0;
			for(; j <= i; j++)
			{
				if((arr[i][j] + arr[i+1][j]) < (arr[i][j] + arr[i+1][j+1]))
				{
					arr[i][j] = arr[i][j] + arr[i+1][j+1];
				}
				else
					arr[i][j] = arr[i][j] + arr[i+1][j];
			}
		}
		std::cout<<arr[0][0]<<std::endl;
	}

	void program_21()
	{
		int* arr = new int[10000];
		long long sum = 0;
		arr[0] = 1;
		arr[1] = 1;
		memset(arr,0,10000*sizeof(int));
		for(int i = 4; i < 10000; i++)
		{
			int sum1 = 0;
			for(int j = 1; j <= i/2; j++)
			{
				if(i%j == 0)
					sum1 += j;
			}
			int sum2 = 0;
			for(int j = 1; j <= sum1/2; j++)
			{
				if(sum1%j == 0)
					sum2 += j;
			}
			if(sum1 != i && sum2 == i)
			{
				sum += sum1;
				sum += sum2;
			}
		}
		std::cout<<sum/2<<std::endl;
	}

	void program_22()
	{
		std::vector<std::string> list;
		std::string temp;
		for(int i = 0; i < 5163; i++)
		{
			std::cin>>temp;
			list.push_back(temp);
		}
		std::sort(list.begin(),list.end());
		unsigned long long sum = 0;
		for(unsigned int i = 0; i < list.size(); i++)
		{
			long long unsigned tempsum = 0;
			for(unsigned int j = 0; j < list[i].size(); j++)
				tempsum = tempsum + list[i][j] - 'A' + 1;
			tempsum = tempsum * (i+1);
			sum += tempsum;
		}
		std::cout<<sum<<std::endl;
	}

	void program_24()
	{
		char arr[] = {0,1,2,3,4,5,6,7,8,9};
		int n = 10;
		int counter = 1;
		while(counter < 1000000)
		{
			counter++;
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
		}
		for(int i = 0; i < n; i++)
			std::cout<<(int)arr[i];
		std::cout<<std::endl;
	}

	//if Sum of divisors greater than number itself
	bool is_abundant(int n)
	{
		int sum = 1;
		for(int j = 2; j <= std::sqrt((double)n); j++)
		{
			if(n%j == 0)
			{
				sum += j;
				if(n/j != j)
				sum += n/j;
			}
		}
		if(sum > n)
			return true;
		else
			return false;
	}

	void program_23()
	{
		const int max = 28123;
		std::vector<long> abundant_nums;
		for(int i = 12; i <= max; i++)
		{
			if(is_abundant(i))
				abundant_nums.push_back(i);
		}
		std::cout<<abundant_nums.size()<<std::endl;
		long net_sum = (max*(max+1))/2;
		std::cout<<net_sum<<std::endl;
		std::bitset<max> bits;
		bits.reset();
		for(unsigned int i = 0; i < abundant_nums.size(); i++)
		{
			if(abundant_nums[i] * 2 <= max)
				bits.set(abundant_nums[i]*2-1,true);
		}
		for(unsigned int i = 0; i < abundant_nums.size(); i++)
		{
			for(unsigned int j = i+1; j < abundant_nums.size(); j++)
			{
				if(abundant_nums[i] + abundant_nums[j] <= max)
					bits.set(abundant_nums[i] + abundant_nums[j] - 1,true);
			}
		}
		
		
		long sum = 0;
		for(unsigned int i = 0; i < max; i++)
		{
			if(!bits.test(i))
				sum = sum + i + 1;
			
		}
		std::cout<<sum<<std::endl;
		std::cout<<net_sum - sum;
	}

	class bignumber
	{
		
	public:
		void print()
		{
			for(int i = data.size()-1; i>=0; i--)
				std::cout<<(int)data[i];
			std::cout<<std::endl;
		}
		bignumber(int n)
		{
			while(n>0)
			{
				char x = n%10;
				data.push_back(x);
				n = n/10;
			}
		}
		void add(int n)
		{
			char x = 0;
			unsigned char i = 0;
			char carry = 0;
			while(n>0)
			{
				x = n%10;
				data[i] += x + carry;
				if(data[i]>=10)
				{
					carry = data[i]/10;
					data[i] = data[i]%10;
				}
				else
					carry = 0;
				n = n/10;
				i++;
				if(i >= (unsigned char)(data.size()-1))	
					data.push_back(0);
			}
		}
		void add(bignumber* n)
		{
			unsigned int i = 0,carry = 0;
			while(i<data.size() && i < n->data.size())
			{
				data[i] += n->data[i] + carry;
				carry = data[i]/10;
				data[i] = data[i]%10;
				i++;
			}
			while(i<data.size())
			{
				data[i] += carry;
				if(data[i] < 10)
				{
					carry = 0;
					break;
				}
				carry = data[i]/10;
				data[i] = data[i]%10;
				i++;
			}
			while(i<n->data.size())
			{
				int temp = n->data[i] + carry;
				carry = temp/10;
				data.push_back(temp%10);
				i++;
			}
			if(carry)
				data.push_back(carry);
		}
		bool ispallindrome()
		{
			for(int i = 0,k=size()-1; i < k; i++,k--)
			{
				if(data[i] != data[k])
					return false;
			}
			return true;
		}
		bignumber reverse()
		{
			bignumber b(0);
			int i = size()-1;
			int k = 0;
			while(k < size() && data[k] == 0)
				k++;
			for(; i>=k; i--)
			{
				b.data.push_back(data[i]);
			}
			return b;
		}
		long sumofdigits()
		{
			long result = 0;
			for(unsigned int i = 0; i < data.size(); i++)
				result += data[i];
			return result;
		}
		int size(){return data.size();}
	private:
		std::vector<char> data;
	};

	void program_25()
	{
		/*bignumber testa = 99823;
		bignumber testb = 9999999;
		testb.add(&testa);
		testb.print();*/

		bignumber a = 1;
		bignumber b = 2;
		int count = 2;
		while(b.size() < 1000)
		{
			bignumber temp = b;
			count++;
			b.add(&a);
			a = temp;
		}
		b.print();
		std::cout<<count+1<<std::endl;
	}

	int decimal_part(int n)
	{
		std::vector<int> data;
		int temp = 0;
		unsigned long long max_power = 10;
		int i = 0,count=0;
		while(max_power < n)
			max_power *= 10;
		while(true)
		{
			
			temp = max_power%n;
			if(!temp)
				break;
			std::vector<int>::iterator it = std::find(data.begin(), data.end(),temp);
			if(it != data.end())
			{
				while(it != data.end())
				{
					it++;
					count++;
				}
				break;
			}
			else
				data.push_back(temp);
			max_power = temp*10;
		}
		//std::cout<<(1.0/n*1.0)<<" : "<<count<<std::endl;
		
		return count;
	}
	void program_26()
	{
		int max = 0,temp= 0,maxd = 0;
		for(int i =2; i < 1000; i++)
		{
			temp = decimal_part(i);
			if(max < temp)
			{
				max = temp;
				maxd = i;
			}
		}
		std::cout<<max<<" : "<<maxd<<std::endl;
	}

	int consecutive_count(std::vector<int> &primes, int a, int b)
	{
		int n = 1;
		while(true)
		{
			std::vector<int>::iterator it = std::find(primes.begin(),primes.end(),n*n+a*n+b);
			if(it != primes.end())
				n++;
			else
				break;
		}
		return n;
	}

	void program_27()
	{
		//Find primes
		std::vector<int> primes;
		primes.push_back(2);
		primes.push_back(3);
		for(int i = 4; i < 100000; i++)
		{
			bool found = false;
			for(unsigned int j = 0; j < primes.size(); j++)
			{
				if( i % primes[j] == 0)
				{
					found = true;
					break;
				}
			}
			if(!found)
				primes.push_back(i);
		}
		std::cout<<primes.size()<<std::endl;
		int max = 0,temp = 0;
		int vala = 0, valb = 0;
		for(int a = -999; a<1000; a++)
		{
			for(int b = primes[0],j=0;b < 1000;j++,b=primes[j])
			{
				temp = consecutive_count(primes,a,b);
				if(temp > max)
				{
					max = temp;
					vala = a;
					valb = b;
				}
			}
		}

		//if(vala<0) vala = -1 *vala;
		std::cout<<vala*valb;
	}


	void program_28()
	{
		const int lim = 1001;
		int max = lim*lim;
		int**arr = new int*[lim];
		for(int i = 0; i < lim; i++)
			arr[i] = new int[lim];
		int col = lim-1,row = lim-1,start = 0,end = 0;
		while(row >start && col > end)
		{
		
			for(int i = col; i >=start; i--)
			{
				arr[start][i] = max;
				max--;
			}
			for(int i = start+1; i <= row; i++)
			{
				arr[i][end] = max;
				max--;
			}
			for(int i = end+1;i<=col;i++)
			{
				arr[row][i]= max;
				max--;
			}
			for(int i = row-1 ; i > start; i--)
			{
				arr[i][col]=max;
				max--;
			}
			col--;
			row--;
			start++;
			end++;
		}
		arr[lim/2][lim/2]=1;
		/*for(int i = 0; i < lim; i++)
		{
			for(int j = 0; j < lim; j++)
				std::cout<<arr[i][j]<<"\t";
			std::cout<<std::endl;
		}*/
		long long sum = 0;
		for(int i = 0; i < lim; i++)
			sum += arr[i][i];
		for(int i = 0; i < lim; i++)
		{
			sum += arr[i][lim-i-1];
		}
		std::cout<<sum-1<<std::endl;
	}


	void program_29()
	{
		const int limit = 101;
		bool isPower[limit];
		for(int i = 0; i < limit; i++)
			isPower[i] = false;
		int sum = 0;
		for(int i = 2;i < limit; i++)
		{
			if(is_Prime(i) || !isPower[i])
			{
				std::cout<< i << " : "<<limit-2<<std::endl;
				sum += limit-2;
				int temp = i,tempPower = limit-2;
				int count = 2;
				while(temp * i < limit)
				{
					if(!isPower[temp*i])
					{
						isPower[temp*i] = true;
						sum = sum + tempPower/count + ((count%2)?4:5);
						std::cout<< temp*i << " : "<<tempPower/count + 1<<std::endl;
					}
					temp = temp*i;
					count++;
				}
			}
		}
		std::cout<<sum<<std::endl;
	}

	void program_30()
	{
		int power[] = {0,1,32,243,1024,3125,7776,16807,32768,59049};
		long long result = 0;
		for(long long i = 10; i < 99999999; i++)
		{
			long long sum = 0;
			long long temp = i;
			while( temp != 0 )
			{
				sum = sum + power[temp%10];
				temp = temp / 10;
			}
			if(sum == i)
			{
				result += sum;
				std::cout<<sum<<std::endl;
			}
		}
		std::cout<<"Result : "<< result<<std::endl;
	}

	//coin change
	void program_31()
	{
		const int limit = 200;
		int** store = new int*[limit];
		int denom[] = {1,2,5,10,20,50,100,200};
		
		for(int i = 0;i < limit; i++)
		{
			store[i] = new int[8];
			store[i][0] = 1;
		}
		for(int i = 0; i < 8; i++)
			store[0][i] = 1;
		
		for(int i = 1;i<limit;i++)
		{
			for(int j = 1; j < 8; j++)
			{
				if(denom[j] > (i+1))
					store[i][j] = store[i][j-1];
				else
				{
					if(i > denom[j])
						store[i][j] = store[i][j-1] + store[i - denom[j]][j];
					else
						store[i][j] = store[i][j-1] + 1;
				}
			}
			
		}
		/*for(int i = 0; i < limit; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				std::cout<<store[i][j]<<"\t";
			}
			std::cout<<std::endl;
		}*/
		std::cout<<store[limit-1][7]<<std::endl;
	}


	bool is_set(int x, int pos)
	{
		return ((x&(1<<pos)) == 1);
	}
	int set_bit(int x, int pos)
	{
		return x | (1<<pos);
	}
	int unset_bit(int x, int pos)
	{
		return x & (~ (1<<pos));
	}
	void program_32()
	{
		int a = 2, b = 100;
		std::set<int> resultset;
		long sum = 0;
		for(;a<100;a++)
		{
			int bitVect = 0;
			int temp = a;
			while(temp != 0)
			{
				if((temp%10) == 0)
					break;
				if(is_set(bitVect,temp%10))
					break;
				bitVect = set_bit(bitVect,temp%10);
				temp = temp/10;
			}
			if(temp != 0)
				continue;
			
			for(b=10;b<10000;b++)
			{
				int another_bit_vect = 0;
				int tempb = b;
				while(tempb != 0)
				{
					if((tempb%10) == 0)
						break;
					if(is_set(another_bit_vect,tempb%10) || is_set(bitVect,tempb%10))
						break;
					another_bit_vect = set_bit(another_bit_vect,tempb%10);
					tempb = tempb/10;
				}
				if(tempb != 0)
					continue;
				another_bit_vect = another_bit_vect | bitVect;
				
				//Check in product
				int product = a*b;
				
				while(product != 0)
				{
					if((product%10) == 0)
						break;
					if(is_set(another_bit_vect,product%10))
						break;
					another_bit_vect = set_bit(another_bit_vect,product%10);
					product = product/10;
				}
				if(product != 0)
					continue;
				int found = false;
				for(int i = 1; i < 10; i++)
				{
					if(!is_set(another_bit_vect,i))
					{
						found = true;
						break;
					}
				}
				if(!found)
				{
					resultset.insert(a*b);
					std::cout<<a<<" * "<<b<<" = "<<a*b<<std::endl;
				}
			}
		}
		sum = 0;
		for(std::set<int>::iterator i = resultset.begin(); i != resultset.end(); i++)
			sum = sum + (*i);
		std::cout<<sum<<std::endl;
	}

	void program_33()
	{
		long num = 1,denom = 1;
		for(int i = 10; i < 100; i++)
		{
			if(i %10 == 0)
				continue;
			for(int j = 10; j < 100; j++)
			{
				if( i >= j || (j %10) == 0)
					continue;
				double val = (i*1.0)/j;
				int firsta = i%10;
				int seconda = i/10;
				int firstb = j%10;
				int secondb = j/10;
				if(firsta == firstb)
				{
					double ratio = (1.0*seconda)/secondb;
					if(ratio == val)
					{
						num = num* seconda;
						denom = denom*secondb;
						continue;
					}
				}
				else if(firsta == secondb)
				{
					double ratio = (1.0*seconda)/firstb;
					if(ratio == val)
					{
						num = num* seconda;
						denom = denom*firstb;
						continue;
					}
				}
				else if(seconda == firstb)
				{
					double ratio = (1.0*firsta)/secondb;
					if(ratio == val)
					{
						num = num* firsta;
						denom = denom*secondb;
						continue;
					}
				}
				else if(seconda == secondb)
				{
					double ratio = (1.0*firsta)/firstb;
					if(ratio == val)
					{
						num = num* firsta;
						denom = denom*firstb;
						continue;
					}
				}
			}
		}
		std::cout<<num<<" : "<<denom<<std::endl;
	}

	void program_34()
	{
		std::vector<int> fact;
		fact.push_back(1);
		int runningfact = 1;
		for(int i = 1; i < 10; i++)
		{
			runningfact *= i;
			fact.push_back(runningfact);
		}
		long long sum = 0;
		for(long long i = 10; i < 9999999; i++)
		{
			long long sumtemp = 0;
			long long temp = i;
			while(temp != 0)
			{
				sumtemp += fact[temp%10];
				temp = temp/10;
			}
			if(sumtemp == i)
			{
				sum += i;
				std::cout<<i<<std::endl;
			}
		}
		std::cout<<"result : "<<sum<<std::endl;
	}

	int rotate(int x)
	{
		int power = 10;
		while(power < x)
			power *= 10;
		power = power /10;
		int y = x % power;
		return (x%power)*10 + (x / power);
	}
	int convert_to_int(char* x, int len)
	{
		int sum = 0;
		for(int i = 0; i < len; i++)
			sum = sum*10 + x[i] - '0';
		return sum;
	}
	void rotate(char* x, int len)
	{
		char temp = x[len-1];
		for(int i = len-1; i >0; i++)
			x[i] = x[i-1];
		x[0] = temp;
	}

	void program_35()
	{
		std::vector<int> primes;
		
		bool * arr = new bool[1000000];
		std::memset(arr,1,1000000*sizeof(bool));
		arr[2] = true;
		arr[3] = true;
		for(int i = 2; i < 1000000; i++)
		{
			if(arr[i])
			{
				primes.push_back(i);
				int temp = i+i;
				while(temp < 1000000)
				{
					arr[temp] = false;
					temp = temp+i;
				}
			}
		}
		delete[] arr;
		int count = 0;
		for(unsigned int i = 0; i < primes.size(); i++)
		{
			int temp = primes[i];
			int rot = temp;
			bool found = false;
			int another_temp = temp;
			while(another_temp != 0)
			{
				if(another_temp %10 == 0)
				{
					found = true;
					break;
				}
				another_temp = another_temp / 10;
			}
			if(found)
				continue;
			//int localcount = 0;
			do
			{
				rot = rotate(rot);
				std::vector<int>::iterator it = std::find(primes.begin(),primes.end(),rot);
				if(it == primes.end())
				{
					found = true;
					break;
				}
				//localcount++;
			}while(rot != temp);
			if(!found)
			{
				std::cout<<temp<<std::endl;
				count ++;
			}
		}
		std::cout<<count<<std::endl;

	}

	bool is_Pallindrome_old(int x, int base)
	{
		char ch[32];
		int i = 0;
		while(x!=0)
		{
			ch[i] = x %base;
			i++;
			x = x/base;
		}
		int len = i;
		for( i = 0; i < len ; i++)
		{
			if(ch[i] != ch[len - 1 - i])
				return false;
		}
		return true;
	}
	bool is_Pallindrome(int x, int base)
	{
		int res = x;
		int che = 0;
		while(res > 0)
		{
			che = che*base + res%base;
			res = res/base;
		}
		return che == x;
	}

	void program_36()
	{
		long sum = 0;
		for(int i = 1; i < 1000000; i++)
		{
			if(is_Pallindrome(i,10) && is_Pallindrome(i,2))
			{
				std::cout<<i<<std::endl;
				sum += i;
			}
		}
		std::cout<<sum<<std::endl;
	}

	void find_Primes(std::vector<int>& primes)
	{
		bool * arr = new bool[1000000];
		std::memset(arr,1,1000000*sizeof(bool));
		arr[2] = true;
		arr[3] = true;
		for(int i = 2; i < 1000000; i++)
		{
			if(arr[i])
			{
				primes.push_back(i);
				int temp = i+i;
				while(temp < 1000000)
				{
					arr[temp] = false;
					temp = temp+i;
				}
			}
		}
		delete[] arr;
	}

	void program_37()
	{
		std::vector<int> primes;
		find_Primes(primes);
		int count = 0;
		long sum = 0;
		for(unsigned int i = 4; i < primes.size(); i++)
		{
			int prime = primes[i];
			while(prime != 0)
			{
				std::vector<int>::iterator it = std::find(primes.begin(),primes.end(),prime);
				if(it == primes.end())
					break;
				prime = prime/10;
			}
			if(prime != 0)
				continue;

			prime = primes[i];
			int power = 10;
			while(power < prime)
				power = power * 10;
			power = power/10;
			while(prime != 0)
			{
				std::vector<int>::iterator it = std::find(primes.begin(),primes.end(),prime);
				if(it == primes.end())
					break;
				prime = prime %power;
				power = power / 10;
			}
			if(prime != 0)
				continue;
			std::cout<<primes[i]<<std::endl;
			count++;
			sum += primes[i];
			if(count == 11)
				break;
		}
		std::cout<<"Result : "<<sum<<std::endl;

	}

	bool isPandigital(long long x)
	{
		bool arr[10];
		std::memset(arr,0,10*sizeof(bool));
		long long temp = x;
		while(temp != 0)
		{
			arr[temp%10] = true;
			if(temp%10 == 0)
				break;
			temp = temp / 10;
		}
		if(temp != 0)
			return false;
		for(int i = 1; i < 10; i++)
		{
			if(arr[i] == false)
				return false;
		}
		return true;
	}
	bool containsDuplicates(long long x)
	{
		bool arr[10];
		std::memset(arr,0,10*sizeof(bool));
		while(x!= 0)
		{
			if(arr[x%10] == true)
				return true;
			arr[x%10] = true;
			x = x/10;
		}
		return false;
	}
	void program_38()
	{
		long long max = 0;
		for(long i = 2; i < 100000; i++)
		{
			long long net = 0;
			for(long j = 1; j < 9; j++)
			{
				long prod = j*i;
				while(prod != 0)
				{
					if(prod % 10 == 0)
						break;
					prod = prod/10;
				}
				if(prod != 0)
					break;
				prod = i*j;
				long power = 10;
				while(power < prod)
				{
					power = power * 10;
				}
				net = net* power + prod;
				if(containsDuplicates(net))
					break;
				if(isPandigital(net))
				{
					std::cout<<i<<" : "<<j<<" : "<<net<<std::endl;
					if(net > max)
						max = net;
					break;
				}
			}
		}
		std::cout<<"Result : "<<max<<std::endl;
	}

	void program_39()
	{
		int limit = 1000;
		int t_max = 0,p_max = 0;
		for(int p = limit/2; p < limit + 1; p+=2)
		{
			int t = 0;
			for(int a = 2; a < p/(2+std::pow(2,0.5))+1; a++)
			{
				if((p*(2*p - a))%(2*(p-a)) == 0)
					t++;
			}
			if(t > t_max)
			{
				t_max = t;
				p_max = p;
			}
		}
		std::cout<<t_max<<" : "<<p_max<<std::endl;
	}

	void program_40()
	{
		long counter = 0;
		int multiplicand = 1;
		bool arr[] = {false,false,false,false,false};
		for(long i = 1; i < 1000010; i++)
		{
			if(i < 10)
				counter++;
			else if( i < 100)
				counter += 2;
			else if( i < 1000)
				counter += 3;
			else if(i < 10000)
				counter += 4;
			else if(i < 100000)
				counter += 5;
			else counter = 6;

			if(!arr[0] && counter >= 100)
			{
				arr[0] = true;
				if(counter == 100)
					multiplicand *= (i%10);
				else
					multiplicand *= (i/10);
			}
			else if(!arr[1] && counter >= 1000)
			{
				arr[1] = true;
				if(counter == 1000)
					multiplicand *= (i%10);
				else if(counter == 1001)
					multiplicand = multiplicand * ((i/10)%10);
				else 
					multiplicand = multiplicand * (i/100);
			}
			else if(!arr[2] && counter >= 10000)
			{
				arr[2] = true;
				if(counter == 10000)
					multiplicand *= (i%10);
				else if(counter == 10001)
					multiplicand = multiplicand * ((i/10)%10);
				else if(counter == 10002)
					multiplicand = multiplicand * ((i/100)%10);
				else
					multiplicand = multiplicand * (i/1000);
			}
			else if(!arr[3] && counter >= 100000)
			{
				arr[3] = true;
				if(counter == 100000)
					multiplicand *= (i%10);
				else if(counter == 100001)
					multiplicand = multiplicand * ((i/10)%10);
				else if(counter == 100002)
					multiplicand = multiplicand * ((i/100)%10);
				else if(counter == 100003)
					multiplicand = multiplicand * ((i/1000)%10);
				else
					multiplicand = multiplicand * (i/10000);
			}
			else if(!arr[4] && counter >= 1000000)
			{
				arr[4] = true;
				if(counter == 1000000)
					multiplicand *= (i%10);
				else if(counter == 1000001)
					multiplicand = multiplicand * ((i/10)%10);
				else if(counter == 1000002)
					multiplicand = multiplicand * ((i/100)%10);
				else if(counter == 1000003)
					multiplicand = multiplicand * ((i/1000)%10);
				else if(counter == 1000004)
					multiplicand = multiplicand * ((i/10000)%10);
				else
					multiplicand = multiplicand * (i/100000);
			}
		}
		std::cout<<multiplicand<<std::endl;
	}

	void program_41()
	{
		int arr[] = {7,6,5,4,3,2,1};
		long largest_prime = 0;
		do
		{
			long num = 0;
			for(int i = 0; i < 7; i++)
				num = num* 10 + arr[i];
			if(is_Prime(num))
			{
				largest_prime = num;
				break;
			}
		}while(std::next_permutation(arr,arr+7,std::greater<int>()));
		std::cout<<largest_prime<<std::endl;
	}

	int binary_search(int* arr, int len, int num)
	{
		int low = 0,high = len-1,mid = 0;
		while(low <= high)
		{
			mid = low + (high - low)/2;
			if(arr[mid] == num)
				return mid;
			else if(arr[mid] > num)
				high = mid-1;
			else
				low = mid + 1;
		}
		return -1;
	}

	void program_42()
	{
		int *summ = new int[20];
		for(int i = 1;i <= 20; i++)
			summ[i-1] = (i*(i+1))/2;
		const int limit = 1786;
		int count = 0;
		std::string str;
		for(int i = 0; i < limit; i++)
		{
			std::cin>>str;
			int sum = 0;
			for(unsigned int j = 0; j < str.size(); j++)
				sum += str[j] - 'A' + 1;
			if(binary_search(summ,20,sum) != -1)
				count++;
		}
		std::cout<<count<<std::endl;
	}

	void program_43()
	{
		int arr[] = {0,1,2,3,4,5,6,7,8,9};
		int div[] = {2,3,5,7,11,13,17};
		long long sum = 0;
		do
		{
			int count = 0;
			int found = false;
			for(int i = 1; i < 8;i++)
			{
				int tempsum = 0;
				for(int j = i; j < i+3;j++)
				{
					tempsum = tempsum*10 + arr[j];
				}
				if(tempsum%div[count])
				{
					found = true;
					break;
				}
				count++;
			}
			if(!found)
			{
				long long temp = 0;
				for(int i = 0; i < 10; i++)
					temp = temp*10 + arr[i];
				sum += temp;
			}
		}while(std::next_permutation(arr,arr+10,std::less<int>()));
		std::cout<<sum<<std::endl;
	}

	void program_44()
	{
		const int limit = 10000;
		int* arr = new int[limit];
		for(int i = 0;i < limit; i++)
		{
			arr[i] = ((i+1)*(3*(i+1) - 1))/2;
		}
		int min = 10000000;
		for(int i = 0; i < limit; i++)
		{
			for(int j = i+1; j<limit;j++)
			{
				if((binary_search(arr,limit,arr[i] + arr[j]) != -1) && (binary_search(arr,limit,arr[j]-arr[i]) != -1))
				{
					if(min > (arr[j] - arr[i]))
					{
						std::cout<<i<<" : "<<j<<std::endl;
						min = arr[j] - arr[i];
					}
				}
			}
		}
		std::cout<<min<<std::endl;
	}

	void program_45()
	{
		for(long i = 144; i < 100000; i++)
		{
			long long hex = i*(2*i - 1);
			long double pent = (long double)(24* hex + 1);
			pent = (std::sqrt((long double)pent) + 1)/6.0;
			int pentint = (int)pent;
			if(pentint == pent)
			{
				//long pentag = (pentint*(3*pentint - 1))/2;
				//long long t = 24*hex + 1;
				std::cout<<hex<<std::endl;
				break;
			}
		}
	}

	void find_Primes(std::set<int>& primes)
	{
		bool * arr = new bool[1000000];
		std::memset(arr,1,1000000*sizeof(bool));
		arr[2] = true;
		arr[3] = true;
		for(int i = 2; i < 1000000; i++)
		{
			if(arr[i])
			{
				primes.insert(i);
				int temp = i+i;
				while(temp < 1000000)
				{
					arr[temp] = false;
					temp = temp+i;
				}
			}
		}
		delete[] arr;
	}
	void program_46()
	{
		std::set<int> primes;
		find_Primes(primes);
		for(int i = 35; i < 10000; i+=2)
		{
			std::set<int>::iterator it = primes.find(i);
			if(it == primes.end())
			{
				//This is a composite number
				it = primes.begin();
				bool found = false;
				while(it != primes.end() && (*it) < i)
				{
					double temp = (i - (*it))/2.0;
					double squa = std::sqrt(temp);
					int squaint = (int)squa;
					if(squaint == squa)
					{
						found = true;
						break;
					}
					it++;
				}
				if(!found)
				{
					std::cout<<i<<std::endl;
					break;
				}

			}
		}
	}

	int prime_factors(std::vector<int>& primes, long x, int* store)
	{
		int prime_count = 0;
		for(unsigned long i = 0; i < primes.size() && primes[i] <= x;i++)
		{
			if(x%primes[i] == 0)
			{
				prime_count++;
				while(x%primes[i] == 0)
					x = x/primes[i];
			}
			if(x < 100000 && store[x] != 0)
			{
				prime_count = prime_count + store[x];
				return prime_count;
			}
		}
		return prime_count;
	}
	void program_47()
	{
		std::vector<int> primes;
		const int counter_limit = 4;
		const int prime_factor_limit = 4;
		int* store = new int[100000];
		std::memset(store,0,100000*sizeof(int));
		store[2] = 1;
		store[3] = 1;
		store[4] = 1;
		find_Primes(primes);
		int count = 0;
		for(long i = 5;;i++)
		{
			long temp = prime_factors(primes,i,store);
			if(i < 100000)
			store[i] = temp;
			while(temp == prime_factor_limit)
			{
				count++;
				if(count == counter_limit)
					break;
				i++;
				temp = prime_factors(primes,i,store);
				if(i < 100000)
				store[i] = temp;
			}
			if(count == counter_limit)
			{
				std::cout<<i-counter_limit+1<<std::endl;
				break;
			}
			else if(count != 0)
			{
				i--;
				count = 0;
			}
		}
	}


	long long power_last_ten(long long x, long long y)
	{
		const long long TEN = 10000000000;
		long long result = 1;
		
		while(y)
		{
			y--;
			result = (result * x)%TEN;
			
		}
		return result%TEN;
	}
	void program_48()
	{
		const long long TEN = 10000000000;
		
		long long sum = 0;
		for(int i = 1; i <= 1000; i++)
		{
			sum = ((sum%TEN) + (power_last_ten(i,i)%TEN))%TEN;
		}
		std::cout<<sum<<std::endl;
	}


	void program_49()
	{
		std::vector<int> primes;
		find_Primes(primes);
		int i = 0;
		while(primes[i] < 1000)
			i++;
		int *arr = new int[4];
		for(; primes[i]<10000; i++)
		{
			int temp = primes[i];
			for(int j = 3; j >=0; j--)
			{
				arr[j] = temp%10;
				temp = temp/10;
			}
			temp = primes[i];
			std::vector<int> perms;
			do
			{
				temp = 0;
				for(int j = 3; j >=0; j--)
				{
					temp = temp*10 + arr[j];
				}
				if(is_Prime(temp))
				{
					int pow = 10;
					while(pow < temp)
						pow = pow*10;
					if(pow == 10000)
						perms.push_back(temp);
				}
			}while(std::next_permutation(arr,arr+4));
			if(perms.size() >= 3)
			{
				std::sort(perms.begin(),perms.end());
				for(unsigned int k = 1; k < perms.size() -1; k++)
				{
					if(perms[k] - perms[k-1] == perms[k+1] - perms[k])
					{
						std::cout<<perms[k-1]<<perms[k]<<perms[k+1]<<std::endl;
						break;
					}
				}
			}
		}
	}

	void program_50()
	{
		std::vector<int> primesVec;
		std::set<int> primesSet;
		find_Primes(primesVec);
		find_Primes(primesSet);
		long long*arr = new long long[primesVec.size()];
		arr[0] = primesVec[0];
		for(unsigned int i = 1; i < primesVec.size(); i++)
		{
			arr[i] = arr[i-1] + primesVec[i];
		}
		unsigned int max = 0,maxnum = 0;
		for(unsigned int i = 0; i < primesVec.size(); i++)
		{
			for(unsigned int j = primesVec.size()-1; j > i; j--)
			{
				if((j-i) < max )
					break;
				long long temp = arr[j] - arr[i];
				if(temp > primesVec[primesVec.size()-1])
					continue;
				std::set<int>::iterator it = std::find(primesSet.begin(),primesSet.end(),temp);
				if(it != primesSet.end() && max < (j-i))
				{
					max = j-i;
					maxnum = (*it);
					std::cout<<maxnum<<" : "<<max<<std::endl;
					break;
				}
			}
		}
		
	}

	void program_51()
	{
		std::vector<int> primes;
		std::map<int,std::vector<int> > maps;
		for(int i = 0; i < 10; i++)
		{
			std::vector<int> temp;
			maps[i] = temp;
		}
		find_Primes(primes);

		unsigned int i = 0;
		while(primes[i] < 9999)
			i++;
		for(; i < primes.size(); i++)
		{
			int*bitcount = new int[10];
			std::memset(bitcount,0,10*sizeof(int));
			int temp = primes[i];
			int highest = 0,which = 0;
			while(temp)
			{
				bitcount[temp%10]++;
				if(highest < bitcount[temp%10])
				{
					highest = bitcount[temp%10];
					which = temp%10;
				}
				temp = temp/10;
			}
			if(highest >=3)
				maps[which].push_back(primes[i]);

		}

		for(int k = 0; k < 3; k++)
		{
			for(unsigned int i = 0; i < maps[k].size(); i++)
			{
				int temp = maps[k][i];
				int count = 0;
				for(int j = k+1; j < 10; j++)
				{
					int finder= 0;
					int power = 1;
					while(power < temp)
						power = power*10;
					power=power/10;
					while(temp)
					{
						if(temp/power == k)
							finder = finder*10 + j;
						else
							finder = finder*10 + temp/power;
						temp = temp - (temp/power)*power;
						power = power/10;
					}
					temp = maps[k][i];

					if((finder %2 == 0) || (finder %3 == 0) || (finder %5 == 0) || (finder%7 == 0))
						continue;
					
					std::vector<int>::iterator it = std::find(maps[j].begin(),maps[j].end(),finder);
					if(it != maps[j].end())
					{
						count++;
						if(count == 7)
						{
							std::cout<<maps[k][i]<<std::endl;
						}
					}
				}
			}
		}
	}

	long long sortnumber(long long x)
	{
		char bitcount[10];
		std::memset(bitcount,0,10*sizeof(char));
		long long result = 0;
		while(x)
		{
			bitcount[x%10]++;
			x = x/10;
		}
		for(int i = 0; i < 10; i++)
		{
			while(bitcount[i])
			{
				result = result*10 + i;
				bitcount[i]--;
			}
		}
		return result;
	}
	void program_52()
	{
		for(long long i = 11;;i++)
		{
			bool found = true;
			long long temp = sortnumber(i);
			for(long long k = 2; k < 7; k++)
			{
				if(temp != sortnumber(i*k))
				{
					found = false;
					break;
				}
			}
			if(found)
			{
				std::cout<<i<<std::endl;
				return;
			}
		}
	}


	void program_53()
	{
		const int limit = 101;
		long long*arr = new long long[limit];
		std::memset(arr,0,limit*sizeof(long long));
		arr[0] = 1;
		arr[1] = 1;
		long long counter = 0;
		for(int n = 2; n < limit; n++)
		{
			long long temp = arr[0];
			for(int r = 1; r <= n; r++)
			{
				long long temp2 = arr[r];
				arr[r] = arr[r] + temp;
				if(arr[r] > 1000000)
				{
					arr[r] = 1000001;
					counter++;
				}
				temp = temp2;
			}
		}
		//for(int i = 0; i < limit; i++)
		//	std::cout<<arr[i]<<std::endl;
		std::cout<<counter<<std::endl;
	}

	enum suit
	{
		C=0,
		H,
		S,
		D
	};
	enum card_point
	{
		TWO=2,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE
	};
	class card
	{
	public:
		suit s;
		card_point c;
	};
	class hand
	{
	public:
		card c[5];
		void sort()
		{
			for(int i = 0; i < 5; i++)
			{
				for(int j= i+1; j < 5; j++)
				{
					if(c[i].c > c[j].c)
					{
						suit temps = c[j].s;
						card_point tempcp= c[j].c;
						c[j].c = c[i].c;
						c[j].s = c[i].s;
						c[i].s = temps;
						c[i].c = tempcp;
					}
				}
			}
		}
		bool isthisbigger(hand* h)
		{

		}
		bool isroyalflush()
		{
			for(int i = 1; i < 5; i++)
			{
				if(c[0].s != c[i].s)
					return false;
			}
			if(c[0].c != TEN)
				return false;
			for(int i = 1; i < 5; i++)
			{
				if(c[i].c != (c[i-1].c + 1))
				{
					return false;
				}
			}
			return true;
		}
		bool isstraightflush()
		{
			for(int i = 1; i < 5; i++)
			{
				if(c[0].s != c[i].s)
					return false;
			}
			for(int i = 1; i < 5; i++)
			{
				if(c[i].c != (c[i-1].c + 1))
				{
					return false;
				}
			}
			return true;
		}
		bool isfourofakind()
		{
			if(c[0].c == c[1].c)
			{
				for(int i = 1; i < 4; i++)
				{
					if(c[i].c != c[0].c)
					{
						return false;
					}
				}
			}
			else if(c[1].c == c[2].c)
			{
				for(int i = 2; i < 5; i++)
				{
					if(c[i].c != c[1].c)
					{
						return false;
					}
				}
			}
			else
				return false;
			return true;
		}

	};
	void program_54()
	{
		const int limit = 1000;
		
	}


	long long reversenumber(long long x)
	{
		long long y = 0;
		while(x>0)
		{
			y = y*10 + x%10;
			x = x/10;
		}
		return y;
	}
	void program_55()
	{
		int lychrel_count = 0;
		for(int i = 10; i < 10000; i++)
		{
			int count = 0;
			bignumber temp(i);
			while(count < 50)
			{
				bignumber temp2 = temp.reverse();
				temp.add(&temp2);
				if(temp.ispallindrome())
					break;
				count++;
			}
			
			if(count == 50)
			{
				lychrel_count++;
				std::cout<<i<<std::endl;
				temp.print();
			}
		}
		std::cout<<lychrel_count<<std::endl;
	}

	class Rational
	{
	public:
		void print()
		{
			std::cout<<num<<"/"<<den<<std::endl;
		}
		void printb()
		{
			numb.print();
			std::cout<<"/";
			denb.print();
			std::cout<<"\n";
			std::cout<<"Num_Sum: "<<numb.sumofdigits()<<"\n";
			std::cout<<"Den_Sum: "<<denb.sumofdigits()<<"\n";
		}
		Rational(long long num, long long den,std::vector<int>& inprime):primes(inprime),numb(num),denb(den)
		{
			this->num = num;
			this->den = den;
		}
		void add(Rational& r)
		{

			long long newden = den * r.den;
			long long newnum = den*r.num + r.den*num;
			den = newden;
			num = newnum;
			reduce();
		}
		void addb(Rational& r)
		{
			bignumber temp(denb);
			for(int i = 1; i < r.num; i++)
			{
				temp.add(&denb);
			}
			numb.add(&temp);
		}
		void reverseb()
		{
			bignumber temp(numb);
			numb = denb;
			denb = temp;
		}
		bool isnumdigitsgreater()
		{
			long long numpow = 1, denpow = 1;
			while(numpow < num)
				numpow *= 10;
			while(denpow < den)
				denpow *= 10;
			if(numpow > denpow)
				return true;
			else return false;
		}
		void reverse()
		{
			long long temp = num;
			num = den;
			den = temp;
		}
		void removedigits()
		{
			long long pow = 1,count=0;
			while(pow < num && pow < den)
			{
				pow = pow*10;
				count++;
			}
			if(count > 15)
			{
				num = num / 10000;
				den = den / 10000;
			}

		}
	private:
		void reduce()
		{
			std::vector<int>::iterator it = std::find(primes.begin(),primes.end(),num);
			if(it != primes.end())
				return;
			it = std::find(primes.begin(),primes.end(),den);
			if(it != primes.end())
				return;
			for(unsigned int i = 0; i < primes.size() && primes[i]<num && primes[i]<den; i++)
			{
				while(num%primes[i] == 0 && den%primes[i] == 0)
				{
					num = num/i;
					den = den/i;
				}
			}
		}

		long long num;
		long long den;
		bignumber numb;
		bignumber denb;
		std::vector<int>& primes;
	};
	void program_57()
	{
		std::vector<int> primes;
		find_Primes(primes);
		int count = 0;
		Rational base(3,2,primes);
		Rational one(1,1,primes);
		for(int i = 0; i < 999; i++)
		{
			base.add(one);
			base.reverse();
			base.add(one);
			if(base.isnumdigitsgreater())
			{
				std::cout<<i<<" : ";
				base.print();
				count++;
			}
			base.removedigits();
		}
		std::cout<<count<<std::endl;
	}
	

	unsigned long long power(unsigned long long x, unsigned long long y)
	{
		unsigned long long result = 1;
		while(y)
		{
			if(y&1)
			{
				y--;
				result = result * x;
			}
			x = x*x;
			y = y/2;
		}
		return result;
	}
	
	void program_58()
	{
		std::set<int> primes;
		find_Primes(primes);
		long netcount = 1;
		long primecount = 0;
		std::set<int>::iterator it = primes.end();
		it--;
		std::set<int>::iterator comp;
		//for(int i = 2;  ;i+=2)
		//{
		//	long long diag = i*i+1;
		//	if(diag < (*it))
		//	{
		//		if(primes.find(diag) !=  primes.end())
		//			primecount++;
		//	}
		//	else
		//	{
		//		std::set<int>::iterator comp = primes.begin();
		//		bool found = true;
		//		while((*comp) < (i*2))
		//		{
		//			if(diag%(*comp) == 0)
		//			{
		//				found = false;
		//				break;
		//			}
		//			comp++;
		//		}
		//		if(found)
		//			primecount++;
		//	}
		//	
		//	diag = i*i + 1 -i;
		//	if(diag < (*it))
		//	{
		//		if(primes.find(diag) !=  primes.end())
		//			primecount++;
		//	}
		//	else
		//	{
		//		std::set<int>::iterator comp = primes.begin();
		//		bool found = true;
		//		while((*comp) < (i*2))
		//		{
		//			if(diag%(*comp) == 0)
		//			{
		//				found = false;
		//				break;
		//			}
		//			comp++;
		//		}
		//		if(found)
		//			primecount++;
		//	}
		//	
		//	diag = i*i + 1 + i;
		//	if(diag < (*it))
		//	{
		//		if(primes.find(diag) !=  primes.end())
		//			primecount++;
		//	}
		//	else
		//	{
		//		std::set<int>::iterator comp = primes.begin();
		//		bool found = true;
		//		while((*comp) < (i*2))
		//		{
		//			if(diag%(*comp) == 0)
		//			{
		//				found = false;
		//				break;
		//			}
		//			comp++;
		//		}
		//		if(found)
		//			primecount++;
		//	}
		//	
		//	netcount = netcount + 4;
		//	//std::cout<<i<<": "<<(primecount*100.0)/netcount<<std::endl;
		//	if((primecount*100.0)/netcount < 10.0)
		//	{
		//		std::cout<<i<<": "<<(primecount*100.0)/netcount<<std::endl;
		//		break;
		//	}
		//}

		for(int i = 2; i < 1000; i++)
		{
			long long diag = i*i+1+i;
			bool found1 = false;
			{
				if(primes.find((int)diag) !=  primes.end())
					found1 = true;
			}
			bool found = true;
			{
				std::set<int>::iterator comp = primes.begin();
				
				while((*comp) < (i*2))
				{
					if(diag%(*comp) == 0)
					{
						found = false;
						break;
					}
					comp++;
				}
			}
			if(found1 != found)
			{
				std::cout<<diag<<std::endl;
			}
		}
	}

	void program_59()
	{
		std::map<int,int> maps[3];
		unsigned int ch;
		for(int i = 0; i < 400; i++)
		{
			std::cin>>ch;
			maps[0][ch]++;
			std::cin>>ch;
			maps[1][ch]++;
			std::cin>>ch;
			maps[2][ch]++;
		}
		for(int i = 0; i < 128; i++)
		{
			if(maps[0][i])
				std::cout<<i<<":"<<maps[0][i]<<std::endl;
		}
		for(int i = 0; i < 128; i++)
		{
			if(maps[1][i])
				std::cout<<i<<":"<<maps[1][i]<<std::endl;
		}
		for(int i = 0; i < 128; i++)
		{
			if(maps[2][i])
				std::cout<<i<<":"<<maps[2][i]<<std::endl;
		}
	}

	bool islargeprime(long long x,std::set<int>& primes)
	{
		std::set<int>::iterator itend = primes.end();
		itend--;
		if(x > (*itend))
		{
			std::set<int>::iterator comp = primes.begin();
			int sqrt = (int)std::pow((double)x,0.5);
			while(comp != primes.end() && (*comp) <= (sqrt+2))
			{
				if(x%(*comp) == 0)
				{
					return false;
				}
				comp++;
			}
		}
		else
		{
			std::set<int>::iterator it = primes.find((int)x);
			if(it == primes.end())
				return false;
		}
		return true;
	}

	bool iscompatible(long long x, long long y, std::set<int>& primes)
	{
		long long powx = 1;
		while(powx < x)
			powx *= 10;
		long long val = y*powx + x;
		if(val%3 ==0 || val%7 == 0)
			return false;
		if(!islargeprime(val,primes))
			return false;
		powx = 1;
		while(powx < y)
			powx *= 10;
		val = x*powx + y;
		if(val%3 ==0 || val%7 == 0)
			return false;
		if(!islargeprime(val,primes))
			return false;
		return true;
	}

	void program_60()
	{
		std::set<int> primes;
		std::vector<int> primesVect;
		find_Primes(primesVect);
		find_Primes(primes);
		const int max = 1100;
		std::map<int,std::vector<int> > maps;
		for(int i = 1; i < max; i++)
		{
			if(i == 2)
				continue;
			for(int j = i+1; j < max; j++)
			{
				if(iscompatible(primesVect[i],primesVect[j],primes))
					maps[i].push_back(j);
			}
		}


		for(int i = 0; i < max; i++)
		{
			int sz = maps[i].size();
			for(int j = 0; j < sz; j++)
			{
				int sec = maps[i][j];
				for(unsigned int k = 0; k < maps[sec].size(); k++)
				{
					int thir = maps[sec][k];
					std::vector<int>::iterator it = std::find(maps[i].begin(),maps[i].end(),thir);
					if(it == maps[i].end())
						continue;
					for(unsigned int l = 0; l < maps[thir].size(); l++)
					{
						int four = maps[thir][l];
						it = std::find(maps[i].begin(),maps[i].end(),four);
						if(it == maps[i].end())
							continue;
						it = std::find(maps[sec].begin(),maps[sec].end(),four);
						if(it == maps[sec].end())
							continue;
						for(unsigned int a = 0; a < maps[four].size(); a++)
						{
							int five = maps[four][a];
							it = std::find(maps[i].begin(),maps[i].end(),five);
							if(it == maps[i].end())
								continue;
							it = std::find(maps[sec].begin(),maps[sec].end(),five);
							if(it == maps[sec].end())
								continue;
							it = std::find(maps[thir].begin(),maps[thir].end(),five);
							if(it == maps[thir].end())
								continue;
							long long sum = 0;
							sum = primesVect[i] + primesVect[sec] + primesVect[thir] + primesVect[four] + primesVect[five];
							std::cout<<i<<" : "<<sec<<" : "<<thir<<" : "<<four<<" : "<<five<<std::endl;
							std::cout<<sum<<std::endl;
							return;
						}
					}
					
				}
			}
		}
		std::cout<<"Not Found"<<std::endl;
	}

	void fill(std::set<int>& nums,int(*func)(int i), int low, int high)
	{
		int i = 1;
		while(func(i) < low) i++;
		while(func(i) < high)
		{
			nums.insert(func(i));
			i++;
		}
	}
	int triangle(int i)
	{
		return (i*(i+1))/2;
	}
	int square(int i)
	{
		return i*i;
	}
	int pentagonal(int i)
	{
		return (i*(3*i-1))/2;
	}
	int hexagonal(int i)
	{
		return i*(2*i-1);
	}
	int heptagonal(int i)
	{
		return (i*(5*i-3))/2;
	}
	int octagonal(int i)
	{
		return i*(3*i-2);
	}
	bool find_next(std::set<int>* nums, int index,std::vector<int>& soln,char indexused)
	{
		if(soln.size() == 0)
		{
			indexused = set_bit(indexused,0);
			for(std::set<int>::iterator i = nums[0].begin(); i != nums[0].end(); i++)
			{
				int temp = *i;
				soln.push_back((*i));
				int k = 1;
				while(k < 6 && find_next(nums,k,soln,indexused))
					k++;
				if(k == 6)
					return true;
				soln.clear();
			}
		}
		else
		{
			for(std::set<int>::iterator i = nums[index].begin(); i != nums[index].end(); i++)
			{
				int temp = *i;
				std::vector<int>::iterator it = std::find(soln.begin(),soln.end(),temp);
				if(it != soln.end() && soln.size() == 6)
				{
					return true;
				}
				else if(it != soln.end())
					continue;
				else
				{
					int prev = soln[soln.size() - 1];
					prev = prev%100;
					temp = temp/100;
					if(prev != temp)
						continue;
					else
					{
						if( soln.size() == 5)
						{
							int first = soln[0];
							first = first/100;
							int last = (*i);
							last = last %100;
							if(first != last)
								continue;
							else
								soln.push_back((*i));
							return true;
						}
						soln.push_back((*i));
						indexused = set_bit(indexused,index);
						//find first unused index
						int k = 0;
						for(k = 0; k < 6; k++)
						{
							if(!is_set(indexused,k))
							{
								if(find_next(nums,k,soln,indexused))
									return true;
							}
						}
						soln.pop_back();
					}
				}
			}
		}
		return false;
	}
	void program_61()
	{
		std::set<int> num_sets[6];
		int(*func[])(int i) = {triangle,square,pentagonal,hexagonal,heptagonal,octagonal};
		
		for(int i = 0; i < 6; i++)
		{
			fill(num_sets[i],func[i],1000,10000);
		}

		std::vector<int> soln;
		char indexused = 0;
		find_next(num_sets,0,soln,indexused);
		int sum = 0;
		for(unsigned int i = 0; i < soln.size(); i++)
		{
			sum += soln[i];
			std::cout<<soln[i]<<std::endl;
		}
		std::cout<<sum<<std::endl;
	}

	void program_62()
	{
		std::map<unsigned long long,std::set<unsigned long long> > cubes;
		for(unsigned long long i = 11; i < 6000; i++)
		{
			unsigned long long temp = i*i*i,sum = 0;
			while(temp != 0)
			{
				sum += temp%10;
				temp = temp/10;
			}
			cubes[sum].insert(i*i*i);
		}
		//std::set<long long> done;
		char* arr = new char[100];
		for(unsigned long long i = 11; i < 6000; i++)
		{
			//if(i%10 == 0)
			//	continue;
			
			unsigned long long cub = i*i*i;
			/*std::set<long long>::iterator it = done.find(cub);
			if(it != done.end())
			{
				continue;
			}
			done.insert(cub);*/
			unsigned long long power = 1,cnt = 0;
			while(power < cub)
			{
				power = power*10;
				cnt++;
			}
			
			int j = 0;
			unsigned long long sum = 0;
			while(cub >0)
			{
				arr[j] = cub%10;
				sum += cub%10;
				cub = cub/10;
				j++;
			}
			if(cub != 0)
				continue;
			std::sort(arr,arr+cnt);
			int count = 0;
			std::set<unsigned long long> dd;
			std::set<unsigned long long>::iterator itend = cubes[sum].end();
			itend--;
			unsigned long long max = *itend;
			do
			{
				if(count == 5)
					break;
				unsigned long long temp = 0;
				if(arr[cnt-1] == 0)
					continue;
				for(unsigned long long j = cnt-1; j >=0; j--)
					temp = temp*10 + arr[j];
				//if(temp > max)
				//	break;
				std::set<unsigned long long>::iterator it2 = dd.find(temp);
				if(it2 != dd.end())
					continue;
				std::set<unsigned long long>::iterator it = cubes[sum].find(temp);
				if(it != cubes[sum].end())
				{
					count++;
					dd.insert(temp);
				}
			}while(std::next_permutation(arr,arr+cnt));
			//std::cout<<i<<" : "<<count<<std::endl;
			if(count == 3)
				std::cout<<i<<std::endl;
			if(count == 5)
			{
				std::cout<<i*i*i<<std::endl;
				break;
			}
		}
	}

	void program_62_another()
	{
		std::map<unsigned long long,int> cubes;
		char* ch = new char[100];
		for(long long i = 3; ; i++)
		{
			long long cub = i*i*i;
			int j = 0;
			while(cub > 0)
			{
				ch[j] = cub%10;
				j++;
				cub = cub/10;
			}
			std::sort(ch,ch+j,std::greater<char>());
			unsigned long long temp = 0;
			for(int k = 0; k < j; k++)
				temp = temp*10 + ch[k];
			cubes[temp]++;
			if(cubes[temp] == 5)
			{
				std::cout<<temp<<std::endl;
				//break;
			}
		}
		std::cout<<"finished"<<std::endl;
	}

	int count_digits(unsigned long long x)
	{
		int count = 0;
		while(x)
		{
			count++;
			x = x/10;
		}
		return count;
	}
	void program_63()
	{
		unsigned long long num = 8;
		int i = 2;
		long long count = 1;
		for(int i = 2 ; i < 10; i++)
		{
			count = count + (long long)(1/(1-std::log10(1.0*i)));
		}
		std::cout<<count<<std::endl;
		/*for(; i < 50; i++)
		{
			bool found = false;
			for( unsigned long long cnt = 2; cnt < 10; cnt++)
			{
				num = power(cnt,i);
				if(num < cnt)
				{
					std::cout<<"Problem : "<<num<<" : "<<cnt<<" : "<<i<<std::endl;
					found = true;
					break;
				}
				if(count_digits(num) == i)
				{
					found = true;
					break;
				}
				else if(count_digits(num) > i)
					break;
			}
			std::cout<<i<<" : "<<num<<std::endl;
			if(!found)
			{
				std::cout<<count<<std::endl;
				break;
			}
			count++;
		}
		std::cout<<"Finished:"<<count<<std::endl;*/
	}

	void program_64()
	{
		int counter = 0;
		for(int num = 2; num < 10001; num++)
		{
			int k = 1, r = (int)std::pow((double)num,0.5);
			int limit = r;
			if(r*r == num)
				continue;
			unsigned char period = 0;
			do
			{
				k = (num - r*r)/k;
				//int i = 1;
				//while(r > i*k) i++;
				//r = i*k - r ;
				r = ((limit + r)/k)*k - r;
				period++;
			}while(k!=1 || period==0);
			if(period %2 == 1)
			{
				counter++;
				std::cout<<num<<std::endl;
			}
		}
		std::cout<<"Net: "<<counter<<std::endl;
	}

	void program_65()
	{
		std::vector<int> primes;
		find_Primes(primes);
		const int limit = 100;
		std::vector<long> series;
		series.push_back(2);
		series.push_back(1);
		series.push_back(2);
		for(long i = 2; series.size() < limit; i++)
		{
			series.push_back(1);
			if(series.size() == limit)
				break;
			series.push_back(1);
			if(series.size() == limit)
				break;
			series.push_back(2*i);
			if(series.size() == limit)
				break;
		}
		Rational result(series[series.size() - 1],1,primes);
		for(long i = series.size()-2; i >= 0; i--)
		{
			result.reverseb();
			Rational temp2(series[i],1,primes);
			result.addb(temp2);		
		}

		result.printb();
	}


	long long pell(int d)
	{
		long long k = 1,y = 0,x1 = 1,x=0,p = 1;
		long double sd = std::pow(d,0.5);
		while(k != 1 || y == 0)
		{
			p = k* ( p/k + 1) - p;
			p = p - (long long)((p - sd)/k) * k;
			x = (p*x1 + d*y)/std::abs((long long)k);
			y = (p*y + x1)/std::abs((long long)k);
			k = (p*p - d)/k;
			x1 = x;
		}
		return x;
	}
	void program_66()
	{
		/*
		//This was brute force
		std::set<unsigned long long> squares;
		for(unsigned long long i = 1; i < 1000; i++)
			squares.insert(i*i);
		unsigned long long maxx = 0;
		for(unsigned long long i = 2; i <= 1000; i++)
		{
			if(squares.find(i) != squares.end())
				continue;
			bool found = false;
			for(unsigned long long it = 1;it!=0; it++)
			{
				unsigned long long x = std::pow((it*it)*i + 1,0.5);
				if( (x*x) != (it*it)*i + 1)
					continue;
				else
				{
					std::cout<<(x) << " = " << i << " * " << (it*it)<<" + 1"<<std::endl;
					found = true;
					if(maxx < (x))
					{
						maxx = (x);
					}
					break;
				}
			}
			if(!found)
			{
				std::cout<<"Incr sqr size: "<<i<<" : "<<i<<std::endl;
				break;
			}
		}
		std::cout<<std::sqrt(maxx*1.0)<<std::endl;*/

		long long maxx = 0,maxd = 0,minx = 0,mind = 0;
		for(int i = 2; i < 1001; i++)
		{
			int sqr = (int)std::pow((double)i,0.5);
			if((sqr*sqr) == i)
				continue;
			long long temp = pell(i);
			if(minx > temp)
			{
				minx = temp;
				mind = i;
			}
			if(maxx < temp)
			{
				maxx = temp;
				maxd = i;
			}
		}
		std::cout<<maxx<<" : "<<maxd<<std::endl;
		std::cout<<minx<<" : "<<mind<<std::endl;
	}

	void program_68()
	{
		const int len = 5;
		int arr[] ={1,2,3,4,5};
		int* consecu = new int[5];
		do
		{
			for(int i = 0; i < len-1; i++)
				consecu[i] = arr[i] + arr[i+1];
			consecu[len - 1] = arr[0] + arr[len-1];
			std::sort(consecu,consecu+5);
			bool found = false;
			if(consecu[0] == 3)
				continue;
			for(int i = 0; i < len-1; i++)
			{
				if(consecu[i] == consecu[i+1])
				{
					found = true;
					break;
				}
			}
			if(!found)
			{
				for(int i = 0; i < len; i++)
					std::cout<<arr[i]<<"\t";
				std::cout<<std::endl;
			}
		}while(std::next_permutation(arr,arr+5));
	}

	int gcd(int x, int y)
	{
		if(x < y)
		{
			int temp = y;
			y = x;
			x = temp;
		}
		int temp;
		while(y != 0)
		{
			temp = y;
			y = x % y;
			x = temp;
		}
		return x;
	}

	void program_69()
	{
		std::vector<int> primes;
		find_Primes(primes);
		long num = 1;
		for(unsigned int i = 0; i < primes.size() && num <= 100000; i++)
		{
			std::cout<<primes[i]<<"\t";
			num = num * primes[i];
		}
		std::cout<<std::endl<<num<<std::endl;
		
	}

	bool are_anagram(long x, long y)
	{
		//cout<<x<<":"<<y<<endl;
		char chx[32],chy[32];
		long long powerx = 1,powery=1,countx=0;
		while(powerx < x) powerx *= 10;
		while(powery < y) powery *= 10;
		if(powerx != powery) return false;
		for(int i = 0; x!= 0; i++,x=x/10,countx++)
			chx[i] = x%10;
		for(int i = 0; y!= 0; i++,y=y/10)
			chy[i] = y%10;

		std::sort(chx,chx+countx);
		std::sort(chy,chy+countx);
		for(int i = 0; i < countx; i++)
		{
			if(chx[i] != chy[i])
				return false;
		}
		return true;
	}

	void program_70()
	{
		std::vector<int> primes;
		find_Primes(primes);
		double min = 1000;
		long reqd;
		for(unsigned int i = 0; i < primes.size() && primes[i] < 10000000; i++)
		{
			for(unsigned int j = i+1; j < primes.size() && primes[j] < 10000000 && (((long)primes[i]*(long)primes[j]) < 10000000); j++)
			{
				long long totient = (primes[i]-1) * (primes[j] - 1);
				if(totient < 0)
					break;
				if(are_anagram((long)totient, (long)primes[i]*(long)primes[j]) && ((long)primes[i]*(long)primes[j]*1.0)/totient < min)
				{
					min = ((long)primes[i]*(long)primes[j]*1.0)/totient;
					reqd = (long)primes[i]*(long)primes[j];
				}
			}
		}
		std::cout<<reqd<<std::endl;
	}

	void program_71()
	{
		const int limit = 1000000;
		double closest = 0;
		long closenum = 0,closed = 0;
		for(int d = 2; d < limit; d++)
		{
			int tempd = d;
			if(tempd%7 == 0)
				continue;
			int num = (int)((tempd*3.0)/7);
			if(num < 1)
				continue;
			
			double rat = (num*1.0)/tempd;
			if(3.0/7.0 - rat < 3.0/7.0 - closest)
			{
				closest = rat;
				closenum = num;
				closed = d;
			}
		}
		std::cout<<closenum<<std::endl;
	}

	bool gcd_mod(std::vector<int>& primes,long x, long y)
	{
		if(x%y==0 || y%x == 0)
			return false;
		for(unsigned int i = 0; i < primes.size() && primes[i] < x && primes[i]< y; i++)
		{
			if(x%primes[i] == 0 && y%primes[i] == 0)
				return false;
		}
		return true;
	}
	
	void program_72()
	{
		const int limit = 1000000;
		double* phi = new double[limit];
		for(int i = 0; i < limit; i++)
		{
			phi[i] = i+1;
		}
		for(int i = 1; i < limit; i++)
		{
			if(phi[i] == i+1)
			{
				for(int k = i; k < limit; k += (i+1))
				{
					phi[k] = (phi[k] * i)/(i+1);
				}
			}
		}
		double sum = 0;
		for(int i = 1; i < limit; i++)
			sum += phi[i];
		std::cout<<(long long)sum<<std::endl;
		
	}

	void program_73()
	{
		//brute force
		std::vector<int> primes;
		find_Primes(primes);
		long counter = 0;
		for(int i = 5; i <= 12000; i++)
		{
			std::cout<<i<<std::endl;
			int numa = (int)((i*1.0)/3.0);
			int numb = (int)((i*1.0)/2.0);
			for(int j = numa; j <= numb; j++)
			{
				if(j*3 <= i || j*2 >= i)
					continue;
				if(gcd_mod(primes,i,j) == 1)
				{
					//std::cout<<j<<"/"<<i<<std::endl;
					counter++;
				}
			}
		}
		std::cout<<counter<<std::endl;
	}

	long factsum(std::vector<int>& fact, int x)
	{
		long sum = 0;
		while(x != 0)
		{
			sum = sum + fact[x%10];
			x = x/10;
		}
		return sum;
	}
	void program_74()
	{
		const int limit = 1000000;
		std::vector<int> fact;
		fact.push_back(1);
		for(int i = 1; i <10; i++)
			fact.push_back(fact[i-1]*i);
		int* arr = new int[limit*100];
		std::memset(arr,0,limit*100*sizeof(int));
		arr[0] = 0;
		arr[1] = 1;
		long count = 0;
		for(int i = 2; i < limit; i++)
		{
			long check = i;
			int countr = 1;
			while(countr < 61)
			{
				long temp = factsum(fact,check);
				if(temp == i)
				{
					arr[temp] = countr;
					break;
				}
				if(temp < limit*100 && arr[temp] != 0)
				{
					arr[i] = countr + arr[temp];
					if(arr[i] == 60)
						count++;
					break;
				}
				check = temp;
				countr++;
			}
		}
		std::cout<<count<<std::endl;
	}

	
	void program_75()
	{
		const int limit = 1500000;
		int limitm = (int)std::sqrt(limit/2.0);
		std::map<int,int> tripmap;
		for(long m = 2; m < limitm; m++)
		{
			for(long n = 1; n < m; n++)
			{
				if((m+n)%2 == 1 && gcd(m,n) == 1)
				{
					long a = m*m + n*n;
					long b = 2*m*n;
					long c = m*m - n*n;
					long sum = a + b + c;
					while(sum <= limit)
					{
						tripmap[sum]++;
						sum = sum + a + b + c;
					}
				}
			}
		}
		long counter = 0;
		for(std::map<int,int>::iterator it = tripmap.begin(); it != tripmap.end(); it++)
		{
			if(it->second == 1)
				counter++;
		}
		std::cout<<counter<<std::endl;
	}

	void program_76()
	{
		const int limit = 101;
		int** store = new int*[limit];
		for(int i = 0; i < limit; i++)
			store[i] = new int[limit];
		
		for(int i = 0; i < limit; i++)
		{
			for(int j = 0; j < limit; j++)
			{
				if(i == 0)
					store[i][j] = 1;
				else if(j == 0)
					store[i][j] = 0;
				else if(j > i)
					store[i][j] = store[i][j-1];
				else
					store[i][j] = store[i-j][j] + store[i][j-1];
			}
		}
		
		
		std::cout<<store[limit-1][limit-1]<<std::endl;
	}

	void program_77()
	{
		std::vector<int> primes;
		find_Primes(primes);
		int limit = 500;
		//while(true)
		{
			limit++;
			int num_primes = 0;
			while(primes[num_primes] < limit)
				num_primes++;
			/*if(primes[num_primes] != limit)
				num_primes--;*/

			int** store = new int*[limit];
		
			for(int i = 0;i < limit; i++)
			{
				store[i] = new int[num_primes];
				std::memset(store[i],0,num_primes*sizeof(int));
			}
			//for(int i = 0; i < num_primes; i++)
			//	store[0][i] = 1;
		
			for(int i = 2;i<limit;i++)
			{
				for(int j = 0; j < num_primes; j++)
				{
					if(j == 0)
						store[i][j] = !(i%2);
					else if(primes[j] > i)
						store[i][j] = store[i][j-1];
					else
					{
						if(i > primes[j])
							store[i][j] = store[i][j-1] + store[i - primes[j]][j];
						else
							store[i][j] = store[i][j-1] + 1;
					}
				}
				std::cout<<i<<" : "<<store[i][num_primes -1 ]<<std::endl;
				if(store[i][num_primes -1 ] > 5000)
				{
					std::cout<<"Found : "<<i<<std::endl;
					break;
				}
			}
		}
	}

	void program_78()
	{
		std::vector<long long> penta;
		penta.push_back(1);
		for(long i = 1; ; i++)
		{
			long long sum = 0;
			for(long j = 0; ; j++)
			{
				long peng = j;
				if((j&1) == 0)
					peng = j/2 +1;
				else
					peng = -1*(j/2+1);
				peng = (peng*(3*peng-1))/2;
				if(peng > i)
					break;
				if((j&3) < 2)
					sum = sum + penta[i - peng];
				else
					sum = sum - penta[i - peng];
				sum = sum % 1000000;
			}
			if(i%1000 == 0)
				std::cout<<sum<<std::endl;
			if(sum == 0)
			{
				std::cout<<i<<std::endl;
				break;
			}
			penta.push_back(sum);
		}
	}

	void find_max(long** arr, long ** dp, int i, int j)
	{
		if(i == 80 || j == 80)
			return;
		if(i == 0 && j == 0)
			dp[i][j] = arr[i][j];
		else
		{
			int maxleft = 0, maxup = 0;
			if(i == 0)
				dp[i][j] = dp[i][j-1] + arr[i][j];
			else if(j == 0)
				dp[i][j] = dp[i-1][j] + arr[i][j];
			else
				dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + arr[i][j];
		}
	}

	void program_81()
	{
		const int limit = 80;
		long** stor = new long*[limit];
		long** dp = new long*[limit];
		for(int i = 0; i < limit; i++)
		{
			stor[i] = new long[limit];
			dp[i] = new long[limit];
		}
		for(int i = 0; i < limit; i++)
		{
			for(int j = 0; j < limit; j++)
				std::cin>>stor[i][j];
		}
		
		for(int i = 0; i < limit; i++)
		{
			for(int j = 0; j < limit; j++)
			{
				find_max((long**)stor,(long**)dp,i,j);
			}
		}
		/*for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 80; j++)
				std::cout<<dp[i][j]<<"\t";
			std::cout<<std::endl;
		}*/
		std::cout<<dp[limit-1][limit-1]<<std::endl;
	}

	void program_82()
	{
		const int limit = 80;
		graph* g = new graph(2+limit*limit);

		int** matrix = new int*[limit];

		for(int i = 0; i < limit; i++)
		{
			matrix[i] = new int[limit];
			for(int j = 0; j < limit; j++)
			{
				std::cin>>matrix[i][j];
			}
		}
		for(int i = 0; i< limit; i++)
		{
			for(int j = 0; j < limit; j++)
			{
				int thisnode = i*limit + j + 1;
				int neighb = 0;
				if( j < (limit - 1))
				{
					neighb = i*limit + j + 1 + 1;
					g->addEdge(thisnode,neighb,matrix[i][j+1]);
				}
				if( i > 0)
				{
					neighb = (i-1)* limit + j + 1;
					g->addEdge(thisnode,neighb,matrix[i-1][j]);
				}
				if( i < (limit - 1))
				{
					neighb = (i+1)*limit + j + 1;
					g->addEdge(thisnode,neighb,matrix[i+1][j]);
				}
				if( j == 0 )
				{
					g->addEdge(0,thisnode,matrix[i][j]);
				}
				if(j == (limit-1))
				{
					g->addEdge(thisnode,limit*limit + 1,0);
				}
			}
		}
		long* dist;
		int* prev;
		g->singleSourceShortestPath(0,&dist,&prev);
		for(int i = 0; i < limit*limit+2; i++)
		{
			std::cout<<dist[i]<<std::endl;
		}
	}

	void program_83()
	{
		const int limit = 80;
		graph* g = new graph(2+limit*limit);

		int** matrix = new int*[limit];

		for(int i = 0; i < limit; i++)
		{
			matrix[i] = new int[limit];
			for(int j = 0; j < limit; j++)
			{
				std::cin>>matrix[i][j];
			}
		}
		for(int i = 0; i< limit; i++)
		{
			for(int j = 0; j < limit; j++)
			{
				int thisnode = i*limit + j + 1;
				int neighb = 0;
				if( j < (limit - 1))
				{
					neighb = i*limit + j + 1 + 1;
					g->addEdge(thisnode,neighb,matrix[i][j+1]);
				}
				if(j > 0)
				{
					neighb = i*limit + j + 1 - 1;
					g->addEdge(thisnode,neighb,matrix[i][j-1]);
				}
				if( i > 0)
				{
					neighb = (i-1)* limit + j + 1;
					g->addEdge(thisnode,neighb,matrix[i-1][j]);
				}
				if( i < (limit - 1))
				{
					neighb = (i+1)*limit + j + 1;
					g->addEdge(thisnode,neighb,matrix[i+1][j]);
				}
				if( j == 0 && i == 0)
				{
					g->addEdge(0,thisnode,matrix[i][j]);
				}
				if(j == (limit-1) && i == (limit-1))
				{
					g->addEdge(thisnode,limit*limit + 1,0);
				}
			}
		}
		long* dist;
		int* prev;
		g->singleSourceShortestPath(0,&dist,&prev);
		for(int i = 0; i < limit*limit+2; i++)
		{
			std::cout<<dist[i]<<std::endl;
		}
	}

	void program_85()
	{
		// Number of ways is sigma(m)*sigma(n)
		std::vector<long long> summations;
		long long sum = 0;
		for(int i = 1; i < 100000; i++)
		{
			sum = sum + i;
			summations.push_back(sum);
		}
		long long area = 0;
		long long diff = 100000;
		for(int i = 1; i < 100000; i++)
		{
			for(int j = 1; j < 100000; j++)
			{
				long long temp = summations[i-1]*summations[j-1];
				if((temp - 2000000) > diff)
					break;
				if(std::abs(temp - 2000000) < diff)
				{
					diff = std::abs(temp - 2000000);
					area = i*j;
				}
			}
		}
		std::cout<<diff<<" : "<<area<<std::endl;
	}

	bool is_shortest_integer(int i, int j, int k)
	{
		long sum = i*i + (j+k)*(j+k);
		long double sqrt = std::sqrt(1.0*sum);
		if(sqrt == (long long)sqrt)
			return true;
		else
			return false;
	}

	void program_86()
	{
		const int limit = 1000000;
		long sum = 0;
		for(int i = 1; ; i++)
		{
			//std::set<std::pair<int,int> > dupl;
			for(int j = 1; j <= i; j++)
			{
				for(int k = 1; k <= j; k++)
				{
					/*std::pair<int,int> temp = (j > k)?std::make_pair(j,k):std::make_pair(k,j);
					if(dupl.find(temp) != dupl.end())
					{
						std::cout<<i<<":"<<j<<":"<<k<<std::endl;
						std::getchar();
						continue;
					}
					dupl.insert(temp);*/
					if(is_shortest_integer(i,j,k))
						sum++;
				}
				
			}
			if(sum >= limit)
			{
				std::cout<<i<<" : "<<sum<<std::endl;
				return;
			}
			
		}
	}

	void program_87()
	{
		const int limit = 50000000;
		std::vector<long> prime_squares;
		std::vector<long> prime_cubes;
		std::vector<long> prime_fourth;
		std::vector<int> primes;
		find_Primes(primes);
		for(int i = 0; ; i++)
		{
			if(((long)primes[i])*((long)primes[i]) < limit)
				prime_squares.push_back(((long)primes[i])*((long)primes[i]));
			else
				break;
		}
		for(int i = 0;;i++)
		{
			if(((long)primes[i])*((long)primes[i])*((long)primes[i]) < limit)
				prime_cubes.push_back(((long)primes[i])*((long)primes[i])*((long)primes[i]));
			else
				break;
		}
		for(int i = 0;;i++)
		{
			if(((long)primes[i])*((long)primes[i])*((long)primes[i])*((long)primes[i]) < limit)
				prime_fourth.push_back(((long)primes[i])*((long)primes[i])*((long)primes[i])*((long)primes[i]));
			else
				break;
		}
		std::set<long> sums_found;
		long count = 0;
		for(unsigned  i = 0; i < prime_squares.size(); i++)
		{
			for(unsigned int j = 0; j < prime_cubes.size(); j++)
			{
				for(unsigned int k = 0; k < prime_fourth.size(); k++)
				{
					long sum = prime_squares[i] + prime_cubes[j] + prime_fourth[k];
					if(sums_found.find(sum) != sums_found.end())
					{
						//std::cout<<"Dup : "<<sum<<std::endl;
						continue;
					}
					sums_found.insert(sum);
					if(sum<0)
						std::cout<<"long"<<std::endl;
					if(sum < limit)
						count++;
				}
			}
		}
		std::cout<<count<<std::endl;
		/*
		int i = 0, j = 0, k = 0;
		while(i<prime_squares.size() && j < prime_cubes.size() && k < prime_fourth.size())
		{
			long sum = prime_squares[i] + prime_cubes[j] + prime_fourth[k];
			if(sum < limit)
				count++;
			int min = min(prime_squares[i],min(prime_cubes[j],prime_fourth[k]));
			if(min = prime_squares[i])
				i++;
			else if(min = prime_cubes[j])
				j++;
			else
				k++;
		}*/
	}

	//Roman numbers
	int romanToInt(char* str, int len)
	{
		switch(len)
		{
		case 1:
			switch(str[0])
			{
			case 'M':
				return 1000;
			case 'D':
				return 500;
			case 'C':
				return 100;
			case 'L':
				return 50;
			case 'X':
				return 10;
			case 'V':
				return 5;
			case 'I':
				return 1;
			default:
				return 0;
			};
			break;
		case 2:
			if(str[0] == 'C' && str[1] == 'M')
				return 900;
			if(str[0] == 'C' && str[1] == 'D')
				return 400;
			if(str[0] == 'X' && str[1] == 'C')
				return 90;
			if(str[0] == 'X' && str[1] == 'L')
				return 40;
			if(str[0] == 'I' && str[1] == 'X')
				return 9;
			if(str[0] == 'I' && str[1] == 'V')
				return 4;
		}
		return 0;
	}
	int readRomanNumbers(char* str, int len)
	{
		int num = 0;
		for(int i = 0; i < len; i++)
		{
			if(i < len-1)
			{
				if(romanToInt(str + i,2))
				{
					num = num + romanToInt(str+i,2);
					i++;
				}
				else
					num = num + romanToInt(str+i,1);
			}
			else
				num = num + romanToInt(str+i,1);
		}
		return num;
	}
	int toRoman(int& num)
	{
		if(num >= 1000)
		{
			num = num - 1000;
			return 1;
		}
		if(num >= 900)
		{
			num = num - 900;
			return 2;
		}
		if(num >= 500)
		{
			num = num - 500;
			return 1;
		}
		if(num >= 400)
		{
			num = num - 400;
			return 2;
		}
		if(num >= 100)
		{
			num = num - 100;
			return 1;
		}
		if(num >= 90)
		{
			num = num - 90;
			return 2;
		}
		if(num >= 50)
		{
			num = num - 50;
			return 1;
		}
		if(num >= 40)
		{
			num = num - 40;
			return 2;
		}
		if(num >= 10)
		{
			num = num - 10;
			return 1;
		}
		if(num >= 9)
		{
			num = num - 9;
			return 2;
		}
		if(num >= 5)
		{
			num = num - 5;
			return 1;
		}
		if(num >= 4)
		{
			num = num - 4;
			return 2;
		}
		if(num >= 1)
		{
			num = num - 1;
			return 1;
		}
		return 0;
	}
	int intToRomanLen(int num)
	{
		int len = 0;
		while(num >0)
		{
			len += toRoman(num);
		}
		return len;
	}
	void program_89()
	{
		char str[100];
		int sum = 0;
		for(int i = 0; i < 1000; i++)
		{
			cin>>str;
			int len = 0; 
			while(str[len] != '\0') len++;
			//cout<<str<<":";
			int num = readRomanNumbers(str,len);
			int newlen = intToRomanLen(num);
			//cout<<num<<":"<<newlen<<endl;
			sum += len - newlen;
		}
		cout<<"Total: "<<sum<<endl;
	}

	//Number of right angled triangles for a range of values
	bool isRightAngled(int x1, int y1, int x2, int y2)
	{
		int d1 = (x1 - x2)*(x1 - x2) + (y1-y2)*(y1-y2);
		int d2 = x1*x1 + y1*y1;
		int d3 = x2*x2 + y2*y2;
		
		if(d1 == (d2+d3))
			return true;
		else if(d2 == (d1+d3))
			return true;
		else if(d3 == (d1+d2))
			return true;

		return false;

	}

	void program_91()
	{
		int limit = 50;
		int counter = 0;
		for(int x1= 0; x1<=limit; x1++)
		{
			for(int y1 = 0; y1 <= limit; y1++)
			{
				if(x1 == 0 && y1 == 0)
					continue;
				for(int x2 = 0; x2<= limit; x2++)
				{
					for(int y2 = 0; y2 <= limit; y2++)
					{
						if(x2 == 0 && y2 == 0)
							continue;
						if(x1 == x2 && y1 == y2)
							continue;
						if(isRightAngled(x1,y1,x2,y2))
						{
							//cout<<x1<<":"<<y1<<":"<<x2<<":"<<y2<<endl;
							counter++;
						}
					}
				}
			}
		}
		//perfectly symmetric in every way so every result would be duplicated
		cout<<counter/2<<endl;
	}

	//A number chain is created by continuously adding the square of the digits in a 
	//number to form a new number until it has been seen before.
	//Tip: Number of unique combinations of digits is very less. Lets generate only for unique combinations
	//and then add the number of their all possible permutations
	void program_92()
	{
		set<int> oneset;
		set<int> eightset;
		oneset.insert(1);
		eightset.insert(89);
		for(int i = 2; i < 568; i++)
		{
			if(oneset.find(i) != oneset.end())
				continue;
			if(eightset.find(i) != eightset.end())
				continue;
			int temp = i;
			vector<int> tempvec;
			tempvec.push_back(temp);
			while(temp != 1 && temp != 89)
			{
				int sum = 0;
				while(temp != 0)
				{
					sum = sum + (temp%10)*(temp%10);
					temp = temp/10;
				}
				if(oneset.find(sum) != oneset.end())
				{
					for(unsigned int k = 0; k < tempvec.size(); k++)
					{
						//if(tempvec[k] < 1000)
							oneset.insert(tempvec[k]);
					}
					break;
				}
				else if(eightset.find(sum) != eightset.end())
				{
					for(unsigned int k = 0; k < tempvec.size(); k++)
					{
						//if(tempvec[k] < 1000)
							eightset.insert(tempvec[k]);
					}
					break;
				}
				tempvec.push_back(sum);
				temp = sum;
			}
		}
		set<int> remeightset;
		for(int i = 568; i < 10000000; i++)
		{
			int temp = i;
			int sum = 0;
			while(temp != 0)
			{
				sum = sum + (temp%10)*(temp%10);
				temp = temp/10;
			}
			if(eightset.find(sum) != eightset.end())
			{
				remeightset.insert(i);
			}
			
		}

		cout<<eightset.size() + remeightset.size()<<endl;
	}

	//By using each of the digits from the set, {1, 2, 3, 4}, exactly once,
	//and making use of the four arithmetic operations (+, ?, *, /) and brackets/parentheses,
	//it is possible to form different positive integer targets.
	double result_93(double a, double b, int op)
	{
		switch(op)
		{
		case 0:
			return a+b;
		case 1:
			return a-b;
		case 2:
			return a/b;
		case 3:
			return a*b;
		}
		return 0;
	}
	void generate_all(vector<double>& op, int i, int j, int k, set<int>& res)
	{
		double temp = result_93(result_93(result_93(op[0],op[1],i),op[2],j),op[3],k);
		double atemp = 0;
		if(modf(temp,&atemp) == 0.0)
			res.insert((int)atemp);
		
		temp = result_93(result_93(op[0],op[1],i),result_93(op[2],op[3],k),j);
		atemp = 0;
		if(modf(temp,&atemp) == 0.0)
			res.insert((int)atemp);

		temp = result_93(result_93(op[0],result_93(op[1],op[2],j),i),op[3],k);
		atemp = 0;
		if(modf(temp,&atemp) == 0.0)
			res.insert((int)atemp);

		temp = result_93(op[0],result_93(result_93(op[1],op[2],j),op[3],k),i);
		atemp = 0;
		if(modf(temp,&atemp) == 0.0)
			res.insert((int)atemp);

		temp = result_93(op[0],result_93(op[1],result_93(op[2],op[3],k),j),i);
		atemp = 0;
		if(modf(temp,&atemp) == 0.0)
			res.insert((int)atemp);

	}
	void generate_combo_operator(vector<double>& op, set<int>& res)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				for(int k = 0; k < 4; k++)
				{
					generate_all(op,i,j,k,res);
				}
			}
		}
	}
	void generate_perms_93(int index, vector<double>& op, set<int>& results)
	{
		if(index == op.size())
		{
			//validate all 5 values generated here
			generate_combo_operator(op,results);
		}
		else
		{
			for(unsigned int i = index; i < op.size(); i++)
			{
				double temp = op[i];
				op[i] = op[index];
				op[index] = temp;
				generate_perms_93(index+1,op,results);
				temp = op[i];
				op[i] = op[index];
				op[index] = temp;
				
			}
		}
	}
	void generate_combo_93(int n, int k, int index, vector<int>& res, vector<int>& result, int& max)
	{
		if(k == 0)
		{
			vector<double> op;
			for(unsigned int i = 0; i < res.size(); i++) 
				op.push_back(res[i]);
			set<int> results;
			generate_perms_93(0,op, results);
			set<int>::iterator itr = results.find(1);
			if(itr != results.end()) 
			{
				int temp = 1;
				itr++;
				while(itr != results.end())
				{
					if(*itr != temp+1)
						break;
					temp++;
					itr++;
				}
				if(max < temp)
				{
					max = temp;
					result.clear();
					for(unsigned int i = 0; i < res.size(); i++)
						result.push_back(res[i]);
				}
			}
			return;
		}
		for(int i = index; i < n -k +1; i++)
		{
			res.push_back(i);
			generate_combo_93(n,k-1,i+1,res,result,max);
			res.pop_back();
		}

	}
    void program_93()
	{
		vector<int> res;
		vector<int> result;
		int max = 0;
		generate_combo_93(10,4,1,res,result,max);
		cout<<"Max:"<<max<<endl;
		for(unsigned int i = 0; i < result.size(); i++)
			cout<<result[i]<<"\t";
		cout<<endl;
	}



	//We shall define an almost equilateral triangle to be a triangle for which 
	//two sides are equal and the third differs by no more than one unit.
	//Find the sum of the perimeters of all almost equilateral triangles with 
	//integral side lengths and area and whose perimeters do not exceed one billion (1,000,000,000).
	//http://en.wikipedia.org/wiki/Pell%27s_equation
	void program_94()
	{
		long long x = 2;
		long long y = 1;
		long long limit = 1000000000;
		long long result = 0;
 
		while(true){
			// b = a+1
			long long aTimes3 = 2 * x - 1;
			long long areaTimes3 = y * (x - 2);
			if (aTimes3 > limit) break;
 
			if (aTimes3 > 0 &&
				areaTimes3 > 0 &&
				aTimes3 % 3 == 0 &&
				areaTimes3 % 3 == 0) {
 
				long long a = aTimes3 / 3;
				long long area = areaTimes3 / 3;
 
				result += 3 * a + 1;
			}
 
			//b = a-1
			aTimes3 = 2 * x + 1;
			areaTimes3 = y * (x + 2);
 
			if (aTimes3 > 0 &&
				areaTimes3 > 0 &&
				aTimes3 % 3 == 0 &&
				areaTimes3 % 3 == 0) {
 
				long long a = aTimes3 / 3;
				long long area = areaTimes3 / 3;
 
				result += 3 * a - 1;
			}
 
			long nextx = 2 * x + y * 3;
			long nexty = y * 2 + x;
 
			x = nextx;
			y = nexty;
		}
		cout<<result<<endl;
	}

	//Amicable chains
	void program_95()
	{
		//vector<bool> bitset;
		//for(int r = 0; r < 1000000; r++) 
		//	bitset.push_back(false);

		//vector<int> primes;
		//find_Primes(primes);

		int i = 2;
		int max_count = 0, min_total = 100000000;
		while(i < 1000000)
		{
			//if(bitset[i])
			//{
			//	i++;
			//	continue;
			//}
			//bitset[i] = true;
			int temp = i;
			int count = 0, min = temp;
			std::set<int> tempvec;
			do
			{
				
				long sum = 1;
				int sq = sqrt((double)temp);
				
				for(int j = 2; j <= sq; j++)
				{
					if(temp%j == 0)
					{
						sum += j;
						if(temp/j != j)
							sum += temp/j;
					}
				}
				if(sum >= 1000000 || sum == temp || sum < i)
				{
					count = 0;
					break;
				}
				temp = sum;
				if(tempvec.find(temp) != tempvec.end())
				{
					count = 0;
					break;
				}
				else
					tempvec.insert(temp);

				//bitset[temp] = true;
				count++;
				if(temp < min)
					min = temp;
			}while(temp != i);
			i++;
			if(count > max_count)
			{
				max_count = count;
				min_total = min;
			}
		}
		cout<<max_count<<":"<<min_total<<endl;

	}

	bool are_anagram(string a, string b)
	{
		std::sort(a.begin(),a.end());
		std::sort(b.begin(), b.end());
		if(strcmp(a.c_str(),b.c_str()) == 0)
			return true;
		else
			return false;
	}

	bool for98(string a, string b, long numa, long numb)
	{
		return true;
	}

	void program_98()
	{
		string inputstr;
		cin>>inputstr;
		std::vector<std::string> elems;
		std::stringstream ss(inputstr);
		std::string item;
		long long maxsize = 0;
		while (std::getline(ss, item, ',')) {
			elems.push_back(item);
			//cout<<item<<endl;
			
		}
		//cout<<elems.size()<<endl;

		map<string,string> anagrammap;
		for(int i = 0; i < elems.size(); i++)
		{
			for(int j = i+1; j < elems.size(); j++)
			{
				if(are_anagram(elems[i],elems[j]))
				{
					anagrammap[elems[i]] = elems[j];
					cout<<elems[i]<<":"<<elems[j]<<endl;
					if(maxsize<elems[i].size())
						maxsize = elems[i].size();
				}
			}
		}
		cout<<anagrammap.size()<<endl;
		
		cout<<maxsize<<endl;
		long long p = 1;
		for(int i = 0; i < maxsize + 1; i++)
			p = p * 10;
		maxsize = 100000000;
		cout<<maxsize<<endl;

		std::vector<long> squares;
		for(long i = 7; i*i < maxsize; i++)
		{
			squares.push_back(i*i);
		}
		cout<<squares.size()<<endl;
		map<long,long> squaremap;
		for(int i = 0; i < squares.size(); i++)
		{
			for(int j = i+1; j < squares.size(); j++)
			{
				long long powerx = 1,powery=1,countx=0;
				while(powerx < squares[i]) powerx *= 10;
				while(powery < squares[j]) powery *= 10;
				if(powerx != powery) break;
				if(are_anagram(squares[i],squares[j]))
				{
					squaremap[squares[i]] = squares[j];
					//cout<<squares[i]<<":"<<squares[j]<<endl;
				}
			}
		}
		cout<<squaremap.size()<<endl;
		
	}

	void program_99()
	{
		int i = 0,maxline = 0;
		long double max = 0;
		while(i < 1000)
		{
			i++;
			long a, b;
			std::cin>>a;
			std::cin>>b;
			long double result = b * std::log10(a);
			if(result > max)
			{
				max = result;
				maxline = i;
			}
		}
		std::cout<<maxline<<endl;
	}
	
	unsigned long long binary_search_100(unsigned long long start)
	{
		unsigned long long low = 0.7*start,high = 0.75*start,x = 0;
		while(low <= high)
		{
			x = low + (high - low)/2;
			if(2*(x * (x-1) ) == start*(start-1))
				return x;
			else if(2*(x * (x-1) ) > start*(start-1))
				high = x - 1;
			else
				low = x + 1;
		}
		return 0;
	}
	void program_100()
	{
		unsigned long long start = 1000000;
		unsigned long long test = 0;
		cout<<--test<<endl;
		int count = 0;
		while(start)
		{
			start++;
			unsigned long long result = binary_search_100(start);
			if(result)
			{
				cout<<result<<" : "<<start<<" : "<<(result*1.0l)/start<<endl;
				long double sec = (result*1.0l)/start;
				unsigned long long end = 1000000000000;
				while(true)
				{
					long double first = sec * end;
					if((first - (unsigned long long)first) == 0)
					{
						cout<<(unsigned long long)first<<" : "<<end<<" : "<<(first/end)*((first-1)/(end-1))<<endl;
					}
					end++;
					if(end > 10000000000000)
						return;
				}
				if(count > 10)
					break;
				count++;
			}
		}
	}
	void program_100_another()
	{
		long long b = 15;
		long long n = 21;
		long long target = 1000000000000;
 
		while(n < target){
			long long btemp = 3 * b + 2 * n - 2;
			long long ntemp = 4 * b + 3 * n - 3;
 
			b = btemp;
			n = ntemp;
		}
		cout<<b<<" : "<<n<<" : "<<((b*1.0l)/n)*((b-1)*1.0l/(n-1))<<":"<<(b*1.0l)/n;
	}

}


