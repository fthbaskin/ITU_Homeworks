/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include <student.h>

// Default constructor.
Student::Student()
{
    // I am unsure about default constructor behaviour, whether it should print log in message or not.
    print_login();
}

// Copy constructor.
Student::Student(const Student &original)
{
    // Copying values of the original student except number_of_admissions counter, it is set as 0 by default.
    m_name = original.get_name();
    m_gpa = original.get_gpa();
    m_gre = original.get_gre();
    m_toefl = original.get_toefl();
    // Log in message.
    print_login();
}

// Constructor with parameters.
Student::Student(std::string name, double gpa, int gre, int toefl)
{
    // Sets every attribute of the new object according to parameters except number_of_admissions counter, it is set as 0 by default.
    m_name = name;
    m_gpa = gpa;
    m_gre = gre;
    m_toefl = toefl;
    // Log in message.
    print_login();
}

// Destructor.
Student::~Student()
{
    // Log out message.
    std::cout << m_name << " logged out of the system with " << m_number_of_applications << " application(s)." << std::endl;
}

// Setters:

void Student::set_name(std::string name) { m_name = name; }
void Student::set_gpa(double gpa) { m_gpa = gpa; }
void Student::set_gre(int gre) { m_gre = gre; }
void Student::set_toefl(int toefl) { m_toefl = toefl; }
void Student::set_number_of_applications(int number_of_applications) const { m_number_of_applications = number_of_applications; }

// Getters:

std::string Student::get_name() const { return m_name; }
double Student::get_gpa() const { return m_gpa; }
int Student::get_gre() const { return m_gre; }
int Student::get_toefl() const { return m_toefl; }
// This function can modify mutable number_of_appliactions counter even though object is const so function is const.
int Student::get_number_of_applications() const { return m_number_of_applications; }

// A utility to print log in messages.
void Student::print_login() const
{
    // Log in message.
    std::cout << m_name << " logged in to the system." << std::endl;
}
