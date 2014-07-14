#ifndef TREEE
#define TREEE

#include<iostream>

class tree
{
public: 
	tree* getRight(){return right;}
	void setRight(tree* t){right = t;}
	tree* getLeft(){return left;}
	void setLeft(tree* t){left = t;}
	void printTree()
	{
		std::cout<<"\nThis tree: "<<this->data;
		if(this->left)
			std::cout<<" left :"<<this->left->data;
		if(this->right)
			std::cout<<" right :"<<this->right->data;
		std::cout<<std::endl;
		if(this->left)
			this->left->printTree();
		if(this->right)
			this->right->printTree();
	}
	tree(int datum){data = datum; right = NULL; left = NULL;}
	void setData(int datum){data = datum;}
	int getData(){return data;}
	~tree()
	{
		if(this->left)
		{
			delete this->left;
			this->left = NULL;
		}
		if(this->right)
		{
			delete this->right;
			this->right = NULL;
		}
	}
private:
	tree* right;
	tree* left;
	int data;
};


#endif