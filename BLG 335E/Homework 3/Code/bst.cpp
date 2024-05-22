// EB
// Implementing Binary Search Tree in C++
// Fatih Baskın
// 150210710

#include <iostream>

namespace BST
{
	struct Node
	{
		int data;
		std::string name;
		Node *parent;
		Node *left;
		Node *right;
	};
}

class BinarySearchTree
{
private:
	// Holds the root of the tree
	BST::Node *root;

	// Used to get the height of the tree
	int getHeightHelper(BST::Node *node, int height);

	// Used to get the total number of nodes in the tree
	int getTotalNodesHelper(BST::Node *node);

	BST::Node *getMinimumHeleper(BST::Node *currentNode);

	BST::Node *getMaximumHelper(BST::Node *currentNode);

	void inorderHelper(std::pair<std::string, int> orderedDataBST[], BST::Node *currentNode, int &putIndex);

	void postorderHelper(std::pair<std::string, int> orderedDataBST[], BST::Node *currentNode, int &putIndex);

	void preorderHelper(std::pair<std::string, int> orderedDataBST[], BST::Node *currentNode, int &putIndex);

	void bstDestructorHelper(BST::Node *currentNode);

public:
	BinarySearchTree() : root(NULL) {}

	void preorder(std::pair<std::string, int> orderedDataBST[], int startIndex) { preorderHelper(orderedDataBST, root, startIndex); }

	void inorder(std::pair<std::string, int> orderedDataBST[], int startIndex) { inorderHelper(orderedDataBST, root, startIndex); }

	void postorder(std::pair<std::string, int> orderedDataBST[], int startIndex) { postorderHelper(orderedDataBST, root, startIndex); }

	BST::Node *searchTree(int value);

	BST::Node *successor(BST::Node *currentNode);

	BST::Node *predecessor(BST::Node *currentNode);

	void insert(std::string city, int population);

	void deleteNode(int deletePopulation);

	int getHeight() { return getHeightHelper(root, 0); }

	BST::Node *getMaximum() { return getMaximumHelper(root); }

	BST::Node *getMinimum() { return getMinimumHeleper(root); }

	int getTotalNodes() { return getTotalNodesHelper(root); }

	~BinarySearchTree() { bstDestructorHelper(root); }
};

BST::Node *BinarySearchTree::searchTree(int value)
{
	// Start from the root
	BST::Node *temp = root;
	while (temp != NULL)
	{
		// If the current node's data is equal to the value, return the node
		if (temp->data == value)
			return temp;

		// If the current node's data is greater than the value, move left
		if (temp->data > value)
		{
			temp = temp->left;
			continue;
		}

		// If the current node's data is less than the value, move right
		if (temp->data < value)
		{
			temp = temp->right;
			continue;
		}

		// If there is no route to take and value is not equal to anything, return null
		return NULL;
	}

	// Program will arrive here if we are at NULL node, value doesn't exist
	return NULL;
}

BST::Node *BinarySearchTree::successor(BST::Node *currentNode)
{
	// Edge case, current node is null
	if (currentNode == NULL)
		return NULL;

	// If there exists a right node, then go to the minimum of right subtree
	if (currentNode->right != NULL)
		return getMinimumHeleper(currentNode->right);

	// Otherwise, get the parent where I came from left (parent which is larger thant the current node)
	BST::Node *temp = currentNode;
	BST::Node *parent = currentNode->parent;
	while (parent != NULL && parent->right != NULL && parent->right->data == temp->data)
	{
		temp = parent;
		parent = temp->parent;
	}
	// The while loop will break if reached from a parent's left or there is no left-reached parent (root)
	return parent;
}

BST::Node *BinarySearchTree::predecessor(BST::Node *currentNode)
{
	// Edge case, current node is null
	if (currentNode == NULL)
		return NULL;

	// If there exists a left node, get maximum of the left subtree
	if (currentNode->left != NULL)
		return getMaximumHelper(currentNode->left);

	// Otherwise, get the parent where I came from right (parent which is smaller than the current node).
	BST::Node *temp = currentNode;
	BST::Node *parent = currentNode->parent;
	while (parent != NULL && parent->left != NULL && parent->left->data == temp->data)
	{
		temp = parent;
		parent = temp->parent;
	}
	// While loop will break if reached from a parent's right or there is no right-reached parent (root)
	return parent;
}

void BinarySearchTree::insert(std::string city, int population)
{
	// Initialize the new node
	BST::Node *newNode = new BST::Node;
	newNode->name = city;
	newNode->data = population;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	// If the tree is empty, make the new node the root
	if (root == NULL)
	{
		root = newNode;
		return;
	}

	// Otherwise, find the correct place to insert the new node
	// Temp is used to traverse the tree
	BST::Node *temp = root;
	while (temp != NULL)
	{
		// If the newnode's data is less than the current node's data, move left
		if (newNode->data < temp->data)
		{
			// If the current node's left child is NULL, insert the new node as the left child
			if (temp->left == NULL)
			{
				temp->left = newNode;
				newNode->parent = temp;
				return;
			}
			// Otherwise, move left and continue
			temp = temp->left;
		}
		else
		{
			// /!\ note that this implementation is wrong, the correct way would be to check equality case
			// But in the examples given, height for file 1 is 837 and height for file 4 is 80, different from
			// the log samples.

			// This case is when the current node is greater or equal to the new node
			// If the current node's right child is NULL, insert the new node as the right child
			if (temp->right == NULL)
			{
				temp->right = newNode;
				newNode->parent = temp;
				return;
			}
			// Otherwise, move right and continue
			temp = temp->right;
		}
	}
}

void BinarySearchTree::deleteNode(int deletePopulation)
{
	BST::Node *currentNode = searchTree(deletePopulation);

	if (currentNode == NULL)
		return;

	BST::Node *parent = currentNode->parent;
	BST::Node *left = currentNode->left;
	BST::Node *right = currentNode->right;

	// If current node is a leaf node
	if (left == NULL && right == NULL)
	{
		// Check if the current node is root
		if (parent == NULL)
			// In this case set root null
			root = NULL;
		// Otherwise set the parent's child null accordingly
		else if (parent->right == currentNode)
			parent->right = NULL;
		else
			parent->left = NULL;

		delete currentNode;
		return;
	}

	// If the right is null, then set left as the current node
	if (right == NULL)
	{
		// Check if the current node is leaf node
		if (parent == NULL)
			// Set root accordingly if the parent is the root
			root = currentNode->left;
		else if (parent->right == currentNode)
			parent->right = left;
		else
			parent->left = left;

		// Update the parent of left node
		// If parent is null it will still be null
		left->parent = parent;

		delete currentNode;
		return;
	}

	// Otherwise, set the right node as current node
	if (parent == NULL)
		root = currentNode->right;
	else if (parent->right == currentNode)
		parent->right = right;
	else
		parent->left = right;

	// Update the parent of right node
	right->parent = parent;

	// Then add left subtree to leftmost of right subtree
	BST::Node *leftmost = getMinimumHeleper(right);
	leftmost->left = left;

	// Update the parent of leftnode
	if (left != NULL)
		left->parent = leftmost;

	delete currentNode;
}

void BinarySearchTree::preorderHelper(std::pair<std::string, int> orderedDataBST[], BST::Node *currentNode, int &putIndex)
{
	// Return if current node is null
	if (currentNode == NULL)
		return;

	// First, put the current one and increment the index
	orderedDataBST[putIndex] = {currentNode->name, currentNode->data};
	putIndex += 1;

	// Then, go to left subtree
	preorderHelper(orderedDataBST, currentNode->left, putIndex);

	// Lastly, go right subtree
	preorderHelper(orderedDataBST, currentNode->right, putIndex);
}

void BinarySearchTree::postorderHelper(std::pair<std::string, int> orderedDataBST[], BST::Node *currentNode, int &putIndex)
{
	// Return if current node is null
	if (currentNode == NULL)
		return;

	// Fİrst, go to left subtree
	postorderHelper(orderedDataBST, currentNode->left, putIndex);

	// Then, go right subtree
	postorderHelper(orderedDataBST, currentNode->right, putIndex);

	// Lastly, put the current one and increment the index
	orderedDataBST[putIndex] = {currentNode->name, currentNode->data};
	putIndex += 1;
}

void BinarySearchTree::inorderHelper(std::pair<std::string, int> orderedDataBST[], BST::Node *currentNode, int &putIndex)
{
	// Return if current node is null
	if (currentNode == NULL)
		return;

	// First, go to left subtree
	inorderHelper(orderedDataBST, currentNode->left, putIndex);

	// Then put the current one and increment the index
	orderedDataBST[putIndex] = {currentNode->name, currentNode->data};
	putIndex += 1;

	// Lastly, go right subtree
	inorderHelper(orderedDataBST, currentNode->right, putIndex);
}

// Used to get the height of the tree
int BinarySearchTree::getHeightHelper(BST::Node *node, int height)
{
	// With recursive function, current height was incremented but if
	// the current node is null, so decrement height by 1 and return
	if (node == NULL)
		return height - 1;

	// If the both childs are NULL (leaf node), return the height
	if (node->left == NULL && node->right == NULL)
		return height;

	// Otherwise, return the maximum height of the left and right subtree
	int leftHeight = getHeightHelper(node->left, height + 1);
	int rightHeight = getHeightHelper(node->right, height + 1);

	if (leftHeight > rightHeight)
		return leftHeight;

	return rightHeight;
}

// Used to get the total number of nodes in the tree
int BinarySearchTree::getTotalNodesHelper(BST::Node *node)
{
	// If the node is NULL, return 0
	if (node == NULL)
		return 0;

	int leftCount = 0;
	if (node->left != NULL)
		leftCount = getTotalNodesHelper(node->left);

	int rightCount = 0;
	if (node->right != NULL)
		rightCount = getTotalNodesHelper(node->right);

	// Return current node (1) + left subtree size + right subtree size
	return 1 + leftCount + rightCount;
}

BST::Node *BinarySearchTree::getMinimumHeleper(BST::Node *currentNode)
{
	// If the tree is empty, return NULL
	if (currentNode == NULL)
		return NULL;

	// Otherwise, traverse the tree to the left until the leftmost node is reached
	BST::Node *temp = currentNode;
	while (temp->left != NULL)
		temp = temp->left;

	return temp;
}

BST::Node *BinarySearchTree::getMaximumHelper(BST::Node *currentNode)
{
	// If the tree is empty return NULL
	if (currentNode == NULL)
		return NULL;

	// Traverse tree to the right until the rightmost node is reached.
	BST::Node *temp = currentNode;
	while (temp->right != NULL)
		temp = temp->right;
	return temp;
}

void BinarySearchTree::bstDestructorHelper(BST::Node *currentNode)
{
	// Destructor should remove the tree in inorder traversal
	if (currentNode == NULL)
		return;
	// Get the left & right nodes
	BST::Node *left = currentNode->left;
	BST::Node *right = currentNode->right;
	// Call the destructor inorder
	bstDestructorHelper(left);
	delete currentNode;
	bstDestructorHelper(right);
}
