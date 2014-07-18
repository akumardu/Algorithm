#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<stdio.h>
#include<iomanip>

namespace peking
{
	using namespace std;
	void tritilling()
	{
		long* d = new long[31];
		long* a = new long[31];
		for(int i = 0; i < 31; i++)
		{
			d[i] = 0;
			a[i] = 0;
		}
		d[0] = 1;
		a[0] = 0;
		d[1] = 0;
		a[1] = 1;
		for(int i = 2; i < 31; i++)
		{
			a[i] = d[i-1] + a[i-2];
			d[i] = d[i-2] + 2*a[i-1];
		}
		int num = 0;
		while(true)
		{
			cin>>num;
			if(num == -1) break;
			cout<<d[num]<<endl;
		}
	}

#define max(a,b) (((a)>(b))?(a):(b))
	void thetriangle()
	{
		int size = 0;
		cin>>size;
		int**num = new int*[size];
		int** dp = new int*[size];
		int max = 0;
		for(int i = 0; i < size; i++)
		{
			num[i] = new int[i+1];
			dp[i] = new int[i+1];
			for(int j = 0; j <= i; j++)
			{
				cin>>num[i][j];
				if(i == 0)
				{
					dp[i][j] = num[i][j] ;
				}
				else
				{
					if(j==0)
					{
						dp[i][j] = dp[i-1][j] + num[i][j];
					}
					else if(i == j)
					{
						dp[i][j] = dp[i-1][j-1] + num[i][j];
					}
					else
					{
						dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]) + num[i][j];
					}
				}
				if(dp[i][j] > max)
					max = dp[i][j];
			}
		}
		cout<<max<<endl;
	}
	int dist[310][310];
		int dp[310][310];
		int w[310][310];
	void postoffice()
	{
		int numvillages = 0, numpostoffices = 0;
		cin>>numvillages;
		cin>>numpostoffices;
		int villages[400];
		for(int i = 0; i < numvillages; i++)
		{
			scanf("%d",&(villages[i]));
		}
		
		memset(dp,0x3f,sizeof(dp));
		memset(dist,0x3f,sizeof(dist));
		// Finding the lowest cost of placing one postoffice between i and j village
		for(int i = 0; i < numvillages; i++)
		{
			dist[i][i] = 0;
			for(int j = i+1; j < numvillages; j++)
			{
				int mindistance = 3000000;
				for(int k = i; k <= j; k++)
				{
					int distancesum = 0;
					for(int l = i; l <= j; l++)
					{
						distancesum += abs(villages[k] - villages[l]);
					}
					if(distancesum < mindistance)
						mindistance = distancesum;
				}
				dist[i][j] = mindistance;
				cout<<dist[i][j]<<'\t';
			}
			cout<<endl;
		}
		for(int i = 0; i < numpostoffices; i++)
		{
			for(int j = i + 1; j < numvillages; j++)
			{
				if(i == 0)
				{
					dp[i][j] = dist[0][j];
					cout<<dp[i][j]<<'\t';
					continue;
				}
				int mindistance = 30000000;
				for(int k = i-1; k < j ; k++)
				{
					int distance = 0;
					
					distance += dist[k+1][j];
					distance += dp[i-1][k];
					
					if(distance < mindistance)
					{
						mindistance = distance;
					}
				}
				dp[i][j] = mindistance;
				cout<<mindistance<<'\t';
			}
			cout<<endl;
		}
		cout<<dp[numpostoffices-1][numvillages-1]<<endl;
		
		memset(w,0x3f,sizeof(w));
		for (int i=1;i<=numvillages;i++)
		{
			int left=0;
			for (int j=i;j<=numvillages;j++)
			{
				left+=villages[j-1];
				int right=0;
				for (int k=j;k<=numvillages;k++)
				{
					right+=villages[k-1];
					if ((j-i+1)*villages[j-1]-left+right-(k-j+1)*villages[j-1]<w[i][k])	
						w[i][k]=(j-i+1)*villages[j-1]-left+right-(k-j+1)*villages[j-1];

				}
			}
		}
		for(int i = 1; i <= numvillages+1; i++)
		{
			for(int j = 1; j <= numvillages+1; j++)
			{
				cout<<w[i][j]<<'\t';
			}
			cout<<endl;
		}
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0;
		int V = numvillages, P = numpostoffices;
		for (int i=1;i<=V;i++)
			for (int j=1;j<=P;j++)
				for (int k=0;k<i;k++)
					if (dp[k][j-1]+w[k+1][i]<dp[i][j])
						dp[i][j]=dp[k][j-1]+w[k+1][i];
		cout << endl;
		for (int i=1;i<=V;i++)
		{
			for (int j=1;j<=V;j++)
				if (dp[i][j]<0x3f3f3f3f)
					printf("%4d",dp[i][j]);
				else
					printf("   M");
			printf("\n");
		} 
		printf("%d\n",dp[V][P]);
	}

	bool validDigit(char a, char b)
	{
		if(a > '2' || a == '0')
			return false;
		if(a == '2' && b > '6')
			return false;
		return true;
	}
	void alphaCode()
	{
		string input;
		cin>>input;
		while(input[0] != '0')
		{
			int* dp = new int[input.size()];
			dp[0] = 1;
			dp[1] = 0;
			if(input.size() > 1 && validDigit(input[0],input[1]))
				dp[1] = 1;
			if(input[1] != '0')
				dp[1]++;
			for(int i = 2; i < input.size(); i++)
			{
				dp[i] = 0;
				if(input[i] != '0')
					dp[i] += dp[i-1];
				if(validDigit(input[i-1],input[i]))
					dp[i] += dp[i-2];
			}
			cout<<dp[input.size()-1]<<endl;
			cin>>input;
		}
	}

	void pallindrome()
	{
		int length;
		string input;
		cin>>length;
		cin>>input;
		int**dp = new int*[length+1];
		for(int i = 0; i < length+1; i++)
		{
			dp[i] = new int[length+1];
			for(int j = 0; j < length+1; j++)
			{
				dp[i][j] = 0;
			}
		}
		for(int t = 1; t < length; t++)
		{
			for(int i = 1, j = i+t; j<=length; i++,j++)
			{
				if(input[i-1] == input[j-1])
					dp[i][j] = dp[i+1][j-1];
				else
				{
					if(dp[i+1][j] > dp[i][j-1])
						dp[i][j] = 1 + dp[i][j-1];
					else
						dp[i][j] = 1 + dp[i+1][j];
				}
				//cout<<dp[i][j]<<'\t';
			}
			//cout<<endl;
		}
		cout<<dp[1][length]<<endl;
	}
	
	int kadane(int* arr, int& start, int& end, int size)
	{
		int maxsofar = arr[0], maxglobal = arr[0];
		int begin_temp=0;
		for(int i = 1; i < size; i++)
		{
			if(maxsofar < 0)
			{
				maxsofar = arr[i];
				begin_temp = i;
			}
			else
			{
				maxsofar += arr[i];
			}
			if(maxglobal < maxsofar)
			{
				maxglobal = maxsofar;
				end = i;
				start = begin_temp;
			}
		}
		return maxglobal;
	}

	void tothemax()
	{
		int size = 0;
		cin>>size;
		int ** arr = new int*[size];
		int*temp = new int[size];
		for(int i = 0; i < size; i++)
		{
			arr[i] = new int[size];
			temp[i] = 0;
			for(int j = 0; j < size; j++)
				cin>>arr[i][j];
		}
		for(int i = 0; i < size; i++)
		{
			for(int j = 1; j < size; j++)
			{
				arr[i][j] += arr[i][j-1];
			}
		}
		int start = 0, end = 0, finalstart=0,finalend=0,finalleft = 0, finalright = 0;
		int finalresult = 0;
		for(int left = 0; left<size; left++)
		{
			for(int right = left; right < size; right++)
			{
				for(int i = 0; i < size; i++)
				{
					if(left != 0)
						temp[i] = arr[i][right] - arr[i][left-1];
					else
						temp[i] = arr[i][right];
				}
				int sum = kadane(temp,start,end,size);
				if(finalresult < sum)
				{
					finalresult = sum;
					finalstart = start;
					finalend = end;
					finalleft = left;
					finalright = right;
				}
			}
		}
		cout<<finalresult<<endl;
	}

	int binarysearchlower(double* overhangs, int size, double key)
	{
		int low = 0, high = size-1;
		while(low <= high)
		{
			int mid = (low + high)/2;
			//if(abs(overhangs[mid] - key) < 0.0001)
			//	return mid;
			if(overhangs[mid] - key > 0.0)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		return low;
	}
	void hangover()
	{
		int max = 300;
		double *overhangs = new double[max];
		overhangs[0] = 0.0;
		for(int i = 1; i < max; i++)
		{
			overhangs[i] = overhangs[i-1] + 1.0/(1+i); 
			cout<<i<<":"<<overhangs[i]<<endl;
		}
		double input;
		cin>>input;
		while(input - 0.0 > 0.01)
		{
			cout<<binarysearchlower(overhangs,max,input)<<" card(s)"<<endl;
			cin>>input;
		}
	}
	
	int merge(char* arr, int start, int middle, int end)
	{
		char* temparr = new char[end-start+1];
		int i = 0,j = 0, ind = 0;
		int inv = 0;
		for( i = start, j = middle+1; i <= middle && j <= end; )
		{
			while(i <= middle && arr[i] <= arr[j])
			{
				temparr[ind] = arr[i];
				i++;
				ind++;
			}
			int temp = j;
			while(j <= end && arr[i] > arr[j])
			{
				temparr[ind] = arr[j];
				j++;
				ind++;
			}
			inv += j - temp ;
			//ind++;
		}
		int b = 1;
		for(;i <= middle;i++)
		{
			temparr[ind] = arr[i];
			ind++;
			if ( !b)
			{
				inv += end - middle ;
			}
			b = 0;
		}
		for(;j<=end; j++)
		{
			temparr[ind] = arr[j];
			ind++;
		}
		for(int i = start; i <= end; i++)
			arr[i] = temparr[i-start];
		delete[] temparr;
		return inv;
	}

	
	int merge_sort(char* arr, int start, int end)
	{
		int inv = 0;
		if(start < end)
		{
			int middle = (start + end) / 2;
			inv += merge_sort(arr,start,middle);
			inv += merge_sort(arr,middle+1,end);
			inv += merge(arr,start,middle,end);
		}
		return inv;
	}
	
	/* This funt merges two sorted arrays and returns inversion count in
	the arrays.*/
	int _merge(char arr[], char temp[], int left, int mid, int right)
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
	int _mergeSort(char arr[], char temp[], int left, int right)
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
			inv_count += _merge(arr, temp, left, mid+1, right);
		}
		return inv_count;
	}

	int mergeSort(char arr[], int array_size)
	{
		char *temp = (char *)malloc(sizeof(char)*array_size);
		return _mergeSort(arr, temp, 0, array_size - 1);
	}

	void dnasort()
	{
		int length = 0, num = 0;
		cin>>length;
		cin>>num;
		map<int, string> sortedorder;
		char* input = new char[length];
		for(int i = 0; i < num ; i++)
		{
			cin>>input;
			string temp(input);
			int order = mergeSort(input,length)*100;
			while(sortedorder.find(order) != sortedorder.end())
				order++;
			sortedorder[order] = temp;
		}
		for(map<int,string>::iterator itr = sortedorder.begin(); itr != sortedorder.end(); itr++)
		{
			cout<<itr->second<<endl;
		}
	}

	int* lisfunction(int* arr, int length)
	{
		int* lis = new int[length];
		lis[0] = 1;
		for(int i = 1; i < length; i++)
		{
			int max = 0;
			for(int j = 0; j < i; j++)
			{
				if(arr[j] < arr[i] && max < lis[j])
					max = lis[j];
			}
			lis[i] = max + 1;
		}
		return lis;
	}
	int* fastlisfunction(int* arr, int length, int& size)
	{
		int* s = new int[length];
		s[0] = 0;
		int sz = 1;
		for(int i = 1; i < length; i++)
		{
			
			if(arr[i] < arr[s[0]])
			{
				s[0] = i;
			}
			else if(arr[i] > arr[s[sz-1]])
			{
				s[sz] = i;
				sz++;
			}
			else
			{
				int low = 0, high = sz;
				while(low < high)
				{
					int mid = (low + high)/2;
					if(arr[i] <= arr[s[mid]])
						high = mid-1;
					else
						low = mid+1;
				}
				s[high] = i;
			}
			for(int j = 0; j < sz; j++)
			{
				cout<<arr[s[j]]<<' ';
			}
			cout<<endl;
		}
		size = sz;
		return s;
	}
	void fastlistest()
	{
		int arr[] = {2, 5, 3, 7, 11, 8, 10, 13, 6};
		int sz = 0;
		int* helper = fastlisfunction(arr,sizeof(arr)/sizeof(arr[0]), sz);
		for(int i = 0; i < sz; i++)
			cout<<helper[i]<<":"<<arr[helper[i]]<<' ';
	}
	int** lcsfunction(int* arr1, int* arr2, int length1, int length2, int**& lcsdir)
	{
		int** lcs = new int*[length1 + 1];
		int** lcsd = new int*[length1 + 1];
		for(int i = 0; i < length1+1; i++)
		{
			lcs[i] = new int[length2 + 1];
			lcs[i][0] = 0;
			lcsd[i] = new int[length2 + 1];
			lcsd[i][0] = 0;
		}
		for(int i = 0; i < length2+1; i++)
		{
			lcs[0][i] = 0;
			lcsd[0][i] = 0;
		}
		for(int i = 1; i < length1+1; i++)
		{
			for(int j = 1; j < length2+1; j++)
			{
				if(arr1[i-1] == arr2[j-1])
				{
					lcs[i][j] = 1 + lcs[i-1][j-1];
					lcsd[i][j] = 1;
				}
				else if(lcs[i-1][j] > lcs[i][j-1])
				{
					lcsd[i][j] = 2;
					lcs[i][j] = lcs[i-1][j];
				}
				else
				{
					lcsd[i][j] = 3;
					lcs[i][j] = lcs[i][j-1];
				}
			}
		}
		lcsdir = lcsd;
		return lcs;
	}
	void gcis_amar()
	{
		int m = 0, n = 0;
		cin>>m;
		int* arr1 = new int[m];
		for(int i = 0; i < m; i++)
			cin>>arr1[i];
		cin>>n;
		int* arr2 = new int[n];
		for(int i = 0; i < n; i++)
			cin>>arr2[i];
		int* lis1 = lisfunction(arr1,m);
		int* lis2 = lisfunction(arr2,n);
		int** lcsroot;
		int** lcs = lcsfunction(arr1,arr2,m,n,lcsroot);
		/*for(int i = 0; i < m; i++)
			cout<<lis1[i]<<'\t';
		cout<<endl;
		for(int i = 0; i < n; i++)
			cout<<lis2[i]<<'\t';
		cout<<endl;
		for(int i = 0; i <= m; i++)
		{
			for(int j = 0; j <= n; j++)
			{
				cout<<lcs[i][j]<<'\t';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i = 0; i <= m; i++)
		{
			for(int j = 0; j <= n; j++)
			{
				cout<<lcsroot[i][j]<<'\t';
			}
			cout<<endl;
		}
		cout<<endl;*/
		int max = 0;
		vector<int> result;
		for(int i = m; i>=0; i--)
		{
			for(int j = n; j>=0; j--)
			{
				if(lcsroot[i][j] == 1)
				{
					if(lcs[i][j] > max)
					{
						int temp = lcs[i][j];
						if(temp > lis1[i-1])
							temp = lis1[i-1];
						if(temp > lis2[j-1])
							temp = lis2[j-1];
						if(temp > max)
						{
							max = temp;
							int a = i, b = j;
							result.clear();
							while(lcsroot[a][b] != 0)
							{
								if(lcsroot[a][b] == 1)
								{
									result.push_back(arr1[a-1]);
									a--;
									b--;
								}
								else if(lcsroot[a][b] == 2)
								{
									a--;
								}
								else
								{
									b--;
								}
							}
						}
					}
				}
			}
		}
		cout<<max<<endl;
		if(max == result.size())
		{
			for(int i = result.size() - 1; i >= 0; i--)
			{
				cout<<result[i]<<' ';
			}
			cout<<endl;
		}
		else
		{
			int* arr = new int[result.size()];
			for(int i = 0; i < result.size(); i++)
				arr[i] = result[result.size() - i - 1];
			int* lishelp = new int[result.size()];
			int* lisarr = new int[result.size()];
			lisarr[0] = 1;
			lishelp[0] = -1;
			for(int i = 1; i < result.size(); i++)
			{
				int index = -1;
				int maxj = 0;
				for(int j = 0; j < i; j++)
				{
					if(arr[j] < arr[i] && maxj < lisarr[j])
					{
						maxj = lisarr[j];
						index = j;
					}
				}
				lisarr[i] = maxj + 1;
				lishelp[i] = index;
			}
			/*for(int i = 0; i < result.size(); i++)
			{
				cout<<arr[i]<<'\t';
			}
			cout<<endl;
			for(int i = 0; i < result.size(); i++)
			{
				cout<<lisarr[i]<<'\t';
			}
			cout<<endl;
			for(int i = 0; i < result.size(); i++)
			{
				cout<<lishelp[i]<<'\t';
			}
			cout<<endl;*/
			int x = result.size() - 1;
			vector<int> newresult;
			bool found_first = false;
			while(x != -1)
			{
				if(x == 0 || lishelp[x] != -1)
				{
					found_first = true;
					newresult.push_back(arr[x]);
					x = lishelp[x];
				}
				else if(found_first == false)
				{
					x--;
				}
				else
				{
					break;
				}
			}
			for(int i = newresult.size() - 1; i>= 0; i--)
			{
				cout<<newresult[i]<<' ';
			}
			cout<<endl;
		}
	}

	// Longest Common Increasing Subsequence
	int LCIS_size( vector< int> A, vector< int> B)
	{
		int N = ( int) A.size(), M = ( int) B.size(), len = 0;
		vector< int> C(M, 0);
		for( int i = 0; i < N; i++)
			for( int cur = 0, j = 0; j < M; j++)
				if( A[i] == B[j] && cur + 1 > C[j]) C[j] = cur + 1;
				else if(C[j] > cur && B[j] < A[i]) cur = C[j];
				for( int i = 0; i < M; i++) if(C[i] > len) len = C[i];
				return len;
	}

	// Longest Common Increasing Subsequence
	vector< int> LCIS( vector< int> A, vector< int> B)
	{
		int N = ( int) A.size(), M = ( int) B.size(), len = 0, idx = -1;
		vector< int> C(M, 0), res;
		vector< vector< pair< int, int> > > possible(M);

		for( int i = 0; i < N; i++)
			for( int cur = 0, last = -1, j = 0; j < M; j++)
				if( A[i] == B[j])
				{
					possible[j].push_back(make_pair(cur + 1, last));
					if(cur + 1 > C[j]) C[j] = cur + 1;
				}
				else if( B[j] < A[i] && C[j] > cur) { cur = C[j]; last = j; }

				for( int i = 0; i < M; i++)
					if(C[i] > len) { len = C[i]; idx = i; }

					while(len)
					{
						res.push_back( B[idx]);
						for( int i = 0; i < (int)possible[idx].size(); i++)
							if(possible[idx][i].first == len)
							{
								idx = possible[idx][i].second;
								break;
							}
							len--;
					}
					reverse(res.begin(),res.end());
					return res;
	}

	void gcis()
	{
		int N,M;
		vector< int> A,B;
		// Leer A
		scanf( "%d",&N); A.clear(); A.resize(N);
		for( int i = 0; i < N; i++) scanf( "%d",&A[i]);
		// Leer B
		scanf( "%d",&M); B.clear(); B.resize(M);
		for( int i = 0; i < M; i++) scanf( "%d",&B[i]);
		// Calcular LCIS
		//printf("%d\n",LCIS_size(A,B));
		vector< int> ans = LCIS(A,B);
		printf( "%d\n",(int )ans.size());
		for( int i = 0; i < ( int)ans.size(); i++)
			if(i == 0) printf( "%d",ans[i]);
			else printf( " %d",ans[i]);
			if(( int)ans.size() != 0) printf( "\n");
	}


	int dfsgraphbalancingact(vector< vector< pair<int, int> > >& data, bool* visited, int index, int& pidx, int pindex)
	{
		visited[index] = true;
		int count = 1;
#ifdef DEBUG
		//printf("N: %d\n",index);
#endif
		
		for(unsigned int i = 0; i < data[index].size(); i++)
		{
			if(!visited[data[index][i].first])
			{
				int idx = -1;
				int temp = dfsgraphbalancingact(data, visited, data[index][i].first, idx, index);
				count += temp;
				data[index][i].second = temp;
				if(idx != -1)
					data[data[index][i].first][idx].second = data.size() - temp;
				
			}
			if(pindex != -1 && pindex == data[index][i].first)
				pidx = i;
		}
		return count;
	}

	int dfsbalance(vector< vector< pair<int, int> > >& data, int& minbalance, bool* visited)
	{
		int numOfNodes = data.size();
		int time = 0;
		
		std::memset(visited,0,sizeof(bool)*numOfNodes);

		for(int i = 0;i<numOfNodes; i++)
		{
			if(!visited[i])
			{
				int pidx=0;
				dfsgraphbalancingact(data, visited, i,pidx,-1);
			}
		}
		
		//std::memset(visited,0,sizeof(bool)*numOfNodes);

		int globalmin = 10000000;
		int globalindex = 0;
		for(int index = 0;index<numOfNodes; index++)
		{
			int max = 0;
			for(unsigned int i = 0; i < data[index].size(); i++)
			{
				if(data[index][i].second > max)
					max = data[index][i].second;
			}
			if(max < globalmin)
			{
				globalmin = max;
				globalindex = index;
			}
		}
		minbalance = globalmin;
		return globalindex;
	}

	void balancingact()
	{
		int testcases = 0;
		cin>>testcases;
		bool* visited = new bool[20000];
		while(testcases--)
		{
			int numnodes = 0;
			cin>>numnodes;
			vector<vector < pair<int,int> > > graph;
			for(int i = 0; i < numnodes; i++)
			{
				std::vector< std::pair<int, int> > temp;
				graph.push_back(temp);
			}
			for(int i = 1; i < numnodes; i++)
			{
				int start = 0, end = 0;
				cin>>start>>end;
				std::pair<int, int> temp(end-1, 0);
				graph[start-1].push_back(temp);
				pair<int,int> temp2(start-1,0);
				graph[end-1].push_back(temp2);
			}
			int minbalance = 0;
			cout<<dfsbalance(graph,minbalance,visited)+1<<" ";
			cout<<minbalance<<endl;
		}
	}

	void verticalhistogram()
	{
		const int start = 65;
		int numstrings = 4;
		string input;
		map<char,int> histogram;
		for(int i = 0; i <26; i++)
			histogram[i+start] = 0;
		int maxCount = 0;
		while(numstrings--)
		{
			getline(cin,input);
			for(int i = 0; i < input.size(); i++)
			{
				if(input[i] >= start && input[i] <= start + 25)
					histogram[input[i]]++;
			}
		}
		for(int i = 0; i < 26; i++)
		{
			if(maxCount < histogram[i + start])
				maxCount = histogram[i + start];
		}
		while(maxCount)
		{
			for(int i = 0; i < 26; i++)
			{
				if(histogram[i + start] == maxCount)
				{
					cout<<"*";
					histogram[i + start]--;
				}
				else
					cout<<" ";
				cout<<" ";
			}
			cout<<endl;
			maxCount--;
		}
		for(int i = 0; i < 26; i++)
			cout<<char(i+start)<<" ";
		cout<<endl;
	}

	void herdsums()
	{
		unsigned int i,j,n,ways=0;
		long int remain;
		scanf("%u", &n);

		for (i=n; i!=0; --i) {
			remain = n;
			for (j=i; remain>0; --j)
				remain -= j;
			if (remain == 0)
				++ways;
		}

		printf("%u\n", ways);
	}

	int reversenum(int input)
	{
		int result = 0;
		while(input)
		{
			result = result*10 + input%10;
			input = input/10;
		}
		return result;
	}
	void addreversenum()
	{
		int testcases;
		cin>>testcases;
		while(testcases--)
		{
			int a,b;
			cin>>a>>b;
			cout<<reversenum(reversenum(a) + reversenum(b))<<endl;
		}
	}

	void ridetoschool()
	{
		int testcases = 1;
		cin>>testcases;
		while(testcases)
		{
			
		}
	}

};
