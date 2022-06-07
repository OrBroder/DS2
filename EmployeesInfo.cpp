#include "EmployeesInfo.h"
#include "exceptions.h"
#include <exception>
#include <memory>

void EmployeesInfo::AddEmployeeToInfo(std::shared_ptr<Employee> emp){
    
          this->Apprentices.insert(emp.get()->getID(),emp);
          apprentices_total_grade += emp.get()->getGrade();
}

void EmployeesInfo::AddOldEmployeeToInfo(std::shared_ptr<Employee> emp){
    
          EmployeesById.insert(emp,emp.get()->getID(),emp.get()->getGrade());
          EmployeeTag tag (emp.get()->getID(),emp.get()->getSalary());
          EmployeesBySalary.insert(emp,tag,emp.get()->getGrade());
}

void EmployeesInfo::removeEmployeeFromInfo(int employee_id)
{
   try
     {
          int grade = Apprentices.find(employee_id).get()->getGrade();
          Apprentices.remove(employee_id);
          apprentices_total_grade -= grade;
          
     }
     catch(KeyNotFound)
     {
          std::shared_ptr<Employee> emp = EmployeesById.find(employee_id);
          int grade = EmployeesById.find(employee_id).get()->getGrade();
          EmployeeTag tag (employee_id,emp.get()->getSalary());
          EmployeesById.remove(employee_id,grade);  
          EmployeesBySalary.remove(tag,grade);     
     }
}


void EmployeesInfo::mergerInfo(EmployeesInfo& other)
{
     EmployeesById.merge(other.EmployeesById);
     EmployeesBySalary.merge(other.EmployeesBySalary);
     apprentices_total_grade += other.apprentices_total_grade;
     Apprentices.merge(other.Apprentices);
     clear();
}



std::shared_ptr<Employee> EmployeesInfo::findEmployeeInInfo(int employee_id)
{
     try
     {
          return Apprentices.find(employee_id);
     }
     catch(KeyNotFound)
     {
            return EmployeesById.find(employee_id);      
     }
}

void EmployeesInfo::clear()
{
     apprentices_total_grade = 0;
     Hash_lib::Hash<std::shared_ptr<Employee>> blankApprentices;
     Avl_lib::Tree<std::shared_ptr<Employee>,int,int> blankEmployeesById;
     Avl_lib::Tree<std::shared_ptr<Employee>,EmployeeTag,int> blankEmployeesBySalary;
     Apprentices = blankApprentices;
     EmployeesById = blankEmployeesById;
     EmployeesBySalary = blankEmployeesBySalary;
}


