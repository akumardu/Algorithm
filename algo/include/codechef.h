#include <iostream>
#include<vector>
#include<map>
#include<string>
#include<set>
#include<algorithm>

//namespace coinflip
//{
//	void coinflip()
//	{
//		int cases;
//		std::cin>>cases;
//		while(cases--)
//		{
//			int subcase;
//			std::cin>>subcase;
//			while(subcase--)
//			{
//				int i = 0,q=0;
//				long long n = 0;
//				std::cin>>i;
//				std::cin>>n;
//				std::cin>>q;
//				if((n%2) == 0)
//					std::cout<<(n/2)<<std::endl;
//				else
//				{
//					if( i == q)
//						std::cout<<(n/2)<<std::endl;
//					else
//						std::cout<<(n/2)+1<<std::endl;
//				}
//			}
//		}
//	}
//}
namespace codechef
{
	using namespace std;
	//testcases: 6 1 2 2 3 5 6
	struct pair
	{
		vector<int> member;
		int sum;
		pair()
		{
			sum = 0;
		}
		pair(int f, int s,int sm)
		{
			member.push_back(f);
			member.push_back(s);
			sum = sm;
		}
		void add(int a)
		{
			member.push_back(a);
		}
	};
	class paircomparator{
	public:
	bool operator()(const pair& a, const pair& b)
	{
		if(a.sum < b.sum)
			return true;
		return false;
	}};
	void sumofpairs()
	{
		int n=0;
		cin>>n;
		int* arr = new int[n];
		for(int i = 0; i < n; i++)
			cin>>arr[i];
		map<int,pair> summap;
		int max = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = i+1; j < n; j++)
			{
				if(summap.find(arr[i]+arr[j]) != summap.end())
				{
					map<int,pair>::iterator it = summap.find(arr[i]+arr[j]);
					if(std::find((*it).second.member.begin(), (*it).second.member.end(), i) == (*it).second.member.end() && 
						std::find((*it).second.member.begin(), (*it).second.member.end(), j) == (*it).second.member.end())
					{
						(*it).second.sum++;
						(*it).second.add(i);
						(*it).second.add(j);
					}
				}
				else
					summap[arr[i]+arr[j]] = pair(i,j,1);
				if(summap[arr[i]+arr[j]].sum > max)
					max = summap[arr[i]+arr[j]].sum;
			}
		}
		cout<<max*2<<endl;
	}

	unsigned long long inTens(int n)
	{
		char maps[32];
		int size = 0;
		unsigned long long result = 0;
		while(n)
		{
			if((n&1) == 0)
				maps[size]=0;
			else
				maps[size]=1;
			size++;
			n = n >> 1;
		}
		size--;
		while(size >= 0)
		{
			if(maps[size])
				result = result*10 + 1;
			else
				result = result*10;
			size--;
		}
		//cout<<result<<endl;
		return result;
	}
	unsigned long long poweroftwomod(unsigned long long n)
	{
		const unsigned long long modnum = 1000000007;
		char maps[64];
		int size = 0;
		unsigned long long result = 0;
		while(n)
		{
			if((n&1) == 0)
				maps[size]=0;
			else
				maps[size]=1;
			size++;
			n = n >> 1;
		}
		size--;
		// Montgomer's ladder technique
		unsigned long long x1 = 2, x2 = 4;
		for(int i = size-1;i>=0; i--)
		{
			if(maps[i] == 0)
			{
				x2 = (x1 * x2)%modnum;
				x1 = (x1 * x1)%modnum;
			}
			else
			{
				x1 = (x1 * x2)%modnum;
				x2 = (x2 * x2)%modnum;
			}
		}
		return (x1*x1)%modnum;
	}
	void superpoweroftwo()
	{
		int testcases;
		cin>>testcases;
		while(testcases)
		{
			testcases--;
			int n = 0;
			cin>>n;
			unsigned long long power = inTens(n);
			cout<<poweroftwomod(power)<<endl;
		}
	}
}

namespace tourmap
{
	void tourmap()
	{
		int cases;
		scanf_s("%d",&cases);
		while(cases--)
		{
			int n;
			scanf_s("%d",&n);
			if(n == 1)
			{
				printf("0$\n");
				continue;
			}
			std::vector< std::string > first;
			std::vector< std::string> second;
			std::vector< int> price;
			int sum = 0;
			///std::string input;
			char buffer[52];
			int temp;
			for( int i = 0; i < n-1; i++)
			{				
				scanf_s("%s",buffer);
				//input = buffer;
				first.push_back(buffer);
				scanf_s("%s",buffer);
				//input = buffer;
				second.push_back(buffer);
				scanf_s("%d$",&temp);
				sum += temp;
				price.push_back(temp);
			}
			int startIndex = 0;
			for(int i = 0; i < n - 1; i++)
			{
				bool found = false;
				for(int j = 0 ; j < n-1; j++)
				{
					if(j != i && !first[i].compare(second[j]))
					{
						found = true;
						break;
					}
				}
				if(found == false)
				{
					startIndex = i;
					break;
				}
			}
			int count = 0;
			while(count != (n-1))
			{
				count++;
				printf("%s %s %d$\n",first[startIndex].c_str(),second[startIndex].c_str(),price[startIndex]);
				
				for(int i = 0 ; i < n-1; i++)
				{
					if(!first[i].compare(second[startIndex]))
					{
						startIndex = i;
						break;
					}
				}
				
			}
			printf("%d$\n",sum);
			//std::cout<<sum<<"$"<<std::endl;
		}
	}
}