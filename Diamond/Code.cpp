#include <iostream>
#include <vector>
#include <type_traits>
#include <assert.h>
#include <cctype>

using namespace std;

// Abstract class Person
class Person{
    protected:
        string fname, lname;
    public:
        static int count;
        Person(){};
        Person(string fname, string lname){
            this->fname = fname;
            this->lname = lname;
            count ++;
        }
        virtual string getEmail() = 0;
        virtual ~Person() = 0;
        Person(Person& person) = delete;

};

// Initialization of conut to 0
int Person :: count = 0;
Person :: ~Person() {
    count--;
}

// Class Student inherited from Person, inherited from virtual Person to avoid diamond problem
class Student : virtual public Person{
    public:
        Student(){};
        Student(string fname, string lname) : Person(fname, lname) {};
        string getEmail() override {
            // Convertation fname and lname to lower case
            for (char& c : fname) {
                c = tolower(c);
            }
            for (char& c : lname) {
                c = tolower(c);
            }
            return string(1, fname[0]) + "." + lname + "@students.org";
        }

};


// Class Emplyee inherited from Person, inherited from virtual Person to avoid diamond problem
class Employee : virtual public Person{
    public:
    Employee(){};
        Employee(string fname, string lname) : Person(fname, lname) {};
        string getEmail() override {
            // Convertation fname and lname to lower case
            for (char& c : fname) {
                c = tolower(c);
            }
            for (char& c : lname) {
                c = tolower(c);
            }
            return string(1, fname[0]) + "." + lname + "@employees.org";
        }

};

//Class TA multiple inherited from Student and Emplyee
class TA : public Student, public Employee{
    public:
        TA(string fname, string lname) : Person(fname, lname) {};
        string getEmail() {
            return Employee::getEmail();
        }
};

int main() {
    static_assert(is_abstract_v<Person>);
    static_assert(is_base_of_v<Person, Employee>);
    static_assert(is_base_of_v<Person, Student>);
    static_assert(is_base_of_v<Person, TA>);
    static_assert(is_base_of_v<Employee, TA>);
    static_assert(is_base_of_v<Student, TA>);
    static_assert(is_polymorphic_v<Student>);
    static_assert(is_polymorphic_v<Employee>);
    static_assert(is_polymorphic_v<TA>);
    static_assert(!is_copy_constructible_v<Person>);
    static_assert(has_virtual_destructor_v<Person>);
    
    string fname, lname;
    
    cin >> fname >> lname;
    Student* s = new Student(fname, lname);
    assert(Person::count == 1);
    
    cin >> fname >> lname;
    Employee* e = new Employee(fname, lname);
    assert(Person::count == 2);
    
    cin >> fname >> lname;
    TA* t = new TA(fname, lname);
    assert(Person::count == 3);

    vector<Person*> people = {s, e, t};
    for(auto& p: people) {
        cout << p->getEmail() << endl;
        delete p;
    }
}