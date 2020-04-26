#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
//individual Jacob Park ID:20857120
using namespace std;

class BinaryTreeNode {
	int val;
	BinaryTreeNode* left, * right;
public:
	BinaryTreeNode(int new_val) : val(new_val), left(NULL), right(NULL) {}
	void print() { cout << val << " "; }

	friend class BinaryTree;
	friend class BinaryTreeTest;	
};

class BinaryTree {
	public:
		BinaryTreeNode* root;
		int size;
public:
	BinaryTree() : root(NULL), size(0) {}
	~BinaryTree() { clean_up(root); size = 0; root = NULL; }
	
	int min(BinaryTreeNode* T) {
		if (!T) return -1;

		BinaryTreeNode* cur = T;
		while (cur && cur->left) 
			cur = cur->left;		

		return cur->val;
	}
	
	int min() {
		return min(root);
	}
	
	int max(BinaryTreeNode* T) {
		if (!T) return -1;

		BinaryTreeNode* cur = T;
		while (cur && cur->right) 
			cur = cur->right;		

		return cur->val;
	}

	int max() {
		return max(root);
	}
	
	bool exists(BinaryTreeNode* T, int key) {
		BinaryTreeNode* cur = T;
		while (cur) {
			if (cur->val == key) 
				return true;
			
			if (cur->val > key)
				cur = cur->left;	
			else
				cur = cur->right;	
		} 

		return false;
	}

	bool exists(int key) {
		return exists(root, key);
	}

	
	bool insert(BinaryTreeNode new_node) {
		BinaryTreeNode** cur = &root;
		while (*cur) {
			if ((*cur)->val == new_node.val) 
				return false;
			
			if ((*cur)->val > new_node.val)
				cur = &((*cur)->left);	
			else
				cur = &((*cur)->right);	
		} 

		*cur = new BinaryTreeNode(new_node);
		++size;
		
		return true;		
	}

	void pre_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		T->print();
		pre_order(T->left);
		pre_order(T->right);
	}

	void pre_order() {
		pre_order(root);
	}

	void in_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		in_order(T->left);
		T->print();
		in_order(T->right);
	}

	void in_order() {
		in_order(root);
	}

	void post_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		post_order(T->left);
		post_order(T->right);
		T->print();
	}

	void post_order() {
		post_order(root);
	}

	void BFT(BinaryTreeNode* T) {
		if (T == NULL) return;
		
		queue<BinaryTreeNode*> bft_queue;
		bft_queue.push(T);

		while(!bft_queue.empty()) {
			BinaryTreeNode* cur = bft_queue.front();
			bft_queue.pop();

			cur->print();
			if (cur->left) bft_queue.push(cur->left);
			if (cur->right) bft_queue.push(cur->right);
		}
	}

	void BFT() {
		BFT(root);
	}
	
	void clean_up(BinaryTreeNode* T) {
		if (T == NULL) return;
		clean_up(T->left);
		clean_up(T->right);
		delete T;
	}
	void find_and_print_sum_of_nodes (BinaryTreeNode* T, int desired_sum,int cur_sum, string buffer)
	{
		if(!T) return;
		
		int new_sum = cur_sum +  T->val;
		
		string new_buffer = buffer + " " + int2ascii(T->val);
		
		if(new_sum == desired_sum)
			cout << new_buffer << endl;
			
		//TODO: continue down the left subtree
		find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);
		//TODO: continue down the right subtree
		find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);
		//TODO: restart from teh left subtree if buffer = ""
		if(buffer == "")
			find_and_print_sum_of_nodes(T->left, desired_sum, 0, "");
		//TODO: retart from the right subtree if buffer = ""
		if(buffer == "")
			find_and_print_sum_of_nodes(T->right, desired_sum, 0, "");
	}
	
	int find_max_sum_of_nodes (BinaryTreeNode* T, int &temp_max_sum)
	{
		int max1, max2, maxnum;
		if(!T) return 0;
		
		
		int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum );
		
		int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);
		
		int cur = T->val + left_sum + right_sum;
		//TODO: update temp_max_sum with the new max
		temp_max_sum = std::max(temp_max_sum, cur);
		//TODO: return max1
		return cur;
	}
	
	int find_max_sum_of_nodes(BinaryTreeNode *T)
	{
		if (!T)
			return 0;
		
		int temp_max_sum = INT_MIN;
		
		find_max_sum_of_nodes(T, temp_max_sum);
		
		return temp_max_sum;
	}
	
	string int2ascii (int val)
	{
		string buffer = "";
		string buffer1 = "";
		if(val < 0)
		{
			val = val*(-1);
			buffer += "-";
		}
			
		while(val > 0)
		{
		//	cout << "val: " << val<< "buffer: " ;
			buffer += '0' + val%10;
			val /= 10;
		//	cout<< buffer << endl;
		}
		
		
		
		for(int i = buffer.length()-1; i >= 0; i--)
		{
			buffer1 += buffer[i];
		}
		//cout << buffer1 << endl;
		return buffer1;
	}
	
	void positive_paths_of_3_length(BinaryTreeNode *T)
	{
		if(!T || !T->val)
			return;
		if(T->left && T->left->left)
		{
			if(T->val - T->left->val - T->left->left->val > 0)
			{
				cout << "( " << T->val << " " << T->left->val << " " << T ->left->left->val << " )" << endl;
			}
		}
		if(T->left && T->left->right)		
			if(T->val - T->left->val - T->left->right->val > 0)
			{
				cout << "( " << T->val << " " << T->left->val << " " << T ->left->right->val << " )" << endl;
			}
			
		if(T->right && T->right->left)
			
			if(T->val - T->left->val - T->right->left->val > 0)
			{
				cout << "( " << T->val << " " << T->right->val << " " << T ->right->left->val << " )" << endl;
			}
			
		if(T->right && T->right->right)
			if(T->val - T->left->val - T->right->right->val > 0)
			{
				cout << "( " << T->val << " " << T->right->val << " " << T ->right->right->val << " )" << endl;
			}
		positive_paths_of_3_length(T->left);	
		positive_paths_of_3_length(T->right);
	}
};

class BinaryTreeTest {
public:
	void test_traversals(BinaryTree& test_tree) {
		
		cout << endl << "Test PreOrder Traversal" << endl;		
		test_tree.pre_order();	

		cout << endl << "Test InOrder Traversal" << endl;		
		test_tree.in_order();	
		
		cout << endl << "Test PostOrder Traversal" << endl;		
		test_tree.post_order();	
		
		cout << endl << "Test Breadth First Traversal" << endl;
		test_tree.BFT();
	}
	
	void test_scenario1() {
		BinaryTree test_tree;

		BinaryTreeNode* root = new BinaryTreeNode(14);
		root->left = new BinaryTreeNode(12);
		root->right = new BinaryTreeNode(25);
		root->right->left = new BinaryTreeNode(21);
		root->right->right = new BinaryTreeNode(36);

		cout << "Min value is " << test_tree.min(root) << endl;
		cout << "Max value is " << test_tree.max(root) << endl;

		cout << (test_tree.exists(root, 25) ? "25 exists" : "25 does not exist") << endl;
		cout << (test_tree.exists(root, 32) ? "32 exists" : "32 does not exist") << endl;
		
		test_tree.clean_up(root);	
	}	
	
	void test_scenario2() {
		BinaryTree test_tree;

		test_tree.insert(BinaryTreeNode(15));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(11));
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(14));
		test_tree.insert(BinaryTreeNode(10));
		test_tree.insert(BinaryTreeNode(9));
		test_tree.insert(BinaryTreeNode(8));
		test_tree.insert(BinaryTreeNode(7));

		test_traversals(test_tree);
	}	

	void test_scenario3() {
		BinaryTree test_tree;

		test_tree.insert(BinaryTreeNode(15));
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(14));
		test_tree.insert(BinaryTreeNode(16));
		test_tree.insert(BinaryTreeNode(11));
		test_tree.insert(BinaryTreeNode(18));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(17));
		test_tree.insert(BinaryTreeNode(19));

		cout << endl << "Min value is " << test_tree.min() << endl;
		cout << "Max value is " << test_tree.max() << endl;

		cout << (test_tree.exists(16) ? "16 exists" : "16 does not exist") << endl;
		cout << (test_tree.exists(42) ? "42 exists" : "42 does not exist") << endl;
		
		test_traversals(test_tree);	
	}	
	
	void test_scenario4()
	{
		cout << endl << "it has reached this point" << endl;
		BinaryTree test_tree;
		BinaryTree test_tree1;
		
		test_tree.insert(BinaryTreeNode(1));
		test_tree.insert(BinaryTreeNode(5));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(2));
		
		int x = test_tree.find_max_sum_of_nodes(test_tree.root);
		cout << "max sum of node is: " << x << endl;
		test_tree.find_and_print_sum_of_nodes(test_tree.root, 19, 0, "");
		
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(22));
		test_tree.insert(BinaryTreeNode(32));
		
		x = test_tree.find_max_sum_of_nodes(test_tree.root);
		cout << "max sum of node is: " << x << endl;
		
		test_tree.find_and_print_sum_of_nodes(test_tree.root, 31, 0, "");
		test_tree.find_and_print_sum_of_nodes(test_tree.root, 8, 0, "");
		
		test_tree1.find_and_print_sum_of_nodes(test_tree1.root, 8, 0, "");
		
		test_tree.insert(BinaryTreeNode(151));
		test_tree.insert(BinaryTreeNode(17));
		test_tree.insert(BinaryTreeNode(-4));
		
	}

	void test_scenario5() {
        // step1. create a test tree
        //data contains only positive element
        BinaryTreeNode* root = new BinaryTreeNode(6);
        root->left = new BinaryTreeNode(1);
        root->right = new BinaryTreeNode(3);
        root->left->left = new BinaryTreeNode(2);
        root->left->left->left = new BinaryTreeNode(5);
        // TODO (PART A) Add more nodes here
        // TESTING negative values
        root->left->left->left->left = new BinaryTreeNode(-15);
        root->right->right = new BinaryTreeNode(2);
        root->right->left = new BinaryTreeNode(-3);
        
        // step2. call the function
        cout << "Expected output: (6 1 2)" << endl;
        cout << "Expected output: (6 3 -3)" << endl;
        cout << "Expected output: (6 3 2)" << endl;
        cout << "Expected output: (2 5 -15)" << endl;
        cout << "Actual output: " << endl;
        BinaryTree test_object;        
        test_object.positive_paths_of_3_length(root);
        
        // step3. clean up the node values
        test_object.clean_up(root);    
    }    
    
    void test_scenario6() {
        // TODO (PART A) Add another test case here
        //when given a tree with one node
        BinaryTreeNode* root = new BinaryTreeNode(0);
        BinaryTree test_object;
        cout << "No child nodes tested successful" << endl;
        test_object.positive_paths_of_3_length(root);
        
        test_object.clean_up(root);
    }    

    void test_scenario7() {
        // TODO (PART A) Add another test case here
        // testing only negative values
        BinaryTreeNode* root = new BinaryTreeNode(-6);
        root->left = new BinaryTreeNode(-1);
        root->right = new BinaryTreeNode(-3);
        root->left->left = new BinaryTreeNode(-2);
        root->left->left->left = new BinaryTreeNode(-5);
        root->right->right = new BinaryTreeNode(-5);
        cout << "Expected output: (-6 -2 -5)" << endl;
        cout << "Expected output: (-6 -3 -5)" << endl;
        cout << "Actual output: " << endl;
        BinaryTree test_object;        
        test_object.positive_paths_of_3_length(root);
        
    }    
    
    void test_scenario8()
    {
    	//test for tree that only has length of 2
        BinaryTreeNode* root = new BinaryTreeNode(1);
        root->left = new BinaryTreeNode(-1);
        root->right = new BinaryTreeNode(-3);
        BinaryTree test_object;        
        test_object.positive_paths_of_3_length(root);
	}

	void test_scenario9()
	{
		// not starting at root
		BinaryTreeNode* root = new BinaryTreeNode(6);
        root->left = new BinaryTreeNode(1);
        root->right = new BinaryTreeNode(3);
        root->left->left = new BinaryTreeNode(1);
        root->left->left->left = new BinaryTreeNode(-5);
        root->left->left->left->left = new BinaryTreeNode(-15);
        root->right->right = new BinaryTreeNode(2);
        root->right->left = new BinaryTreeNode(-3);
        cout << "Expected output(1 1 -5)" << endl;
        cout << "Expected output(1 -5 -15)" << endl;
        BinaryTree test_object;        
        test_object.positive_paths_of_3_length(root->left);
	}
	
	void test_scenario10()
	{
		//testing for tree that has length greater than 3 but no positive value when subtracted second and third node
		BinaryTreeNode* root = new BinaryTreeNode(0);
		root->left = new BinaryTreeNode(1);
        root->right = new BinaryTreeNode(3);
        root->left->left = new BinaryTreeNode(1);
        root->left->left->left = new BinaryTreeNode(5);
        root->left->left->left->left = new BinaryTreeNode(15);
        root->right->right = new BinaryTreeNode(2);
        root->right->left = new BinaryTreeNode(3);
        cout<< "expected output:" << endl << "none" << endl;
        BinaryTree test_object;        
        test_object.positive_paths_of_3_length(root);
	}
    void run_tests1() {
        // TODO (PART B) List at least six test cases / equivalence classes here
        test_scenario5();
        test_scenario6();    
        test_scenario7();   
   		test_scenario8();
   		test_scenario9();
   		test_scenario10();
    }

//	void run_tests() {
//		test_scenario1();
//		test_scenario2();
//		test_scenario3();
//		test_scenario4();
//	}
};

int main() {	
	BinaryTreeTest test1;
	test1.run_tests1();
}
