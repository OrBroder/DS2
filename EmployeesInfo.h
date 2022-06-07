#ifndef EMPLOYEESINFO_H
#define EMPLOYEESINFO_H

#include "Employee.h"
#include "Hash.hpp"
#include "RankAVL.h"
#include "EmployeeTag.h"

class EmployeesInfo {
    public:
    Hash_lib::Hash<std::shared_ptr<Employee>> Apprentices;
    Avl_lib::Tree<std::shared_ptr<Employee>,int,int> EmployeesById;
    Avl_lib::Tree<std::shared_ptr<Employee>,EmployeeTag,int> EmployeesBySalary;
    int apprentices_total_grade;
    bool IsEmpty();

    EmployeesInfo() = default;
    EmployeesInfo(EmployeesInfo& other) = default;
    EmployeesInfo& operator=(EmployeesInfo& other) = default;
    ~EmployeesInfo() = default;

    // promote function
    void AddEmployeeToInfo(std::shared_ptr<Employee> new_employee);
    void AddOldEmployeeToInfo(std::shared_ptr<Employee> new_employee);
    std::shared_ptr<Employee> findEmployeeInInfo(int employee_id);
    void removeEmployeeFromInfo(int employee_id);
    void mergerInfo(EmployeesInfo& other);
    void clear();
    
};
   

#endif