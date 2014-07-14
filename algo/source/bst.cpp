#include<iostream>
#include<stack>
#include "bst.h"


bst::bst(int data)
{
	this->data = data;
	this->left = NULL;
	this->right = NULL;
	this->count = 1;
}

void bst::post_order_traversal(bst* root, int key)
{
	std::stack<bst*> st;
	while(true)
	{
		while(root && root->data != key)
		{
			st.push(root);
			root = root->left;
		}

		if(root && root->data == key)
			break;

		if(st.top()->right == NULL)
		{
			root = st.top();
			st.pop();

			while(!st.empty() && st.top()->right == root)
			{
				root = st.top();
				st.pop();
			}
		}

		root = st.empty()?NULL:st.top()->right;
	}

	while(!st.empty())
	{
		std::cout<<st.top()->data<<" ";
		st.pop();
	}

	std::cout<<std::endl;
}

bst* bst::CreateBstfromPre(std::vector<int>& vec, int& index, int parent)
{
	if(index >= vec.size())
		return NULL;
	bst* root = new bst(vec[index]);
	if(index < (vec.size()-1))
	{
		if(root->data > vec[index + 1])
		{
			root->left = CreateBstfromPre(vec,++index, root->data);
			if(root->left == NULL) index--;
		}
	}
	if(index < (vec.size()-1))
	{
		if(root->data <= vec[index + 1] && vec[index+1] < parent)
		{	
			root->right = CreateBstfromPre(vec,++index, parent);
			if(root->right == NULL) index--;
		}
	}
	return root;
}

bool bst::CompareBst(bst* rootFirst, bst* rootSecond)
{
	if(rootFirst == NULL && rootSecond == NULL)
		return true;
	if(rootFirst == NULL || rootSecond == NULL)
		return false;
	if(rootFirst->data != rootSecond->data)
		return false;
	return CompareBst(rootFirst->left,rootSecond->left) && CompareBst(rootFirst->right,rootSecond->right);
}

bool bst::ValidBst2(bst* root, int& prev)
{
	if(root == NULL)
		return true;
	if(ValidBst2(root->left, prev))
	{
		if(prev < root->data)
		{
			prev = root->data;
			if(ValidBst2(root->right,prev))
				return true;
		}
	}
	return false;
}

bool bst::ValidBst(bst* root,int min, int max)
{
	if(root == NULL)
		return true;
	if(root->data > min && root->data < max)
	{
		return ValidBst(root->left,min,root->data) && ValidBst(root->right,root->data,max);
	}
	return false;
}

void bst::preOrd(bst* root, std::vector<int>& vec)
{
	if(root != NULL)
	{
		vec.push_back(root->data);
		preOrd(root->left,vec);
		preOrd(root->right,vec);
	}
}

void bst::postOrd(bst* root, std::vector<int>& vec)
{
	if(root == NULL)
		return;
	postOrd(root->left,vec);
	postOrd(root->right,vec);
	vec.push_back(root->data);
}

void bst::inOrd(bst* root, std::vector<int>& vec)
{
	if(root == NULL)
		return;
	inOrd(root->left,vec);
	vec.push_back(root->data);
	inOrd(root->right, vec);
}


bst* bst::bstToList(bst* root, bst* last)
{
	if(root->right != NULL)
	{
		last = bstToList(root->right,last);
	}
	root->right = last;
	// Comment the next if block to make this a singly linked list
	if(last != NULL)
		last->left = root;
	last = root;
	if(root->left != NULL)
	{
		last = bstToList(root->left, last);
	}
	return last;
}

bst* bst::bstToList(bst*root)
{
	std::stack<bst*> st;
	bst* current = root;
	bst* head = NULL, *prev = NULL;
	while(current || !st.empty())
	{
		while(current)
		{
			st.push(current);
			current = current->left;
		}
		current = st.top();
		st.pop();
		if(head == NULL)
		{
			head = current;
			head->left = NULL;
			prev = head;
			head->right = NULL;
		}
		else
		{
			current->left = prev;
			prev->right = current;
			prev = current;
		}
		current = current->right;
	}
	prev->right = NULL;

	//print;
	bst* temp = head;
	while(temp != NULL)
	{
		std::cout<<temp->data<<"\t";
		temp = temp->right;
	}
	std::cout<<"\n";
	while(prev != NULL)
	{
		std::cout<<prev->data<<"\t";
		prev = prev->left;
	}
	return head;
}

void bst::printbstList(bst* root)
{ 
	bst* temp = root;
	while(root != NULL)
	{
		std::cout<<root->data<<"\t"; 
		temp = root;
		root= root->right;
	}
	std::cout<<std::endl;
	//traversing the other way
	while(temp != NULL)
	{
		std::cout<<temp->data<<"\t";
		temp = temp->left;
	}
}

void bst::print_right_only(bst* root, int level, int& level_done)
{
	if(!root) return;
	if(level > level_done)
	{
		std::cout<<root->data<<std::endl;
		level_done = level;
	}
	print_right_only(root->right,level+1,level_done);
	print_right_only(root->left,level+1,level_done);
}

bst* bst::insertNodeR(int data)
{
	if(data < this->data)
	{
		if(this->left != NULL)
			this->left = this->left->insertNodeR(data);
		else
			this->left = new bst(data);
	}
	else if(data > this->data)
	{
		if(this->right != NULL)
			this->right = this->right->insertNodeR(data);
		else
			this->right = new bst(data);
	}
	return this;
}

void bst::insertNode(int data)
{
	bst* node = this;
	bst* parent = NULL;
	while(node != NULL)
	{
		if(node->data == data)
			return;
		else if(node->data < data)
		{
			parent = node;
			node = node->right;
		}
		else
		{
			parent = node;
			if(parent != NULL)
				parent->setSize(parent->getSize() + 1);
			node = node->left;
		}
	}
	bst* child = new bst(data);
	//if(parent != NULL)
	//	parent->setSize(parent->getSize() + 1);
	if(parent->data < data)
		parent->right = child;
	else
		parent->left = child;
}

bool bst::lookupNode(int data)
{
	bst* node = this;
	while(node != NULL)
	{
		if(node->data == data)
			return true;
		if(node->data < data)
			node = node->right;
		else
			node = node->left;
	}
	return false;
}



int bst::inordPred(int data, bst** pred)
{
	int returnValue=0;
	if(this->left)
	{
		returnValue = this->left->inordPred(data, pred);
		if(returnValue)
			return returnValue;
	}
	if(this->data == data)
	{
		if((*pred) != NULL)
			return (*pred)->data;
	}
	(*pred) = this;
	if(this->right)
		return this->right->inordPred(data, pred);
	return returnValue;
}

int bst::rank(int data)
{
	if(data == this->data)
		return getSize(this->left);
	else if (data > this->data)
	{
		if(this->right != NULL)
			return 1 + getSize(this->left) + this->right->rank(data);
		else
			return 1 + getSize(this->left);
	}
	else
	{
		if(this->left != NULL)
			return this->left->rank(data);
		else
			return 0;
	}
}
void bst::deleteNode(int data)
{
	bst* node = this;
	bst* parent = NULL;
	while(node != NULL)
	{
		if(node->data == data)
			break;
		if(node->data < data)
		{
			parent = node;
			node = node->right;
		}
		else
		{
			parent = node;
			node = node->left;
		}
	}
	if(node == NULL)
		return;
	bst* child = NULL;
	bst* inordpa = node;
	if(node->right == NULL && node->left == NULL)
	{
	}
	else if(node->left == NULL || node->left == NULL)
	{
		child = (node->left)?(node->left):(node->right);
	}
	else
	{
		child = node->left;
		while(child->right != NULL)
		{
			inordpa = child;
			child = child->right;
		}
		if(inordpa == node)
		{
			child->right = node->right;
		}
		else
		{
			inordpa->right = child->left;
			child->left = node->left;
			child->right = node->right;
		}
	}
	// if parent is null means it is the root node;
	if(parent == NULL)
	{
		this->data = child->data;
		child->left = NULL;
		child->right = NULL;
		delete child;
		return;
	}
	if(parent->left == node)
		parent->left = child;
	else
		parent->right = child;
	node->left = node->right = NULL;
	delete node;
}

void bst::printTree()
{
	std::cout<<"\nThis tree: "<<this->data<<" : "<<this->getSize()<<" : ";
	if(this->left)
		std::cout<<" left :"<<this->left->data<<" : "<<this->left->getSize();
	if(this->right)
		std::cout<<" right :"<<this->right->data<<" : "<<this->right->getSize();
	std::cout<<std::endl;
	if(this->left)
		this->left->printTree();
	if(this->right)
		this->right->printTree();
}

bst::~bst()
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
