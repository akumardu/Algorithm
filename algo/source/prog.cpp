#include<iostream>
#include<time.h>

using namespace std;

bool checkDuplicates(long num)
{
	long use = 0;
	while(num>0)
	{
		long ind = num%10;
		num = num/10;
		long index = 1 << ind;
		//cout<<"use :"<<use<<" index: "<<index<<endl;
		if((use & index) == index)
			return false;
		use = use | index;
	}
	return true;
}
int prog()
{
	int count=0;
        int jump = 0, big_jump = 0;
	clock_t start = clock();
        //long i = 999;
	for(long i = 1; i < 100000000; i++)
	{ 
		if(checkDuplicates(i))
		{
			//cout<<i<<endl;
			count++;
                        if(jump && jump > big_jump)
				big_jump = jump;
			jump = 0;
		}
		else
			jump++;
	}
        cout<<"Count : "<<count<<" Jump: "<<big_jump<<endl;
        clock_t ends = clock();
	cout<<"Running time: "<<(double)(ends - start)/CLOCKS_PER_SEC;
	cout<<endl;
	return 0;
}
