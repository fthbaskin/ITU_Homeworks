//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Fatih Baskın
//---Student Number: 150210710
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue()
{
    // Initially priority queue starts with no element.
    this->head = nullptr;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node *newnode)
{
    // If the head is empty, set the node as head.
    if (this->head == nullptr)
    {
        this->head = newnode;
        return;
    }
    // This queue has the smallest elements as its top element.
    // If head > newnode, set newnode as head.
    if (this->head->token.val > newnode->token.val)
    {
        newnode->next = this->head;
        this->head = newnode;
        return;
    }
    // We need to traverse the nodes to find the spot for newnode.
    // For traversals, previous node should be kept.
    Node *prev = this->head;
    // While next is not null and next is smaller or equal to newnode, traverse.
    while (prev->next != nullptr && prev->next->token.val <= newnode->token.val)
    {
        prev = prev->next;
    }
    // Set the previous node's next as newnode's next.
    newnode->next = prev->next;
    // Set the previous node's next as newnode.
    prev->next = newnode;
};

//-------------Remove Node From Priority Queue-------------//
Node *PriorityQueue::dequeue()
{
    // Deequeue shall return a node ptr, so defining it early on.
    Node *ret = this->head;
    // If head is null, skip, otherwise program will get seg fault.
    // Setting next element as head and detaching old head from queue.
    if (this->head != nullptr)
    {
        this->head = head->next;
        ret->next = nullptr;
    }
    return ret;
};

//-------------Initialize Tree-------------//
Tree::Tree()
{
    // Since we are not passing any parameters to constructor, tree is empty.
    this->root = nullptr;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree()
{
    // This function calls a recursive code to delete its all nodes.
    deleteTree(this->root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node *node)
{
    // Recursive code to delete all the nodes from the tree.
    // Basically a postorder traversal to delete children first, then itself.
    // Doing null checks in every step.
    if (node->left != nullptr)
        deleteTree(node->left);
    if (node->right != nullptr)
        deleteTree(node->right);
    if (node != nullptr)
        delete node;
    return;
}

//-------------Merges Two Node Into One-------------//
Node *Tree::mergeNodes(Node *temp1, Node *temp2)
{
    // It will genereate a new node, which has temp1 on its left and temp2 on its right.
    Node *merged = new Node;
    merged->left = temp1;
    merged->right = temp2;
    // Its symbol is concatination of temp1 and temp2's symbols.
    merged->token.symbol = temp1->token.symbol + temp2->token.symbol;
    // Its value is addition of temp1 and temp2's values.
    merged->token.val = temp1->token.val + temp2->token.val;
    return merged;
};

void Tree::printTree(Node *traverse, int level)
{
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if (traverse->left)
        printTree(traverse->left, level + 1);
    if (traverse->right)
        printTree(traverse->right, level + 1);
};

// The constructor that I added for safety aganist segmentation fault.
Node::Node()
{
    // Setting node's values to 0 and empty string.
    this->token.val = 0;
    this->token.symbol = "";
    // Setting node's pointers to NULL.
    this->left = nullptr;
    this->next = nullptr;
    this->right = nullptr;
};