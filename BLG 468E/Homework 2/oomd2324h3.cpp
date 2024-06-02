// OOMD 2023-2024 Assignment 3

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

// Reperesents the grade earned by a student for a particular course
class GradeForCourse {
public:
    GradeForCourse(std::string in_course, float in_grade)        // constructor
        :m_course{ in_course }, m_grade{ in_grade }
    { }                                         
    const std::string& getCourse() const { return m_course; }
    float getGrade() const { return m_grade; }
private:
    std::string m_course;          // Code of the course e.g. "BLG468E"
    float m_grade;                 // Grade earned by the student
};

// Class that represents the remote system RemoteA
class RemoteA {
public:
    void establish_connection() {
        cout << "Connection to RemoteA is established" << endl;
    }
    void close_connection() {
        cout << "Connection to RemoteA is closed" << endl;
    }
    // This method represents the operation that is performed by RemoteA to receive necessary information
    // It receives ID and name
    void post(const std::string& ID, const std::string& name) {
        cout << "RemoteA receives:" << endl;
        cout << "ID: " << ID << endl;
        cout << "Name: " << name << endl;
    }
};

// Class that represents the remote system RemoteB
class RemoteB {
public:
    void connect() {
        cout << "Connect to RemoteB" << endl;
    }
    void disconnect() {
        cout << "Disconnect from RemoteB" << endl;
    }
    // This method represents the operation that is performed by RemoteB to receive necessary information
    // It receives ID and vector of grades
    void send_data(const std::string& ID, const std::vector<GradeForCourse*>& grades) {
        cout << "RemoteB receives:" << endl;
        cout << "ID: " << ID << endl;
        cout << "Courses and grades" << endl;
        for (unsigned int j = 0; j < grades.size(); j++)    // display vector contents
            cout << grades[j]->getCourse() << ' ' << grades[j]->getGrade() << endl;
    }
};

// Student class
// This class is not properly designed !! Correct it.
class Student {
public:
    Student(RemoteA *, RemoteB *);                              // Get the addresses of the reomete systems, read ID, name, and grades from the keyboard
    void setGradeforCourse();               // read code of course and grade for that course
    void send() const;                            // Connect to a remote system and send data
    ~Student();                             // Destructor
private:
    std::string m_ID, m_name, m_department;
    std::vector<GradeForCourse*> m_grades;           // create the vector of grades
    RemoteA * m_ptrToA{};                           // Pointer to remote system A
    RemoteB * m_ptrToB{};                           // Pointer to remote system B
};

//  Constructor: Get the addresses of the reomete systems, read ID, name, and grades from the keyboard
Student::Student(RemoteA* in_ptrToA, RemoteB* in_ptrToB)
                : m_ptrToA{in_ptrToA}, m_ptrToB{in_ptrToB}              // initialize pointers to remote systems
{
    cout << "Enter the ID of the student: ";
    std::getline(cin, m_ID);
    cout << "Enter the name of the student: ";
    std::getline(cin, m_name);
    cout << "Enter the deparment of the student: ";
    std::getline(cin, m_department);
    setGradeforCourse();      // We enter just two grades as an example.  
    setGradeforCourse();
}

// Destructor deletes GradeForCourse objects in the vector of the grades
Student::~Student() {
    for (unsigned int j = 0; j < m_grades.size(); j++)
        delete m_grades[j];
}

// This method creates the grade for a particular course and writes the data into the vector of the grades in the Student object
void Student::setGradeforCourse() {
    cout << "Give the code of the Course: ";
    std::string code;
    cin >> code;            // Write the code without a space character e.g. "BLG468E"                  
    float grade;
    do {
        cout << "Give the grade for the course: ";
        cin >> grade;
    } while (grade < 0 || grade >4);
    GradeForCourse* courseGrade = new GradeForCourse{ code, grade };    // Create the grade for the course
    m_grades.push_back(courseGrade);                                    //Put the grade into the vector of the grades
}

// Connect to a remote system and send data
// This method is not properly implmented !!! Corect it
void Student::send()const {
    //checks the conditon. The condition could be more complex
    if (m_department == "BLGE") {                           // Send to RemoteA   
        m_ptrToA->establish_connection();
        m_ptrToA->post(m_ID, m_name);
        m_ptrToA->close_connection();
    }
    else {
        m_ptrToB->connect();
        m_ptrToB->send_data(m_ID, m_grades);
        m_ptrToB->disconnect();
    }
};

// Test Create students, grades, send data to different systems (A or B), change the systems in run-time
int main()
{
    RemoteA remoteSystemA;
    RemoteB remoteSystemB;
    Student student{ &remoteSystemA, &remoteSystemB };
    student.send();
    return 0;
}