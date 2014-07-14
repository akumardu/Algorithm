#include<iostream>

#ifndef ALGO4IV
#define ALGO4IV

//Implement a fasthteger square root function that takes
//in a 32-bit unsigned integer and returns another 32-bit unsigned integer
//that is the floor of the square root of the input.

int sq_root(int num)
{
	int low = 0,high = num/2,mid = 0;
	while(low <= high)
	{
		mid = low + (high-low)/2;
		if(mid* mid <= num && (mid + 1) * (mid + 1) > num)
			return mid;
		else if(mid * mid < num)
			low = mid + 1;
		else 
			high = mid - 1;
	}
	return 0;

}


//Write a method that takes a sorted array A of integers and a key k md
//retums the hdex of first occurrmce of k h A.Retum-l if k does Rot
//appear in A. Write tests to verify your code.

int bin_search_1(int* arr, int n, int k)
{
	int low = 0, high = n-1,mid = 0;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if(arr[mid] == k && ( mid == 0 || arr[mid - 1] < k))
			return mid;
		else if( arr[mid] >= k)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}


//Design amfacieIIt algorithm1hatfiMs the iMex ofthe first occurrence of larger than a speCed key k; return -1 every element is
//less than or equal to k.

int big_bin_search(int* arr, int n, int k)
{
	int low = 0, high = n-1, mid = 0;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if((mid == (n - 1)) && arr[mid] <= k)
			return -1;
		else if( arr[mid] > k && (mid == 0 || arr[mid - 1] <= k))
			return mid;
		else if(arr[mid] > k)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

//SEARCH A SORTED ARRAY FOR A[i] = i

int exact_match_bin_search(int* arr, int n)
{
	int low = 0, high = n-1, mid = 0;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if(arr[mid] == mid)
			return arr[mid];
		else if(arr[mid] > mid)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

//SEARCH AN ARRAY OF UNKNOWN LENGTH
int bin_search_unknown(int* arr, int n, int k)
{
	int low = 0, high = 1, mid = 0;
	while(high < n && arr[high] < k)
		high = high*2;
	low = high/2;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if(arr[mid] == k)
			return mid;
		else if(arr[mid] > k)
			high = mid -1;
		else
			low = mid + 1;
	}
	return -1;
}

//Search lowest 
int bin_search_lowest(int* arr, int n)
{
	int low = 0, high = n-1, mid = 0;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if(arr[mid] - 1 > mid)
		{
			if( mid && (arr[mid - 1] - 1 > (mid - 1)))
				high = mid -1;
			else if(mid == 0)
				return 1;
			else
				return arr[mid-1] + 1;
		}
		else
			low = mid + 1;
	}
	return -1;
}

#endif