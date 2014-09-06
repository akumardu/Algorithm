#include<iostream>
#include<math.h>

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


	//Finding square root of a number
	double program_2(double n)
	{
		double x = n;
		double y = 1;
		double e = 0.00001;
		while(abs(x-y) > e)
		{
			x = (x+ y)/2;
			y = n/x;
		}
		return x;
	}
	void testprogram_2()
	{
		cout<<program_2(20.0)<<":"<<sqrt(20.0)<<endl;
		cout<<program_2(1.0)<<":"<<sqrt(1.0)<<endl;
		cout<<program_2(2.0)<<":"<<sqrt(2.0)<<endl;
		cout<<program_2(0.5)<<":"<<sqrt(0.5)<<endl;
	}

	
	//Given an array, find the maximum sum that can be formed from the array such that no two adjacent elements are taken into consideration..
	//for ex:- 1,2,3,5 should return 7.
	int program_3(int* arr, int size)
	{
		if(size == 1)
			return arr[0];
		if(size == 2)
			return (arr[0]>arr[1])?arr[0]:arr[1];
		int adjmaxsum = max(max(arr[0],arr[1]),0);
		int farmaxsum = max(arr[0],0);
		for(int i = 2; i < size; i++)
		{
			int temp = max(farmaxsum + arr[i], adjmaxsum);
			farmaxsum = adjmaxsum;
			adjmaxsum = temp;
		}
		return adjmaxsum;
	}
	void testprogram_3()
	{
		int arr[] = {10,2,-3,3,10};
		cout<<program_3(arr,5);
	}
}





