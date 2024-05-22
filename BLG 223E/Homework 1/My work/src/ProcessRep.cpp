/* @Author
Student Name: Fatih Baskın
Student ID : 150210710
Date: 12.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ProcessRep.h"

using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{
    // constructor, assiging values to corresponding variables.
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;
    this->mpNext = nullptr;
    // assigning public variables to numbers that would not be used
    // and won't create a problem
    // because we need values such that we can directly understand that
    // those vere not initialized yet (initializes in CPURep)
    this->remainingTime = -1;
    this->startTime = -1;
    this->endTime = -1;
}

ProcessRep::~ProcessRep()
{
    // destructor, no need to delete since no value held in private
    // is allocated from the heap (using new)
}

ProcessRep *ProcessRep::getNext()
{
    // mpNext is in private, can't be accessed directy
    // returns mpNext
    return mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    // mpNext is in private, can't be accessed directy
    // assigns the pointer to mpNext
    mpNext = next;
}

string ProcessRep::getProcessType()
{
    // mProcessType is in private, can't be accessed directy
    // returns mProcessType
    return mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    // mProcessType is in private, can't be accessed directy
    // assigns the string to mProcessType
    mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    // mDeliverTime is in private, can't be accessed directy
    // returns mDeliverTime
    return mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    // mDeliverTime is in private, can't be accessed directy
    // assigns the integer to mDeliverTime
    mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    // mProcessID is in private, can't be accessed directy
    // returns mProcessID
    return mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    // mProcessID is in private, can't be accessed directy
    // assigns the integer to mProcessID
    mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    // mProcessTime is in private, can't be accessed directly
    // returns mProcessTime
    return mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    // mProcessTime is in private, can't be accessed directly
    // assigns integer to mProcessTime
    mProcessTime = ProcessTime;
}
