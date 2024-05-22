/* @Author
Student Name: Fatih Baskın
Student ID : 150210710
Date: 12.10.2022
*/
#ifndef _CPUREP
#define _CPUREP

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

class CPURep
{
private:
    FIFORep *mFinishedProcess;

public:
    CPURep();
    ~CPURep();

    FIFORep *getFinishedProcess();
    void setFinishedProcess(FIFORep *);

    ProcessRep *runCPU(ProcessRep *, int);
};

#endif