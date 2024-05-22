// Fatih Baskın
// 150210710

#include "Computer.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// methods of the Computer Class

// constructor, prints message
Computer::Computer() { cout << "Computer is ready" << std::endl; };
// setter-getter
void Computer::setCPU(const CPU &inCPU) { attachedCPU = &inCPU; }
const CPU *Computer::getCPU() const { return attachedCPU; }
void Computer::setGPU(const GPU &inGPU) { attachedGPU = &inGPU; }
const GPU *Computer::getGPU() const { return attachedGPU; }
// // attach, + overload
void Computer::operator+(const CPU &inCPU)
{
    // if there is already an attached CPU, function should exit with a message
    if (getCPU() != nullptr)
    {
        cout << "There is already a CPU" << endl;
        return;
    }
    // if there is no CPU attached use setter to attach CPU and print message
    setCPU(inCPU);
    cout << "CPU is attached" << endl;
}
void Computer::operator+(const GPU &inGPU)
{
    // if there is already an attached GPU, function should exit with a message
    if (getGPU() != nullptr)
    {
        cout << "There is already a GPU" << endl;
        return;
    }
    // if there is no GPU attached use setter to attach GPU and print message
    setGPU(inGPU);
    cout << "GPU is attached" << endl;
}
// execute command of the computer
void Computer::execute(const string &operation) const
{
    // if it is a CPU operation, delegate operation to CPU and print result (return type is int)
    if (operation == "subtract" || operation == "add" || operation == "multiply")
        cout << attachedCPU->execute(operation) << endl;
    // if it is a GPU operation, delegate operation to GPU, GPU will print the result
    else if (operation == "render" || operation == "trainModel")
        attachedGPU->execute(operation);
}

// methods of the CPU class

// constructor, it initializes mALU in initializer list with constructor with numPerCores argument then prints messagge
CPU::CPU(int numPerCores) : mALU(numPerCores) { cout << "CPU is ready" << endl; }
// execute method of CPU, const because it does not change anything
int CPU::execute(const string &operation) const
{
    // asking for two integers
    cout << "Enter two integers" << endl;
    int a{}, b{}, result{};
    cin >> a >> b;
    //  delegating operation to ALU
    if (operation == "subtract")
        result = mALU.subtract(a, b);

    else if (operation == "add")
        result = mALU.add(a, b);

    else if (operation == "multiply")
        result = mALU.multiply(a, b);
    // return result
    return result;
}
// getters
const ALU &CPU::getALU() const { return mALU; }

// methods of the ALU class

// constructor, it sets numPerCores in initializer list
ALU::ALU(int inNumPerCores) : numPerCores(inNumPerCores) { cout << "ALU is ready" << endl; }
// ALU operations
int ALU::add(int a, int b) const { return a + b; }
int ALU::subtract(int a, int b) const { return a - b; }
int ALU::multiply(int a, int b) const { return a * b; }
// getters
int ALU::getNumPerCores() const { return numPerCores; }

// methods of the GPU class

// constructor, it initializes mCUDA in initializer list with constructor with numCores argument then prints messagge
GPU::GPU(int numCores) : mCUDA{numCores} { cout << "GPU is ready" << endl; }
// execute method of GPU, const because it does not change anything
bool GPU::execute(const string &operation) const
{
    bool result{};
    //  delegating operation to CUDA
    if (operation == "render")
    {
        result = mCUDA.render();
        // if successful, print message
        if (result)
            cout << "Video is rendered" << endl;
    }
    else if (operation == "trainModel")
    {
        result = mCUDA.trainModel();
        // if successful, print message
        if (result)
            cout << "AI Model is trained" << endl;
    }
    // return result
    return result;
}
// getters
const CUDA &GPU::getCUDA() const { return mCUDA; }

// methods of the CUDA class

// constructor, it sets numCores in initializer list
CUDA::CUDA(int inNumCores) : numCores(inNumCores) { cout << "CUDA is ready" << endl; }
// CUDA operations, there is no operations being done, so just return true
bool CUDA::render() const { return true; }
bool CUDA::trainModel() const { return true; }
// getters
int CUDA::getNumCores() const { return numCores; }
