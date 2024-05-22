/* @Author
Student Name: Fatih Baskın
Student ID : 150210710
Date: 12.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    // allocate memory for a FIFORep using constructor.
    mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    // delete mFinishedProcess FIFORep using destructor.
    delete mFinishedProcess;
}

ProcessRep *CPURep::runCPU(ProcessRep *p, int time)
{
    // security check for seg fault
    if (p == nullptr)
        return nullptr;

    // if current process is finished set end time and
    // add to mFinishedProcess and return null
    if (p->remainingTime == 0)
    {
        p->endTime = time;
        mFinishedProcess->queue(p);
        return nullptr;
    }

    // if not finished return p
    return p;
}

FIFORep *CPURep::getFinishedProcess()
{
    return mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep *finishedProcess)
{
    // sets the mFinishedProcess
    mFinishedProcess = finishedProcess;
}