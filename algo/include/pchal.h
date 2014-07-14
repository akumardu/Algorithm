#include<iostream>
#include<vector>

namespace threen
{
	long crumppum(long num)
	{
		int counter = 1;
		while(num != 1)
		{
			//counter++;
			//if(num == 1)
			//	break;
			if(num % 2 == 1)
				num = num*3 + 1;
			else
				num = num/2;
			counter++;
		}
		return counter;
	}

	void threen()
	{
		/*long* dp = new long[MAX];
		std::memset(dp,0,MAX*sizeof(long));
		dp[0] = 0;
		dp[1] = 1;*/
		while(true)
		{
			long a,b;
			std::cin>>a;
			std::cin>>b;
			if(std::cin.fail())
				break;
			long tempa = a,tempb = b;
			if(b < a)
			{
				tempa = b;
				tempb = a;
			}
			long max = 0;
			for(long i = tempa;i<=tempb;i++)
			{
				long res = crumppum(i);
				if(max < res)
					max = res;
			}
			std::cout<<a<<" "<<b<<" "<<max<<std::endl;
		}
	}
}
namespace minesweeper
{
	void sweeper()
	{
		int counter = 0;
		while(true)
		{
			int a , b;
			std::cin>>a;
			std::cin>>b;
			if(a == 0 && b == 0)
				return;
			counter++;
			char** arr = new char*[a];
			for(int i = 0 ; i < a; i++)
			{
				arr[i] = new char[b];
				std::memset(arr[i],'0',b*sizeof(char));
			}
			for(int i = 0; i< a; i++)
			{
				for(int j = 0; j < b; j++)
				{
					char temp;
					std::cin>>temp;
					if(temp == '.')
						continue;
					arr[i][j] = temp;
					if(i > 0)
					{
						if(arr[i - 1][j] != '*')
							arr[i - 1][j]++;
						if(j > 0 && arr[i-1][j-1] != '*')
							arr[i-1][j-1]++;
						if(j < (b-1) && arr[i - 1][j + 1] != '*')
							arr[i - 1][j + 1]++;

					}
					if( i < (a-1))
					{
						if(arr[i + 1][j] != '*')
							arr[i + 1][j]++;
						if(j > 0 && arr[i+1][j - 1] != '*')
							arr[i+1][j - 1]++;
						if(j < (b - 1) && arr[i + 1][j + 1] != '*')
							arr[i + 1][j + 1]++;
					}
					if( j > 0 && arr[i][j-1] != '*')
					{
						arr[i][j-1]++;
					}
					if(j < (b - 1) && arr[i][j+1] != '*')
					{
						arr[i][j+1]++;
					}
				}
			}
			std::cout<<"Field #"<<counter<<":"<<std::endl;
			for( int i = 0; i < a; i++)
			{
				for(int j = 0; j < b; j++)
				{
					std::cout<<arr[i][j];
				}
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
		}

	}
}

