/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include <university.h>

// Default constructor.
University::University()
{
    // m_name and m_country are defined as empty string using curly braces notation.

    // Other attributes will take a random value.
    m_weight_gpa = (double)rand() / RAND_MAX;   // This will be a positive double value between 0 and 1.
    m_weight_gre = (double)rand() / RAND_MAX;   // This will be a positive double value between 0 and 1.
    m_weight_toefl = (double)rand() / RAND_MAX; // This will be a positive double value between 0 and 1.
    m_bias = -((double)rand() / RAND_MAX);      // This will be a negative double value between 0 and 1.
}

// Constructor with parameters excluding country.
University::University(std::string name, double weight_gpa, double weight_gre, double weight_toefl, double bias)
{
    // Sets every attribute of the new object according to parameters except counrty, it is set as empty string by default.
    m_name = name;
    m_weight_gpa = weight_gpa;
    m_weight_gre = weight_gre;
    m_weight_toefl = weight_toefl;
    m_bias = bias;
}

// Constructor with all parameters.
University::University(std::string name, double weight_gpa, double weight_gre, double weight_toefl, double bias, std::string country)
{
    // Sets every attribute of the new object according to parameters.
    m_name = name;
    m_weight_gpa = weight_gpa;
    m_weight_gre = weight_gre;
    m_weight_toefl = weight_toefl;
    m_bias = bias;
    m_country = country;
}

// Destructor.
University::~University()
{
    // There is nothing to do special using destructor. This acts as a default destructor.
}

// Getters, they only return values of the attributes so they are const functions.

std::string University::get_name() const { return m_name; }
double University::get_weight_gpa() const { return m_weight_gpa; }
double University::get_weight_gre() const { return m_weight_gre; }
double University::get_weight_toefl() const { return m_weight_toefl; }
double University::get_bias() const { return m_bias; }
std::string University::get_country() const { return m_country; }

// Setters, they modify attributes.

void University::set_name(std::string name) { m_name = name; }
void University::set_weight_gpa(double weight_gpa) { m_weight_gpa = weight_gpa; }
void University::set_weight_gre(double weight_gre) { m_weight_gre = weight_gre; }
void University::set_weight_toefl(double weight_toefl) { m_weight_toefl = weight_toefl; }
void University::set_bias(double bias) { m_bias = bias; }
void University::set_country(std::string country) { m_country = country; }

// Evaluate student method using perceptron method. It does not modify attributes so it is a const function.
// Also this function does not modify Student's attributes except number_of_attributes counter which is mutable.
void University::evaluate_student(const Student &x) const
{
    // Calculate the value according to perceptron algorithm.
    double perceptron = m_weight_gpa * x.get_gpa() + m_weight_gre * x.get_gre() + m_weight_toefl * x.get_toefl() + m_bias;

    // Evaluation of the student
    if (perceptron >= 0)
        std::cout << x.get_name() << " is admitted to " << m_name << "." << std::endl;
    else
        std::cout << x.get_name() << " is rejected from " << m_name << "." << std::endl;

    // Update the number_of_admissions counter.
    x.set_number_of_applications(x.get_number_of_applications() + 1);
}