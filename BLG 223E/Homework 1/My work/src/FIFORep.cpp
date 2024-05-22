/* @Author
Student Name: Fatih Baskın
Student ID : 150210710
Date: 12.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    // default constructor, initialize as null
    this->mpHead = nullptr;
    this->mpTail = nullptr;
}

FIFORep::FIFORep(ProcessRep *head)
{
    // custom constructor, set the mpHead as head
    this->mpHead = head;

    // there is a possibility that if given head is a chain where there are
    // multiple nodes connected then going to its end is necessary
    ProcessRep *currPtr = head;
    // function will iterate until currPtr reaches tail (next == null)
    while (currPtr != nullptr && currPtr->getNext() != nullptr)
        currPtr = currPtr->getNext();

    // after the while loop, currPtr is at the last node of the chain
    // if head was null or single node, it would be the same with head
    this->mpTail = currPtr;
}

FIFORep::~FIFORep()
{
    // to delete a linked list entirely you need to delete all the nodes
    // to traverse the linked list, generating a pointer
    ProcessRep *currPtr = mpHead;
    while (currPtr != nullptr)
    {
        // while current pointer (currPtr) is not null traverse and delete

        // if head was already null, there is nothing to delete so function
        // will not iterate at all

        // when function reaches tail, tail's next is null so it would stop
        // after deleting tail

        // need a temporary pointer (tempPtr) to delete currPtr without
        // losing the next pointer
        ProcessRep *tempPtr = currPtr->getNext();
        delete currPtr;
        currPtr = tempPtr;
    }
    // to prevent destructor to delete already deleted pointer adresses
    // set these adresses to null (preventing double deletion exeption)
    mpTail = nullptr;
    mpHead = nullptr;
}

void FIFORep::setHead(ProcessRep *head)
{
    // warning: if head is a nullptr or current fifo has elements then this
    // would result in the loss of old content and memory leak.

    // i wrote this function on the premise that head is not a nullptr and
    // FIFO is empty

    if (head == nullptr)
        return;

    // assigning head to mpHead
    mpHead = head;
}

ProcessRep *FIFORep::getHead()
{
    // mpHead is in private, returns mpHead
    return mpHead;
}

void FIFORep::setTail(ProcessRep *tail)
{
    // warning: if tail is a nullptr or fifo has elements then this would
    // result in two unconnected chains of nodes.

    // i wrote this function on the premise that tail is not a nullptr and
    // FIFO is empty

    if (tail == nullptr)
        return;

    // assigning tail to mpTail
    mpTail = tail;
}

ProcessRep *FIFORep::getTail()
{
    // return the value of mpTail
    return mpTail;
}

void FIFORep::queue(ProcessRep *p)
{
    // warning: if p is a nullptr then assigning p as head will result in
    // the loss of old content

    // i wrote this function on the premise that p is not a nullptr
    if (p == nullptr)
        return;

    // queue is a fifo data structure, first in first out, so queueing to
    // the tail and dequeueing from the head

    // For queue operation updating the mpTail's next as p and setting p as
    // new tail would be sufficient

    // there is a possibility that if given p is a chain where there are
    // multiple nodes connected then going to its end is necessary
    ProcessRep *newTail = p;
    // function will iterate until currPtr reaches tail (next == null)
    while (newTail != nullptr && newTail->getNext() != nullptr)
        newTail = newTail->getNext();

    // after the while loop, newTail is at the last node of the chain
    // if p was null or single node, it would be the same with p

    // case: if queue is empty function will finish after if check
    if (mpHead == nullptr)
    {
        mpHead = p;
        mpTail = newTail;
        return;
    }

    // if queue is not empty function will arrive here and assign p as
    // mpTail's next then set mpTail as newTail
    mpTail->setNext(p);
    mpTail = newTail;
}

ProcessRep *FIFORep::dequeue()
{
    // in fifo dequeueing means to seperate first item in the linked list
    // therefore meaning taking from the head

    // if fifo is empty (head = null) dequeue operation is impossible
    if (mpHead == nullptr)
        return nullptr;

    // if head is not null then there are two cases and also saving head
    // to return it
    ProcessRep *result = mpHead;

    // if head does not have a next (head is the only element in queue)
    // after dequeue operation fifo should be empty
    if (mpHead->getNext() == nullptr)
    {
        mpTail = nullptr;
        mpHead = nullptr;
        return result;
    }
    // if function came here so far there are more than one element in the
    // queue so shift head to next item in the queue
    mpHead = mpHead->getNext();
    // setting result's next to prevent it linking previous list when used
    result->setNext(nullptr);
    return result;
}

ProcessRep *FIFORep::searchID(int id)
{
    // if item is not found, return null
    // if found return its pointer

    // if check for empty fifo, if fifo is empty return null
    if (mpHead == nullptr)
        return nullptr;

    // if not empty, traversing the whole linked list for value
    ProcessRep *currPtr = mpHead;
    while (currPtr != nullptr)
    {
        // if currPtr's id is equal to id, return currPtr
        if (currPtr->getProcessID() == id)
            return currPtr;
        // otherwise move to next
        currPtr = currPtr->getNext();
    }

    // if function didn't return anything in the loop then return  null
    // means not in the list and while loop iterated until tail's next, null
    return nullptr;
}

void FIFORep::printFIFO()
{
    // The function prints the proceses in the queue starting from Head to tail.
    // if check for empty fifo
    if (mpHead == nullptr)
        return;

    // If fifo is not empty, using a temporary pointer to traverse the fifo
    ProcessRep *currPtr = mpHead;
    while (currPtr != nullptr)
    {
        cout << currPtr->getProcessType() << currPtr->getProcessID() << " " << currPtr->startTime << " " << currPtr->endTime << " ";
        currPtr = currPtr->getNext();
    }
}
