// Fatih Baskın
// 150210710

#include <iostream>
#include <string>

using std::string;

class CUDA
{
public:
    // constructor
    CUDA(int);
    // CUDA operations, they return bool (success/fail)
    bool render() const;
    bool trainModel() const;
    // getters
    int getNumCores() const;
    // there is no use for setters since numCores is a const
private:
    // const, because it can't be modified after initiailization
    const int numCores;
};

class ALU
{
public:
    // constructor
    ALU(int);
    // ALU operations, they return int
    int add(int, int) const;
    int subtract(int, int) const;
    int multiply(int, int) const;
    // getters
    int getNumPerCores() const;
    // there is no use for setters since numPerCores is a const

private:
    // const, because it can't be modified after initiailization
    const int numPerCores;
};

class CPU
{
public:
    // constructor
    CPU(int);
    // execute command, it returns an integer from ALU operations
    int execute(const string &) const;
    // getters
    const ALU &getALU() const;
    // there is no use for setters since mALU is a const object
private:
    // const, because it can't be modified after initiailization
    const ALU mALU;
};

class GPU
{
public:
    // constructor
    GPU(int);
    // execute command, it returns bool (success/fail)
    bool execute(const string &) const;
    // getters
    const CUDA &getCUDA() const;
    // there is no use for setters since mCUDA is a const object
private:
    // const, because it can't be modified after initiailization
    const CUDA mCUDA;
};

class Computer
{
public:
    // execute command of the computer
    void execute(const string &) const;
    // constructor
    Computer();
    // setter-getter
    void setCPU(const CPU &);
    const CPU *getCPU() const;
    void setGPU(const GPU &);
    const GPU *getGPU() const;
    // attach, + overload
    void operator+(const CPU &);
    void operator+(const GPU &);

private:
    // using pointers to constant objects because computer shouldn't change any values of these.
    CPU const *attachedCPU{nullptr};
    GPU const *attachedGPU{nullptr};
};
