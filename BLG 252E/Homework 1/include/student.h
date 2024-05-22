/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include <string>
#include <iostream>

class Student
{
public:
    // Default constructor.
    Student();

    // Copy constructor.
    Student(const Student &);

    // Constructor with parameters.
    Student(std::string, double, int, int);

    // Destructor.
    ~Student();

    // Getters, they only return values of the attributes so they are const functions.

    std::string get_name() const;
    double get_gpa() const;
    int get_gre() const;
    int get_toefl() const;
    int get_number_of_applications() const;

    // Setters, they modify attributes.

    void set_name(std::string);
    void set_gpa(double);
    void set_gre(int);
    void set_toefl(int);
    // This function can modify mutable number_of_appliactions counter even though object is const so function is const.
    void set_number_of_applications(int) const;

private:
    // These are the attributes of the student class. They are initially zero or empty.

    std::string m_name{};
    double m_gpa{};
    int m_gre{};
    int m_toefl{};

    // Constant object's counter should be modifiable.
    mutable int m_number_of_applications{};

    // A utility to print log in messages.
    void print_login() const;
};