// EB
// Implementing Red-Black Tree in C++
// 150210710
// Fatih Baskın

#include <iostream>

namespace RBT
{
	struct Node
	{
		int data;
		std::string name;
		Node *parent;
		Node *left;
		Node *right;
		int color;
	};
}

class RedBlackTree
{
private:
	RBT::Node *root;

	// Used to get the height of the tree
	int getHeightHelper(RBT::Node *node, int height);

	// Used to get the total number of nodes in the tree
	int getTotalNodesHelper(RBT::Node *node);

	RBT::Node *getMinimumHeleper(RBT::Node *currentNode);

	RBT::Node *getMaximumHelper(RBT::Node *currentNode);

	void inorderHelper(std::pair<std::string, int> orderedDataRBT[], RBT::Node *currentNode, int &putIndex);

	void postorderHelper(std::pair<std::string, int> orderedDataRBT[], RBT::Node *currentNode, int &putIndex);

	void preorderHelper(std::pair<std::string, int> orderedDataRBT[], RBT::Node *currentNode, int &putIndex);

	RBT::Node *getUncle(RBT::Node *currentNode);

	RBT::Node *getSibling(RBT::Node *currentNode);

	RBT::Node *getGrandparent(RBT::Node *currentNode);

	void rbtFixerUp(RBT::Node *currentNode);

	void rbtTransplant(RBT::Node *parentNode, RBT::Node *childNode);

	void rbtDoubleBlackFixer(RBT::Node *doubleBlackNode);

	void swapNodes(RBT::Node *node1, RBT::Node *node2);

	RBT::Node *findReplacement(RBT::Node *currentNode);

	void deleteNodeHelper(RBT::Node *currentNode);

	void rightRotation(RBT::Node *currentNode);

	void leftRotation(RBT::Node *currentNode);

	int isRBThelper(RBT::Node *, int);

	void rbtDestructorHelper(RBT::Node *currentNode);

public:
	RedBlackTree() : root(NULL)
	{
	}

	void preorder(std::pair<std::string, int> orderedDataRBT[], int startIndex) { preorderHelper(orderedDataRBT, root, startIndex); }

	void inorder(std::pair<std::string, int> orderedDataRBT[], int startIndex) { inorderHelper(orderedDataRBT, root, startIndex); }

	void postorder(std::pair<std::string, int> orderedDataRBT[], int startIndex) { postorderHelper(orderedDataRBT, root, startIndex); }

	RBT::Node *searchTree(int value);

	RBT::Node *successor(RBT::Node *currentNode);

	RBT::Node *predecessor(RBT::Node *currentNode);

	void insert(std::string city, int population);

	void deleteNode(int deletePopulation);

	int getHeight() { return getHeightHelper(root, 0); }

	RBT::Node *getMaximum() { return getMaximumHelper(root); }

	RBT::Node *getMinimum() { return getMinimumHeleper(root); }

	int getTotalNodes() { return getTotalNodesHelper(root); }

	bool isRBT();

	~RedBlackTree() { rbtDestructorHelper(root); }
};

int RedBlackTree::getHeightHelper(RBT::Node *node, int height)
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

int RedBlackTree::getTotalNodesHelper(RBT::Node *node)
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

RBT::Node *RedBlackTree::getMinimumHeleper(RBT::Node *currentNode)
{
	// If the tree is empty, return NULL
	if (currentNode == NULL)
		return NULL;

	// Otherwise, traverse the tree to the left until the leftmost node is reached
	RBT::Node *temp = currentNode;
	while (temp->left != NULL)
		temp = temp->left;

	return temp;
}

RBT::Node *RedBlackTree::getMaximumHelper(RBT::Node *currentNode)
{
	// If the tree is empty return NULL
	if (currentNode == NULL)
		return NULL;

	// Traverse tree to the right until the rightmost node is reached.
	RBT::Node *temp = currentNode;
	while (temp->right != NULL)
		temp = temp->right;
	return temp;
}

void RedBlackTree::inorderHelper(std::pair<std::string, int> orderedDataRBT[], RBT::Node *currentNode, int &putIndex)
{
	// Return if current node is null
	if (currentNode == NULL)
		return;

	// First, go to left subtree
	inorderHelper(orderedDataRBT, currentNode->left, putIndex);

	// Then put the current one and increment the index
	orderedDataRBT[putIndex] = {currentNode->name, currentNode->data};
	putIndex += 1;

	// Lastly, go right subtree
	inorderHelper(orderedDataRBT, currentNode->right, putIndex);
}

void RedBlackTree::postorderHelper(std::pair<std::string, int> orderedDataRBT[], RBT::Node *currentNode, int &putIndex)
{
	// Return if current node is null
	if (currentNode == NULL)
		return;

	// Fİrst, go to left subtree
	postorderHelper(orderedDataRBT, currentNode->left, putIndex);

	// Then, go right subtree
	postorderHelper(orderedDataRBT, currentNode->right, putIndex);

	// Lastly, put the current one and increment the index
	orderedDataRBT[putIndex] = {currentNode->name, currentNode->data};
	putIndex += 1;
}

void RedBlackTree::preorderHelper(std::pair<std::string, int> orderedDataRBT[], RBT::Node *currentNode, int &putIndex)
{
	// Return if current node is null
	if (currentNode == NULL)
		return;

	// First, put the current one and increment the index
	orderedDataRBT[putIndex] = {currentNode->name, currentNode->data};
	putIndex += 1;

	// Then, go to left subtree
	preorderHelper(orderedDataRBT, currentNode->left, putIndex);

	// Lastly, go right subtree
	preorderHelper(orderedDataRBT, currentNode->right, putIndex);
}

RBT::Node *RedBlackTree::searchTree(int value)
{
	// Start from the root
	RBT::Node *temp = root;
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

RBT::Node *RedBlackTree::successor(RBT::Node *currentNode)
{
	// Edge case, current node is null
	if (currentNode == NULL)
		return NULL;

	// If there exists a right node, then go to the minimum of right subtree
	if (currentNode->right != NULL)
		return getMinimumHeleper(currentNode->right);

	// Otherwise, get the parent where I came from left (parent which is larger thant the current node)
	RBT::Node *temp = currentNode;
	RBT::Node *parent = currentNode->parent;
	while (parent != NULL && parent->right != NULL && parent->right->data == temp->data)
	{
		temp = parent;
		parent = temp->parent;
	}
	// The while loop will break if reached from a parent's left or there is no left-reached parent (root)
	return parent;
}

RBT::Node *RedBlackTree::predecessor(RBT::Node *currentNode)
{
	// Edge case, current node is null
	if (currentNode == NULL)
		return NULL;

	// If there exists a left node, get maximum of the left subtree
	if (currentNode->left != NULL)
		return getMaximumHelper(currentNode->left);

	// Otherwise, get the parent where I came from right (parent which is smaller than the current node).
	RBT::Node *temp = currentNode;
	RBT::Node *parent = currentNode->parent;
	while (parent != NULL && parent->left != NULL && parent->left->data == temp->data)
	{
		temp = parent;
		parent = temp->parent;
	}
	// While loop will break if reached from a parent's right or there is no right-reached parent (root)
	return parent;
}

RBT::Node *RedBlackTree::getGrandparent(RBT::Node *currentNode)
{
	// Check if the current node is null
	if (currentNode == NULL)
		return NULL;

	// If the current node is the root
	if (currentNode->parent == NULL)
		return NULL;

	// Return the grapdparent of the current node
	return currentNode->parent->parent;
}

RBT::Node *RedBlackTree::getUncle(RBT::Node *currentNode)
{
	// Check if the current node is null
	if (currentNode == NULL)
		return NULL;

	// If the current node is the root
	if (currentNode->parent == NULL)
		return NULL;

	RBT::Node *grandparent = getGrandparent(currentNode);
	// If grandparent doesn't exist, return null
	if (grandparent == NULL)
		return NULL;

	// If the current node's parent is the left child of the grandparent, return the right child of the grandparent
	if (grandparent->left == currentNode->parent)
		return grandparent->right;

	// Otherwise, return the left child of the grandparent
	return grandparent->left;
}

RBT::Node *RedBlackTree::getSibling(RBT::Node *currentNode)
{
	// Check if the current node is null
	if (currentNode == NULL)
		return NULL;

	// If the current node is the root
	if (currentNode->parent == NULL)
		return NULL;

	// If the current node is the left child of its parent, return the right child of the parent
	if (currentNode->parent->left == currentNode)
		return currentNode->parent->right;

	// Otherwise, return the left child of the parent
	return currentNode->parent->left;
}

// TODO
void RedBlackTree::insert(std::string city, int population)
{
	RBT::Node *newNode = new RBT::Node;
	newNode->data = population;
	newNode->name = city;
	newNode->left = NULL;
	newNode->right = NULL;
	// Color codes: 0 -> Black, 1 -> Red
	newNode->color = 1;

	// If the tree is empty, make the new node root and color it black
	if (root == NULL)
	{
		root = newNode;
		newNode->parent = NULL;
		newNode->color = 0;
		return;
	}

	// Otherwise, find the correct place to insert the new node
	RBT::Node *temp = root;
	while (temp != NULL)
	{
		// If the current node is greater than the new node, go left
		if (temp->data > newNode->data)
		{
			// If the left child is null, insert the new node here
			if (temp->left == NULL)
			{
				temp->left = newNode;
				newNode->parent = temp;
				break;
			}
			// Otherwise, go left
			temp = temp->left;
		}
		else
		{
			// If the right child is null, insert the new node here
			if (temp->right == NULL)
			{
				temp->right = newNode;
				newNode->parent = temp;
				break;
			}
			// Otherwise, go right
			temp = temp->right;
		}
	}
	// So far, we inserted the node as in the BST logic, now we need to fix the red-black tree properties
	rbtFixerUp(newNode);
}

void RedBlackTree::rbtFixerUp(RBT::Node *currentNode)
{
	// If the current node is null, return
	if (currentNode == NULL)
		return;

	// If the current node is the root, color it black and return
	if (currentNode->parent == NULL)
	{
		currentNode->color = 0;
		return;
	}

	// If the parent is black, return
	if (currentNode->parent->color == 0)
		return;

	// If the parent is red, get the uncle
	RBT::Node *uncle = getUncle(currentNode);
	// If the uncle is red as the parent, color both parent and uncle black,
	// paint grandparent red and recursively call the function for the grandparent
	if (uncle != NULL && uncle->color == 1)
	{
		currentNode->parent->color = 0;
		uncle->color = 0;
		RBT::Node *grandparent = getGrandparent(currentNode);
		// No need to do nullcheck since if there exists an uncle, there is a grandparent
		grandparent->color = 1;
		rbtFixerUp(grandparent);
		return;
	}

	// If the uncle is black or null(count as black), then we need to do rotations
	// There is no need to check if the grandparent is null since if the parent is red, there is a grandparent
	RBT::Node *grandparent = getGrandparent(currentNode);

	// This is the case 2 in the lecture nodes, current node is located at lr or rl
	// lr case, parent is located left of grandparent and current node is at the right of parent
	if (currentNode->parent->right == currentNode && grandparent->left == currentNode->parent)
	{
		leftRotation(currentNode->parent);
		// To make it case 3, now the parent is located left of curent node, so the current node is updated
		// as the left of the current node (old parent)
		currentNode = currentNode->left;
	}
	// rl ce, parent is located at right of grandparent and current node is at the left of parent
	else if (currentNode->parent->left == currentNode && grandparent->right == currentNode->parent)
	{
		rightRotation(currentNode->parent);
		// To make it case 3, now the parent is located right of the current node, so the current node is
		// updated as the right of current node (old parent)
		currentNode = currentNode->right;
	}

	// Case 3, ll or rr,
	// currentnode is located left of parent and parent is located left of grandparent
	if (currentNode->parent->left == currentNode && grandparent->left == currentNode->parent)
	{
		rightRotation(grandparent);
		// parent is located at the location of grandparent, its color is black now
		currentNode->parent->color = 0;
		// and grandparent and curren node is located at the same level, they should be red
		grandparent->color = 1;
	}
	// currentnode is located right of parent and parent is located right of grandparent
	else if (currentNode->parent->right == currentNode && grandparent->right == currentNode->parent)
	{
		leftRotation(grandparent);
		// parent is located at the location of grandparent, its color is black now
		currentNode->parent->color = 0;
		// and grandparent and curren node is located at the same level, they should be red
		grandparent->color = 1;
	}
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightRotation(RBT::Node *currentNode)
{
	if (currentNode == NULL)
		return;

	RBT::Node *leftChild = currentNode->left;
	// if the left child is null, we can't do the rotaiton
	if (leftChild == NULL)
		return;

	// if the left child has a right child, then make it the left child of the current node
	currentNode->left = leftChild->right;
	if (leftChild->right != NULL)
		leftChild->right->parent = currentNode;

	// If the current node has a parent, then make the left child the parent of the current node
	leftChild->parent = currentNode->parent;
	if (currentNode->parent != NULL)
	{
		// If the current node is the left child of its (old) parent, then make the left child the left child of the parent
		if (currentNode->parent->left == currentNode)
			currentNode->parent->left = leftChild;
		// Otherwise, make the left child the right child of the parent
		else
			currentNode->parent->right = leftChild;
	}
	else
		// If the parent of the current node is null (current node is root) update root
		root = leftChild;

	// Finally, set the current node as the right child of the left child
	leftChild->right = currentNode;
	currentNode->parent = leftChild;
}

void RedBlackTree::leftRotation(RBT::Node *currentNode)
{
	if (currentNode == NULL)
		return;

	RBT::Node *rightChild = currentNode->right;
	// If the right child is null, we can't do the rotation
	if (rightChild == NULL)
		return;

	// If the right child has a left child, then make it the right child of the current node
	currentNode->right = rightChild->left;
	if (rightChild->left != NULL)
		rightChild->left->parent = currentNode;

	// If the current node has a parent, then make the right child the parent of the current node
	rightChild->parent = currentNode->parent;
	if (currentNode->parent != NULL)
	{
		// If the current node is the left child of its (old) parent, then make the right child the left child of the parent
		if (currentNode->parent->left == currentNode)
			currentNode->parent->left = rightChild;
		// Otherwise, make the right child the right child of the parent
		else
			currentNode->parent->right = rightChild;
	}
	else
		// If the parent of the current node is null (current node is root) update root
		root = rightChild;

	// Finally, set the current node as the left child of the right child
	rightChild->left = currentNode;
	currentNode->parent = rightChild;
}

void RedBlackTree::deleteNode(int deletePopulation)
{
	RBT::Node *currentNode = searchTree(deletePopulation);
	if (currentNode == NULL)
		return;
	// The delete node works recursively, I had to use it with pointers since there might be two cities with
	// same population and without pointers it might select the wrong city.
	deleteNodeHelper(currentNode);
}

void RedBlackTree::deleteNodeHelper(RBT::Node *currentNode)
{
	// Solutions are a combination from the CLRS Book, GeeksForGeeks code and my own interpretation.

	// If the node doesn't exist, return
	if (currentNode == NULL)
		return;

	// Trivial case, if the current node is red and leaf, delete it immediately
	if (currentNode->left == NULL && currentNode->right == NULL && currentNode->color == 1)
	{
		// check whether the current node is root, if so, set root null
		if (currentNode == root)
			root == NULL;
		else
		{
			// othervise, set parent's child accordingly
			if (currentNode->parent->left == currentNode)
				currentNode->parent->left == NULL;
			else
				currentNode->parent->right == NULL;
		}
		delete currentNode;
		return;
	}

	// So, we might require to replace the current node, either with its child or successor, or none
	RBT::Node *replacementNode = findReplacement(currentNode);

	// Double black happens when we are moving a black node from its place, so then the black height for parent
	// and sibling tree must be adjusted, if replacement node is null, this means we are moving TIL node to current place
	bool doubleBlack = ((replacementNode == NULL || replacementNode->color == 0) && (currentNode->color == 0));
	RBT::Node *parent = currentNode->parent;
	RBT::Node *sibling = getSibling(currentNode);

	// If there is no replacement node, ie. current node is leaf, repacing current node with TIL
	if (replacementNode == NULL)
	{
		// If current node is root, set root null
		if (currentNode == root)
			root = NULL;
		else
		{
			// If the case is doubleblack, fix doubleblack (black node replaced with TIL)
			if (doubleBlack)
				rbtDoubleBlackFixer(currentNode);

			else if (sibling != NULL)
				// sibling is not null, make it red to preserve black height from the parent
				// this might be unnecessary since it is impossible to not have a non-double black
				// case where sibling is black (current node -> red, sibling black)
				sibling->color = 1;

			// delete current node
			if (currentNode->parent->left == currentNode)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		delete currentNode;
		return;
	}

	// One child case, taken from the clrs
	if (currentNode->right == NULL)
	{
		// Transplant will replace this node with its child
		rbtTransplant(currentNode, currentNode->left);
		// if current node is black, then it is guaranteed that only one chlid node is red.
		// Update the only child's color to black in order to restore color depth
		// We don't need else case, since current node can't be red and its only child do exist.
		// If current node is red then there should be two black children
		currentNode->left->color = 0;
		delete currentNode;
		return;
	}
	// one child case, taken from the clrs
	if (currentNode->left == NULL)
	{
		// Same as the case above except we are manipulating the right child
		rbtTransplant(currentNode, currentNode->right);
		currentNode->right->color = 0;
		delete currentNode;
		return;
	}

	// LAST CASE, current node has two children, swap values with successor and recursively delete the successor
	// v has 2 children, swap values with successor and recurse
	swapNodes(replacementNode, currentNode);
	// Continue on deleting replacement node (note that values are swapped)
	deleteNodeHelper(replacementNode);
}

void RedBlackTree::rbtDoubleBlackFixer(RBT::Node *currentNode)
{
	// Double black can move up if the sibling and parent are both black, in this case
	// fixes and rotations can move up, and if the current node is root and it is double black,
	// then we reduced the black height of entire tree by one, return if we reached the top.
	if (currentNode == root)
	{
		// Reached root, make sure root is black
		currentNode->color = 0;
		return;
	}

	RBT::Node *sibling = getSibling(currentNode);
	RBT::Node *parent = currentNode->parent;

	if (sibling == NULL)
		// No sibling, double black pushed up
		// This case would have been solved using rotations, but without a sibling,
		// it is impossible to solve it.
		rbtDoubleBlackFixer(parent);
	else
	{
		if (sibling->color == 1)
		{
			// Sibling red case
			// If the sibling is red, it has two black children,
			parent->color = 1;
			sibling->color = 0;
			if (sibling->parent->left == sibling)
				// left case
				rightRotation(parent);
			else
				// right case
				leftRotation(parent);
			// With this operations, sibling has replaced the parent as a black node,
			// parent is now red with current node and one of the sibling's child being black,
			// and sibling's other child is still black but it is easily fixable with rotation.
			// recurse below (else statement) since new sibling would be black
			rbtDoubleBlackFixer(currentNode);
		}
		else
		{
			// Sibling black, will reach here if sibling is black or sibling was red and we recursed here.
			// Siblings red case, at least one of them should be red
			if ((sibling->left && sibling->left->color == 1) || (sibling->right && sibling->right->color == 1))
			{
				// at least 1 red children, on the left or on the right
				// It is possible to preserve tree black depth without
				if (sibling->left != NULL && sibling->left->color == 1)
				{
					if (sibling->parent->left == sibling)
					{
						// sibling is at left and its red children is at the left
						// left left case,
						// we want to have left left or right right case,
						// do right coloring relative to parent & sibling
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rightRotation(parent);
					}
					else
					{
						// right left case, first convert it to left left case
						// sibling will be down below after this rotations so update only the sibling's child
						sibling->left->color = parent->color;
						rightRotation(sibling);
						leftRotation(parent);
					}
				}
				// This is the same scenario except symmetric
				else
				{
					if (sibling->parent->left == sibling)
					{
						// left right
						sibling->right->color = parent->color;
						leftRotation(sibling);
						rightRotation(parent);
					}
					else
					{
						// right right
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						leftRotation(parent);
					}
				}
				// finally, update the parent's color to black to preserve the black depth of tree
				// If it was black originally, since we updated nodes colors relative to parent, black depth is preserved.
				// So if the parent was red originally, tree will have red parent and two black siblings
				// If it was all black, then this will not have any effect.
				parent->color = 0;
			}
			else
			{
				// No children case for sibling, (two TIL (black children))
				// Then it is impossible for us to fix this with rotation,
				// If the parent was red, it is fixable by making parent black and
				// sibling red, but if parent and sibling is black, then double black
				// is moved upwards.
				sibling->color = 1;
				if (parent->color == 0)
					rbtDoubleBlackFixer(parent);
				else
					parent->color = 0;
			}
		}
	}
}

void RedBlackTree::rbtTransplant(RBT::Node *parentNode, RBT::Node *childNode)
{
	// If the parent node is the root, update the root
	if (parentNode->parent == NULL)
		root = childNode;
	// Update the parent of parentNode accordingly;
	else if (parentNode == parentNode->parent->left)
		parentNode->parent->left = childNode;
	else
		parentNode->parent->right = childNode;

	// Finally, update the parent node of the child node
	if (childNode)
		childNode->parent = parentNode->parent;
}

RBT::Node *RedBlackTree::findReplacement(RBT::Node *currentNode)
{
	// This function finds replacement for a node in red black tree
	// If the current node has two children, return its successor
	if (currentNode->left != NULL and currentNode->right != NULL)
		return successor(currentNode);

	// when it is a leaf, return null
	if (currentNode->left == NULL and currentNode->right == NULL)
		return NULL;

	// when it has a single child, return its child.
	if (currentNode->left != NULL)
		return currentNode->left;
	else
		return currentNode->right;
}

void RedBlackTree::swapNodes(RBT::Node *node1, RBT::Node *node2)
{
	// This function is used for swapping the nodes
	if (node1 == NULL || node2 == NULL)
		return;

	std::string tempName = node1->name;
	int tempData = node1->data;

	node1->name = node2->name;
	node2->name = tempName;

	node1->data = node2->data;
	node2->data = tempData;
}

bool RedBlackTree::isRBT()
{
	if (isRBThelper(root, 0) == -1)
		return false;

	return true;
}

int RedBlackTree::isRBThelper(RBT::Node *currentNode, int currentBlackHeight)
{
	// This function is used to check the criteria for rbt
	int leftHeight = currentBlackHeight;
	int rightHeight = currentBlackHeight;

	if (currentNode->left)
	{
		// If the left node is black, increment the left black height
		if (currentNode->left->color == 0)
			leftHeight += 1;
		// check the red-red case
		else if (currentNode->color == 1 && currentNode->left->color == 1)
			return -1;
		// recursively continue on the left subtree
		leftHeight = isRBThelper(currentNode->left, leftHeight);
	}
	if (currentNode->right)
	{
		// same steps as above, but for the right subtree
		if (currentNode->right->color == 0)
			rightHeight += 1;
		else if (currentNode->color == 1 && currentNode->right->color == 1)
			return -1;
		rightHeight = isRBThelper(currentNode->right, rightHeight);
	}
	// Check whether heights are different or one of the subtrees returned -1
	if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
		return -1;
	return leftHeight;
}

void RedBlackTree::rbtDestructorHelper(RBT::Node *currentNode)
{
	// Destructor should work inorder to destroy tree properly
	if (currentNode == NULL)
		return;
	// same as the bst destructor
	RBT::Node *left = currentNode->left;
	RBT::Node *right = currentNode->right;
	rbtDestructorHelper(left);
	delete currentNode;
	rbtDestructorHelper(right);
}
