#include<iostream>
#include<vector>
#include<set>
#include<map>
#include "time.h"
#include "graph.h"
#include <stdio.h>

#ifndef ALGO_PART2
#define ALGO_PART2

#define MAX(x,y) ((x>y)?(x):(y))

class unionfind
{
public:
	unionfind(long numOfObjects)
	{
		data = new long[numOfObjects];
		sz = new long[numOfObjects];

		for(long i = 0; i < numOfObjects; i++)
		{
			data[i] = i;
			sz[i] = 1;
		}
		this->numOfObjects = numOfObjects;
		this->countComponents = numOfObjects;
	}

	long findGroupSize(long p)
	{
		long i = root(p);
		return sz[i];
	}

	void makeUnion(long p, long q)
	{
		long i = root(p);
		long j = root(q);
		if(sz[i] < sz[j])
		{
			data[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			data[j] = i;
			sz[i] += sz[j];
		}
		countComponents--;
	}

	bool isConnected(long p, long q)
	{
		return root(p) == root(q);
	}

	long getcountComponents()
	{
		return countComponents;
	}

	~unionfind()
	{
		delete[] data;
		delete[] sz;
	}

private:
	long root(long p)
	{
		while(p != data[p])
		{
			data[p] = data[data[p]];
			p = data[p];
		}
		return p;
	}
	
	long* data;
	long* sz;
	long countComponents;
	long numOfObjects;

};

namespace algo_part2
{
	struct job
	{
		int weight;
		int length;
		//int rand;
	};
	class comp
	{
	public:
		bool operator()( const job& first, const job& seco)
		{
			/*int res1 = first.weight - first.length;
			int res2 = seco.weight - seco.length;
			if(res1 == res2)
				return first.weight > seco.weight;
			return res1 > res2;*/
			double rat1 = ((double)first.weight)/first.length;
			double rat2 = ((double)seco.weight)/seco.length;
			return rat1 > rat2;
		}
	};
	void scheduler()
	{
		int num_jobs= 0,twt,tlen;
		//time_t secs;
		//time(&secs);
		//srand((unsigned int)secs);
		std::cin>>num_jobs;
		std::multimap<job,int,comp> coll;
		for(int i = 0; i < num_jobs; i++)
		{
			std::cin>>twt>>tlen;
			job j;
			j.weight = twt;
			j.length = tlen;
			//j.rand = rand();
			coll.insert(std::make_pair(j,twt));
		}
		std::cout<<coll.size()<<std::endl;
		std::multimap<job,int,comp>::iterator it = coll.begin();
		long long result = 0,length = 0;
		while(it != coll.end())
		{
			length += (*it).first.length;
			result = result + length*(*it).first.weight;
			it++;
		}
		std::cout<<result<<std::endl;
		//69119377652
		//67311454237
	}

	void prim()
	{
		long numVer=0,numEdge=0,src,dest,wt;
		std::cin>>numVer>>numEdge;
		unDirectedGraph gr(numVer);
		for(int i = 0; i < numEdge; i++)
		{
			std::cin>>src>>dest>>wt;
			src--;
			dest--;
			gr.addUndirectedEdge(src,dest,wt);
		}
		std::cout<<gr.primsMinSpanTree()<<std::endl;

	}

	void clustering_algo()
	{
		//Weight as Key and vertices as paired value
		std::multimap<long, std::pair<long, long> > store;
		long numofEdges,twt,tveta,tvetb, numofVerts;
		std::cin>>numofVerts;
		numofEdges = (numofVerts * numofVerts)/2 - numofVerts/2;
		for(long i = 0; i < numofEdges; i++)
		{
			std::cin>>tveta>>tvetb>>twt;
			tveta--;
			tvetb--;
			store.insert(std::make_pair(twt,std::make_pair(tveta,tvetb)));
		}
		unionfind dist(numofVerts);

		std::multimap<long, std::pair<long, long> >::iterator it = store.begin();
		long long netWtSum = 0,spacing =0;
		for( ; it != store.end() ; it++ )
		{
			if(!dist.isConnected((*it).second.first, (*it).second.second))
			{
				std::cout<<"Last: "<<(*it).first<<" : "<<(*it).second.first<<": "<<(*it).second.second<<std::endl;
				netWtSum += (*it).first;
				dist.makeUnion((*it).second.first, (*it).second.second);
				if(dist.getcountComponents() == 4)
				{	
					for(;it!= store.end(); it++)
					{
						if(!dist.isConnected((*it).second.first, (*it).second.second))
						{
							spacing = (*it).first;
							break;
						}
					}
					break;
				}
			}

		}
		std::cout<<spacing<<std::endl;
	}

	void clustering_algo2()
	{
		int num = 0, bits = 0;
		std::cin>>num>>bits;
		std::multimap<int, int> store;
		unionfind uf(num);
		std::multimap<int, int>::iterator it = store.begin();
		std::multimap<int,int>::iterator it2 = store.begin();
		for(int i = 0; i < num; i++)
		{
			int temp = 0, tempnum = 0;
			for(int j = 0; j < bits; j++)
			{
				std::cin>>temp;
				tempnum = tempnum | temp;
				tempnum = tempnum << 1;
			}
			tempnum = tempnum >> 1;
			if((it = store.find(tempnum)) == store.end())
				store.insert(std::make_pair(tempnum,i));
			else
			{
				if(!uf.isConnected(it->second,i))
					uf.makeUnion(it->second,i);
			}
		}
		//first merge all same elements
		
		//for(;it != store.end(); it++)
		//{
		//	it2 = it;
		//	it2++;
		//	while(it2 != store.end() && it2->first == it->first)
		//	{
		//		if(!uf.isConnected(it2->second,it->second))
		//			uf.makeUnion(it2->second,it->second);
		//		//it2++;
		//		std::multimap<int,int>::iterator eraseIter = it2++;
		//		store.erase(eraseIter);
		//		if(it2 == store.end())
		//			break;
		//	}
		//}
		std::cout<<store.size()<<" : "<<uf.getcountComponents()<<std::endl;
		it = store.begin();
		for(;it != store.end(); it++)
		{
			//Search while flipping 1 bit at a time
			int tempnum = it->first;
			int bitmapper = 1;
			for(int i = 0; i < bits; i++)
			{
				tempnum = it->first;
				bitmapper = 1<< i;
				//flipping the bit
				if(tempnum & bitmapper)
				{
					tempnum = tempnum & (~bitmapper);
				}
				else
				{
					tempnum = tempnum | bitmapper;
				}
				//find this number
				it2 = store.end();
				if((it2 = store.find(tempnum)) != store.end())
				{
					//std::cout<<"Found : "<<std::endl;
					if(!uf.isConnected(it->second, it2->second))
					{
						//std::cout<<"Found : "<<it->first<<" : "<<it2->first<<std::endl;
						uf.makeUnion(it->second,it2->second);
					}
				}
			}

			//Search while flipping 2 bits at a time
			tempnum = it->first;
			bitmapper = 1;
			int comparer1 = 0;
			for(int i = 0; i < bits; i++)
			{
				tempnum = it->first;
				comparer1 = bitmapper << i;
				//flipping the bit
				if(tempnum & comparer1)
				{
					tempnum = tempnum & (~comparer1);
				}
				else
				{
					tempnum = tempnum | comparer1;
				}
				for(int j = i+1; j < bits; j++)
				{
					int tempnum2 = tempnum;
					int comparer2 = bitmapper << j;
					if(tempnum2 & comparer2)
					{
						tempnum2 = tempnum2 & (~comparer2);
					}
					else
					{
						tempnum2 = tempnum2 | comparer2;
					}

					//find this number
					it2 = store.end();
					if((it2 = store.find(tempnum2)) != store.end())
					{
						//std::cout<<"Found : "<<std::endl;
						if(!uf.isConnected(it->second, it2->second))
						{
							//std::cout<<"Found : "<<it->first<<" : "<<it2->first<<std::endl;
							uf.makeUnion(it->second,it2->second);
						}
					}

				}
			}
		}
		std::cout<<uf.getcountComponents()<<std::endl;
	}

	void knapsack()
	{
		int knapsize=0,items = 0;
		std::cin>>knapsize>>items;
		int* arrVal = new int[items];
		int* arrWt = new int[items];
		for(int i = 0; i < items; i++)
			std::cin>>arrVal[i]>>arrWt[i];

		int **work = new int*[items+1];
		for(int i = 0; i < items+1; i++)
		{
			work[i] = new int[knapsize + 1];
			std::memset(work[i],0,(knapsize+1)*sizeof(int));
		}

		for(int i = 1; i < items+1; i++)
		{
			for(int j = 0; j < knapsize+1; j++)
			{
				if(j >= arrWt[i-1])
					work[i][j] =  MAX(work[i-1][j],work[i-1][j-arrWt[i-1]] + arrVal[i-1]);
				else
					work[i][j] = work[i-1][j];
			}
		}

		std::cout<<work[items][knapsize];

	}

	void knapsack_2()
	{
		int knapsize=0,items = 0;
		std::cin>>knapsize>>items;
		int* arrVal = new int[items];
		int* arrWt = new int[items];
		for(int i = 0; i < items; i++)
			std::cin>>arrVal[i]>>arrWt[i];

		int **work = new int*[2];
		for(int i = 0; i < 2; i++)
		{
			work[i] = new int[knapsize + 1];
			std::memset(work[i],0,(knapsize+1)*sizeof(int));
		}
		int final = 0;
		for(int i = 1; i < items+1; i++)
		{
			int temp = i % 2;
			int prev = temp?0:1;
			for(int j = 0; j < knapsize+1; j++)
			{	
				if(j >= arrWt[i-1])
					work[temp][j] =  MAX(work[prev][j],work[prev][j-arrWt[i-1]] + arrVal[i-1]);
				else
					work[temp][j] = work[prev][j];
			}
			final = temp;
		}

		std::cout<<work[final][knapsize];
	}

	namespace external
	{

		typedef std::map<int, int> MemoType;

		MemoType fullMemo[500];

		int N;
		std::vector<std::pair<int, int> > O;

		int f(int k, int W)
		{
		  if (k >= N)
			return 0;
		  MemoType& memo = fullMemo[k];
		  MemoType::iterator it = memo.find(W);
		  if (it != memo.end())
			return it->second;
		  int best = f(k + 1, W);
		  if (O[k].second <= W)
			best = MAX(best, f(k + 1, W - O[k].second) + O[k].first);
		  memo.insert(MemoType::value_type(W, best));
		  return best;
		}

		int knapsack_3()
		{
		  clock_t start = clock();
		  int M;
		  //scanf("%d %d", &M, &N);
		  std::cin>>M>>N;
		  O.resize(N);
		  for (int i = 0; i < N; ++i)
			//scanf("%d %d", &O[i].first, &O[i].second);
			std::cin>>O[i].first>>O[i].second;
		  clock_t read_end = clock();
		  int sol = f(0, M);
		  clock_t dp_end = clock();
		  printf("%d\n", sol);
		  printf("\ntimes:\n");
		  printf(" read: %.4lf seconds\n", double(read_end - start) / CLOCKS_PER_SEC);
		  printf("   dp: %.4lf seconds\n", double(dp_end - read_end) / CLOCKS_PER_SEC);
		  printf("total: %.4lf seconds\n", double(dp_end - start) / CLOCKS_PER_SEC);
		  return 0;
		}
	}

}

namespace codejam
{
	bool checkrow(char**arr,int row, char& start)
	{
		if(arr[row][0] == '.' || arr[row][1] == '.')
			return false;
		start = arr[row][0];
		if(start == 'T')
			start = arr[row][1];
		for(int k = 1; k < 4; k++)
		{
			if(arr[row][k] != 'T' && arr[row][k] != start)
			{
				return false;
			}
		}
		return true;
	}
	bool checkcol(char**arr,int col, char& start)
	{
		if(arr[0][col] == '.' || arr[1][col] == '.')
			return false;
		start = arr[0][col];
		if(start == 'T')
			start = arr[1][col];
		for(int k = 1; k < 4; k++)
		{
			if(arr[k][col] != 'T' && arr[k][col] != start)
			{
				return false;
			}
		}
		return true;
	}
	bool checkdiagonal(char**arr, char& start)
	{
		if(arr[0][0] == '.' || arr[1][1] == '.')
			return false;
		start = arr[0][0];
		if(start == 'T')
			start = arr[1][1];
		for(int k = 1; k < 4; k++)
		{
			if(arr[k][k] != 'T' && arr[k][k] != start)
			{
				return false;
			}
		}
		return true;
	}
	bool checkinversediagonal(char**arr, char& start)
	{
		if(arr[0][3] == '.' || arr[1][2] == '.')
			return false;
		start = arr[0][3];
		if(start == 'T')
			start = arr[1][2];
		for(int k = 1; k < 4; k++)
		{
			if(arr[k][3-k] != 'T' && arr[k][3-k] != start)
			{
				return false;
			}
		}
		return true;
	}
	void tictactoe()
	{
		int cases;
		std::cin>>cases;
		char** arr = new char*[4];
		for(int j = 0 ; j < 4; j++)
			arr[j] = new char[4];
		for(int i = 1; i <= cases; i++)
		{
			bool gamenotcompleted = false;
			for(int j = 0; j < 4; j++)
			{
				for(int k = 0; k < 4; k++)
				{
					std::cin>>arr[j][k];
					if(!gamenotcompleted && arr[j][k] == '.')
						gamenotcompleted = true;
				}
			}
			//check every row
			bool found = false;
			char start;
			for(int j = 0 ; j < 4;j++)
			{
				if(checkrow(arr,j,start))
				{
					found = true;
					break;
				}
			}
			if(found)
			{
				std::cout<<"Case #"<<i<<": "<<start<<" won"<<std::endl;
				continue;
			}
			//check every column
			for(int j = 0; j < 4; j++)
			{
				if(checkcol(arr,j,start))
				{
					found = true;
					break;
				}
			}
			if(found)
			{
				std::cout<<"Case #"<<i<<": "<<start<<" won"<<std::endl;
				continue;
			}
			//check either diagonal
			if(checkdiagonal(arr,start))
			{
				std::cout<<"Case #"<<i<<": "<<start<<" won"<<std::endl;
				continue;
			}
			if(checkinversediagonal(arr,start))
			{
				std::cout<<"Case #"<<i<<": "<<start<<" won"<<std::endl;
				continue;
			}
			if(gamenotcompleted)
			{
				std::cout<<"Case #"<<i<<": "<<"Game has not completed"<<std::endl;
				continue;
			}
			else
			{
				std::cout<<"Case #"<<i<<": "<<"Draw"<<std::endl;
				continue;
			}
		} 
	}


	bool checkup(int**arr, int m, int n, int i, int j)
	{
		int thisval = arr[i][j];
		int up = i;
		while(up >= 0)
		{
			if(arr[up][j] > thisval)
			{
				return false;
			}
			up--;
		}
		return true;
	}
	bool checkdown(int**arr, int m, int n, int i, int j)
	{
		int thisval = arr[i][j];
		int down = i;
		while(down < m)
		{
			if(arr[down][j] > thisval)
			{
				return false;
			}
			down++;
		}
		return true;
	}
	bool checkleft(int**arr, int m, int n, int i, int j)
	{
		int thisval = arr[i][j];
		int left = j;
		while(left >= 0)
		{
			if(arr[i][left] > thisval)
			{
				return false;
			}
			left--;
		}
		return true;
	}
	bool checkright(int**arr, int m, int n, int i, int j)
	{
		int thisval = arr[i][j];
		int right = j;
		while(right < n)
		{
			if(arr[i][right] > thisval)
			{
				return false;
			}
			right++;
		}
		return true;
	}
	void lawnmower()
	{
		int cases;
		std::cin>>cases;
		for(int cs = 1; cs <= cases; cs++)
		{
			int m,n;
			std::cin>>m>>n;
			int** arr = new int*[m];
			for(int i = 0 ; i < m; i++)
				arr[i] = new int[n];
			for(int i  = 0; i < m; i++)
			{
				for(int j = 0; j < n; j++)
				{
					std::cin>>arr[i][j];
				}
			}
			bool canbedone = true;
			for(int i = 0; i < m; i++)
			{
				bool found = false;
				for(int j = 0; j < n; j++)
				{
					bool vert = false,hor = false;
					if(!checkup(arr,m,n,i,j) || !checkdown(arr,m,n,i,j))
					{
						vert = true;
					}
					if(!checkleft(arr,m,n,i,j) || !checkright(arr,m,n,i,j))
					{
						hor = true;
					}
					if(vert && hor)
					{
						//std::cout<<i<<j<<std::endl;
						found = true;
						break;
					}
				}
				if(found)
				{
					canbedone = false;
					break;
				}
			}
			if(canbedone)
			{
				std::cout<<"Case #"<<cs<<": YES"<<std::endl;
			}
			else
				std::cout<<"Case #"<<cs<<": NO"<<std::endl;
			for(int i = 0 ; i < m; i++)
				delete[] arr[i];
			delete[] arr;
		}
	}

	class bignumber
	{
		
	public:
		void print()
		{
			for(unsigned int i = 0; i<data.size(); i++)
				std::cout<<(int)data[i];
			std::cout<<std::endl;
		}
		bignumber(unsigned long long n)
		{
			unsigned long long power = 1;
			while(power < n)
				power = power*10;
			power = power / 10;
			while(power != 0)
			{
				char x = (char)(n/power);
				data.push_back(x);
				n = n%power;
				power = power/10;
			}
		}
		void add(int n)
		{
			int carry = 0,i = data.size() - 1;
			do
			{
				data[i] = data[i] + n%10 + carry;
				if(data[i] > 10)
				{
					data[i] = data[i]%10;
					carry = data[i] / 10;
				}
				n = n / 10;
				i--;
			}while(carry && i >= 0);
			if(carry)
			{

			}
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
		void multiplyby10()
		{
			data.push_back(0);
		}
		void divideby10()
		{
			data.pop_back();
		}
		int modulo10()
		{
			return data[data.size() - 1];
		}
		bool isnull()
		{
			if(size() == 0)
				return true;
			int num = 0;
			for(unsigned int i = 0; i < data.size(); i++)
			{
				num = num*10 +data[i];
				if(num != 0)
					return false;
			}
			return true;
		}
		bool islessthan(bignumber& n)
		{
			if(n.size() > size())
				return true;
			else if(n.size() < size())
				return false;
			else
			{
				int i = data.size() - 1;
				while(i >= 0)
				{
					if(n.data[i] > data[i])
						return true;
					else if(n.data[i] < data[i])
						return false;
					i--;
				}
				return false;
			}
		}
		int size(){return data.size();}
	private:
		std::vector<char> data;
	};

	void next_pallindrome(bignumber& x, bool oddlength)
	{
		bignumber res = x;
		if(oddlength)
			x.divideby10();
		while(!x.isnull())
		{
			res.multiplyby10();
			res.add(x.modulo10());
			x.divideby10();
		}
		x = res;
	}

	void fairandsquare()
	{
		int cases;
		std::cin>>cases;
		for(int cs = 1; cs <= cases; cs++)
		{
			unsigned long long a, b;
			std::cin>>a>>b;
			bignumber biga = a;
			bignumber bigb = b;
			bignumber x = 1;

			for(;x.islessthan(bigb);x.add(1))
			{
				bignumber temp = x;
				next_pallindrome(temp,true);
				temp.print();
				temp = x;
				next_pallindrome(temp,false);
				temp.print();
				x.add(1);
			}
		}
	}

	bool is_Pallindrome(unsigned long long x)
	{
		unsigned long long res = x;
		unsigned long long che = 0;
		while(res > 0)
		{
			che = che*10 + res%10;
			res = res/10;
		}
		return che == x;
	}

	long long next_pallindrome(unsigned long long x, bool oddlength)
	{
		static int base = 10;
		long long res = x;
		if(oddlength)
			x = x/base;
		while(x > 0)
		{
			res = base * res + x % base;
			x = x/base;
		}
		return res;
	}

	void fairandsquare_large()
	{
		int cases;
		std::cin>>cases;
		std::set<long long> pallindromic_squares;
		long long x = 1;
		for(;x < 100000000;x++)
		{
			long long p = next_pallindrome(x,true);
			if(p < 0)
				break;
			int temp = p%10;
			if(temp == 2 || temp == 3 || temp == 7 || temp == 8 || temp == 0)
				continue;
			long long sqrt = (long long)std::pow((double)p,0.5);
			temp = sqrt%10;
			if(temp == 0 || temp > 3)
				continue;
			if(sqrt*sqrt == p && is_Pallindrome(sqrt))
				pallindromic_squares.insert(p);
		}
		x = 1;
		for(;x < 100000000;x++)
		{
			long long p = next_pallindrome(x,false);
			if(p < 0)
				break;
			int temp = p%10;
			if(temp == 2 || temp == 3 || temp == 7 || temp == 8 || temp == 0)
				continue;
			long long sqrt = (long long)std::pow((double)p,0.5);
			temp = sqrt%10;
			if(temp == 0 || temp > 3)
				continue;
			if(sqrt*sqrt == p && is_Pallindrome(sqrt))
				pallindromic_squares.insert(p);
		}
		//std::cout<<pallindromic_squares.size();
		long long* arr = new long long[pallindromic_squares.size()];
		int i = 0;
		for(std::set<long long>::iterator it = pallindromic_squares.begin(); it != pallindromic_squares.end(); it++,i++)
			arr[i] = (*it);

		for(int cs = 1; cs <= cases; cs++)
		{
			long long a,b;
			std::cin>>a>>b;
			unsigned int i = 0;
			while(arr[i] < a)
				i++;
			int count = 0;
			while(i < pallindromic_squares.size() && arr[i] <= b)
			{
				count++;
				i++;
			}
			if(i == pallindromic_squares.size())
			{
				std::cout<<"Problem";
				break;
			}
			std::cout<<"Case #"<<cs<<": "<<count<<std::endl;
		}
	}

	void fairandsquare_small()
	{
		int cases;
		std::cin>>cases;

		std::vector<int> pallindromic_squares;
		for(int i = 1; i <= 100000; i++)
		{
			int sqrt = (int)std::pow((double)i,0.5);
			if(sqrt*sqrt != i)
				continue;
			if(is_Pallindrome(i) && is_Pallindrome(sqrt))
				pallindromic_squares.push_back(i);
		}

		for(int cs = 1; cs <= cases; cs++)
		{
			unsigned long long a, b;
			std::cin>>a>>b;
			int i = 0;
			while(pallindromic_squares[i] < a)
				i++;
			//if(i) i--;
			int count = 0;
			while(pallindromic_squares[i] <= b)
			{
				//std::cout<<pallindromic_squares[i]<<"\t";
				count++;
				i++;
			}
			std::cout<<"Case #"<<cs<<": "<<count<<std::endl;
		}
	}

	bool traversal(std::multiset<int>& canopen,std::map<int, std::vector<int> >& graph, std::map<int, std::vector<int> >&keystochests, bool*opened, std::vector<int>& output, std::multiset<int> & keys,std::map<int,int>& cheststokeys)
	{
		bool allopened = true;
		for(unsigned int i = 0; i < graph.size(); i++)
		{
			if(!opened[i+1])
			{
				allopened = false;
				break;
			}
		}
		if(allopened)
			return true;
		if(canopen.size() == 0)
			return false;
		
		for(std::multiset<int>::iterator i = canopen.begin(); i != canopen.end();)
		{
			int it = (*i);
			if(opened[it])
			{
				i++;
				continue;
			}

			//canopen.erase(i++);
			int thiskey = cheststokeys[it];
			std::vector<int> thiskeychests = keystochests[thiskey];
			for(unsigned int abc = 0; abc < thiskeychests.size(); abc++)
			{
				canopen.erase(canopen.find(thiskeychests[abc]));
			}
			
			opened[it] = true;
			output.push_back(it);

			std::vector<int> newkeys = graph[it];
			for(unsigned int ki = 0; ki < newkeys.size(); ki++)
			{
				std::vector<int> chests = keystochests[newkeys[ki]];
				for(unsigned int jk = 0; jk < chests.size(); jk++)
					canopen.insert(chests[jk]);
			}
				
			if(traversal(canopen,graph,keystochests,opened,output,keys,cheststokeys))
				return true;
				
			for(unsigned int ki = 0; ki < newkeys.size(); ki++)
			{
				std::vector<int> chests = keystochests[newkeys[ki]];
				for(unsigned int jk = 0; jk < chests.size(); jk++)
					canopen.erase(canopen.find(chests[jk]));
			}
				
			opened[it] = false;
			output.pop_back();
			
			for(unsigned int abc = 0; abc < thiskeychests.size(); abc++)
			{
				canopen.insert(thiskeychests[abc]);
			}
			i = canopen.find(it);
			while(i != canopen.end() && (*i) == it)
				i++;
		}
		return false;
	}

	void treasure()
	{
		int cases;
		std::cin>>cases;
		for(int cs = 1; cs <= cases; cs++)
		{
			int numkeys,numchests;
			std::cin>>numkeys>>numchests;
			std::multiset<int> keys;
			std::map<int,int> cheststokeys;
			std::map<int,std::vector<int> > keystochests;
			std::map<int,std::vector<int> > graph;
			int key;
			for(int k = 0;k < numkeys; k++)
			{
				std::cin>>key;
				keys.insert(key);
			}
			for(int i = 1; i <= numchests; i++)
			{
				int numlinks = 0;
				key = 0;
				std::cin>>key>>numlinks;
				if(keystochests.find(key) == keystochests.end())
				{
					std::vector<int> temp;
					keystochests[key] = temp;
				}
				keystochests[key].push_back(i);
				cheststokeys[i] = key;
				std::vector<int> temp;
				int keylink;
				for(int j = 0; j < numlinks; j++)
				{
					std::cin>>keylink;
					temp.push_back(keylink);
				}
				graph[i]=temp;
			}
			std::vector<int> output;
			bool* opened = new bool[numchests + 1];
			std::memset(opened,0,(numchests+1)*sizeof(bool));
			std::multiset<int> canopen;
			for(std::multiset<int>::iterator it = keys.begin(); it != keys.end(); it++)
			{
				int key = (*it);
				std::vector<int> chests = keystochests[key];
				for(unsigned int i = 0; i < chests.size(); i++)
					canopen.insert(chests[i]);
			}


			if(traversal(canopen,graph,keystochests,opened,output,keys,cheststokeys))
			{
				std::cout<<"Case #"<<cs<<": ";
				for(unsigned int i = 0; i < output.size(); i++)
					std::cout<<output[i]<<" ";
				std::cout<<std::endl;
			}
			else
			{
				std::cout<<"Case #"<<cs<<": IMPOSSIBLE"<<std::endl;
			}
		}
	}

}

#endif