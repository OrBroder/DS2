#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H
#include "library2.h"
#include "exceptions.h"
#include "Company.h"
#include "EmployeesInfo.h"
#include "RankAVL.h"
#include "Union.hpp"
#include <memory>

class Manager {
    Union_lib::Union<std::shared_ptr<Company>> Companies;
    EmployeesInfo AllEmployees; 

    public: 
    Manager(int k):Companies(k){
        for (size_t i = 0; i < k; i++)
        {
            Companies.makeSet(i,std::make_shared<Company>(i+1));
        }
    }
    ~Manager() = default;

    StatusType AddEmployee(int employeeID, int companyID, int grade);
	StatusType RemoveEmployee(int employeeID);
	StatusType AcquireCompany(int companyID1, int companyID2, double factor);
	StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease);
	StatusType PromoteEmployee(int employeeID, int bumpGrade);
	StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void* sumBumpGrade);
	StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void* averageBumpGrade);
	StatusType CompanyValue(int companyID, void* standing);


    
    private:
    StatusType addEmployeeToCompany(std::shared_ptr<Employee> employee, int CompanyId);
    bool verifyInputIntegrity(int a,int b);
    static void logPrep();
    static void sumCompaniesVal( Company company,int* sum );
    static void sumGrades(Employee emp);
};

#endif