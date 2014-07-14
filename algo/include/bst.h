#ifndef BST
#define BST

#include<vector>
#include<limits>

class bst
{

public:
	static void preOrd(bst* root, std::vector<int>& vec);
	static void postOrd(bst* root, std::vector<int>& vec);
	
	static void inOrd(bst* root, std::vector<int>& vec);
	
	static bst* CreateBstfromPre(std::vector<int>& vec, int& index, int parent);
	
	static bool CompareBst(bst* rootFirst, bst* rootSecond);

	//Use the inorder property of bst to verify it
	static bool ValidBst2(bst* root, int& min);

	//Standard method to validate BST using the limit_min, limit_max method
	static bool ValidBst(bst* root, int min = std::numeric_limits< int >::min(), int max = std::numeric_limits<int>::max());

	//bstToList - A cute function which converts bst to a sorted doubly linked list with right child as the next pointer
	// and left child as prev
	//freeing the allocated memory is not possible
	static bst* bstToList(bst* root, bst* last);

	static bst* bstToList(bst*root);

	//Adjoining function to above to print the sorted doubly linked list
	static void printbstList(bst* root);

	//print rightmost node in each level
	static void print_right_only(bst* root, int level, int& level_done);

	static void post_order_traversal(bst* root, int key);

	bst(int data);
	~bst();
	void insertNode(int data);
	bst* insertNodeR(int data);
	void deleteNode(int data);
	bool lookupNode(int data);
	void printTree();
	int inordPred(int data, bst** pred);
	int getData(){return data;}
	int getSize(){return count;}
	int getSize(bst* node){if(node == NULL) return 0; else return node->getSize();}
	void setSize(int size){count = size;}
	int rank(int data);
private:
	int count;
	int data;
	bst* left;
	bst* right;
};

#endif