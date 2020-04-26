#include <iostream>
#include "lab3_binary_search_tree.hpp"
//Jacob Park ID:20857120
//Mark Baula ID:20823953
using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() : root(NULL), size(0) {}
void BinarySearchTree::clean_up(TaskItem* T) {
		if (T == NULL) return;
		clean_up(T->left);
		clean_up(T->right);
		delete T;
	}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {clean_up(root); root = NULL; size = 0;}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max(TaskItem* T) const {
	if(size <= 0)
		BinarySearchTree::TaskItem(-1, "N/A");

	TaskItem* curr = new TaskItem(*T);
	while(curr -> right)
	{
		curr = curr->right;
	}
	return *curr;
}

BinarySearchTree::TaskItem BinarySearchTree::max() const {
	return max(root); 
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min(TaskItem* T) const {
	if(size <= 0)
		return BinarySearchTree::TaskItem(-1, "N/A");
	
	TaskItem* curr = new TaskItem(*T);
	while(curr -> left)
	{
		curr = curr->left;
	}
	return *curr;
}

BinarySearchTree::TaskItem BinarySearchTree::min() const {
	return min(root);
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height(TaskItem* T) const {
	if(size == 0 || size == 1)
		return 0;
		
	int leftHeight = -1;
	int rightHeight = -1;
	if(T->left)
		leftHeight = height(T->left);
	if(T->right)
		rightHeight = height(T->right);
	
	if(leftHeight > rightHeight)
	{
		return leftHeight + 1;
	}
	else
	{
		return rightHeight + 1;
	}
}

unsigned int BinarySearchTree::height() const {
	return height(root);
	}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {	
	print(root);
}

void BinarySearchTree::print(TaskItem* T) const {
	
	if(T == NULL)
		return;
		
	cout << "Priority: " << T->priority << endl << "Description: " << T->description << endl << endl;
	print(T->left);
	print(T->right); 
}
	
bool BinarySearchTree::exists(TaskItem* T, int key) const
{
	TaskItem* cur = T;
	while (cur)
	{
		if (cur->priority == key)
			return true;
		
		if(key < cur->priority)
			cur = cur->left;
		else
			cur = cur->right;
	}
}

bool BinarySearchTree::exists(int key) const
{
	return exists(root, key);	
}
// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	TaskItem* cur = root;
	while (cur) {
    	// chekc for duplicates; if found, reject them
    	if(cur->priority == val.priority)
			return true;
		// mov elef tif the given key is smaller than cur's key
		if (val.priority < cur->priority) // point to the location where
			cur = cur->left;			// *cur's left pointer is stored
		// move right if given key is greater than cur's key
		else
			cur = cur->right;	
	}
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	
	if(size == 0)
	{
		root = new TaskItem(val);
		size++;
		return true;
	}
	
	TaskItem** cur = &root;
    
    while (*cur) {
    	// chekc for duplicates; if found, reject them
    	if((*cur)->priority == val.priority)
			return false;
		// mov elef tif the given key is smaller than cur's key
		if (val.priority < (*cur)->priority) // point to the location where
			cur = &((*cur)->left);			// *cur's left pointer is stored
		// move right if given key is greater than cur's key
		else
			cur = &((*cur)->right);	
	}
	*cur = new TaskItem(val);
	++size;
	
	return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {

    TaskItem* cur = root;
	TaskItem* prev = root;
    int ind = -1;
    int depth = 0;
    if(size == 0)
    {
    	return false;
	}
	while (cur && !(cur->priority == val.priority)) {
    	// chekc for duplicates; if found, reject them
		// move leftif the given key is smaller than cur's key
		if (val.priority < cur->priority)
		{
			prev = cur;
			cur = cur->left;
			ind = 0;
			depth++;
		}
		else
		{
			prev = cur;
			cur = cur->right;	
			ind = 1;
			depth++;
		}
			
	}
	if(!cur)
	{
		return false;
	}
	
	if(cur && !cur->left && !cur->right && cur->priority == val.priority)
	{
		if(ind == 0)
		{
			prev->left = NULL;
		}		
		else if(ind == 1)
		{
			prev->right = NULL;
		}
		else if(ind == -1)
		{
			root = NULL;
		}
		size--;
		return true;
	}
	else if(cur && !cur->left && !cur->right & cur->priority != val.priority)
	{
		return false;
	}
	
	else if(cur && (cur->left || cur->right) && !(cur->left && cur->right))
	{
		if(cur->left)
		{
			if(ind == 0)
			{
			prev->left = cur->left;
			}		
			else if(ind == 1)
			{
			prev->right = cur->left;
			}
			else if(ind == -1)
			{
			root = root->left;
			}	
		}
		else if(cur->right)
		{
			if(ind == 0)
			{
			prev->left = cur->right;
			}		
			else if(ind == 1)
			{
			prev->right = cur->right;
			}
			else if(ind == -1)
			{
				root = root->right;
			}
		}
		size--;
		return true;
	}
	else if(cur && cur->left && cur->right)
	{
		TaskItem* temp = cur->right;
		TaskItem nodeReplace = min(temp);
		TaskItem* nodeRep = new TaskItem(nodeReplace);
		
		remove(nodeReplace);
		size++; //this recursive function causes the size to drop . meant for adjustment
		nodeRep ->left = cur->left;
		nodeRep ->right = cur->right;
		
		
		if(ind == 0)
		{
			prev->left = nodeRep;
		}		
		else if(ind == 1)
		{
			prev->right = nodeRep;
		}
		else if(ind == -1)
		{
			root = nodeRep;
		}
		size--;
		return true;
	}
}
