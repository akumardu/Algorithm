#include<iostream>

using namespace std;

namespace geeksforgeeks
{
	// Find the difference between max and min elements of an array such that max lies 
	// to the right of the min element
	void maxDifference()
	{
		int testarr[] = {-2,-3,-10,-4,-7,-8};
		int length = 6;

		// Approach 1: Keep a count of min element and max difference
		int minelement = 0;
		int maxdifference = 0;
		for(int i = 1; i < length; i++)
		{
			if(testarr[minelement] > testarr[i])
			{
				minelement = i;
			}
			if(maxdifference < (testarr[i] - testarr[minelement]))
			{
				maxdifference = testarr[i] - testarr[minelement];
			}
		}
		cout<<maxdifference<<endl;

		// Approach 2: Create an array of consecutive differences, then find the 
		// max consecutive subarray. Using diff for consecutive differences.
		int localsum = 0;
		int globalsum = 0;
		int diff = 0;
		for(int i = 1; i < length; i++)
		{
			diff = testarr[i] - testarr[i-1];
			if(localsum + diff > 0)
				localsum = localsum + diff;
			else
				localsum = diff;
			if(globalsum < localsum)
				globalsum = localsum;
		}
		cout<<globalsum<<endl;
	}

	void fillXorO(char** arr, int startx, int starty, int endx, int endy, char input)
	{
		for(int i = starty; i <= endy; i++)
		{
			arr[startx][i] = input;
			arr[endx][i] = input;
		}
		for(int i = startx; i <= endx; i++)
		{
			arr[i][starty] = input;
			arr[i][endy] = input;
		}
	}

	void printMatrix(char** arr, int m, int n)
	{
		for(int i = 0; i< m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				cout<<arr[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void printAlternate(int m, int n)
	{
		char **arr = new char*[m];
		for(int i = 0;i < m; i++)
		{
			arr[i] = new char[n];
		}
		int startx = 0, starty = 0, endx = m-1, endy = n-1;
		int i = 0;
		while(startx < endx || starty < endy)
		{
			fillXorO(arr,startx,starty,endx,endy,((i%2) == 0)?'X':'O');
			i++;
			startx++;endx--;starty++;endy--;
		}
		if(startx == endx && starty == endy)
		{
			arr[startx][starty] = ((i%2) == 0)?'X':'O';
		}
		printMatrix(arr,m,n);
	}

}



