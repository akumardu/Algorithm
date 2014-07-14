
#include<iostream>
#include<string>
#include<deque>
#include<vector>

using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
	node* parent;

	node(int d, node* p = NULL, node* l = NULL, node* r = NULL )
	{
		data = d;
		parent = p;
		left = l;
		right = r;
	}
};

//You have a c style string containing some spaces. Move the spaces to the starting of the string. Do it in place in one iteration.
void program_1(char* str, int len)
{
	int j = len-1;
	for(int i = len-1; i>=0; i--)
	{
		if(str[i] == ' ')
			continue;
		else if(i != j)
		{
			char temp = str[i];
			str[i] = str[j];
			str[j] = temp;
			j--;
		}
	}
	for(;j>=0;j--)
		str[j] = ' ';
}

void test_program_1()
{
	char str[] = "abcd asd allk aa  aa  ";
	program_1(str,22);
	cout<<str<<endl;
}


//You have a bit pattern and an infinite stream of bits coming in. You need to raise an alarm whenever the given pattern comes. Storing the stream is not allowed.

int program_2(char* str, char* patt, int strlen, int pattlen)
{
	//use kmp to process bit patterns
	//pre-process the pattern to create jump table
	int* prearr = new int[pattlen];
	int i = 1,len = 0;
	prearr[0] = 0;
	while( i < pattlen)
	{
		if(patt[i] == patt[len])
		{
			len++;
			prearr[i] = len;
			i++;
		}
		else if(len != 0)
			len = prearr[len-1];
		else
		{
			prearr[i] = 0;
			i++;
		}
	}

	//print prearr
	for(int i = 0; i < pattlen; i++)
	{
		cout<<prearr[i]<<"\t";
	}
	cout<<"\n";

	//use the jump table for faster search
	for(int i = 0,j = 0; i < strlen;)
	{
		if(str[i] == patt[j])
		{
			i++;j++;
			if( j == pattlen)
				return i - pattlen;
		}
		else if ( j != 0)
			j = prearr[j-1];
		else
			i++;
	}
	return -1;
}

void test_program_2()
{
	char* str = "abcabcabcd";
	char* patt = "abcabcd";
	cout<<program_2(str,patt,10,7)<<endl;
}


//A sorted array has been rotated. You need to find out the point of inflexion, i.e the position at which the smallest element of the array is present.(I did this in log n time)
//    For example if the array is [6,7,8,9,1,2,3,4,5], the output should be 4

int program_3(int* arr, int len)
{
	int low = 0, high = len-1;
	int mid = 0;
	while(high >= low)
	{
		mid = low + (high - low)/2;
		if(((mid > 0 && arr[mid] < arr[mid - 1]) || mid == 0) && ( (mid < (len-1) && arr[mid] < arr[mid+1]) || mid == (len-1)))
			return mid;
		else if(arr[low] < arr[high])
		{
			high = mid - 1 ;
		}
		else
		{
			low = mid + 1;
		}
		
	}
	return 0;
}

void test_program_3()
{
	int arr[] = {5,6,7,8,9,10,11,12,13,14,1,2,3,4};
	cout<<arr[program_3(arr,14)];
}



//There is a 2D matrix of size 10 X 10, where you have to begin from the location (0,0) and move to the location (9,9). You can either move right on down. Find out the number of distinct paths in which you can reach (9,9) from (0,0).

int program_4(int n)
{
	int** arr2d = new int*[n];
	for(int i = 0; i < n; i++)
		arr2d[i] = new int[n];
	arr2d[0][0] = 0;
	for(int i = 1; i < n; i++)
	{
		arr2d[0][i] = 1;
		arr2d[i][0] = 1;
	}

	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j < n; j++)
		{
			arr2d[i][j] = arr2d[i-1][j] + arr2d[i][j-1];
		}
	}
	return arr2d[n-1][n-1];
}

void test_program_4()
{
	cout<<program_4(4)<<endl;
}



//Given an array of numbers, print the smallest numbers in a sliding window of size k. [Ex: 5,2,4,3,1 is the array and if k=3, the output should be 2, 3, 1].

//Hint: Using heap - takes O(n lg k). Using a modified queue structure, it takes O(n) :)

void program_5(int* arr, int len, int k)
{
	int i = 0;
	deque<int> dq;
	for(;i<k;i++)
	{
		while(!dq.empty() && arr[dq.back()] > arr[i])
			dq.pop_back();
		dq.push_back(i);
	}
	for(;i<len;i++)
	{
		cout<<arr[dq.front()]<<endl;
		while(!dq.empty() && dq.front() <= i-k)
			dq.pop_front();

		while(!dq.empty() && arr[dq.back()] > arr[i])
			dq.pop_back();
		dq.push_back(i);
	}

	cout<<arr[dq.front()];
}

void test_program_5()
{
	int arr[] = {5,2,4,3,1,6,0};
	program_5(arr,7,3);
}


//Generating all permutations of valid paranthesis
void program_6(int n, char* str, int left, int right, int index)
{
	if(2*n == index)
	{
		cout<<str<<endl;
		return;
	}
	if(left == right)
	{
		str[index] = '(';
		program_6(n,str,left+1,right,index+1);
	}
	if(left > right)
	{
		if(left < n)
		{
			str[index] = '(';
			program_6(n,str,left+1,right,index+1);
		}
		str[index] = ')';
		program_6(n,str,left,right+1,index+1);
		
	}
}

void test_program_6()
{
	int n = 3;
	char* str = new char[2*n + 1];
	str[2*n] = '\0';
	program_6(n,str,0,0,0);
}


//Find the first missing positive int
int program_7(int* arr, int len)
{
	for(int i = 0; i < len; )
	{
		while(i < len &&(arr[i] == i+1 || arr[i] == 0))
			i++;
		if(i == len)
			break;
		if(arr[i] <= 0)
			arr[i] = 0;
		else
		{
			int temp = arr[arr[i]-1];
			arr[arr[i]-1] = arr[i];
			if(temp < len && temp > 0 && arr[temp-1] == temp)
				continue;
			else if(temp >= len ) continue;
			else
			{
				arr[i] = temp;
			}
		}
	}
	for(int i = 0; i < len; i++)
	{
		if(arr[i] == 0)
			return i + 1;
	}
	return -1;
}

void test_program_7()
{
	int arr[] = {3,4,-1,1};
	cout<<program_7(arr,4)<<endl;
}


//number of ways to decode a message
void program_8(char* str, int len, int index, string result)
{
	if(index == len)
	{
		cout<<result<<endl;
		return;
	}
	if(index < len-1 && (str[index] == '1' || (str[index] == '2' && str[index+1] <= '6')))
	{
		int num = (str[index]-'0')*10 + str[index+1] - '0';
		string res = result;
		res = res.append(1,(char)(num-1 + 'A'));
		program_8(str,len,index+2,res);
		result = result.append(1,(char)(str[index] - '1' + 'A'));
		program_8(str,len,index+1,result);
	}
	else
	{
		result = result.append(1,(char)(str[index] - '1' + 'A'));
		program_8(str,len,index+1,result);
	}
}

void test_program_8()
{
	char str[] = "121";
	string res;
	program_8(str,3,0,res);
}



//all combinations which sum up to a number
//solutions repeat so need a way to discard duplicate solutions
void program_9(int* arr, int index, int k, int len,vector<int>& soln)
{
	if(k == 0)
	{
		for(unsigned int i = 0; i < soln.size(); i++)
			cout<<soln[i]<<"\t";
		cout<<endl;
		return;
	}

	if(k < 0)
		return;

	//if reps are allowed
	for(int i = 0; i < len; i++)
	{
		soln.push_back(arr[i]);
		program_9(arr,i,k-arr[i],len,soln);
		soln.pop_back();
	}

	//if reps are not allowed
	/*
	for(int i = index; i < len; i++)
	{
		soln.push_back(arr[i]);
		program_9(arr,i+1,k-arr[i],len,soln);
		soln.pop_back();
	}*/
}

void test_program_9()
{
	int arr[] = {1,2,5,6,7,10};
	vector<int> soln;
	program_9(arr,0,8,6,soln);
}


//Given an array of n elements which contains elements from 0 to n-1, with any of these numbers appearing any number of times. Find these repeating numbers in O(n) and using only constant memory space.
void program_10(int* arr, int len)
{
	for(int i = 0; i < len; i++)
	{
		if(arr[std::abs(arr[i])] < 0)
			cout<<abs(arr[i])<<endl;
		else
			arr[std::abs(arr[i])] = -arr[std::abs(arr[i])];
	}
}

void test_program_10()
{
	int arr[] =  {1, 2, 5, 1, 5, 6, 6};
	program_10(arr,7);
}


//Generate nCk : Different ways to chose k elements from n elements
void program_11(int* arr, int n, int k, int index,vector<int>& op)
{
	if(k == 0)
	{
		for(unsigned int i = 0; i < op.size(); i++)
			cout<<op[i]<<"\t";
		cout<<endl;
	}
	else
	{
		for(int i = index; i < n-k+1; i++)
		{
			op.push_back(arr[i]);
			program_11(arr,n,k-1,i+1,op);
			op.pop_back();
		}
	}
}

void test_program_11()
{
	int arr[] = {1,2,3,4,5};
	vector<int> op;
	program_11(arr,5,3,0,op);
}


//Given a binary tree with parent pointers, find the right sibling of a given node(pointer to the node will be given), 
//if it doesn’t exist return null. Do it in O(1) space and O(n) time.
node* program_12(node* root)
{
	int k = 1;
	node* parent = root->parent;
	while(parent != NULL)
	{
		if(root == parent->left)
		{
			int temp = k;
			node* r = parent->right;
			while(temp != 1 && r != NULL)
			{
				if(r->left == NULL)
					r = r->right;
				else
					r = r->left;
				temp--;
			}
			if(temp == 1 && r != NULL)
				return r;
		}
		
		root = parent;
		parent = parent->parent;
		k++;
		
	}
	return NULL;
}

void test_program_12()
{
	node* root = new node(1);
	node* a = new node(2,root);
	node* b = new node(3,root);
	root->left = a;
	root->right = b;
	node* c = new node(4,a);
	node* d = new node(5,b);

	a->left = c;
	b->right = d;

	cout<<program_12(c)->data<<endl;
	

}


//Printing a 2D matrix spirally
void spiralPrint(int str[3][4], int m, int n)
{
	int i = 0, j = 0, k = m, l = n;
	while(i < k && j < l)
	{
		for(int x = j; x < l; x++)
			cout<<str[i][x]<<"\t";
		i++;
		for(int x = i; x < k; x++)
			cout<<str[x][l-1]<<"\t";
		l--;
		if(i < k)
		for(int x = l-1; x >= j; x--)
			cout<<str[k-1][x]<<"\t";
		k--;
		if(j < l)
		for(int x = k-1; x >= i; x--)
			cout<<str[x][j]<<"\t";
		j++;
	}
}

void test_program_spiral()
{
	//int str[6][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16},{17,18,19,20},{21,22,23,24}};
	int str[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	spiralPrint(str,3,4);
}


//RLE
void stringCompression(char* str, int len)
{
	int i = 0, j= 0;
	while(j < len)
	{
		int count = 0;
		while(j < len && str[i] == str[j])
		{
			j++;count++;
		}
		if(count == 1)
		{
			i++;
			str[i] = str[j];
		}
		else
		{
			//assuming max_count < 10
			str[i+1] = count + '0';
			i+=2;
			str[i] = str[j];
		}
	}
}

void test_program_string_compression()
{
	//char str[] = "aaaabbbccaad";
	char str[] = "cabefgbbccaad";
	stringCompression(str,12);
	cout<<str<<endl;
}


void flipkart()
{
	int x, n;
	cin>>x;
	cin>>n;
	int* rating = new int[n];
	int* hike = new int[n];
	for(int i = 0; i < n; i++)
	{
		cin>>rating[i];
		hike[i] = 0;
	}
	set<int> local_min;
	for(int i = 0; i < n; i++)
	{
		if( i == 0 && rating[i] < rating[i+1])
			local_min.insert(i);
		else if(i == n-1 && rating[i] < rating[i-1])
			local_min.insert(i);
		else if( i != 0 && i != n-1 && rating[i] < rating[i-1] && rating[i] < rating[i+1])
			local_min.insert(i);
	}
	for(set<int>::iterator itr = local_min.begin(); itr != local_min.end(); itr++)
	{
		int this_min_low = *itr;
		int this_min_high = *itr;
		hike[this_min_low] = x;
		this_min_low--;
		this_min_high++;
		int count = 1;
		while(this_min_low >= 0 && rating[this_min_low ] > rating[this_min_low + 1]) 
		{
			count++;
			hike[this_min_low] = max(hike[this_min_low],count*x);
			this_min_low--;
		}
		if(this_min_low == 0 && rating[this_min_low] < rating[this_min_low+1])
			hike[this_min_low] = x;
		count = 1;
		while(this_min_high < n && rating[this_min_high ] > rating[this_min_high - 1]) 
		{
			count++;
			hike[this_min_high] = max(hike[this_min_high],count*x);
			this_min_high++;
		}
		if(this_min_high == n-1 && rating[this_min_high] < rating[this_min_high - 1])
		{
			hike[this_min_high] = x;
		}
	}
	long sum = 0;
	for(int i = 0; i < n; i++)
	{
		//cout<<hike[i]<<endl;
		sum += hike[i];
	}
	cout<<sum<<endl;
}

