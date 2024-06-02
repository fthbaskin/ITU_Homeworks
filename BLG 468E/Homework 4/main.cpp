// Fatih Baskın
// 150210710

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Employee Interface provides a common interface for all employee types
class EmployeeInterface
{
public:
    // Virtual destructor so that it can be overridden by derived classes
    virtual ~EmployeeInterface() = default;
    // Virtual method so that it can be overridden by derived classes
    virtual int getSalary() = 0;
    // Virtual method so that it can be overridden by derived classes
    virtual string getName() = 0;
    // Virtual method so that it can be overridden by derived classes
    virtual void setName(string name) = 0;
};

// Worker class is a concrete class that implements the EmployeeInterface
class Worker : public EmployeeInterface
{
public:
    // Constructor
    Worker(string name, int wage, int hours) : name{name}, wage{wage}, hours{hours} {}
    // Overridden method from the interface EmployeeInterface
    string getName() { return name; }
    // Overridden method from the interface EmployeeInterface
    void setName(string name) { this->name = name; }
    // Overridden method from the interface EmployeeInterface
    int getSalary() { return wage * hours; }
    // Getter for wage
    int getWage() { return wage; }
    // Getter for hours
    int getHours() { return hours; }
    // Setter for wage
    void setWage(int wage) { this->wage = wage; }
    // Setter for hours
    void setHours(int hours) { this->hours = hours; }

private:
    string name;
    int wage;
    int hours;
};

// Researcher class is a concrete class that implements the EmployeeInterface
class Researcher : public EmployeeInterface
{
public:
    // Constructor
    Researcher(string name, int number_of_projects);
    // Overridden method from the interface EmployeeInterface
    string getName() { return name; }
    // Overridden method from the interface Employee
    void setName(string name) { this->name = name; }
    // Overridden method from the interface EmployeeInterface
    int getSalary();
    // Getter for number_of_projects
    int getNumberOfProjects() { return number_of_projects; }
    // Setter for number_of_projects
    void setNumberOfProjects(int number_of_projects) { this->number_of_projects = number_of_projects; }

private:
    string name;
    int number_of_projects;
};

// Company Interface provides a common interface for all company structures
class CompanyInterface
{
public:
    // Virtual destructor so that it can be overridden by derived classes
    virtual ~CompanyInterface() = default;
    // Virtual method so that it can be overridden by derived classes
    virtual void addEmployee(EmployeeInterface *employee) = 0;
    // Virtual method so that it can be overridden by derived classes
    virtual bool removeEmployee(EmployeeInterface *employee) = 0;
    // Virtual method so that it can be overridden by derived classes
    virtual vector<EmployeeInterface *> getEmployees() = 0;
    // Virtual method so that it can be overridden by derived classes
    virtual string getName() = 0;
    // Virtual method so that it can be overridden by derived classes
    virtual void setName(string name) = 0;
};

// CompanyStructure class is a concrete class that implements the Company Interface
class CompanyStructure : public CompanyInterface
{
public:
    // Constructor
    CompanyStructure(string name) : name{name} {}
    // Overridden method from the interface Company
    void addEmployee(EmployeeInterface *employee) { employees.push_back(employee); }
    // Overridden method from the interface Company
    bool removeEmployee(EmployeeInterface *employee);
    // Overridden method from the interface Company
    vector<EmployeeInterface *> getEmployees() { return employees; }
    // Overridden method from the interface Company
    string getName() { return name; }
    // Overridden method from the interface Company
    void setName(string name) { this->name = name; }
    // Destructor
    ~CompanyStructure();

private:
    string name;
    vector<EmployeeInterface *> employees;
};

class CompanyComposite : public CompanyInterface
{

public:
    // Constructor
    CompanyComposite(string name) : name{name} {}
    // Overridden method from the interface Company
    void addEmployee(EmployeeInterface *employee) { employees.push_back(employee); }
    // Overridden method from the interface Company
    bool removeEmployee(EmployeeInterface *employee);
    // Overridden method from the interface Company
    vector<EmployeeInterface *> getEmployees();
    // Overridden method from the interface Company
    string getName() { return name; }
    // Overridden method from the interface Company
    void setName(string name) { this->name = name; }
    // Add a new company to the composite
    void addCompany(CompanyInterface *company) { company_structures.push_back(company); }
    // Remove a company from the composite
    bool removeCompany(CompanyInterface *company);
    // Destructor
    ~CompanyComposite();

private:
    string name;
    vector<EmployeeInterface *> employees;
    vector<CompanyInterface *> company_structures;
};

// Accounting Strategy Interface provides a common interface for all accounting strategies
class AccountingStrategyInterface
{
public:
    // Virtual destructor so that it can be overridden by derived classes
    virtual ~AccountingStrategyInterface() = default;
    // Virtual method so that it can be overridden by derived classes
    virtual double applyStrategy(vector<EmployeeInterface *> employees) = 0;
};

// A class that represents an accounting strategy that calculates the total salary of all employees
class TotalSalaryStrategy : public AccountingStrategyInterface
{
public:
    double applyStrategy(vector<EmployeeInterface *> employees);
};

// A class that represents an accounting strategy that calculates the average salary of all employees
class AverageSalaryStrategy : public AccountingStrategyInterface
{
public:
    double applyStrategy(vector<EmployeeInterface *> employees);
};

// A class that represents an accounting strategy that calculates the minimum salary of all employees
class MinimumSalaryStrategy : public AccountingStrategyInterface
{
public:
    double applyStrategy(vector<EmployeeInterface *> employees);
};

// A class that represents an accounting strategy that calculates the maximum salary of all employees
class MaximumSalaryStrategy : public AccountingStrategyInterface
{
public:
    double applyStrategy(vector<EmployeeInterface *> employees);
};

class Accounting
{
public:
    double doAccounting(CompanyInterface *company_structure, AccountingStrategyInterface *strategy);
};

int main()
{
    // Create the company
    CompanyComposite *company = new CompanyComposite("Company");
    // Add the employees to the company
    company->addEmployee(new Worker("worker1", 500, 100));
    // Create a depoartment
    CompanyComposite *department = new CompanyComposite("Department1");
    // Add the employees to the department
    department->addEmployee(new Worker("worker2", 200, 160));
    department->addEmployee(new Worker("worker3", 300, 160));
    // Add the department to the company
    company->addCompany(department);
    // Create a sub-department
    CompanyStructure *sub_department = new CompanyStructure("Department1.1");
    // Add the employees to the sub-department
    sub_department->addEmployee(new Worker("worker4", 100, 120));
    sub_department->addEmployee(new Researcher("researcher1", 2));
    sub_department->addEmployee(new Researcher("researcher2", 3));
    // Add the sub-department to the department
    department->addCompany(sub_department);

    // Create the accounting strategy to calculate the total salary
    TotalSalaryStrategy *total_salary_strategy = new TotalSalaryStrategy();
    // Create the accounting
    Accounting *accounting = new Accounting();
    // Apply the accounting strategy to the company
    cout << "Total salary of all employees in the company: " << accounting->doAccounting(company, total_salary_strategy) << endl;
    // Create the accounting strategy to calculate the average salary
    AverageSalaryStrategy *average_salary_strategy = new AverageSalaryStrategy();
    // Apply the accounting strategy to the company
    cout << "Average salary of all employees in the company: " << accounting->doAccounting(company, average_salary_strategy) << endl;
    // Create the accounting strategy to calculate the minimum salary
    MinimumSalaryStrategy *minimum_salary_strategy = new MinimumSalaryStrategy();
    // Apply the accounting strategy to the company
    cout << "Minimum salary of all employees in the company: " << accounting->doAccounting(company, minimum_salary_strategy) << endl;
    // Create the accounting strategy to calculate the maximum salary
    MaximumSalaryStrategy *maximum_salary_strategy = new MaximumSalaryStrategy();
    // Apply the accounting strategy to the company
    cout << "Maximum salary of all employees in the company: " << accounting->doAccounting(company, maximum_salary_strategy) << endl;

    // Delete the company
    delete company;

    // Delete the accounting strategies
    delete total_salary_strategy;
    delete average_salary_strategy;
    delete minimum_salary_strategy;
    delete maximum_salary_strategy;

    // Delete the accounting
    delete accounting;

    return 0;
}

Researcher::Researcher(string name, int number_of_projects)
{
    // Set the name of the researcher
    this->name = name;
    // If the number of projects is less than 0, set it to 0
    if (number_of_projects < 0)
    {
        this->number_of_projects = 0;
        return;
    }
    // Set the number of projects to the given value
    this->number_of_projects = number_of_projects;
}

int Researcher::getSalary()
{
    // If the number of projects is less than 1, return 0 (no projects, no salary)
    if (number_of_projects < 1)
        return 0;
    // If the number of projects is 1, return 30000
    if (number_of_projects == 1)
        return 30000;
    // If the number of projects is 2, return 50000
    if (number_of_projects == 2)
        return 50000;
    // If the number of projects is 3 or more, return 65000
    return 65000;
}

bool CompanyStructure::removeEmployee(EmployeeInterface *employee)
{
    // Find and remove the employee from the employees vector
    for (int i = 0; i < (int)employees.size(); i++)
    {
        // If the employee is found, delete it and remove it from the vector
        if (employees[i] == employee)
        {
            delete employees[i];
            employees.erase(employees.begin() + i);
            return true;
        }
    }

    // If cannot find the employee, return false
    return false;
}

CompanyStructure::~CompanyStructure()
{
    // Delete all employees in the company structure
    for (int i = 0; i < (int)employees.size(); i++)
        delete employees[i];
}

bool CompanyComposite::removeEmployee(EmployeeInterface *employee)
{
    // Find and remove the employee from the employees vector
    for (int i = 0; i < (int)employees.size(); i++)
    {
        // If the employee is found, delete it and remove it from the vector
        if (employees[i] == employee)
        {
            delete employees[i];
            employees.erase(employees.begin() + i);
            return true;
        }
    }
    // If cannot find the employee, then search in the company structures
    for (int i = 0; i < (int)company_structures.size(); i++)
    {
        // If the employee is found in the company structure, remove it
        if (company_structures[i]->removeEmployee(employee))
            return true;
    }
    // If cannot find the employee, return false
    return false;
}

vector<EmployeeInterface *> CompanyComposite::getEmployees()
{
    // Get all employees in the company aggregate
    vector<EmployeeInterface *> all_employees;
    // Get all employees in the company aggregate itself
    for (EmployeeInterface *employee : employees)
    {
        all_employees.push_back(employee);
    }
    // Get all employees in the company structures in the company aggregate
    for (CompanyInterface *company_structure : company_structures)
    {
        vector<EmployeeInterface *> company_structure_employees = company_structure->getEmployees();
        for (EmployeeInterface *employee : company_structure_employees)
        {
            all_employees.push_back(employee);
        }
    }
    return all_employees;
}

bool CompanyComposite::removeCompany(CompanyInterface *company)
{
    // Find and remove the company from the company structures vector
    for (int i = 0; i < (int)company_structures.size(); i++)
    {
        // If the company is found, delete it and remove it from the vector
        if (company_structures[i] == company)
        {
            delete company_structures[i];
            company_structures.erase(company_structures.begin() + i);
            return true;
        }
    }
    // If cannot find the company, return false
    return false;
}

CompanyComposite::~CompanyComposite()
{
    // Delete all employees in the company composite
    for (int i = 0; i < (int)employees.size(); i++)
        delete employees[i];
    // Delete all company structures in the company composite
    for (int i = 0; i < (int)company_structures.size(); i++)
        delete company_structures[i];
}

double TotalSalaryStrategy::applyStrategy(vector<EmployeeInterface *> employees)
{
    // Calculate the total salary of all employees
    double total_salary = 0;
    for (EmployeeInterface *employee : employees)
    {
        total_salary += employee->getSalary();
    }
    return total_salary;
}

double AverageSalaryStrategy::applyStrategy(vector<EmployeeInterface *> employees)
{
    // Calculate the total salary of all employees
    double total_salary = 0;
    for (EmployeeInterface *employee : employees)
    {
        total_salary += employee->getSalary();
    }
    // Calculate the average salary
    return total_salary / employees.size();
}

double Accounting::doAccounting(CompanyInterface *company_structure, AccountingStrategyInterface *strategy)
{
    // Apply the given strategy to the company structure
    return strategy->applyStrategy(company_structure->getEmployees());
}

double MinimumSalaryStrategy::applyStrategy(vector<EmployeeInterface *> employees)
{
    // Calculate the minimum salary of all employees
    double minimum_salary = employees[0]->getSalary();
    for (EmployeeInterface *employee : employees)
    {
        if (employee->getSalary() < minimum_salary)
            minimum_salary = employee->getSalary();
    }
    return minimum_salary;
}

double MaximumSalaryStrategy::applyStrategy(vector<EmployeeInterface *> employees)
{
    // Calculate the maximum salary of all employees
    double maximum_salary = employees[0]->getSalary();
    for (EmployeeInterface *employee : employees)
    {
        if (employee->getSalary() > maximum_salary)
            maximum_salary = employee->getSalary();
    }
    return maximum_salary;
}