/* @Author
Student Name: Fatih Baskın
Student ID : 150210710
Date: 12.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    // constructor, calling constructor for FIFOReps and CPURep
    this->mpProcessFIFO[0] = new FIFORep();
    this->mpProcessFIFO[1] = new FIFORep();
    this->mpProcessFIFO[2] = new FIFORep();
    this->pCpuObj = new CPURep();
    // assigning 0 or null to remaineer
    this->mpRunningProcess = nullptr;
    this->timeSliceCount = 0;
    this->totalTime = 0;
}
SchedulerRep::~SchedulerRep()
{
    // using delete operator to call destructor;
    delete mpProcessFIFO[0];
    // mpProcessFIFO[0]->~FIFORep();
    // mpProcessFIFO[0] = nullptr;

    delete mpProcessFIFO[1];
    // mpProcessFIFO[1]->~FIFORep();
    // mpProcessFIFO[1] = nullptr;

    delete mpProcessFIFO[2];
    // mpProcessFIFO[2]->~FIFORep();
    // mpProcessFIFO[2] = nullptr;

    delete pCpuObj;
    // pCpuObj->~CPURep();
    // pCpuObj = nullptr;

    delete mpRunningProcess;
}

FIFORep *SchedulerRep::getProcessFIFO(int index)
{
    // to prevent seg fault, if index is out of boundaries return null
    if (index > 2 || index < 0)
        return nullptr;

    return mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep *fifo, int index)
{
    // to prevent seg fault, if index is out of boundaries return
    if (index > 2 || index < 0)
        return;

    mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep *p)
{
    // set mpRunningProcess as p
    mpRunningProcess = p;
}

ProcessRep *SchedulerRep::getRunningProcess()
{
    // return mpRunningProcess
    return mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep *p)
{
    // this function queues processes into fifos according to their types
    // type "A" -> [0], "B" -> [1], "C" -> [2]
    string processType = p->getProcessType();
    if (processType == "A")
    {
        mpProcessFIFO[0]->queue(p);
        return;
    }
    if (processType == "B")
    {
        mpProcessFIFO[1]->queue(p);
        return;
    }
    if (processType == "C")
    {
        mpProcessFIFO[2]->queue(p);
        return;
    }
    return;
}

ProcessRep *SchedulerRep::popProcess()
{
    // this process will pop a process from fifos in order of A>B>C, ie
    // if A is empty it will check B, if B is empty it will check C

    // if A is not empty, pop A and return
    if (mpProcessFIFO[0]->getHead() != nullptr)
    {
        return mpProcessFIFO[0]->dequeue();
    }

    // if B is not empty, pop B and return
    if (mpProcessFIFO[1]->getHead() != nullptr)
    {
        return mpProcessFIFO[1]->dequeue();
    }

    // if C is not empty, pop C and return
    if (mpProcessFIFO[2]->getHead() != nullptr)
    {
        return mpProcessFIFO[2]->dequeue();
    }
    // if all fifos are empty
    return nullptr;
}

bool SchedulerRep::checkTimeSlice()
{
    // there are three cases where quantum number is met

    // first, if mpRunningProcess is null (no running process)
    // return false
    if (mpRunningProcess == nullptr)
        return false;

    string processType = mpRunningProcess->getProcessType();

    // processType == "A" and quantum number is 2 return true
    if (processType == "A" && timeSliceCount == 2)
        return true;

    // processType == "B" and quantum number is 4 return true
    if (processType == "B" && timeSliceCount == 4)
        return true;

    // processType == "C" and quantum number is 8 return true
    if (processType == "C" && timeSliceCount == 8)
        return true;

    // otherwise return false
    return false;
}
ProcessRep *SchedulerRep::sendProcessToCPU(ProcessRep *p)
{
    // if p is null (no running process) pop from the list and set quantum 0
    if (p == nullptr)
    {
        p = popProcess();
        timeSliceCount = 0;
    }

    // if p is being run in the cpu for the first time
    // set start time and remaining time
    if (p != nullptr && p->startTime == -1)
    {
        p->startTime = totalTime;
        p->remainingTime = p->getProcessTime();
    }

    // to mimic cpu being run decrement remaining time
    // and increment quantum and total time
    if (p != nullptr)
        p->remainingTime -= 1;

    timeSliceCount += 1;
    totalTime += 1;

    // run the cpu with current pointer
    p = pCpuObj->runCPU(p, totalTime);

    // if p is done inside cpu
    return p;
}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */
    // first create a object to use in FIFOs from new coming process
    ProcessRep *newProcess = new ProcessRep(type, id, arrivalTime, processTime);
    // then push it to three fifos where A B C type processes are held
    pushProcess(newProcess);

    // if there is no running process pop from fifo list and reset counter
    if (mpRunningProcess == nullptr)
    {
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }

    // if there is higher priority process that has arrived terminate current
    // one and start to use new one and reset quantum

    // Case C
    if (mpRunningProcess != nullptr && mpRunningProcess->getProcessType() == "C")
    {
        // if there is higher priority process "A" or "B"
        if (mpProcessFIFO[0]->getHead() != nullptr || mpProcessFIFO[1]->getHead() != nullptr)
        {
            pushProcess(mpRunningProcess);
            mpRunningProcess = popProcess();
            timeSliceCount = 0;
        }
    } // Case B
    else if (mpRunningProcess != nullptr && mpRunningProcess->getProcessType() == "B")
    {
        if (mpProcessFIFO[0]->getHead() != nullptr)
        {
            pushProcess(mpRunningProcess);
            mpRunningProcess = popProcess();
            timeSliceCount = 0;
        }
    }

    // if quantum time is arrived push running process to FIFOs then pop
    // from the fifo list and reset counter
    if (checkTimeSlice())
    {
        pushProcess(mpRunningProcess);
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }

    // run the the cpu
    mpRunningProcess = sendProcessToCPU(mpRunningProcess);

    // after cpu being run if process ended pull next process
    if (mpRunningProcess == nullptr)
    {
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }
}

void SchedulerRep::schedule(ProcessRep *p)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */
    // if there is no running process pop from fifo list and reset counter
    // if there is no running process pop from fifo list and reset counter
    if (mpRunningProcess == nullptr)
    {
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }

    // if quantum time is arrived push running process to FIFOs then pop
    // from the fifo list and reset counter
    if (checkTimeSlice())
    {
        pushProcess(mpRunningProcess);
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }

    // run the the cpu
    mpRunningProcess = sendProcessToCPU(mpRunningProcess);

    // after cpu being run if process ended pull next process
    if (mpRunningProcess == nullptr)
    {
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }
}
