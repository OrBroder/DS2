#ifndef EMPLOYEE_TAG_H
#define EMPLOYEE_TAG_H

class EmployeeTag
{
    public:
        EmployeeTag() = default;
    EmployeeTag(int id, int salary) : id(id), salary(salary) {}
    EmployeeTag(int id):id(id), salary(0){};
    int id;
    int salary;

    bool operator<(EmployeeTag& other);

    bool operator>(EmployeeTag& other);
    bool operator==(EmployeeTag& other);
    bool operator!=(EmployeeTag& other);
    bool operator<=(EmployeeTag& other);
    bool operator>=(EmployeeTag& other);

};


#endif