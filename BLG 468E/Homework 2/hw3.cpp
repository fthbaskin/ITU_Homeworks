// OOMD 2023-2024 Assignment 3
// Fatih Baskın
// 150210710

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

// -----------------------------
// These classes are unaffected.
// -----------------------------

// Reperesents the grade earned by a student for a particular course
class GradeForCourse
{
public:
    GradeForCourse(std::string in_course, float in_grade) // constructor
        : m_course{in_course}, m_grade{in_grade}
    {
    }
    const std::string &getCourse() const { return m_course; }
    float getGrade() const { return m_grade; }

private:
    std::string m_course; // Code of the course e.g. "BLG468E"
    float m_grade;        // Grade earned by the student
};

// Class that represents the remote system RemoteA
class RemoteA
{
public:
    void establish_connection()
    {
        cout << "Connection to RemoteA is established" << endl;
    }
    void close_connection()
    {
        cout << "Connection to RemoteA is closed" << endl;
    }
    // This method represents the operation that is performed by RemoteA to receive necessary information
    // It receives ID and name
    void post(const std::string &ID, const std::string &name)
    {
        cout << "RemoteA receives:" << endl;
        cout << "ID: " << ID << endl;
        cout << "Name: " << name << endl;
    }
};

// Class that represents the remote system RemoteB
class RemoteB
{
public:
    void connect()
    {
        cout << "Connect to RemoteB" << endl;
    }
    void disconnect()
    {
        cout << "Disconnect from RemoteB" << endl;
    }
    // This method represents the operation that is performed by RemoteB to receive necessary information
    // It receives ID and vector of grades
    void send_data(const std::string &ID, const std::vector<GradeForCourse *> &grades)
    {
        cout << "RemoteB receives:" << endl;
        cout << "ID: " << ID << endl;
        cout << "Courses and grades" << endl;
        for (unsigned int j = 0; j < grades.size(); j++) // display vector contents
            cout << grades[j]->getCourse() << ' ' << grades[j]->getGrade() << endl;
    }
};

// ------------------------------------
// Student class is affected.
// Method definitions are after main().
// ------------------------------------

// Student class
class Student
{
public:
    Student();                // Get the addresses of the reomete systems, read ID, name, and grades from the keyboard
    void setGradeforCourse(); // read code of course and grade for that course
    void send() const;        // Connect to a remote system and send data
    ~Student();               // Destructor

    // Getters for private members
    const std::string &getID() const { return m_ID; };
    const std::string &getName() const { return m_name; }
    const std::string &getDepartment() const { return m_department; }
    const std::vector<GradeForCourse *> &getGrades() const { return m_grades; }

private:
    std::string m_ID, m_name, m_department;
    std::vector<GradeForCourse *> m_grades; // create the vector of grades

    // Student class should not be aware of remote logic
    // RemoteA *m_ptrToA{};                    // Pointer to remote system A
    // RemoteB *m_ptrToB{};                    // Pointer to remote system B
};

// ------------------------------
// These classes are newly added.
// ------------------------------

// RemoteInterface provides a stable interface to Student class' send() method to send data about student.
// This is a virtual (interface) class and adapters are derived from it.
class RemoteInterface
{
public:
    // Pure virtual function to send data using the stable interface.
    // Constant pointer to student is used because different remotes might require different information.
    virtual void sendData(const Student *) = 0;

    // Virtual destructor, adaptors must implement their own destructors.
    virtual ~RemoteInterface(){};
};

// An adapter to RemoteA implementing RemoteInterface.
// Seperates the Student from RemoteA by providing a stable interface to Student.
class RemoteAdapterA : public RemoteInterface
{
public:
    // Adapter must send appropiate information to RemoteA from the Student.
    void sendData(const Student *);

    // Constructor must create a connection to RemoteA.
    RemoteAdapterA();
    // Destructor must destruct the RemoteA connection.
    ~RemoteAdapterA();

private:
    RemoteA *m_remote;
};

// An adapter to RemoteB implementing RemoteInterface.
// Seperates the Student from RemoteB by providing a stable interface to Student.
class RemoteAdapterB : public RemoteInterface
{
public:
    // Adapter must send appropiate information to RemoteA from the Student.
    void sendData(const Student *);

    // Constructor must create a connection to RemoteA.
    RemoteAdapterB();
    // Destructor must destruct the RemoteA connection.
    ~RemoteAdapterB();

private:
    RemoteB *m_remote;
};

// A singleton factory class that creates RemoteAdapter'X' objects
class RemoteAdapterFactory
{
public:
    // Used for returning the instance of RemoteAdapterFactory
    static RemoteAdapterFactory *getInstance();

    // Used for deleting the instance of RemoteAdapterFactory to prevent memory leaks.
    static void deleteInstance();

    // Used to return appropiate RemoteAdapter'X' to Student.
    // Requires the Student information to choose the correct adapter.
    RemoteInterface *getAdapter(const Student *);

private:
    // Singleton instance
    static RemoteAdapterFactory *mInstance;

    // Adapters are created in the factory and returned to Student.
    RemoteAdapterA *mAdapterA;
    RemoteAdapterB *mAdapterB;

    // Getters for adapters, creates the adapter if it is not created yet.
    RemoteAdapterA *getAdapterA();
    RemoteAdapterB *getAdapterB();

    // Private constructor for singleton
    RemoteAdapterFactory();
    // Copy constructor and copy assignment operators are deleted for singleton.
    RemoteAdapterFactory(const RemoteAdapterFactory &) = delete;
    RemoteAdapterFactory &operator=(const RemoteAdapterFactory &) = delete;
    // Destructor is private for singleton.
    ~RemoteAdapterFactory();
};

// Initialize the singleton instance as nullptr.
RemoteAdapterFactory *RemoteAdapterFactory::mInstance = nullptr;

// Test Create students, grades, send data to different systems (A or B), change the systems in run-time
int main()
{
    // No need to initialize remote systems, factory will initialize adapters for them.
    // RemoteA remoteSystemA;
    // RemoteB remoteSystemB;
    Student student{}; // Modified constructor, no need to use Remote'X' information.
    student.send();

    // Delete the factory instance to prevent memory leaks.
    // Destructor of RemoteAdapterFactory is private, so we need to call deleteInstance() to delete the instance.
    RemoteAdapterFactory::deleteInstance();

    return 0;
}

// -------------------------
// Methods of Student class.
// -------------------------

//  Constructor: read ID, name, and grades from the keyboard
Student::Student() // initialize pointers to remote systems
{
    cout << "Enter the ID of the student: ";
    std::getline(cin, m_ID);
    cout << "Enter the name of the student: ";
    std::getline(cin, m_name);
    cout << "Enter the deparment of the student: ";
    std::getline(cin, m_department);
    setGradeforCourse(); // We enter just two grades as an example.
    setGradeforCourse();
}

// Destructor deletes GradeForCourse objects in the vector of the grades
Student::~Student()
{
    for (unsigned int j = 0; j < m_grades.size(); j++)
        delete m_grades[j];
}

// This method creates the grade for a particular course and writes the data into the vector of the grades in the Student object
void Student::setGradeforCourse()
{
    cout << "Give the code of the Course: ";
    std::string code;
    cin >> code; // Write the code without a space character e.g. "BLG468E"
    float grade;
    do
    {
        cout << "Give the grade for the course: ";
        cin >> grade;
    } while (grade < 0 || grade > 4);
    GradeForCourse *courseGrade = new GradeForCourse{code, grade}; // Create the grade for the course
    m_grades.push_back(courseGrade);                               // Put the grade into the vector of the grades
}

// Connect to a remote system and send data
// Gets the proper adapter from the factory and sends the data.
void Student::send() const
{
    // ------------------------------------------------------------------------
    // This part is replaced with the following code.
    // Following code is stable and does not require any changes in the future.
    // ------------------------------------------------------------------------

    // Get the factory instance and get the proper adapter for the student.
    RemoteAdapterFactory *factory = RemoteAdapterFactory::getInstance();
    RemoteInterface *adapter = factory->getAdapter(this);

    // Send the data using the adapter.
    adapter->sendData(this);
};

// --------------------------------------
// Methods of RemoteAdapterFactory class.
// --------------------------------------

// Used for returning the instance of RemoteAdapterFactory
RemoteAdapterFactory *RemoteAdapterFactory::getInstance()
{
    // If instance is uninitialized, create a new instance
    if (mInstance == nullptr)
        mInstance = new RemoteAdapterFactory;
    // Return the current instance
    return mInstance;
}

// Private constructor for singleton
RemoteAdapterFactory::RemoteAdapterFactory()
{
    // Initialize adapters as nullptr
    mAdapterA = nullptr;
    mAdapterB = nullptr;
}

// Destructor is private for singleton.
RemoteAdapterFactory::~RemoteAdapterFactory()
{
    cout << "Deleting RemoteAdapterFactory" << endl;
    // Delete the adapters if they are created.
    if (mAdapterA != nullptr)
        delete mAdapterA;
    if (mAdapterB != nullptr)
        delete mAdapterB;
}

// Used for deleting the instance of RemoteAdapterFactory to prevent memory leaks.
void RemoteAdapterFactory::deleteInstance()
{
    // If instance is initialized, delete the instance
    if (mInstance != nullptr)
    {
        delete mInstance;
        mInstance = nullptr;
    }
}

// Getter for adapter A, creates the adapter if it is not created yet.
RemoteAdapterA *RemoteAdapterFactory::getAdapterA()
{
    // If adapter is not created yet, create a new one.
    if (mAdapterA == nullptr)
        mAdapterA = new RemoteAdapterA;
    // Return the adapter.
    return mAdapterA;
}

// Getter for adapter B, creates the adapter if it is not created yet.
RemoteAdapterB *RemoteAdapterFactory::getAdapterB()
{
    // If adapter is not created yet, create a new one.
    if (mAdapterB == nullptr)
        mAdapterB = new RemoteAdapterB;
    // Return the adapter.
    return mAdapterB;
}

// Used to return appropiate RemoteAdapter'X' to Student.
// Requires the Student information to choose the correct adapter.
RemoteInterface *RemoteAdapterFactory::getAdapter(const Student *student)
{
    // -----------------------------------------------
    // This section is open for future changes.
    // Adapter selection can be changed in the future.
    // -----------------------------------------------

    // If student is from BLGE department, return RemoteAdapterA
    if (student->getDepartment() == "BLGE")
        return getAdapterA();
    // If student is from another department, return RemoteAdapterB
    return getAdapterB();
}

// --------------------------------
// Methods of RemoteAdapterA class.
// --------------------------------

// Constructor must create a RemoteA object.
RemoteAdapterA::RemoteAdapterA() { m_remote = new RemoteA; }

// Destructor must destruct the RemoteA object.
RemoteAdapterA::~RemoteAdapterA() { delete m_remote; }

// Adapter must send appropiate information to RemoteA from the Student.
void RemoteAdapterA::sendData(const Student *student)
{
    // This part is coded according to the requirements of RemoteA.
    m_remote->establish_connection();
    m_remote->post(student->getID(), student->getName());
    m_remote->close_connection();
}
// --------------------------------
// Methods of RemoteAdapterB class.
// --------------------------------

// Constructor must create a RemoteB object.
RemoteAdapterB::RemoteAdapterB() { m_remote = new RemoteB; }

// Destructor must destruct the RemoteB object.
RemoteAdapterB::~RemoteAdapterB() { delete m_remote; }

// Adapter must send appropiate information to RemoteB from the Student.
void RemoteAdapterB::sendData(const Student *student)
{
    // This part is coded according to the requirements of RemoteB.
    m_remote->connect();
    m_remote->send_data(student->getID(), student->getGrades());
    m_remote->disconnect();
}