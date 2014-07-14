// For fb projects

#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool valid_rpn(string& src)
{
	vector<char> stack;
	for(unsigned int i = 0; i < src.size(); i++)
	{
		if(src[i] == 'x')
			stack.push_back(src[i]);
		else
		{
			if(stack.size() > 1)
			{
				stack.pop_back();
			}
			else
				return false;
		}
	}
	if(stack.size() > 1)
		return false;
	return true;
}

int tester_rpn(string& src)
{
	int xs = 0;
	int noOfReplaces = 0;
	int noOfdeletes = 0;
	int noOfInserts = 0;
	for (unsigned int i = 0; i < src.length(); i++) 
	{
		if (src[i] == 'x')
			xs++;
		else 
		{
			if (xs > 1) 
			{
				xs--;
			} 
			else if (xs == 1) 
			{
				if (noOfdeletes > 0) 
				{
					noOfReplaces++;
					noOfdeletes--;
				} 
				else 
				{
					// If this is last {
					if (i == src.length() - 1) 
					{
						// Add one x at first
						noOfInserts++;
					} 
					else 
					{
						noOfdeletes++;
					}
				}
			} 
			else 
			{
				if (noOfdeletes > 1) 
				{
					// As the 2 deletes can be replcaced with xs
					noOfdeletes = noOfdeletes - 2;
					noOfReplaces = noOfReplaces + 2;
				}
				else
				{
					noOfdeletes++;
				}
			}
		}
	}
	while (xs > 1) 
	{
		if (xs > 2) {
			// Replace one x with *
			noOfReplaces++;
			xs = xs - 2;
		}
		if (xs == 2) {
			// Add one * at last
			noOfInserts++;
			xs--;
		}
	}
	cout<<"Deletes: "<<noOfdeletes<<" : Inserts :"<<noOfInserts<<" : replaces : "<<noOfReplaces<<std::endl;
	return noOfdeletes + noOfInserts + noOfReplaces;
}

void check_valid_rpn()
{
	string str = "xx*xx*xx*";
	cout<<tester_rpn(str)<<std::endl;
}
