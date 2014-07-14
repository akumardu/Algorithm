#include<iostream>
#include<string>
#include<functional>
#include<map>
#include<set>
#include<vector>
#include "graph.h"
#include<math.h>
#include<Windows.h>
#include<climits>
#include<list>
#include<set>
#include "heap.h"
#include<stack>
#include<regex>
#include "algo_part2.h"

//When Help is required
/*import java.util.Scanner;

public class Solution {

    public static void main(String args[]) throws Exception {
        Scanner scanner = new Scanner(System.in);
        StringBuilder str = new StringBuilder();
        while (scanner.hasNextLine()) {
            str.append(scanner.nextLine()).append(" ");
        }

        scanner.close();
        throw new Exception(str.toString());
    }
}
*/
namespace eventree
{
	void find_eventree()
	{
		int numofNodes = 0, numofEdges = 0;
		std::cin>>numofNodes;
		std::cin>>numofEdges;
		graph* g = new graph(numofNodes);
		while(numofEdges)
		{
			numofEdges--;
			int vertexa=0,vertexb=0;
			std::cin>>vertexa;
			std::cin>>vertexb;
			vertexa--;
			vertexb--;
			g->addEdge(vertexa,vertexb,0);
			g->addEdge(vertexb,vertexa,0);
		}
		g->dfs();
		std::cout<<g->maxPossibleCuts()<<std::endl;
	}


}

namespace findstring
{
	void findString()
	{
		int cases = 0;
		std::cin>>cases;
		std::vector<std::string> actual;
		{
			//std::map<std::string,int> trymap;
			std::set<std::string> trySet;
			while(cases--)
			{
				std::string temp;
				std::cin>>temp;
				for(unsigned int i = 0; i < temp.size(); i++)
				{
					for(unsigned int j = i ; j < temp.size(); j++)
					{
						std::string input = temp.substr(i, j-i + 1);
						//trymap[input] = 0;
						trySet.insert(input);
					}
				}
			}
			//std::map<std::string,int>::iterator itr = trymap.begin();
			//while(itr != trymap.end())
			std::set<std::string>::iterator itr = trySet.begin();
			while(itr != trySet.end())
			{
				actual.push_back(*itr);
				itr++;
			}
		}
		unsigned long netSize = actual.size();
		unsigned long numquery = 0,query = 0;
		std::cin>>numquery;
		while(numquery--)
		{
			std::cin>>query;
			query--;
			if(query > netSize)
				std::cout<<"INVALID"<<std::endl;
			else
				std::cout<<actual[query]<<std::endl;
		}
	}
}

namespace quadrantqueries
{
	int ** segtree;
	void initialize_segment_tree(long arrysize)
	{
		int x = (int)std::ceil(std::log(double(arrysize))/std::log(2.0)) + 1;
		long size = 2* (int)std::powl((long)2,(long)x);
		segtree = new int*[size];
		for(long i = 0; i < size; i++)
			segtree[i] = new int[6];
		//memset(segtree,-1,sizeof(segtree[0][0])*size*6);
	}
	int find_quadrant(int** arryNum, long node)
	{
		if(arryNum[node][0] < 0 && arryNum[node][1] < 0)
			return 3;
		else if (arryNum[node][0] > 0 && arryNum[node][1] > 0)
			return 1;
		else if (arryNum[node][0] < 0 && arryNum[node][1] > 0)
			return 2;
		else if (arryNum[node][0] > 0 && arryNum[node][1] < 0)
			return 4;
		return -1;
	}
	void initialize(long node, long start, long end, int** arryNum)
	{
		if(start == end)
		{
			segtree[node][0] = 0;//X operation
			segtree[node][1] = 0;//Y operation
			segtree[node][2] = 0;// first quadrant
			segtree[node][3] = 0;// second
			segtree[node][4] = 0;// third
			segtree[node][5] = 0;// fourth
			//segtree[node][6] = 0;// lets see
			int x = find_quadrant(arryNum,start);
			switch(x)
			{
			case 1:
				segtree[node][2] = 1;
				break;
			case 2:
				segtree[node][3] = 1;
				break;
			case 3:
				segtree[node][4] = 1;
				break;
			case 4:
				segtree[node][5] = 1;
				break;
			}
		}
		else
		{
			int mid = start + (end - start)/2;
			initialize(2*node,start,mid,arryNum);
			initialize(2*node + 1 , mid+ 1, end, arryNum);
			segtree[node][2] = segtree[2*node][2] + segtree[2*node + 1][2];
			segtree[node][3] = segtree[2*node][3] + segtree[2*node + 1][3];
			segtree[node][4] = segtree[2*node][4] + segtree[2*node + 1][4];
			segtree[node][5] = segtree[2*node][5] + segtree[2*node + 1][5];
		}
	}
	void queryAndUpdate(long node, long start, long end, long i, long j, char update, long* result)
	{
		if(segtree[node][0] != 0 || segtree[node][1] != 0)
		{
			if(start != end)
			{
				segtree[2*node][0] += segtree[node][0];
				segtree[2*node + 1][0] += segtree[node][0];
				segtree[2*node][1] += segtree[node][1];
				segtree[2*node + 1][1] += segtree[node][1];
			}
			if(segtree[node][0]%2 != 0)
			{
				int temp = segtree[node][2];
				segtree[node][2] = segtree[node][5];
				segtree[node][5] = temp;
				temp = segtree[node][3];
				segtree[node][3] = segtree[node][4];
				segtree[node][4] = temp;
			}
			if(segtree[node][1]%2 != 0)
			{
				int temp = segtree[node][2];
				segtree[node][2] = segtree[node][3];
				segtree[node][3] = temp;
				temp = segtree[node][5];
				segtree[node][5] = segtree[node][4];
				segtree[node][4] = temp;
			}
			segtree[node][0] = 0;
			segtree[node][1] = 0;
		}

		if(i > end || j < start)
			return;
		if(start >= i && end <= j)
		{
			if(update == 'X')
			{
				if(start != end)
				{
					segtree[2*node][0]++;
					segtree[2*node + 1][0]++;
				}
				int temp = segtree[node][2];
				segtree[node][2] = segtree[node][5];
				segtree[node][5] = temp;
				temp = segtree[node][3];
				segtree[node][3] = segtree[node][4];
				segtree[node][4] = temp;
			}
			else if (update == 'Y')
			{
				if(start != end)
				{
					segtree[2*node][1]++;
					segtree[2*node + 1][1]++;
				}
				int temp = segtree[node][2];
				segtree[node][2] = segtree[node][3];
				segtree[node][3] = temp;
				temp = segtree[node][5];
				segtree[node][5] = segtree[node][4];
				segtree[node][4] = temp;
			}
			else if(update == 'C')
			{
				result[0] += segtree[node][2];
				result[1] += segtree[node][3];
				result[2] += segtree[node][4];
				result[3] += segtree[node][5];
			}
			return;
		}

		int mid = start + (end - start)/2;
		queryAndUpdate(2*node,start,mid,i,j,update,result);
		queryAndUpdate(2*node+1,mid+1,end,i,j,update,result);

		segtree[node][2] = segtree[2*node][2] + segtree[2*node + 1][2];
		segtree[node][3] = segtree[2*node][3] + segtree[2*node + 1][3];
		segtree[node][4] = segtree[2*node][4] + segtree[2*node + 1][4];
		segtree[node][5] = segtree[2*node][5] + segtree[2*node + 1][5];

	}
	void quadrant()
	{
		long points = 0;
		std::cin>>points;
		int ** arryNum;
		arryNum = new int*[points];
		for(long i = 0; i < points; i++)
			arryNum[i] = new int[2];
		for(long i = 0; i < points; i++)
		{
			std::cin>>arryNum[i][0];
			std::cin>>arryNum[i][1];
		}
		/*for(long i = 0; i < points; i++)
		{
			std::cout<<arryNum[i][0]<<" "<<arryNum[i][1]<<std::endl;
		}*/
		initialize_segment_tree(points);
		initialize(1,0,points-1,arryNum);
		long queries=0,begin=0,end=0;
		char update = 'X';
		std::cin>>queries;
		while(queries--)
		{
			std::cin>>update;
			std::cin>>begin;
			std::cin>>end;
			begin--;
			end--;
			if(update == 'C')
			{
				long *result = new long[4];
				std::memset(result,0,sizeof(long)*4);
				queryAndUpdate(1,0,points-1,begin,end,update,result);
				std::cout<<result[0]<<" "<<result[1]<<" "<<result[2]<<" "<<result[3]<<std::endl;
			}
			else
			{
				queryAndUpdate(1,0,points-1,begin,end,update,NULL);
			}
		}
	}
}

namespace stringsimilarity
{
	bool filltable(std::string& input,int* table, int start, int end)
	{
		long i = start,j = 0;
		bool changes = false;
		while( i <= end)
			{
				if(input[i] == input[j])
				{
					j++;
					table[i] = j;
					i++;
					changes = true;
				}
				else if(j > 0)
					j = table[j-1];
				else
				{
					table[i] = 0;
					i++;
				}
			}
		return changes;
	}
	void detect_changes(std::string& input, int* table,long start, long end)
	{
		bool changes = false;
		changes = filltable(input,table,start,end);
		/*for(long i = 0; i < input.size(); i++)
			std::cout<<table[i]<<" ";
		std::cout<<std::endl;*/
		if(changes)
		{
			for(long i = start;i <= end; i++)
			{
				if(table[i]>1)
				{
					//int value = table[i];
					int start = i;
					int temp = table[i];
					while(i<=end && table[i]>table[i-1])
					{
						temp = table[i];
						//table[i] = 0;
						i++;
					}
					
					table[start-1] = temp;
					while(i <= end && table[i]>0) i++;
					if(i > end) 
					{
						i--;
					}
						for(int j = start; j <=i; j++)
							table[j] = 0;
						detect_changes(input,table,start,i);
					
				}
			}
		}
		
	}
	void similarity()
	{
		int cases = 0;
		std::cin>>cases;
		while(cases--)
		{
			std::string input;
			std::cin>>input;
			int* table = new int[input.size()];
			std::memset(table,0,sizeof(int)*input.size());
			long i = 1,j = 0;
			table[0] = 0;
			
			

			detect_changes(input,table,1,input.size()-1);

			for(unsigned long i = 0; i < input.size(); i++)
				std::cout<<table[i]<<" ";
			std::cout<<std::endl;

			long sum = 0;
			for(long i = input.size() - 1;i >=0; i--)
			{
				sum += table[i];
			}
			sum += input.size();
			std::cout<<sum<<std::endl;
		}
	}
}

namespace xorekey
{
	unsigned short * segtree;
	void initialize_segment_tree(long arrysize)
	{
		int x = (int)std::ceil(std::log(double(arrysize))/std::log(2.0)) + 1;
		long size = 2* (int)powl((long)2,(long)x);
		segtree = new unsigned short[size];
		//for(long i = 0; i < size; i++)
		//{
		//	segtree[i] = new int[17];
			std::memset(segtree,0,size*sizeof(unsigned short));
			/*for(int j = 0; j < 17; j++)
				segtree[i][j] = 0;*/
		//}
	}
	void reinitialize(long arrysize)
	{
		int x = (int)std::ceil(std::log(double(arrysize))/std::log(2.0)) + 1;
		long size = 2* (int)powl((long)2,(long)x);
		//for(long i = 0; i < size; i++)
		//{
			std::memset(segtree,0,size*sizeof(unsigned short));
			/*for(int j = 0; j < 17; j++)
				segtree[i][j] = 0;*/
		//}
	}

	bool getBit(int v, int bit)
    {
            return ((v >> bit) & 0x1) > 0;
    }

	void initialize(long node, long start, long end, unsigned short* arryNum)
	{
		if(start == end)
		{
			segtree[node] = arryNum[start];
			//segtree[node][0] = 1;
			//for(int j = 0; j < 16; j++)
			//{
			//	if(getBit(arryNum[start],j))
			//		segtree[node][j+1]=1;
			//}
			
		}
		else
		{
			int mid = start + (end - start)/2;
			initialize(2*node,start,mid,arryNum);
			initialize(2*node + 1 , mid+ 1, end, arryNum);
			//for(int j = 0; j < 17; j++)
			segtree[node] = segtree[2*node] | segtree[2*node + 1];
		}
	}
	void queryAndUpdate(long node, long start, long end, long i, long j, short value, unsigned short* result, unsigned short* arrynum, unsigned short *maxbit)
	{

		if(i > end || j < start)
			return;
		if(start >= i && end <= j)
		{
			if(start == end)
			{
				if((value ^ arrynum[start]) > (*result))
					(*result) = value ^ arrynum[start];
				return;
			}
			else
			{
				//finding max xore
				int maxlocal = 0;
				unsigned short temp = value ^ segtree[node];
				for(int i = 15; i >= 0 ; i--)
				{
					if(!getBit(temp,i))
						continue;
					maxlocal = i;
					break;
				}
				if((*maxbit) != 16 && (*maxbit) > maxlocal)
				{
					//std::cout<<"at least once"<<std::endl;
					return;
				}
				(*maxbit) = maxlocal;
			}
			//return;
		}

		int mid = start + (end - start)/2;
		queryAndUpdate(2*node,start,mid,i,j,value, result, arrynum, maxbit);
		queryAndUpdate(2*node+1,mid+1,end,i,j,value, result, arrynum, maxbit);
	}

	void segmented_xore()
	{
		int cases = 0;
		std::cin>>cases;
		initialize_segment_tree(100000);
		unsigned short * arr = new unsigned short[100000];
		while(cases--)
		{
			int total_numbers = 0, queries = 0, number = 0;
			std::cin>>total_numbers;
			std::cin>>queries;
			//initialize_segment_tree(total_numbers);
			//short * arr = new short[total_numbers];
			for(int i = 0 ; i < total_numbers; i++)
			{
				std::cin>>arr[i];
			}
			initialize(1,0,total_numbers-1,arr);
			while(queries--)
			{
				int query=0,limita=0,limitb=0;
				std::cin>>query;
				std::cin>>limita;
				std::cin>>limitb;
				limita--;
				limitb--;
				if((limitb - limita) <= 15)
				{
					int max = 0;
					for(int i = limita ; i <= limitb; i++)
					{
						if((query ^ arr[i]) > max)
						{
							max = query ^ arr[i];
						}
					}
					std::cout<<max<<std::endl;
					continue;
				}
				else
				{
					unsigned short result = 0, maxbit = 16;
					queryAndUpdate(1,0,total_numbers-1,limita,limitb,query,&result,arr,&maxbit);
					std::cout<<result<<std::endl;
				}
			}
			if(cases)
				reinitialize(total_numbers);
		}
	}

	int binary_search_first(short* arr, int value, int length)
	{
		int low = 0, high = length-1, med = 0;
		while(low <= high)
		{
			med = (low + high)/2;
			if(arr[med] == value) return med;
			//else if(arr[med] < value && arr[med + 1] >= value) return med + 1;
			else if(arr[med] < value) low = med + 1;
			else high = med - 1;
		}
		if(low <= 0 && high <= 0)
			return 0;
		if(low >= (length-1) && high >= (length-1))
			return -1;
		if(low > high)
			return low;
		return 0;
	}
	int binary_search_second(short* arr, int value, int length)
	{
		int low = 0, high = length-1, med = 0;
		while(low <= high)
		{
			med = (low + high)/2;
			if(arr[med] == value) return med;
			//else if(arr[med-1] <= value && arr[med] > value) return med;
			else if(arr[med] < value) low = med + 1;
			else high = med - 1;
		}
		if(low >= (length-1) && high >= (length -1))
			return length -1 ;
		if(low<= 0 && high <=0)
			return -1;
		if(high < low)
			return high;
		return length-1;
	}

	void straight_xore()
	{
		int cases = 0;
		std::cin>>cases;
		while(cases--)
		{
			int total_numbers = 0, queries = 0, number = 0;
			std::cin>>total_numbers;
			std::cin>>queries;
			short * arr = new short[total_numbers];
			for(int i = 0 ; i < total_numbers; i++)
			{
				std::cin>>arr[i];
			}
			while(queries--)
			{
				int query=0,limita=0,limitb=0;
				std::cin>>query;
				std::cin>>limita;
				std::cin>>limitb;
				limita--;
				limitb--;
				int max = 0, best = 0,index = 0;
				for(int i = limita ; i <= limitb; i++)
				{
					if((query ^ arr[i]) > max)
					{
						max = query ^ arr[i];
						best = arr[i];
						index = i;
					}
				}
				std::cout<<max<<std::endl;
			}
		}
	}

	void xorekey()
	{
		int cases = 0;
		std::cin>>cases;
		while(cases--)
		{
			int total_numbers = 0, queries = 0, number = 0;
			std::cin>>total_numbers;
			std::cin>>queries;
			short * arr = new short[total_numbers];
			int* set = new int[16];
			int* counter = new int[32];
			std::memset(set,0,sizeof(int)*16);
			std::memset(counter,0,sizeof(int)*32);
			short * bigarr = new short[total_numbers * 16];
			//initialize_segment_tree(total_numbers);
			for(int i = 0 ; i < total_numbers; i++)
			{
				std::cin>>number;
				for(int index = 0 ; index < 16 ; index++)
				{
					if(getBit(number,index))
						set[index]++;
				}
				arr[i] = number;
			}

			
			for(int i = 0 ; i < total_numbers; i++)
			{
				for(int index = 0 ; index < 16; index++)
					if(getBit(arr[i],index))
					{
						bigarr[index*total_numbers + counter[2*index]] = i;
						counter[2*index]++;
					}
					else
					{
						bigarr[index*total_numbers + set[index] + counter[2*index + 1]] = i;
						counter[2*index + 1]++;
					}
			}
			
			for(int i = 0; i < total_numbers;i++)
					std::cout<<i<<" ";
				std::cout<<std::endl;

			for( int j = 0; j < 16 ; j++)
			{
				for(int i = 0; i < total_numbers;i++)
					std::cout<<bigarr[j* total_numbers + i]<<" ";
				std::cout<<std::endl;
			}
			

			while(queries--)
			{
				int query = 0, limita = 0, limitb = 0;
				std::cin>>query;
				std::cin>>limita;
				std::cin>>limitb;
				limita--;
				limitb--;
				if(limitb - limita < 10)
				{
					int max = 0;
					for(int i = limita ; i <= limitb; i++)
					{
						if((query ^ arr[i]) > max)
							max = query ^ arr[i];
					}
					std::cout<<max<<std::endl;
				}
				else
				{
					int tempa=0,tempb = 0;
					for(int i = 15 ; i >=0 ; i--)
					{
						std::cout<<limita<<" : "<<limitb<<std::endl;
						if(getBit(query,i))
						{
							tempa = binary_search_first(bigarr + i*total_numbers + set[i],limita,total_numbers - set[i]);
							if(tempa <= -1)
								continue;
							tempa = bigarr[i*total_numbers + set[i] + tempa];
							tempb = binary_search_second(bigarr + i*total_numbers + set[i], limitb , total_numbers - set[i]);
							if(tempb <= -1)
								continue;
							tempb = bigarr[i*total_numbers + set[i] + tempb];
							if(tempa > tempb)
								continue;
							limita = tempa;
							limitb = tempb;
							if((limitb - limita) <= 5) break;
						}
						else
						{
							tempa = binary_search_first(bigarr + i*total_numbers,limita,set[i]);
							if(tempa <= -1)
								continue;
							tempa = bigarr[i*total_numbers + tempa];
							tempb = binary_search_second(bigarr + i*total_numbers, limitb , set[i]);
							if(tempb <= -1)
								continue;
							tempb = bigarr[i*total_numbers + tempb];
							if(tempa > tempb)
								continue;
							limita = tempa;
							limitb = tempb;
							if((limitb - limita) <= 5) break;
						}
					}

					int max = 0, best = 0;
					for(int i = limita ; i <= limitb; i++)
					{
						if((query ^ arr[i]) > max)
						{
							max = query ^ arr[i];
							best = arr[i];
						}
					}
					std::cout<<max<<" : "<<best<<std::endl;
					
				}
			}
			delete[] counter;
			delete[] bigarr;
			delete[] arr;
			delete[] set;
		}
	}
}

namespace pairs
{
	void pairs()
	{
		unsigned long n=0,k=0;
		std::cin>>n;
		std::cin>>k;
		unsigned long* a = new unsigned long[n];
		for(unsigned long i = 0; i < n ; i++)
			std::cin>>a[i];
		unsigned long count = 0;
		std::sort(a,a+n);          //#include <algorithm>
		if(a[n] - a[0] < k)         //a[]
		std::cout<<0<<std::endl;
		else
		{
		  for(long long i = n-1;i>=0;i--)
			{ // cout<<"1";
			  for(long long j = i - 1;j >= 0;j--)
				{
				   if( a[i] - a[j] > k)
				   break;
				   else if((a[i]-a[j])==k)
				   count++;
				}
			}
		std::cout<<count<<std::endl;
		}

	}
}

namespace onemorexore
{
	unsigned short * segtree;
	void initialize_segment_tree(long arrysize)
	{
		int x = (int)std::ceil(std::log(double(arrysize))/std::log(2.0)) + 1;
		long size = 2* (int)powl((long)2,(long)x);
		segtree = new unsigned short[size];
		//for(long i = 0; i < size; i++)
		//{
		//	segtree[i] = new int[17];
			std::memset(segtree,0,size*sizeof(unsigned short));
			/*for(int j = 0; j < 17; j++)
				segtree[i][j] = 0;*/
		//}
	}
	void reinitialize(long arrysize)
	{
		int x = (int)std::ceil(std::log(double(arrysize))/std::log(2.0)) + 1;
		long size = 2* (int)powl((long)2,(long)x);
		//for(long i = 0; i < size; i++)
		//{
			std::memset(segtree,0,size*sizeof(unsigned short));
			/*for(int j = 0; j < 17; j++)
				segtree[i][j] = 0;*/
		//}
	}

	bool getBit(int v, int bit)
    {
            return ((v >> bit) & 0x1) > 0;
    }

	void initialize(long node, long start, long end, unsigned short* arryNum)
	{
		if(start == end)
		{
			segtree[node] = arryNum[start];
			//segtree[node][0] = 1;
			//for(int j = 0; j < 16; j++)
			//{
			//	if(getBit(arryNum[start],j))
			//		segtree[node][j+1]=1;
			//}
			
		}
		else
		{
			int mid = start + (end - start)/2;
			initialize(2*node,start,mid,arryNum);
			initialize(2*node + 1 , mid+ 1, end, arryNum);
			//for(int j = 0; j < 17; j++)
			segtree[node] = segtree[2*node] | segtree[2*node + 1];
		}
	}
	void queryAndUpdate(long node, long start, long end, long i, long j, short value, unsigned short* result, unsigned short* arrynum, unsigned short *maxbit)
	{

		if(i > end || j < start)
			return;
		if(start >= i && end <= j)
		{
			if(start == end)
			{
				if((value ^ arrynum[start]) > (*result))
					(*result) = value ^ arrynum[start];
				return;
			}
			else
			{
				//finding max xore
				int maxlocal = 0;
				unsigned short temp = value ^ segtree[node];
				for(int i = 15; i >= 0 ; i--)
				{
					if(!getBit(temp,i))
						continue;
					maxlocal = i;
					break;
				}
				if((*maxbit) != 16 && (*maxbit) > maxlocal)
				{
					//std::cout<<"at least once"<<std::endl;
					return;
				}
				(*maxbit) = maxlocal;
			}
			//return;
		}

		int mid = start + (end - start)/2;
		queryAndUpdate(2*node,start,mid,i,j,value, result, arrynum, maxbit);
		queryAndUpdate(2*node+1,mid+1,end,i,j,value, result, arrynum, maxbit);
	}

	void segmented_xore()
	{
		int cases = 0;
		std::cin>>cases;
		initialize_segment_tree(100000);
		unsigned short * arr = new unsigned short[100000];
		while(cases--)
		{
			int total_numbers = 0, queries = 0, number = 0;
			std::cin>>total_numbers;
			std::cin>>queries;
			//initialize_segment_tree(total_numbers);
			//short * arr = new short[total_numbers];
			for(int i = 0 ; i < total_numbers; i++)
			{
				std::cin>>arr[i];
			}
			initialize(1,0,total_numbers-1,arr);
			while(queries--)
			{
				int query=0,limita=0,limitb=0;
				std::cin>>query;
				std::cin>>limita;
				std::cin>>limitb;
				limita--;
				limitb--;
				if((limitb - limita) <= 15)
				{
					int max = 0;
					for(int i = limita ; i <= limitb; i++)
					{
						if((query ^ arr[i]) > max)
						{
							max = query ^ arr[i];
						}
					}
					std::cout<<max<<std::endl;
					continue;
				}
				else
				{
					unsigned short result = 0, maxbit = 16;
					queryAndUpdate(1,0,total_numbers-1,limita,limitb,query,&result,arr,&maxbit);
					std::cout<<result<<std::endl;
				}
			}
			if(cases)
				reinitialize(total_numbers);
		}
	}

	void try_xoree()
	{
		//Sleep(10000);
		int cases;
		std::cin>>cases;
		
		while(cases--)
		{
			long total_numbers=0,queries = 0;
			std::cin>>total_numbers;
			std::cin>>queries;
			std::vector<int> *tree = new vector<int>[65536];
			std::vector<int> data;
			int num;
			for(int i = 0; i < total_numbers; i++)
			{
				std::cin>>num;
				data.push_back(num);
				//tree[num + 32768].push_back(i);
				int node = 1;
				for(int j = 14 ; j >=0; j--)
				{
					//tree[node].push_back(i);
					if(getBit(num,j))
					{
						node = 2*node;
					}
					else
					{
						node = 2*node + 1;
					}
					tree[node].push_back(i);
				}
			}
			
			while(queries--)
			{
				int query=0,limita=0,limitb=0;
				std::cin>>query;
				std::cin>>limita;
				std::cin>>limitb;
				limita--;
				limitb--;
				if(limita == limitb)
				{
					std::cout<<(query^data[limita])<<std::endl;
					continue;
				}
				
				bool notfound = true;
				int j = 14,node = 1;
				bool lookedp = false,lookedn = false;
				int result = 0;
				while(j >=0)
				{
					bool bitquery = getBit(query,j);
					if(lookedp && lookedn)
					{
						lookedp = false;
						lookedn = false;
					}
					if((bitquery && !lookedp) || (!bitquery && lookedn))
					{
						node = 2*node + 1;
						lookedp = true;
						int length = tree[node].size();
						if(length == 0)
						{
							node = node/2;
							continue;
						}
						else if(length == 1)
						{
							if(tree[node][0] >= limita && tree[node][0] <=limitb)
							{
								//result = result << 1;
								//if(!lookedn || !j)
									break;
							}
							node = node/2;
							continue;
						}
						else if(limita < tree[node][0] && limitb < tree[node][0])
						{
							node = node/2;
							continue;
						}
						else if( limita > tree[node][length-1] && limitb > tree[node][length - 1])
						{
							node = node/2;
							continue;
						}
						else if( limita < tree[node][0] && limitb > tree[node][length - 1])
						{
							j--;
							lookedp = false;
							lookedn = false;
							continue;

						}
						int low = 0, high = length-1, med = 0,limita_temp=-1,limitb_temp = -1;
						while(low <= high)
						{
							med = (low + high)/2;
							if(tree[node][med] == limita) { limita_temp = med; break;}
							else if(tree[node][med] < limita) low = med + 1;
							else high = med - 1;
						}

						if(limita_temp == -1 && low > high)
							limita_temp = low;
						if(limita < tree[node][0]) limita_temp = -1;
						low = 0, high = length-1, med = 0;
						while(low <= high)
						{
							med = (low + high)/2;
							if(tree[node][med] == limitb) { limitb_temp = med; break;}
							else if(tree[node][med] < limitb) low = med + 1;
							else high = med - 1;
						}

						if(limitb_temp == -1 && low > high)
							limitb_temp = low;
						if(limitb > tree[node][length - 1]) limitb_temp = length;
						if((limita_temp == -1 && limitb_temp == -1) || (limita_temp == length && limitb_temp == length))
						{
							node = node/2;
							continue;
						}
						if(limitb_temp == limita_temp && tree[node][limitb_temp] <= limitb && tree[node][limita_temp] >= limita)
						{
							result = limita_temp;
							if(!lookedn)
								break;
						}
						if(limitb_temp == (limita_temp + 1))
						{
							//result = result<<1;
							result = limita_temp;
							if(!lookedn)
								break;
						}
						//else
						if(limitb_temp > limita_temp)
						{
							//result = result << 1;
							//result = result | 0x1;
							j--;
							lookedp = false;
							lookedn = false;
							continue;
						}
						
						node = node/2;
						

					}
					else if(( !lookedn && !bitquery) || (lookedp && bitquery))
					{
						node = 2* node;
						lookedn = true;
						int length = tree[node].size();
						if(length == 0)
						{
							node = node/2;
							continue;
						}
						else if(length == 1)
						{
							if(tree[node][0] >= limita && tree[node][0] <=limitb)
							{
								//result = result <<1;
								//result = result | 0x1;
								//if(!lookedp || !j)
									break;
							}
							node = node/2;
						
							continue;
						}
						else if(limita < tree[node][0] && limitb < tree[node][0])
						{
							node = node/2;
						
							continue;
						}
						else if( limita > tree[node][length-1] && limitb > tree[node][length - 1])
						{
							node = node/2;
						
							continue;
						}
						else if( limita < tree[node][0] && limitb > tree[node][length - 1])
						{
							
							j--;
							lookedp = false;
							lookedn = false;
							continue;

						}
						int low = 0, high = length-1, med = 0,limita_temp=-1,limitb_temp = -1;
						while(low <= high)
						{
							med = (low + high)/2;
							if(tree[node][med] == limita) { limita_temp = med; break;}
							else if(tree[node][med] < limita) low = med + 1;
							else high = med - 1;
						}

						if(limita_temp == -1 && low > high)
							limita_temp = low;
						if(limita < tree[node][0]) limita_temp = -1;
						low = 0, high = length-1, med = 0;
						while(low <= high)
						{
							med = (low + high)/2;
							if(tree[node][med] == limitb) { limitb_temp = med; break;}
							else if(tree[node][med] < limitb) low = med + 1;
							else high = med - 1;
						}

						if(limitb_temp == -1 && low > high)
							limitb_temp = low;
						if(limitb > tree[node][length - 1]) limitb_temp = length;
						if((limita_temp == -1 && limitb_temp == -1) || (limita_temp == length && limitb_temp == length))
						{
							node = node/2;
							continue;
						}
						if(limitb_temp == limita_temp && tree[node][limitb_temp] <= limitb && tree[node][limita_temp] >= limita)
						{
							result = limita_temp;
							if(!lookedp)
								break;
						}
						 if(limitb_temp == (limita_temp + 1))
						{
							//result = result <<1;
							//result = result | 0x1;
							result = limita_temp;
							if(!lookedp)
								break;
						}
						//else 
						if(limitb_temp > limita_temp)
						{
							//result = result <<1;
							//result = result | 0x1;
							j--;
							lookedp = false;
							lookedn = false;
							continue;
						}
						
						node = node/2;
						
					}
					else
					{
						j--;
					}


				}
				//std::cout<<data[tree[node][0]]<<std::endl;
				//std::cout<<node<<" : ";
				//result = data[tree[node][0]];
				int len = tree[node].size();
				/*for(int i = 0; i < len; i++)
					if(tree[node][i] <= limitb && tree[node][i] >= limita)
						std::cout<<data[tree[node][i]]<<" : ";*/
				/*if(counter == 914)
				std::cout<<result<<" : " <<len<<" : "<<tree[node][0]<<" : ";*/
				if(len > 1)
				{
					if(result<0)
					{
						result = data[tree[node][0]];
					//std::cout<<tree[node].size()<<" : "<<tree[node][0]<<" : "<<result<<" : ";
					std::cout<<(result^query)<<std::endl;
					}
					else if(result >= len)
					{
						result = data[tree[node][len -1]];
						std::cout<<(result^query)<<std::endl;
					}
					else
					{

						int low = 0, high = len-1, med = 0,limita_temp=-1,limitb_temp = -1;
						while(low <= high)
						{
							med = (low + high)/2;
							if(tree[node][med] == limita) { limita_temp = med; break;}
							else if(tree[node][med] < limita) low = med + 1;
							else high = med - 1;
						}

						if(low > high)
							limita_temp = low;
						if(limita < tree[node][0]) limita_temp = 0;
						low = 0, high = len-1, med = 0;
						while(low <= high)
						{
							med = (low + high)/2;
							if(tree[node][med] == limitb) { limitb_temp = med; break;}
							else if(tree[node][med] < limitb) low = med + 1;
							else high = med - 1;
						}

						if(low > high)
							limitb_temp = low;
						if(limitb > tree[node][len - 1]) limitb_temp = len-1;
						if(limita_temp >= (len-1) )limita_temp = len - 1;
						if(limitb_temp < 0) limitb_temp = 0;

						int max_xore = 0,index = 0,best = 0;
						for(int x = limita_temp; x <= limitb_temp; x++)
						{
							if(tree[node][x] <= limitb && tree[node][x] >= limita && (data[tree[node][x]] ^ query) > max_xore)
							{
								//std::cout<<data[tree[node][x]]<<" : ";
								index = tree[node][x];
								best = data[tree[node][x]];
								max_xore = data[tree[node][x]] ^ query;
							}
						}
						std::cout<<max_xore<<std::endl;//<<" : "<<best<<" : "<<index<<std::endl;
						
						
					}

				}
				else
				{
					result = data[tree[node][0]];
					//std::cout<<tree[node].size()<<" : "<<tree[node][0]<<" : "<<result<<" : ";
					std::cout<<(result^query)<<std::endl;
				}
			}
			delete[] tree;

		}
	}
}

namespace meetingpoint
{
	long long distance(long long x1, long long y1, long long x2, long long y2)
	{
		long long absx = std::abs(x2-x1);
		long long absy = std::abs(y2-y1);
		return (absx>absy)?absx:absy;
	}

	void straight_meeting(long long** arr, unsigned int points)
	{
		long long** dArray = new long long*[points];
		for(long long i = 0; i < points; i++)
		{
			dArray[i] = new long long[points];
			std::memset(dArray[i],0,sizeof(long long)*points);
		}
		long long min = ULONG_MAX, temp = 0;;
		for(long long i = 0 ; i < points; i++)
		{
			long long sum = 0;
			for(long long j = 0 ; j < points; j++)
			{
				if(i == j)
					continue;
				if(dArray[i][j])
					sum += dArray[i][j];
				else
				{
					temp = distance(arr[i][0],arr[i][1],arr[j][0],arr[j][1]);
					sum += temp;
					dArray[i][j] = temp;
					dArray[j][i] = temp;
				}
			}
			if(sum < min)
				min = sum;
		}
		std::cout<<min<<std::endl;
	}

	void arithmetic_meeting( long** arr, long long points)
	{
		long double ave_x=0,ave_y = 0;
		for(long long i = 0 ; i < points; i++)
		{
			ave_x += (long double)arr[i][0]/points;
			ave_y += (long double)arr[i][1]/points;
		}
		long double min = std::sqrt((ave_x-arr[0][0])*(ave_x-arr[0][0]) + (ave_y-arr[0][1])*(ave_y-arr[0][1]));
		
		long long index = 0,sec_index = 0;
		for(long long i = 1; i < points; i++)
		{
			long double diff = std::sqrt((ave_x-arr[i][0])*(ave_x-arr[i][0]) + (ave_y-arr[i][1])*(ave_y-arr[i][1]));
			if(diff < min)
			{
				index = i;
				min = diff;
			}
		}
		long long sum = 0;
		for(long long i = 0; i < points; i++)
			sum += distance(arr[i][0],arr[i][1],arr[index][0],arr[index][1]);
		std::cout<<sum<<std::endl;
	}
	void meeting()
	{
		long points = 0;
		std::cin>>points;
		long **arr = new long* [points];
		for(long i = 0; i < points; i++)
		{
			arr[i] = new long[2];
			std::cin>>arr[i][0];
			std::cin>>arr[i][1];
		}
		arithmetic_meeting(arr,points);
	}
}

namespace unfriendly
{
	long long gcd(long long a, long long b)
	{
		if(a == 0) return b;
		if(b == 0) return a;

		if( a > b) {
			return gcd(b,a%b);
		}
		else
		{
			return gcd(a,b%a);
		}
	}
	void factors(long long n, std::list<long long>& vec)
	{
		long long sq = (long long)std::sqrt((long double)n);
		std::list<long long> temp;
		for(long long i = 2 ; i <= sq ; i++)
		{
			if(!(n%i))
			{
				vec.push_back(i);
				if( i != (n/i))
					temp.push_front(n/i);
			}
		}
		temp.push_back(n);
		vec.merge(temp);
	}
	void unfriendly()
	{
		long long n=0,k=0,temp=0;
		std::cin>>n;
		std::cin>>k;
		std::list<long long> fac;
		factors(k,fac);
		//fac.sort();
		std::set<long long> arr;
		for(long long i = 0 ; i < n ; i++)
		{
			std::cin>>temp;
			arr.insert(gcd(k,temp));
			if(temp == k)
			{
				std::cout<<0<<std::endl;
				return;
			}
		}
		
		for( std::set<long long>::iterator i = arr.begin(); i != arr.end(); i++)
		{
			
			if(fac.size() == 0)
				break;
			std::list<long long>::iterator it = fac.begin();
			for(; it != fac.end(); )
			{
				if((*i) < (*it))
					break;
				if(((*i) % (*it)) == 0)
				{
					it = fac.erase(it);
				}
				else
					it++;
			}
		}
		
		std::cout<<fac.size()<<std::endl;
	}
	void dumpPrimes()
	{
		int n = 1000000;
		std::vector<long long> primes;
		bool* ok = new bool[n];
		std::memset(ok,0,n*sizeof(bool));
        for (long long i = 2; i < n; ++i) // primes up to 1000000 (only need up to sqrt of 1 000 000 actually)
        {
            if (!ok[i])
            {
                primes.push_back(i);

                for (long long j = i; j < n; j += i)
                    ok[j] = true;
            }
        }
		std::cout<<primes.size()<<std::endl;
		/*for(long long i = 0; i < primes.size(); i++)
			std::cout<<primes[i]<<std::endl;*/
	}
}

namespace stonepiles
{
	const int MAX = 51;
	std::vector<vector<int> > out[MAX];
	std::vector<int> table;
	void decompose(int n0, int n, vector<int>& seq, int last)
	{
		if(n == 0 && seq.size() > 1)
		{
			out[n0].push_back(seq);
			return;
		}
		for( int i = last+1; i < (n+1); i++)
		{
			seq.push_back(i);
			decompose(n0,n-i,seq,i);
			seq.pop_back();
		}
	}
	void compute()
	{
		for(int i = 3; i < MAX; i++)
		{
			vector<int> seq;
			decompose(i,i,seq,0);
		}
	}
	int findmex(vector<int> & mex)
	{
		for(int i = 0 ; i < MAX; i++)
		{
			bool found = false;
			for(unsigned int j = 0; j < mex.size(); j++)
			{
				if(i == mex[j])
				{
					found = true;
					break;
				}
			}
			if(found == false)
				return i;
		}
		return 0;
	}
	void filltable()
	{
		table.push_back(0);
		table.push_back(0);
		table.push_back(0);
		table.push_back(1);
		for(int i = 4; i < MAX; i++)
		{
			vector<vector<int> > seq = out[i];
			vector<int> mex;
			for(unsigned int j = 0 ; j < seq.size(); j++)
			{
				int ans = 0;
				for(unsigned int k = 0; k < seq[j].size(); k++)
				{
					ans = ans ^ table[seq[j][k]];
				}
				mex.push_back(ans);
			}
			table.push_back(findmex(mex));
		}
	}
	void stonepiles()
	{
		int cases;
		std::cin>>cases;
		compute();
		filltable();
		while(cases--)
		{
			int numpiles = 0;
			std::cin>>numpiles;
			int temp=0,ans=0;
			for(int i = 0; i < numpiles ; i++)
			{
				std::cin>>temp;
				ans = ans^table[temp];
			}
			if(ans == 0)
				std::cout<<"BOB"<<std::endl;
			else
				std::cout<<"ALICE"<<std::endl;
		}
	}
}

namespace equations
{
	void equations()
	{
		long n = 0;
		std::cin>>n;
		std::vector<long long> primes;
		bool* ok = new bool[n+1];
		std::memset(ok,0,(n+1)*sizeof(bool));
        for (int i = 2; i <= n; ++i) // primes up to 10 00 000 (only need up to sqrt of 1 000 000 actually)
        {
            if (!ok[i])
            {
				//if(n%i == 0)
				primes.push_back(i);

                for (int j = i; j <= n; j+=i)
                    ok[j] = true;
            }
        }
		long long result = 1,pow = 0;
		for(unsigned int i = 0; i < primes.size(); i++)
		{
			long long temp = n,div = primes[i];
			pow = 0;
			while(temp != 0)
			{
				pow = pow + (temp/div);
				temp = temp/div;
			}
			result = (result * (1+2*pow))%1000007;
		}
		std::cout<<(result%1000007)<<std::endl;
	}
}

namespace stringreduction
{
	int find_result(int x, int y)
	{
		switch(x)
		{
		case 'a':
			switch(y){
			case 'b':
				return 'c';
			case 'c':
				return 'b';
			}
		case 'b':
			switch(y){
			case 'a':
				return 'c';
			case 'c':
				return 'a';
			}
		case 'c':
			switch(y){
			case 'a':
				return 'b';
			case 'b':
				return 'a';
			}
		}
		return 0;
	}
	void string_reduction()
	{
		int cases;
		std::cin>>cases;
		while(cases--)
		{
			std::string input;
			std::cin>>input;
			int n = input.size();
			int**m = new int*[input.size()];
			std::set<int> end[100][100];// = new int**[n];// = new int**[input.size()];
			for(unsigned int i = 0; i < input.size(); i++)
			{
				m[i] = new int[input.size()];
				m[i][i] = 1;

				end[i][i].insert(input[i]);
			}
			for(int ii = 1; ii < n; ii++)
			{
				for(int i = 0; i < n - ii; i++)
				{
					int j = i + ii;
					m[i][j] = 2000000;
					int tempchar = 0,tempchar2 = 0;
					//bool foundtwice = false;
					for(int k = i; k < j; k++)
					{
						int loccost = m[i][k] + m[k+1][j];
						for(std::set<int>::iterator lksize =  end[i][k].begin(); lksize != end[i][k].end();lksize++)
						{
							for(std::set<int>::iterator yksize = end[k+1][j].begin(); yksize != end[k+1][j].end(); yksize++)
							{
								if((*lksize) == (*yksize))
								{
									if(m[i][j] > loccost)
									{
										m[i][j] = loccost;
										
									}
								}
								else
								{
									if((k - i + 1) %2 == 1 && (j - k) % 2 == 1)
									{
										loccost = 1;
										if(m[i][j] > loccost)
										{
											m[i][j] = loccost;
											
										}
									}
									else if((k-i +1)%2 == 1)
									{
										loccost = 1;
										if(m[i][j] > loccost)
										{
											m[i][j] = loccost;
										}
									}
									else if((j-k)%2 == 1)
									{
										loccost = 1;
										if(m[i][j] > loccost)
										{
											m[i][j] = loccost;
										}
									}
									else
									{
										if((k-i+1) > (j - k))
										{
											loccost = j-k;
											if(m[i][j] > loccost)
											{
												
												m[i][j] = loccost;
											}
										}
										else if((k-i+1) < (j - k))
										{
											loccost = k - i + 1;
											if(m[i][j] > loccost)
											{
												
												m[i][j] = loccost;
												
											}
										}
										else
										{
											
											loccost = k - i + 1;
											if(m[i][j] > loccost)
											{
											
												m[i][j] = loccost;
											
											}
										}
										
									}
								}
							}
						}
					}
					//int loccost = m[i][j];
					for(int k = i; k < j; k++)
					{
						int loccost = m[i][k] + m[k+1][j];
						for(std::set<int>::iterator lksize =  end[i][k].begin(); lksize != end[i][k].end();lksize++)
						{
							for(std::set<int>::iterator yksize = end[k+1][j].begin(); yksize != end[k+1][j].end(); yksize++)
							{
								if((*lksize) == (*yksize))
								{
									if(m[i][j] == loccost)
									{
										end[i][j].insert((*lksize));
									}
								}
								else
								{
									if((k - i + 1) %2 == 1 && (j - k) % 2 == 1)
									{
										loccost = 1;
										if(m[i][j] == loccost)
										{
											end[i][j].insert(find_result((*lksize),(*yksize)));
											
										}
									}
									else if((k-i +1)%2 == 1)
									{
										loccost = 1;
										if(m[i][j] == loccost)
										{
											
											end[i][j].insert(*lksize);
										}
									}
									else if((j-k)%2 == 1)
									{
										loccost = 1;
										if(m[i][j] == loccost)
										{
											end[i][j].insert(*yksize);
										}
									}
									else
									{
										if((k-i+1) > (j - k))
										{
											loccost = j-k;
											if(m[i][j] == loccost)
											{
												end[i][j].insert(*yksize);
												
											}
										}
										else if((k-i+1) < (j - k))
										{
											loccost = k - i + 1;
											if(m[i][j] == loccost)
											{
												
												end[i][j].insert(*lksize);
											}
										}
										else
										{
											
											loccost = k - i + 1;
											if(m[i][j] == loccost)
											{
												
												end[i][j].insert(*lksize);
												end[i][j].insert(*yksize);
											}
										}
										
									}
								}
							}
						}
					}
					
				}
			}
			
			for(int ilk = 0; ilk < n; ilk++)
			{
				for(int jlk = 0; jlk < n; jlk++)
				{
					//for(int slk = 0; slk < end[ilk][jlk].size(); slk++)
					std::cout<<end[ilk][jlk].size()<<" ";
					//std::cout<<std::endl;
				}
				std::cout<<std::endl;
			}
			for(int ilk = 0; ilk < n; ilk++)
			{
				for(int jlk = 0; jlk < n; jlk++)
				{
					std::cout<<m[ilk][jlk]<<" ";
				}
				std::cout<<std::endl;
			}
			std::cout<<m[0][n-1]<<std::endl;
		}
	}
	void string_reduce()
	{
		int cases;
		std::cin>>cases;
		while(cases--)
		{
			std::string input;
			std::cin>>input;
			int acount=0,bcount=0,ccount=0;
			for(unsigned int i = 0; i < input.size(); i++)
			{
				switch(input[i])
				{
				case 'a':
					acount++;
					break;
				case 'b':
					bcount++;
					break;
				case 'c':
					ccount++;
					break;
				}
			}
			if(acount == input.size())
			{
				std::cout<<acount<<std::endl;
				continue;
			}
			else if(bcount == input.size())
			{
				std::cout<<bcount<<std::endl;
				continue;
			}
			else if(ccount == input.size())
			{
				std::cout<<ccount<<std::endl;
				continue;
			}
			else if((acount%2 == 0 && bcount%2 ==0 && ccount%2==0) || (acount%2 == 1 && bcount%2 ==1 && ccount%2==1) )
			{
				std::cout<<2<<std::endl;
				continue;
			}
			else
			{
				std::cout<<1<<std::endl;
				continue;
			}
		}
	}
}

namespace candies
{
#define HUGE 1000000
	int find_valley(int i, int* arr, int n)
	{
		if( i < 0 || i > (n-1))
			return HUGE;
		return arr[i];
	}

	void candies()
	{
		int n;
		std::cin>>n;
		int* arr = new int[n];
		int* res = new int[n];
		std::memset(res,0,n*sizeof(int));
		for(int i = 0; i < n; i++)
			std::cin>>arr[i];
		std::vector<int> valley;
		for(int i = 0; i < n; i++)
		{
			if( find_valley(i,arr,n) <= find_valley(i-1,arr,n) && find_valley(i,arr,n) <= find_valley(i+1,arr,n))
				valley.push_back(i);
		}

		for(unsigned int i = 0; i < valley.size(); i++)
		{
			res[valley[i]] = 1;
			int curindex = valley[i] - 1;
			int curvalue = 2;
			while(curindex >= 0 && find_valley(curindex,arr,n) > find_valley(curindex + 1, arr, n))
			{
				res[curindex] = (res[curindex]>curvalue)?res[curindex]:curvalue;
				curindex--;
				curvalue++;
			}
			curindex = valley[i] + 1;
			curvalue = 2;
			while(curindex < n && find_valley(curindex,arr,n) > find_valley(curindex - 1, arr, n))
			{
				res[curindex] = (res[curindex]>curvalue)?res[curindex]:curvalue;
				curindex++;
				curvalue++;
			}
		}
		int sum = 0;
		for(int i = 0; i < n; i++)
			sum += res[i];
		std::cout<<sum<<std::endl;
		
	}
}

namespace median
{
	void median()
	{
		int operations;
		std::cin>>operations;
		heap<int> minHeap;
		maxheap<int> maxHeap;
		while(operations--)
		{
			char oper;
			int number;
			std::cin>>oper;
			std::cin>>number;
			if(oper=='r')
			{
				if(!minHeap.remove(number) && !maxHeap.remove(number))
				{
					std::cout<<"Wrong!"<<std::endl;
					continue;
				}
			}
			if(oper == 'a')
			{
				//int min = minHeap.peekMin();
				if(maxHeap.size() != 0)
				{
					int max = maxHeap.peekMin();
					if(number <= max)
						maxHeap.insert(number);
					else
						minHeap.insert(number);
				}
				else if(minHeap.size() != 0)
				{
					int min = minHeap.peekMin();
					if(number >= min)
						minHeap.insert(number);
					else
						maxHeap.insert(number);
				}
				else
				{
					maxHeap.insert(number);
				}

			}
			int minSize = minHeap.size();
			int maxSize = maxHeap.size();
			if(maxSize == 0 &&  minSize == 0)
			{
				std::cout<<"Wrong!"<<std::endl;
				continue;
			}
			if(maxSize - minSize > 0)
			{
				int val = maxHeap.extractMin();
				minHeap.insert(val);
				minSize++;
				maxSize--;
			}
			if(minSize - maxSize > 1)
			{
				int val = minHeap.extractMin();
				maxHeap.insert(val);
				minSize--;
				maxSize++;
			}
			if(minSize == 0)
			{
				std::cout<<maxHeap.peekMin()<<std::endl;
			}
			else if(maxSize == 0)
			{
				std::cout<<minHeap.peekMin()<<std::endl;
				
			}
			else if((maxHeap.size() + minHeap.size()) % 2 == 0)
			{
				std::cout<<(double)(maxHeap.peekMin() + minHeap.peekMin())/2<<std::endl;
				
			}
			else 
			{
				unsigned int median = (maxHeap.size() + minHeap.size())/2 + 1;
				if(median > maxHeap.size())
				{
					std::cout<<minHeap.peekMin()<<std::endl;
					
				}
				else
				{
					std::cout<<maxHeap.peekMin()<<std::endl;
				}
			}
		}
	}
}

namespace flowers
{
	void flowers()
	{
		int n=0,k=0;
		std::cin>>n;
		std::cin>>k;
		std::vector< std::vector<int> > temp;
		for(int i = 0 ; i < k; i++)
		{
			std::vector<int> res;
			temp.push_back(res);
		}
		std::vector<int> numbers;
		int num;
		for(int i = 0; i < n; i++)
		{
			std::cin>>num;
			numbers.push_back(num);
		}
		std::sort(numbers.begin(),numbers.end(),std::greater<int>());
		for(unsigned int i = 0; i < numbers.size();)
		{
			int counter = 0;
			while(counter<k)
			{
				temp[counter].push_back(numbers[i]);
				counter++;
				i++;
				if( i >= numbers.size())
					break;
			}
		}
		int result = 0;
		for(unsigned int i = 0; i < temp.size(); i++)
		{
			for(unsigned int j = temp[i].size() - 1; j >= 0 ; j--)
				result = result + (j+1)* temp[i][j];
		}
		std::cout<<result<<std::endl;
	}
}

namespace verticalSticks
{
	void arrswap(int* a, int* b)
	{
		int temp = *a;
		(*a) = (*b);
		(*b) = temp;
	}
	int findValue(int* arr, int n)
	{
		int* temparr = new int[n];
		std::memset(temparr,-1,n*sizeof(int));
		temparr[0] = 0;
		temparr[1] = 1;
		for(int i = 2; i < n; i++)
		{
			if(arr[i] < arr[i-1])
			{
				temparr[i] = 1;
			}
			else
			{
				int j = i-1;
				while(arr[i] > arr[j])
				{
					j = j - temparr[j];
				}
				temparr[i] = i - j;
			}
		}
		int sum = 0;
		for(int i = 0; i < n; i++)
			sum += temparr[i];
		return sum;
	}
	void generatePerms(int*arr, int n, int index, int* sum, int* count)
	{
		if( index == (n-1))
		{
			/*for(int i = 1 ; i < n; i++)
			{
				std::cout<<arr[i]<<" ";
			}
			std::cout<<std::endl;*/
			(*count)++;
			(*sum) = (*sum) + findValue(arr,n);
		}
		else
		{
			for(int i = index; i < n; i++)
			{
				arrswap(arr + index, arr + i);
				generatePerms(arr,n,index+1,sum,count);
				arrswap(arr + index, arr+ i);
			}
		}
	}
	void verticalsticks()
	{
		int cases;
		std::cin>>cases;
		while(cases--)
		{
			int n;
			std::cin>>n;
			int* arr = new int[n+1];
			for(int i = 1; i <= n; i++)
			{
				std::cin>>arr[i];
			}
			arr[0] = 2000; 
			int sum = 0,count = 0;
			generatePerms(arr,n+1,1,&sum, &count);
			double result = ((double)sum)/count;
			printf("%.2f\n",result);
		}
	}
}

namespace billboards
{
	void billboards()
	{
		std::vector<long> vect;
		long n = 0, k = 0;
		std::cin>>n;
		std::cin>>k;
		int* arr = new int[n];
		long* dp = new long[n];
		long netSum = 0;
		for(int i = 0; i < n; i++)
		{
			std::cin>>arr[i];
			netSum += arr[i];
		}
		if(n <= k)
        {
            std::cout<<netSum<<std::endl;
            return;
        }
		long min = arr[0], minPos = 0;
        for(int i = 0; i <= k; i++)
        {    
            dp[i] = arr[i];
            //vect.push_back(dp[i]);
			if(min > arr[i])
			{
				min = arr[i];
				minPos = i;
			}
        }
		/*dp[0] = arr[0];
		vect.push_back(dp[0]);*/
		std::make_heap(vect.begin(), vect.end(),std::greater<long>());
		for(int i = k+1; i < n; i++)
		{
			dp[i] = min + arr[i];
			if(i >= (minPos + k + 1))
			{
				min = dp[minPos+1];
				minPos++;
				for(int j = minPos + 1; j <= i; j++)
				{
					if(min > dp[j])
					{
						min = dp[j];
						minPos = j;
					}
				}
			}
			//vect.erase(std::remove(vect.begin(),vect.end(),dp[i-k-1]),vect.end());
			//std::vector<long>::iterator position = std::find(vect.begin(), vect.end(), dp[i - k - 1]);
			//if (position != vect.end()) // == vector.end() means the element was not found
			//	vect.erase(position);
			//vect.push_back(dp[i]);
			//std::make_heap(vect.begin(),vect.end(),std::greater<long>());
		}
		for(int i = 0; i < n; i++)
			std::cout<<dp[i]<<"\t";
		std::cout<<std::endl;
		//long min = dp[n-1];
		//for(int i = n-1; i > (n - k - 2); i--)
		//	if(min > dp[i])
		//		min = dp[i];
		std::cout<<netSum - min<<std::endl;
	}
}

namespace kingdom
{
	#define MOD 1000000000
	void kingdom()
	{
		vector<int> adj[10001], invadj[10001];
		int indegree[10001];
		int visited[10001];
		int ranks[10001];
		long long total[10001];
		adj[0].push_back(1);
		invadj[1].push_back(0);
		indegree[1] = 1;
		int N, M;
		std::cin>>N>>M;
		std::memset(indegree,0,(N+1)*sizeof(int));
		std::memset(visited,0,(N+1)*sizeof(int));
		int s, t;
		for(int i = 0; i < M; i++)
		{
			std::cin>>s>>t;
			adj[s].push_back(t);
			invadj[t].push_back(s);
			indegree[t]++;
		}

		stack<int> st;
		st.push(0);
		visited[0] = 1;
		while(!st.empty())
		{
			int vert = st.top();
			st.pop();
			
			visited[vert] = 1;
			for(unsigned int i = 0 ; i < adj[vert].size(); i++)
			{
				st.push(adj[vert][i]);
			}
		}

		if(!visited[N])
		{
			std::cout<<0<<std::endl;
			return;
		}

		for(int i = 0; i <=N; i++)
		{
			if(!visited[i])
			{
				for(unsigned int j = 0; j < adj[i].size(); j++)
					indegree[adj[i][j]]--;
			}
		}

		int count = 0;
		stack<int> topo;

		for(int i = 0; i <= N; i++)
		{
			int j = 0;
			for(;j <=N; j++)
			{
				if(visited[j] && indegree[j] == 0)
					break;
			}

			if(j > N)
			{
				std::cout<<"INFINITE PATHS"<<std::endl;
				return;
			}
			else
			{
				topo.push(j);
				ranks[count++] = j;
				if(j == N)
					break;
				indegree[j] = -1;
				for(unsigned int k = 0; k < adj[j].size(); k++)
					indegree[adj[j][k]]--;
			}
		}
		memset(total, 0, (N+1)*sizeof(long long));
		total[N] = 1;
		for (int i=count - 1;i>=0;i--)
		{
			int r = ranks[i];
			for (unsigned int j=0;j<invadj[r].size();j++)
				if(visited[invadj[r][j]])
				{
					total[invadj[r][j]] = (total[invadj[r][j]] + total[r]) % MOD;
				}
		}
		cout << total[0] << endl;
		
	}
}
// Not Completed
namespace substringdiff
{
	void substringdiff()
	{
		int cases;
		std::cin>>cases;
		while(cases--)
		{
			int k;
			std::cin>>k;
			std::string str1, str2;
			std::cin>>str1;
			std::cin>>str2;

			int* curr = new int[str2.size()];
			int* prev = new int[str2.size()];

			int* currError = new int[str2.size()];
			int* prevError = new int[str2.size()];

			std::memset(curr,0,str2.size()*sizeof(int));
			std::memset(currError,0,str2.size()*sizeof(int));
			std::memset(prev,0,str2.size()*sizeof(int));
			std::memset(prevError,0,str2.size()*sizeof(int));
			
			int* swap;
			int maxsubs = 0;

			for(unsigned int i = 0; i < str1.size(); i++)
			{
				for(unsigned int j = 0; j < str2.size(); j++)
				{
					if(str1[i] != str2[j])
					{
						if(prevError[j-1] < k)
						{
							if( i==0 || j==0)
							{
								curr[j] = 1;
								
							}
							else
							{
								curr[j] = 1 + prev[j-1];
								//currError[j] = 1 + prevError[j-1];
							}

							if(!j)
									currError[j] = 1;
								else
									currError[j] = 1 + prevError[j-1];

							if(maxsubs < curr[j])
								maxsubs = curr[j];
						}
						else
						{
							curr[j] = 0;
							currError[j] = 0;
						}
					}
					else
					{
						if( i==0 || j==0)
						{
							curr[j] = 1;
							
						}
						else
						{
							curr[j] = 1 + prev[j-1];
							//currError[j] = prevError[j-1];
						}

						if(!j)
								currError[j] = 0;
							else
								currError[j] = prevError[j-1];
	
						
						if(maxsubs < curr[j])
							maxsubs = curr[j];
					}
				}
				swap = curr;
				curr = prev;
				prev = swap;
				swap = currError;
				currError = prevError;
				prevError = swap;
			}
			delete[] curr;
			delete[] prev;
			delete[] currError;
			delete[] prevError;
			std::cout<<maxsubs<<std::endl;
		}
	}
}
// Not Completed
namespace house
{
	void house()
	{
		int a=0, b=0;
		std::cin>>a>>b;
		int x1,y1,x2,y2,x3,y3,x4,y4;
		std::cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
		//int c1 = 
	}
}

namespace triplets
{
	void basic_triplets()
	{
		int num;
		std::cin>>num;
		int* arr = new int[num];
		for(int i = 0; i < num; i++)
			std::cin>>arr[i];
		int* less = new int[num];
		std::memset(less,0,num*sizeof(int));
		std::set<int> sets;
		for(int i = 1 ; i < num; i++)
		{
			for( int j = i-1; j >=0 ; j--)
			{
				if(arr[i] > arr[j])
				{
					sets.insert(arr[j]);
				}
				else if(arr[i] == arr[j])
				{
					j--;
					while(j >= 0 && !sets.empty())
					{
						sets.erase(arr[j]);
						j--;
					}
					break;
				}
			}
			less[i] = sets.size();
			sets.clear();
		}
		int* great = new int[num];
		std::memset(great,0,num*sizeof(int));
		sets.clear();
		for(int i = num - 2; i >=0; i--)
		{
			for(int j = i + 1; j <= num-1; j++)
			{
				if(arr[i] < arr[j])
					sets.insert(arr[j]);
				/*else if(arr[i] == arr[j])
				{
					j++;
					while(j < num)
					{
						sets.erase(arr[j]);
						j++;
					}
					break;
				}*/
			}
			great[i] = sets.size();
			sets.clear();
		}
		long result = 0;
		for(int i = 1; i < num ; i++)
		{
			//std::cout<<result<<"\t";
			if(arr[i] == arr[i + 1])
			{
				result = result + (great[i+1] * less[i]);
				//i++;
				continue;
			}
			result += (great[i] * less[i]);
		}
		for(int i = 0; i < num; i++)
			std::cout<<less[i]<< ":"<<great[i]<<std::endl;
		std::cout<<result<<std::endl;
	}
}

namespace manipu
{
	void manipu()
	{
		int num;
		std::cin>>num;
		unsigned int* arr = new unsigned int[num];
		for(int i = 0; i < num; i++)
			std::cin>>arr[i];
		unsigned int* workarr = new unsigned int[num];
		for(int k = 31; k >=0; k--)
		{
			for(int i = 0; i < num; i++)
				workarr[i] = arr[i] >> k;
			unsigned int majority = workarr[0];
			int count = 1;
			for(int i = 1; i < num; i++)
			{
				if(majority == workarr[i])
					count++;
				else if(count > 1)
					count--;
				else
				{
					majority = workarr[i];
				}
			}
			count = 0;
			for(int i = 0; i < num; i++)
			{
				if(workarr[i] == majority)
					count++;
			}
			if(count > num/2)
				continue;
			else
			{
				std::cout<<k<<std::endl;
				break;
			}
		}
	}
}

namespace taskscheduler
{
	struct job
	{
		int time;
		int deadline;
	};
	struct value
	{
		long max_overshoot;
		long running_count;
	};
	struct comp
	{
		bool operator()(const job& a, const job& b) const
		{
			if(a.deadline < b.deadline)
				return true;
			else if(a.deadline == b.deadline)
			{
				if(a.time < b.time)
					return true;
				else
					return false;
			}
			return false;
		}
	};
	void taskscheduler()
	{
		int tasks;
		std::cin>>tasks;
		std::multimap<job,value,comp> jobs;
		std::vector<job> keeper;
		for(int i = 0; i < tasks; i++)
		{
			job temp;
			std::cin>>temp.deadline>>temp.time;
			keeper.push_back(temp);
		}

#if 1
		job maxJob,holder;
		value maxVal;
		maxJob.deadline = 0;
		maxJob.time = 0;
		holder.deadline = 100001;
		holder.time = 0;
		maxVal.max_overshoot = 0;
		maxVal.running_count = 0;
		comp p;
		
	for(int i = 0; i < tasks; i++)
	{
		value val;
		val.max_overshoot = 0;
		val.running_count = 0;
		std::multimap<job,value,comp>::iterator it3 = jobs.insert(std::make_pair(keeper[i],val));
		int max=0,run_cnt=0,overshoot;
		if(p(maxJob, keeper[i]))
		{
				
				
			std::multimap<job,value,comp>::iterator it = jobs.find(holder); 
			if(it == jobs.end())
				it = jobs.find(keeper[i]);
			std::multimap<job,value,comp>::iterator it2 = it;
			if(it != jobs.begin())
				it2--;
			for(; it != jobs.end(); it++)
			{
				if(it != jobs.begin())
				{
					(*it).second.running_count = (*it2).second.running_count + (*it).first.time;
					max = (*it2).second.max_overshoot;
					overshoot = (*it).second.running_count - (*it).first.deadline;
					if(max < overshoot)
					{
						max = overshoot;
						maxJob.deadline = (*it).first.deadline;
						maxJob.time = (*it).first.time;
						maxVal.max_overshoot = max;
					}
					(*it).second.max_overshoot = max;
					it2++;
				}
				else
				{
					(*it).second.running_count = (*it).first.time;
					//if(((*it).second.running_count - (*it).first.deadline) > 0)
						max = (*it).second.running_count - (*it).first.deadline;
					maxJob.deadline = (*it).first.deadline;
					maxJob.time = (*it).first.time;
					maxVal.max_overshoot = max;
					(*it).second.max_overshoot = max;
				}
				
			}
		}
		else
		{
				
			if(holder.deadline >= keeper[i].deadline)
			{
				long before = 0;
				if(it3 != jobs.begin())
				{
					it3--;
					before = (*it3).second.running_count;
					it3++;
					(*it3).second.running_count = (*it3).first.time + before;
				}
				holder.deadline = keeper[i].deadline;
				holder.time = keeper[i].time;
				long localmax = maxVal.max_overshoot + holder.time;
				if( localmax > (keeper[i].time + before - keeper[i].deadline))
					maxVal.max_overshoot = localmax;
				else
				{
					maxJob.deadline = holder.deadline;
					maxJob.time = holder.time;
					maxVal.max_overshoot = (keeper[i].time + before - keeper[i].deadline);
				}	
			}
			else
			{
				it3++;
				std::multimap<job,value,comp>::iterator it = jobs.find(holder); 
				if(it == jobs.end())
					it = jobs.find(keeper[i]);
				std::multimap<job,value,comp>::iterator it2 = it;
				if(it != jobs.begin())
					it2--;
				for(; it != it3; it++)
				{
					if(it != jobs.begin())
					{
						(*it).second.running_count = (*it2).second.running_count + (*it).first.time;
						max = (*it2).second.max_overshoot;
						overshoot = (*it).second.running_count - (*it).first.deadline;
						if(max < overshoot)
						{
							max = overshoot;
							maxJob.deadline = (*it).first.deadline;
							maxJob.time = (*it).first.time;
							//maxVal.max_overshoot = max;
						}
						(*it).second.max_overshoot = max;
						it2++;
					}
					else
					{
						(*it).second.running_count = (*it).first.time;
						//if(((*it).second.running_count - (*it).first.deadline) > 0)
							max = (*it).second.running_count - (*it).first.deadline;
						maxJob.deadline = (*it).first.deadline;
						maxJob.time = (*it).first.time;
						//maxVal.max_overshoot = max;
						(*it).second.max_overshoot = max;
					}
				
				}
				int localmax = maxVal.max_overshoot + keeper[i].time;
				if(localmax > max)
				{
					max = localmax;
					maxVal.max_overshoot = max;
				}
				else
				{
					maxVal.max_overshoot = max;
				}
			}
				
			max = maxVal.max_overshoot;
		}
		if(max < 0)
			max = 0;
		std::cout<<max<<std::endl;
	}
#else
		for(int i = 0; i < tasks; i++)
		{
			value val;
			std::multimap<job,value,comp>::iterator it = jobs.insert(std::make_pair(keeper[i],val));
			std::multimap<job,value,comp>::iterator it2 = it;
			if(it != jobs.begin())
				it2--;
			int max=0,run_cnt=0,overshoot;
			for(; it != jobs.end(); it++)
			{
				if(it != jobs.begin())
				{
					(*it).second.running_count = (*it2).second.running_count + (*it).first.time;
					max = (*it2).second.max_overshoot;
					overshoot = (*it).second.running_count - (*it).first.deadline;
					if(max < overshoot)
						max = overshoot;
					(*it).second.max_overshoot = max;
					it2++;
				}
				else
				{
					(*it).second.running_count = (*it).first.time;
					if(((*it).second.running_count - (*it).first.deadline) > 0)
						max = (*it).second.running_count - (*it).first.deadline;
					(*it).second.max_overshoot = max;
				}
				
			}
			std::cout<<max<<std::endl;
		}
#endif
		/*for(std::vector<job>::iterator it = jobs.begin(); it != jobs.end(); it++)
		{
			std::sort(jobs.begin(),it+1,comp);
			std::vector<job>::iterator it2 = jobs.begin();
			int running_count = 0,overshoot = 0,max_overshoot = 0;
			while(true)
			{
				running_count += (*it2).time;
				overshoot = (running_count - (*it2).deadline);
				if(max_overshoot < overshoot)
					max_overshoot = overshoot;
				if(it == it2)
					break;
				else
					it2++;
			}
			std::cout<<max_overshoot<<std::endl;
		}*/
	}
}


namespace amazon
{
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
	void fibonacci_factor()
	{
		std::vector<int> primes;
		find_Primes(primes);
		std::vector< unsigned long long> fibs;
		for( unsigned long long a = 1,b=2,c=0; ;)
		{
			fibs.push_back(b);
			c = b;
			b = a+b;
			a = c;
			if(b < a)
				break;
		}
		std::cout<<fibs.size()<<std::endl;
		std::vector<unsigned long long> mapprime;
		for(unsigned int i = 0; i < primes.size(); i++)
		{
			int temp = primes[i];
			bool found = false;
			for(unsigned int j = 0; j < fibs.size(); j++)
			{
				if(fibs[j] % temp == 0)
				{
					mapprime.push_back(fibs[j]);
					found = true;
					break;
				}
			}
			if(!found)
			{
				mapprime.push_back(1);
				//std::cout<<"Could not find for : "<<temp<<std::endl;
			}
		}
		int cases;
		std::cin>>cases;
		while(cases > 0)
		{
			cases--;
			int k  = 0;
			std::cin>>k;
			for(unsigned int i = 0; i < primes.size(); i++)
			{
				if(k%primes[i] == 0)
				{
					if(mapprime[i] != 1)
					{
						std::cout<<mapprime[i]<<" "<<primes[i]<<std::endl;
						break;
					}
				}
			}
		}
	}
}



namespace hackerrank_sorting
{
	void insertion()
	{
		int test_cases=0;
		cin>>test_cases;
		while(test_cases>0)
		{
			test_cases--;
			vector<int> stack;
			int num_elements;
			cin>>num_elements;
			map<int, int> bin_map;
			int tmp;
			long count = 0;
			int min = 10000000, max = 0;
			cin>>tmp;
			bin_map[tmp]++;
			min = tmp;
			max = tmp;
			int* num = new int[num_elements];
			for(int i = 1; i < num_elements; i++)
				cin>>num[i];
			for(int j = 1; j < num_elements; j++)
			{
				tmp = num[j];
				if(tmp >= min && tmp < max)
				{
					for(map<int,int>::reverse_iterator itr = bin_map.rbegin(); itr != bin_map.rend() && itr->first > tmp; itr++)
					{
						count += itr->second;
					}
				}
				else if(tmp < min)
				{
					count += j;
					min = tmp;
				}
				else
					max = tmp;
				bin_map[tmp]++;
			}
			cout<<count<<endl;
			//delete[] num;
		}
    }

	/* This funt merges two sorted arrays and returns inversion count in
	   the arrays.*/
	int merge(int arr[], int temp[], int left, int mid, int right)
	{
	  int i, j, k;
	  int inv_count = 0;
  
	  i = left; /* i is index for left subarray*/
	  j = mid;  /* i is index for right subarray*/
	  k = left; /* i is index for resultant merged subarray*/
	  while ((i <= mid - 1) && (j <= right))
	  {
		if (arr[i] <= arr[j])
		{
		  temp[k++] = arr[i++];
		}
		else
		{
		  temp[k++] = arr[j++];
  
		 /*this is tricky -- see above explanation/diagram for merge()*/
		  inv_count = inv_count + (mid - i);
		}
	  }
  
	  /* Copy the remaining elements of left subarray
	   (if there are any) to temp*/
	  while (i <= mid - 1)
		temp[k++] = arr[i++];
  
	  /* Copy the remaining elements of right subarray
	   (if there are any) to temp*/
	  while (j <= right)
		temp[k++] = arr[j++];
  
	  /*Copy back the merged elements to original array*/
	  for (i=left; i <= right; i++)
		arr[i] = temp[i];
  
	  return inv_count;
	}

	/* An auxiliary recursive function that sorts the input array and
	  returns the number of inversions in the array. */
	int _mergeSort(int arr[], int temp[], int left, int right)
	{
	  int mid, inv_count = 0;
	  if (right > left)
	  {
		/* Divide the array into two parts and call _mergeSortAndCountInv()
		   for each of the parts */
		mid = (right + left)/2;
  
		/* Inversion count will be sum of inversions in left-part, right-part
		  and number of inversions in merging */
		inv_count  = _mergeSort(arr, temp, left, mid);
		inv_count += _mergeSort(arr, temp, mid+1, right);
  
		/*Merge the two parts*/
		inv_count += merge(arr, temp, left, mid+1, right);
	  }
	  return inv_count;
	}
  
	
	void insertion_2()
	{
		int test_cases=0;
		cin>>test_cases;
		while(test_cases>0)
		{
			test_cases--;
			
			int num_elements;
			cin>>num_elements;
			long count = 0;
			int* num = new int[num_elements];
			int* tmp = new int[num_elements];
			for(int i = 0; i < num_elements; i++)
				cin>>num[i];
			count = _mergeSort(num,tmp,0,num_elements-1);
			cout<<count<<endl;
			//delete[] num;
		}
	}


	int partition(long* arr, int low, int high, bool ascending = true)
	{
		long temp = arr[low];
		int i = low, j = high;
		if(ascending)
		{
			while(i < j)
			{
				while(i < j && arr[i] <= temp)
					i++;
				while(arr[j] > temp) 
					j--;
				if(i < j)
				{
					int t = arr[i];
					arr[i] = arr[j];
					arr[j] = t;
				}
			}
			i--;
			int t = arr[low];
			arr[low] = arr[i];
			arr[i] = t;
			return i;
		}
		else
		{
			while(i < j)
			{
				while(i <= j && arr[i] >= temp)
					i++;
				while(arr[j] < temp)
					j--;
				if(i < j)
				{
					int t = arr[i];
					arr[i] = arr[j];
					arr[j] = t;
				}
			}
			i--;
			int t = arr[low];
			arr[low] = arr[i];
			arr[i] = t;
			return i;
		}
	}
	void quicksort(long* arr, int low, int high, bool ascending = true)
	{
		if(high > low)
		{
			int mid = low + (high-low)/2;
			int pivot = partition(arr,low,high,ascending);
			quicksort(arr,low,pivot-1,ascending);
			quicksort(arr,pivot+1,high,ascending);
		}
	}
	void buyToys()
	{
		long numtoys, netvalue;
		cin>>numtoys;
		cin>>netvalue;
		long* toys = new long[numtoys];
		for(int i = 0; i < numtoys; i++)
			cin>>toys[i];
		quicksort(toys,0,numtoys-1);
		long j = 0, count = 0;
		while(count <= netvalue && j < numtoys)
		{
			count += toys[j];
			j++;
		}
		cout<<j-1<<endl;
	}


	void twoarrays()
	{
		int testcases;
		cin>>testcases;
		while(testcases > 0)
		{
			testcases--;
			long num, sum;
			cin>>num;
			cin>>sum;
			long* arr1 = new long[num];
			long* arr2 = new long[num];
			for(int i = 0; i < num; i++)
				cin>>arr1[i];
			for(int i = 0; i < num; i++)
				cin>>arr2[i];
			quicksort(arr1,0,num-1,true);
			quicksort(arr2,0,num-1,false);
			int j = 0;
			for(j = 0; j < num; j++)
			{
				if(arr1[j] + arr2[j] < sum)
					break;
			}
			if(j == num)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}
	}



}


namespace hackerrank_regex
{
	void first()
	{
		int testcases;
		cin>>testcases;
		cin.clear();
		char str[200];
		while(testcases > 0)
		{
			testcases--;
			string input;
			while(input.size() == 0)
				getline(cin,input);
			regex star("^(hackerrank).*");
			regex end(".*(hackerrank)$");
			
			bool foundstart = false,foundend = false;
			smatch s;
			if(regex_match(input,s,star))
				foundstart = true;
			if(regex_match(input,s,end))
				foundend = true;
			if(foundstart && foundend)
				cout<<0<<endl;
			else if(foundstart)
				cout<<1<<endl;
			else if(foundend)
				cout<<2<<endl;
			else
				cout<<-1<<endl;
			
		}
	}
}

















