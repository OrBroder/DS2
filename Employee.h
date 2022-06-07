#ifndef EMPLOYEE_H
#define EMPLOYEE_H


#include <memory>

class Employee {
    int EmployeeID;
    int Salary; 
    int Grade; 
    int EmployerCompany;

    public:
    Employee(int EmployeeID, int Grade,int employerCompany) :
    EmployeeID(EmployeeID), Grade(Grade),EmployerCompany(employerCompany) ,Salary(0) {}
    Employee(Employee& other) = default;
    Employee& operator=(Employee& other) = default;
    ~Employee() = default;
    
    /**
     * getters
     */
    int getID() const;
    int getSalary() const;
    int getGrade() const;
    int getCompany() const;

    /**
     * setters
     */
    void setID(int new_ID);
    void setSalary(int new_salary);
    void setGrade(int new_grade);
    void promote(int salaryIncrement, int gradeIncrement);
};

#endif