/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include "student.h"
#include <string>
#include <iostream>

// Those are required for random values.
#include <cstdlib>

class University
{
public:
    // Default constructor.
    University();

    // Constructor with parameters excluding country.
    University(std::string, double, double, double, double);

    // Constructor with all parameters.
    University(std::string, double, double, double, double, std::string);

    // Destructor.
    ~University();

    // Getters, they only return values of the attributes so they are const functions.

    std::string get_name() const;
    double get_weight_gpa() const;
    double get_weight_gre() const;
    double get_weight_toefl() const;
    double get_bias() const;
    std::string get_country() const;

    // Setters, they modify attributes.

    void set_name(std::string);
    void set_weight_gpa(double);
    void set_weight_gre(double);
    void set_weight_toefl(double);
    void set_bias(double);
    void set_country(std::string);

    // Evaluate student method using perceptron method. It does not modify attributes so it is a const function.
    // Also this function does not modify Student's attributes except number_of_attributes counter which is mutable.
    void evaluate_student(const Student &) const;

private:
    // Attributes of the University class. They are initially set to zero or empty.

    std::string m_name{};
    double m_weight_gpa;
    double m_weight_gre;
    double m_weight_toefl;
    double m_bias;
    std::string m_country{};
};