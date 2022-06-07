#include "Employee.h"


int Employee::getID() const {
    return this->EmployeeID;
}
int Employee::getSalary() const {
    return this->Salary;
}
int Employee::getGrade() const {
    return this->Grade;
}
int Employee::getCompany() const {
    return this->EmployerCompany;
}

void Employee::setID(int new_ID) {
    this->EmployeeID = new_ID;
}
void Employee::setSalary(int new_salary) {
    this->Salary = new_salary;
}
void Employee::setGrade(int new_grade) {
    this->Grade = new_grade;
}

void Employee::promote(int salaryIncrement, int gradeIncrement)
{
    Salary+=salaryIncrement;
    Grade+= gradeIncrement;
}


