#include <iostream>
#include "time.h"
#include "limits.h"
#include "misc_small.h"
#include<stack>

#ifndef MISC_H
#define MISC_H

#define RANDOMLENGTH 50
// Generate random array 
// Deletion is handed over to the client
int* randomArrayGenerator(int& length, int maxLimit = INT_MAX, int minLimit=0)
{
	time_t secs;
	time(&secs);
	//To introduce random order between two consecutive calls
	Sleep(1000);
	srand((unsigned int)secs);
	while(!length)
	length = rand()%RANDOMLENGTH;
	int* arr = new int[length];
	for(int i = 0 ; i < length; i++)
	{
		if(minLimit < 0)
			arr[i] = rand()%maxLimit - rand()%(-minLimit);
		else
		{
			arr[i] = rand()%maxLimit + minLimit;
			if(arr[i] > maxLimit) arr[i] = maxLimit;
		}
	}
	return arr;
}

void printArra(const int* arr, const int length)
{
	for(int i = 0; i < length; i++)
		std::cout<<arr[i]<<" ";
	std::cout<<"Done !!"<<std::endl;
}

int partition(int* arr,int low,int high)
{
	int pivotal = arr[low];
	int pivot = low;
	while(low < high)
	{
		while(arr[low] <= pivotal && low <= high)
			low++;
		while(arr[high] > pivotal && high > 0)
			high--;
		if(low < high)
		{
			swap<int>(arr[low],arr[high]);
			//low++;
			//high--;
		}
	}
	
	swap<int>(arr[pivot],arr[high]);
	return high;
}

void quicksort(int* arr, int low, int high)
{
	if(low >= high)
		return;
	int pivot = (high+low)/2;
	swap<int>(arr[pivot],arr[low]);
	pivot = partition(arr,low, high);
	//printArra(arr+low,high - low + 1);
	quicksort(arr,low,pivot -1 );
	quicksort(arr,pivot + 1,high);
}

/*Dutch National Flag problem, 
Three color problem : Partition the given integer array in three parts such that all the elements of part P1 < Part p2 < part p3. 
(Two color problem sort binary array)*/
void dnf_3color()
{
	int length = 0;
	int* arr = randomArrayGenerator(length,3);
	printArra(arr,length);
	int first = 0, second = 0, third = length -1;
	while(second <= third)
	{
		if(arr[second] == 0)
		{
			// Move both since first is already sorted
			swap<int>(arr[second],arr[first]);
			first++;
			second++;
		}
		else if(arr[second] == 1)
			second++;
		else if(arr[second] == 2)
		{
			swap<int>(arr[second],arr[third]);
			third--;
		}
	}
	printArra(arr,length);
	delete[] arr;

}


//Find the median of two sorted arrays with minimum possible memory and time complexity
// Same size arrays
int findmediancaller(int* arrA, int*arrB, int lowA, int highA, int lowB, int highB)
{
	int medA = (lowA + highA)/2, medB = (lowB+highB)/2;
	if(lowA > highA || lowB > highB) return -1;
	if(lowA == highA && lowB == highB)
		return (arrA[lowA] + arrB[lowB])/2;
	if((highA - lowA) == 1 && (highB - lowB) == 1)
	{
		return (max_am(arrA[lowA],arrB[lowB]) + min_am(arrA[highA],arrB[highB]))/2;
	}
	if(arrA[medA] == arrB[medB]) return arrA[medA];
	else
	{

		if(arrA[medA] < arrB[medB])
		{
			if((highA - medA) < (medB - lowB))
				medA--;
			else if((highA - medA) > (medB - lowB))
				medB++;
			return findmediancaller(arrA,arrB,medA,highA,lowB,medB);
		}
		else
		{
			if((medA - lowA) > (highB - medB))
				medB--;
			else if((medA - lowA) < (highB - medB))
				medA++;
			return findmediancaller(arrA,arrB,lowA,medA,medB,highB);
		}
	}
}

int verifymedian(int* arrA, int* arrB, int lenA, int lenB)
{
	int total = lenA + lenB,i = 0, j = 0,k=0;
	int* arr = new int[total];
	while(i < lenA && j < lenB)
	{
		if(arrA[i] < arrB[j])
			arr[k++] = arrA[i++];
		else
			arr[k++] = arrB[j++];
	}
	while(i<lenA)
		arr[k++] = arrA[i++];
	while(j<lenB)
		arr[k++] = arrB[j++];
	if(total %2)
	{
		int temp = arr[total/2 +1];
		delete[] arr;
		return temp;
	}
	else
	{
		int temp = (arr[total/2] + arr[total/2 + 1])/2;
		delete[] arr;
		return temp;
	}
}

void findmedianoftwo()
{
	int lenA=0,lenB=0, i = 0;
	while(i < 20)
	{
		int* arrA = randomArrayGenerator(lenA);
		lenB = lenA; // switch this on for same size arrays
		int* arrB = randomArrayGenerator(lenB);
		//printArra(arrA,lenA);
		quicksort(arrA,0,lenA-1);
		quicksort(arrB,0,lenB-1);
		//printArra(arrA,lenA);
		//printArra(arrB,lenB);
		int temp = verifymedian(arrA,arrB,lenA,lenB);
		std::cout<<"median: "<<findmediancaller(arrA,arrB,0,lenA,0,lenB)<<std::endl;
		std::cout<<"True : "<<temp<<std::endl;
		delete[] arrA;
		delete[] arrB;
		i++;
	}
}



//Binary search - Recursive
int binSearchR(int* arr, int start, int length, int value)
{
	int mid = (start+length)/2;
	if(length < start)
		return -1;
	if(arr[mid] == value) return mid;
	else if(arr[mid] < value) return binSearchR(arr, mid + 1 ,length, value);
	else
		return binSearchR(arr,start, mid - 1,value);
}
//Binary search - Iterative
int binSearchI(int* arr, int length, int value)
{
	int low = 0, high = length-1, med = 0;
	while(low <= high)
	{
		med = (low + high)/2;
		if(arr[med] == value) return med;
		else if(arr[med] < value) low = med + 1;
		else high = med - 1;
	}
	return -1;
}
//binsearch testing
void binsearch()
{
	int i = 0;
	while(i++ < 20)
	{
		int len=0;
		int* arr = randomArrayGenerator(len);
		//printArra(arr,len);
		quicksort(arr,0,len-1);
		time_t secs;
		time(&secs);
		srand((unsigned int)secs);
		int value = arr[rand()%len];
		std::cout<<" val : "<<value<<std::endl;
		std::cout<<binSearchI(arr,len,value)<<" : "<<binSearchR(arr,0,len-1,value)<<std::endl;
		//std::cout<<binSearchI(arr,len,value)<<std::endl;
	}
}


//Suppose that you are given a sorted sequence of distinct integers {a1, a2, . . . , an}. 
//Give an O(lg n) algorithm to determine whether there exists an i index such as A[i] = i.
//For example, in {−10,−3, 3, 5, 7}, a3 = 3. In {2, 3, 4, 5, 6, 7}, there is no such i.
int binSearchMod(int* arr, int low, int high)
{
	if(low > high)
		return -1;
	int mid = (low+high)/2;
	if(mid > arr[mid])
		return binSearchMod(arr,mid + 1,high);
	else if(mid < arr[mid])
		return binSearchMod(arr,low,mid -1);
	else
		return mid;
}



class doublist
{
public:
	char data;
	doublist *next;
	doublist * prev;
	doublist(char d, doublist* n): data(d), next(n){}
	void make_double(doublist* prevdll){
		this->prev = prevdll;
		if(this->next != NULL)
			this->next->make_double(this);
	}
};

//create random double list
doublist* create()
{
	doublist *dev = new doublist('a',
					new doublist('b',
						new doublist('c',
							new doublist('d',
								new doublist('e',
									new doublist('f',NULL))))));
	dev->make_double(NULL);
	return dev;

}

//Finding middle element in a list
doublist* findMiddle(doublist* head)
{
	doublist* fp = head;
	doublist* sp = head;
	while(fp != NULL && fp->next != NULL)
	{
		fp = fp->next->next;
		sp = sp->next;
	}
	return sp;
}

//Converting dll to bst
doublist* nodetolist(doublist* head, doublist* end);
void test_1()
{
	doublist* dll = create();
	doublist* d = dll;

	while(d->next != NULL)
		d = (doublist*)(d->next);
	doublist* midd = nodetolist(dll,d);
	std::cout<<"done"<<std::endl;
}
doublist* nodetolist(doublist* head, doublist* end)
{
	if(head == end)
	{
		head->prev = NULL;
		end->next = NULL;
		return head;
	}

	if(head == NULL || end == NULL)
		return NULL;

	head->prev = NULL;
	end->next = NULL;

	doublist* mid = (doublist*)findMiddle(head);
	mid->prev = nodetolist(head,mid->prev);
	mid->next = nodetolist((doublist*)mid->next,end);
	return mid;
}

void kswap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
int findKthSmallest(int* arr, int k, int start, int end)
{
	int j = start, i = start - 1;
	int pivot = arr[end];
	for(;j < end; j++)
	{
		if(arr[j] < pivot)
		{
			i++;
			kswap(arr,i,j);
		}
	}

	i++;
	kswap(arr,i,end);
	
	int smaller = i - start + 1;
	if(smaller == k)
		return arr[i];
	else if(smaller > k)
		return findKthSmallest(arr,k,start,i-1);
	else
		return findKthSmallest(arr,k-smaller,i+1,end);
}

//Rearrange into alternate positive and negative numbers
void rearrange_alternate(int* arr, int len)
{
	int pos = 0, neg = 1;
	while(pos < len && neg < len)
	{
		while(pos < len && arr[pos] > 0)
			pos += 2;
		while(neg < len && arr[neg] < 0)
			neg += 2;
		if(pos < len && neg < len)
			kswap(arr,pos,neg);
	}
}

//generates kmp table for a-z chars
int** kmptable(char* pattern, int len)
{
	const int charsize = 26;
	int** dfa = new int*[len];
	for(int i = 0; i < len; i++)
	{
		dfa[i] = new int[charsize];
		std::memset(dfa[i],0,charsize*sizeof(int));
	}
	dfa[0][pattern[0] - 'a'] = 1;
	int x = 0;
	for(int i = 1; i < len; i++)
	{
		for(int j = 0; j < charsize; j++)
			dfa[i][j] = dfa[x][j];
		dfa[i][pattern[i] - 'a'] = i+1;
		x = dfa[x][pattern[i] - 'a'];
	}
	return dfa;
}

int find_kmp(char* text, int textlen, char* pattern, int patternlen)
{
	int** dfa = kmptable(pattern,patternlen);
	int i = 0, j = 0;
	for(; j < patternlen && i < textlen; i++)
	{
		j = dfa[j][text[i] - 'a'];
	}
	if(j == patternlen)
		return i - patternlen;
	return textlen;
}

//generate bm skip table and compare
int find_bm(char*text, int textlen, char* pattern, int patternlen)
{
	const int charsize = 26;
	int* right = new int[charsize];
	std::memset(right,-1,charsize*sizeof(char));
	for(int i = 0; i < patternlen; i++)
		right[pattern[i] - 'a'] = i;
	int skip = 0;
	for(int i = 0; i <= textlen-patternlen; i+=skip)
	{
		skip = 0;
		for(int j = patternlen - 1; j >= 0; j--)
		{
			if(pattern[j] != text[i+j])
			{
				skip = ((j - right[text[i+j] - 'a']) > 1)?(j - right[text[i+j] - 'a']):1;
				break;
			}
		}
		if(skip == 0) return i;
	}
	return textlen;
}


//Find the largest rectangle under a histogram
int largest_rectangle_under_histogram(int* hist, int len)
{
	std::stack<int> st;
	int i = 0;
	int max_area = 0;
	while(i < len)
	{
		if(st.empty() || hist[i] <= hist[st.top()])
		{
			st.push(i);
			i++;
		}
		else
		{
			int tp = st.top();
			st.pop();
			int area = hist[tp]*(st.empty()?i:i-st.top()-1);
			if(area > max_area)
				max_area = area;
		}
	}
	while(!st.empty())
	{
		int tp = st.top();
		st.pop();
		int area = hist[tp]*(st.empty()?i:i-st.top() - 1);
		if(area > max_area)
			max_area = area;
	}
	return max_area;
}

//Ones and twos and threes
void counttwos(int* arr, int len)
{
	int ones = 0, twos = 0, not_threes = 0, x = 0,threes = 0;
	for(int i = 0; i < len; i++)
	{
		x = arr[i];
		twos = twos | (ones & x);
		ones = ones ^ x;
		not_threes = ~(ones & twos);
		ones = ones & not_threes;
		twos = twos & not_threes;
	}
	
	x = 0;
	for(int i = 0; i < len; i++)
		x = x ^ arr[i];
	threes = x ^ ones;

	std::cout<<ones<<" : "<<twos<<" : "<<threes<<std::endl;
}

// Printing pascal's triangle
void printPascal(int n)
{
  for (int line = 1; line <= n; line++)
  {
    int C = 1;  // used to represent C(line, i)
    for (int i = 1; i <= line; i++)  
    {
      printf("%d ", C);  // The first value in a line is always 1
      C = C * (line - i) / i;  
    }
    printf("\n");
  }
}


// finding pivot in a rotated sorted array
int find_pivot(int* arr, int len)
{
	int l = 0, h = len-1, mid = 0;
	while(l < h)
	{
		mid = l + (h - l) / 2;
		if(arr[mid] > arr[h])
			l = mid + 1;
		else
			h = mid;
	}
	//std::cout<<mid<<" : "<< l<<std::endl;
	return mid;
}

//choosing coins from either end DP solution
int max_coin_choose(int* arr, int len)
{
	int** dp = new int*[len];
	for(int i = 0; i < len; i++)
	{	
		dp[i] = new int[len];
		std::memset(dp[i],0,len*sizeof(int));
		dp[i][i] = arr[i];
		if(i < (len-1))
			dp[i][i+1] = max(arr[i],arr[i+1]);
	}

	for(int l = 2; l < len; l++)
	{
		for(int i = 0; i < len - l ; i++)
		{
			int j = i + l ;
			dp[i][j] = max(arr[i] + min(dp[i+2][j],dp[i+1][j-1]),arr[j] + min(dp[i+1][j-1],dp[i][j-2]));
			
		}
	}
	
	std::cout<<dp[0][len-1]<<std::endl;
	return dp[0][len-1];
}


//n choose r
void n_choose_r_util(char* arr, int n, int r, char* data, int dindex, int arrindex)
{
	if(dindex == r)
	{
		for(int i = 0; i < r; i++)
			std::cout<<data[i]<<" ";
		std::cout<<std::endl;
		return;
	}
	if(arrindex == (n))
		return;
	data[dindex] = arr[arrindex];
	n_choose_r_util(arr,n,r,data,dindex+1,arrindex+1);
	n_choose_r_util(arr,n,r,data,dindex,arrindex+1);
}
void n_choose_r(char* arr, int n, int r)
{
	char* data = new char[r];

	n_choose_r_util(arr, n, r, data, 0, 0);
}

//fill an array of k elements from len
void print_combo(char* arr, int len, int k, char* result, int index)
{
	if(index == k)
	{
		for(int i = 0; i < k; i++) std::cout<<result[i];
		std::cout<<std::endl;
		return;
	}
	for(int i = 0; i < len; i++)
	{
		result[index] = arr[i];
		print_combo(arr,len,k,result,index+1);
	}
}


//is String interleave of two given strings
bool is_string_interleaved(std::string& astr, std::string& bstr, std::string cstr)
{
	if(astr.size() + bstr.size() != cstr.size())
		return false;

	int** inter = new int*[astr.size() + 1];
	for(unsigned int i = 0; i < astr.size() + 1; i++)
	{
		inter[i] = new int[bstr.size() + 1];
		std::memset(inter[i],0,sizeof(int)*(bstr.size()+1));
	}
	inter[0][0] = true;

	for(unsigned  int i = 0; i <= astr.size(); i++)
	{
		for(unsigned int j = 0; j <= bstr.size(); j++)
		{

			if(i == 0 && j == 0)
				inter[i][j]= true;
			else if(i == 0 && bstr[j-1] == cstr[i+j - 1])
				inter[i][j] = inter[i][j-1];
			else if(j == 0 && astr[i-1] == cstr[i+j-1])
				inter[i][j] = inter[i-1][j];
			else if(i > 0 && astr[i-1] != cstr[i+j-1] && j > 0 && bstr[j-1] == cstr[i+j-1])
				inter[i][j] = inter[i][j-1];
			else if(i > 0 && astr[i-1] == cstr[i+j-1] && j > 0 && bstr[j-1] != cstr[i+j-1])
				inter[i][j] = inter[i-1][j];
			else if(i > 0 && astr[i-1] == cstr[i+j-1] && j > 0 && bstr[j-1] == cstr[i+j-1])
				inter[i][j] = (inter[i][j-1] || inter[i-1][j]);

		}
	}
	return (inter[astr.size()][bstr.size()] != 0);
}

int findMissing(std::vector<int> input, int col = 0 )
{
	if(col == sizeof(int)) return 0;
	if(input.size() == 0) return 0;
	std::vector<int> odd;
	std::vector<int> even;
	for(uint i = 0; i < input.size(); i++)
	{
		if((input[i] & (1 << col)) == 0)
			even.push_back(input[i]);
		else
			odd.push_back(input[i]);
	}

	if(odd.size() >= even.size())
		return (findMissing(even,col + 1) << 1)|0;
	else
		return (findMissing(odd,col + 1)<<1)|1;
}

#endif