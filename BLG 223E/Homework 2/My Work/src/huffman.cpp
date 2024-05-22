//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Fatih Baskın
//---Student Number: 150210710
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char *argv)
{
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if (readKeyFile.is_open())
    {
        while (!readKeyFile.eof())
        {
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey()
{
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency()
{
    // DO NOT CHANGE THIS
    sortKey();
    // DO NOT CHANGE THIS
    // All of the chars in the key are sorted here.
    // Counting until char change and pushing count and char into queue.
    int count = 1;                // Count starts from 1
    char chr = sortedKey[0];      // With char as first char in sortedKey.
    int limit = sortedKey.size(); // For loop limit set as size of sortedKey.
    for (int i = 1; i < limit; i++)
    {
        // If there is a char change, create a node with count and char itself.
        if (sortedKey[i] != chr)
        {
            Node *intoQueue = new Node;
            // Initially string starts as empty, append char to string.
            intoQueue->token.symbol += chr;
            intoQueue->token.val = count;
            queue.enque(intoQueue);
            // Start a new char counter
            count = 1;
            chr = sortedKey[i];
        }
        else
        {
            count += 1;
        }
    }
    // Since this method only check for char changes, push last char counter manually.
    Node *intoQueue = new Node;
    intoQueue->token.symbol += chr;
    intoQueue->token.val = count;
    queue.enque(intoQueue);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree()
{
    // Huffman algorithm works by merging smaller nodes into larger nodes.
    // This process repeats until only one node is remaining in the queue.
    // This last node will be the root of the tree.
    findFrequency();
    while (queue.head->next != nullptr)
    {
        Node *temp1 = queue.dequeue();
        Node *temp2 = queue.dequeue();
        // Merge top two nodes into a new node and push it back to queue.
        queue.enque(huffmanTree.mergeNodes(temp1, temp2));
    }
    // When only last 1 element is left, use that element as the tree's root.
    huffmanTree.root = queue.dequeue();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree()
{
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node *traverse, string tokenBinary)
{
    // If correct char is found, return it.
    if (traverse->token.symbol.size() == 1 && traverse->token.symbol[0] == tokenChar)
        return tokenBinary;

    // If the char is found on the left direction, add 0 to that binary representation.
    // Move until you find the char standalone recursively.
    if (traverse->left != nullptr)
    {
        for (char x : traverse->left->token.symbol)
        {
            if (x == tokenChar)
            {
                string temp = tokenBinary + "0";
                return getTokenBinary(tokenChar, traverse->left, temp);
            }
        }
    }

    // If the char is found on the right direction, add 1 to that binary representation.
    // Move until you find the char standalone recursively.
    if (traverse->right != nullptr)
    {
        for (char x : traverse->right->token.symbol)
        {
            if (x == tokenChar)
            {
                string temp = tokenBinary + "1";
                return getTokenBinary(tokenChar, traverse->right, temp);
            }
        }
    }

    // If left node and right node doesn't exist, we are at a leaf, so return. (might be redundant)
    return tokenBinary;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password)
{
    // First, clear the encoded previous password.
    this->encodedBinaryPassword = "";
    this->encodedValPassword = "";
    // After constructing the tree, encodedBinaryPassword should be generated,
    // with obtanining the correct binary values for chars from the tree,
    for (char x : password)
    {
        // Find the binary representation of char x.
        string binLetter = getTokenBinary(x, this->huffmanTree.root, "");
        // Append binary representation for each letter.
        this->encodedBinaryPassword += binLetter;
        // Append the lenght of binary representation as a char.
        this->encodedValPassword += ('0' + binLetter.size());
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword()
{
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword)
{
    // First, clear the old decodedPassword
    this->decodedPassword = "";
    // Then start to generate the decoded password.
    // For reading from binary password, keeping the index outside of for loop's scope.
    int binIdx = 0;
    // For each char of valPassword which shows number of bits, read that amount of bits,
    // then look for that letter and store that letter in decodedPassword.
    for (char x : encodedValPassword)
    {
        // We need to read x amount of bits.
        string token = "";
        // Converting char x into integer
        int readAmount = x - '0';
        for (int i = 0; i < readAmount; i++)
        {
            // Read x amount of bits from binary password.
            token += encodedBinaryPassword[binIdx];
            // Increment the binIdx index.
            binIdx += 1;
        }
        // Lastly add token to decodedPassword using decodeToken
        decodeToken(token);
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken)
{
    // Start traversing the Huffman Tree from the root.
    Node *traverse = this->huffmanTree.root;
    // For every char of encoded token, move right if char is 1,
    // move left if char is 0. Get the char at last and append it.
    for (char x : encodedToken)
    {
        // Before checking the left/right if we manage to get somewhere wrong
        // to prevent seg fault we need to do these checks. Might be redundant.
        if (traverse == nullptr)
            return; // Before doing any accessing to null, just return to prevent seg fault.
        if (x == '1')
            traverse = traverse->right;
        else if (x == '0')
            traverse = traverse->left;
    }
    // Appending the symbol held in traverse to decodedPassword.
    this->decodedPassword += traverse->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword()
{
    cout << "Decoded Password: " << decodedPassword << endl;
};