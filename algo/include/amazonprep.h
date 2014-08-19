#include<iostream>

namespace amazonprep
{
	using namespace std;

	//Given an array of 0s and 1s sorted. Find the first occurrence of 1 ( Binary Search)
	int program_1(int* arr, int size)
	{
		int low = 0, high = size - 1;
		int mid = 0;
		while(low < high)
		{
			mid = low + (high - low)/2;
			if(arr[mid] == 0 && arr[mid+1] == 1)
				return mid+1;
			else if(arr[mid] == 1)
			{
				high = mid-1;
			}
			else
			{
				low = mid+1;
			}
		}
		if(mid == 0)
			return mid;
		else
			return -1;
	}
	void testprogram_1()
	{
		int arr[] = {0,1,1,1,1,1};
		cout<<program_1(arr,6);
	}
}