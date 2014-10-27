
#include<iostream>
#include "bst.h"
#include<cstdlib>
#include "time.h"

#include<fstream>
#include<vector>
#include<string>
#include "stringtostring.h"
#include "trie.h"
#include "tree.h"
#include "glasses.h"

#include "SimpleTimer.h"
#include "graph.h"
#include "misc.h"
#include "sort.h"
#include "fb.h"
#include "ivstreet.h"
#include "pchal.h"
#include "codechef.h"
#include "project_euler.h"
#include "algo_part2.h"
#include "algo4iv.h"
#include "geeksforgeeks.h"
#include<iostream>
#include<algorithm>

#include "msiv.h"
#include "topcoder.h"
#include "peking.h"
#include "compprogprac.h"
#include "amazonprep.h"

typedef unsigned long long int big;

using namespace std;

tree* CreateRandomTree()
{
	std::cout<<"Testing Tree"<<std::endl;
	time_t secs;
	time(&secs);
	srand((unsigned int)secs);
	tree* root = new tree(rand());
	tree* retValue = root;
	for(int i =0; i<10; i++)
	{
		if(rand()%2)
		{
			tree* temp = new tree(rand());
			root->setLeft(temp);
		}
		if(rand()%2)
		{
			tree* temp = new tree(rand());
			root->setRight(temp);
		}
		if(rand()%2)
		{
			if(root->getLeft() != NULL)
				root = root->getLeft();
			else if(root->getRight() != NULL)
				root = root->getRight();
		}
		else
		{
			if(root->getRight() != NULL)
				root = root->getRight();
			else if(root->getLeft() != NULL)
				root = root->getLeft();
		}
	}
	return retValue;
}

void randomTreeTesting()
{
	tree* root = CreateRandomTree();
	root->printTree();
	delete root;
}

void bst_testing()
{
	
	bst* root = new bst(100);
	root->insertNode(50);
	root->insertNode(500);
	root->insertNode(5);
	root->insertNode(250);
	root->insertNode(25);
	root->insertNode(240);
	root->insertNode(501);
	root->insertNode(10);
	root->insertNode(3);
	root->insertNode(2);
	root->insertNode(1);
	root->insertNode(2500);
	root->insertNode(6);

	root->printTree();
	/*int done = -1;
	root->print_right_only(root,0,done);*/

	bst::post_order_traversal(root,2500);

}

//void treeTesting()
//{
//	std::cout<<"Testing Tree"<<std::endl;
//	time_t secs;
//	time(&secs);
//	srand((unsigned int)secs);
//	bst b(rand());
//	for(int i =0; i<10; i++)
//		b.insertNode(rand());
//	b.printTree();
//	int min = std::numeric_limits<int>::min();
//	std::cout<<"Validbst: "<<std::boolalpha<<b.ValidBst2(&b,min);
//	//int data;
//	//std::cin>>data;
//	//b.deleteNode(data);
//	//b.printTree();
//	//std::cin>>data;
//	//bst *temp1 = new bst(3);
//	//bst *temp = temp1;
//	//std::cout<<b.inordPred(data,&temp);
//	//std::cout<<temp->getData();
//	//delete temp1;
//	/*vector<int> vec;
//	bst::preOrd(&b,vec);*/
//	/*for(int i = 0; i < vec.size(); i++)
//		std::cout<<vec[i]<<"\t";*/
//	/*int index = 0;
//	bst* btree = bst::CreateBstfromPre(vec,index,std::numeric_limits<int>::max());
//	btree->printTree();
//	btree->insertNode(123);
//	std::cout<<std::boolalpha<<"Compared tree: "<<bst::CompareBst(btree, &b)<<std::endl;
//	std::cout<<std::boolalpha<<"Valid BST: "<<bst::ValidBst(btree)<<std::endl;*/
//
//	//std::cout<<std::boolalpha<<"Valid BST: "<<bst::ValidBst(&b)<<std::endl;
//
//	//bst::printbstList(bst::bstToList(&b,NULL));
//}

void trietesting()
{
	trie* root;
	root = trie::CreateTrie();
	std::cout<<root->find("curb")<<std::endl;
	std::cout<<root->find("curbed")<<std::endl;
}

//Declarations
void factorial_cc();
void double_squares();
void diamonds_inheritance();
void elephant_n_candy();

long fibs_logarithmic(long n);
long fibs_iterative(long n);
void bus_error_example();
void longest_pallindrome();
long fibs_prime_greater(long n);
long sum_prime_divisors(long n);
long subsets_of_sums();


void fibonacci_testing()
{
	long data;
	std::cin>>data;
	SimpleTimer st;
	st.startTimer();
	std::cout<<fibs_iterative(data)<<std::endl;
	st.stopTimer();
	std::cout<<st.getElapsedTime()<<std::endl;
	st.startTimer();
	std::cout<<fibs_logarithmic(data)<<std::endl;
	st.stopTimer();
	std::cout<<st.getElapsedTime()<<std::endl;
	std::getchar();
}

void heap_tester()
{
	heap<int> testHeap;
	time_t secs;
	time(&secs);
	srand((unsigned int)secs);
	for(int i = 0 ; i < rand()%100000; i++)
		testHeap.insert(rand());
	for(unsigned int i = 0; i < testHeap.size() %10; i++)
		testHeap.extractMin();
	std::cout<<testHeap.verifyHeap()<<std::endl;
}

void removeDuplicatesEff(char *str) {
	if (!str)
		return;
	int len = strlen(str);
	if (len < 2)
		return;
	bool hit[256];
	for(int i = 0; i < 256; ++i)
		hit[i] = false;
	hit[str[0]] = true;
	int tail = 1;
	for (int i = 1; i < len; ++i) {
		if (!hit[str[i]]) {
			str[tail] = str[i];
			++tail;
			hit[str[i]] = true;
		}
	}
	str[tail] = 0;
}


double derivative_order(double*x,double*y, int sz)
{
	double* deriv = new double[sz];
	int start = 0,end = sz-1;
	double order = 0;
	double sigma = 0.1;
	while(start < end)
	{
		order += 1;
		deriv[start] = 0;
		deriv[end] = 0;
		double mean = 0;
		//for(int i = 0; i < start + 1; i++)
		//	std::cout<<"0\t";
		for(int i = start + 1; i < end; i++)
		{
			deriv[i] = (y[i+1] - y[i-1])/(x[i+1] - x[i-1]);
			//std::cout<<deriv[i]<<"\t";
			mean = mean + deriv[i];
		}

		//std::cout<<std::endl;

		double prev = deriv[start + 1];
		bool dec = false;
		for(int i = start + 2; i < end; i++)
		{
			if(prev > deriv[i])
				dec = true;
		}

		if(dec)
			return order - 0.5;

		mean = mean / (end - start);
		double maxerror = 0,min = 1000;
		for(int i = start + 1; i < end; i++)
		{
			if(std::abs(deriv[i] - mean) > maxerror)
				maxerror = std::abs(deriv[i] - mean);
		}
		std::cout<<"Maxerror: "<<maxerror<<std::endl;
		if(maxerror < (sigma * mean))
			return order;
		start++;
		end--;
		double * temp = deriv;
		deriv = y;
		y = temp;
	}
	return -1;


}

int next_pallindrome(int x, int base, bool oddlength)
{
	int res = x;
	if(oddlength)
		x = x/base;
	while(x > 0)
	{
		res = base * res + x % base;
		x = x/base;
	}
	return res;
}

void create_all_Pallindromes()
{
	int x = 1;
	while(x < 1)
	{
		int p = next_pallindrome(x,10,true);
		x = x+1;
		std::cout<<p<<std::endl;
	}
	x = 1;
	while(x < 100)
	{
		int p = next_pallindrome(x,10,false);
		x = x+1;
		std::cout<<p<<std::endl;
	}
}


int main()
{
	CubeStacking2::main2();
	
	std::getchar();
	std::getchar();
	return 0;
}
