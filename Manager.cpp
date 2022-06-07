#include "Manager.h"
#include "library2.h"
#include "exceptions.h"

static int minSalaryAssist;
static int minGradeAssist;
static int logAssist;

StatusType Manager::AddEmployee(int EmployeeID, int CompanyID,int Grade){ 
        //non-postive values checked outside
        if(CompanyID > Companies.getCapacity())
            return INVALID_INPUT;

        try
        {
             std::shared_ptr<Employee> new_employee = std::shared_ptr<Employee>(new Employee(EmployeeID, Grade,CompanyID));
             AllEmployees.AddEmployeeToInfo(new_employee); // add to main data
             (Companies.get(CompanyID - 1)).get()->addEmployee(new_employee);
        }
        catch (std::bad_alloc)
        {  
             return ALLOCATION_ERROR;
        }
         catch(KeyExists)
        {
             return FAILURE;
        }
        catch(KeyNotFound)
        {
            return FAILURE;
        }
  

    return SUCCESS;
}

StatusType Manager::RemoveEmployee(int EmployeeID){

    try{
         int companyId = (AllEmployees.findEmployeeInInfo(EmployeeID).get()->getCompany());
         AllEmployees.removeEmployeeFromInfo(EmployeeID);
         Companies.get(companyId - 1).get()->removeEmployee(EmployeeID);  
    }
    catch(std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }
    catch(KeyNotFound)
    {
        return FAILURE;
    }
      return SUCCESS; 
}

StatusType Manager::AcquireCompany(int AcquirerID, int TargetID, double Factor){
    if(AcquirerID > Companies.getCapacity())
            return INVALID_INPUT;
    if(TargetID > Companies.getCapacity())
            return INVALID_INPUT;
    try
    {
        std::shared_ptr<Company> acquirer = Companies.get(AcquirerID - 1);
        std::shared_ptr<Company> target = Companies.get(TargetID - 1);
        Companies.unite(AcquirerID - 1,TargetID - 1);
        int targetValue = target.get()->getValue();
        acquirer.get()->increaseValue(targetValue*Factor);
        int acquirerNew = acquirer.get()->getValue();
        target.get()->increaseValue(-acquirerNew);
        acquirer.get()->CompanyEmployees.mergerInfo(target.get()->CompanyEmployees);
    }
    catch(KeyNotFound)
    {
        return FAILURE;
    }
    catch(std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }

      return SUCCESS;
}

StatusType Manager::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    try
    {
        std::shared_ptr<Employee> employee = AllEmployees.findEmployeeInInfo(employeeID);
        int companyId = employee.get()->getCompany();
        std::shared_ptr<Company> company = Companies.get(companyId - 1);
        company.get()->removeEmployee(employeeID);
        AllEmployees.removeEmployeeFromInfo(employeeID);
        employee.get()->promote(salaryIncrease,0);
        AllEmployees.AddOldEmployeeToInfo(employee);
        company.get()->getEmployees().AddOldEmployeeToInfo(employee);
    }
    catch(KeyNotFound)
    {
        return FAILURE;
    }
    catch(std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}


StatusType Manager::PromoteEmployee(int EmployeeID, int BumpGrade){
    
        try {
           std::shared_ptr<Employee> employee = AllEmployees.findEmployeeInInfo(EmployeeID);
            employee.get()->promote(0,BumpGrade);
           if(employee.get()->getSalary() == 0)
           {
                AllEmployees.apprentices_total_grade+= BumpGrade;
                std::shared_ptr<Company> company = Companies.get(employee.get()->getCompany() - 1);
                company.get()->getEmployees().apprentices_total_grade+= BumpGrade;
           }
        }
        catch(KeyNotFound)
        {
            return FAILURE;
        }
        catch(std::bad_alloc)
        {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
        
}

StatusType Manager::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void* sumBumpGrade)
{
    if(companyID > Companies.getCapacity())
            return INVALID_INPUT;
    
    try
    {
        EmployeesInfo employees;
        if(companyID > 0)
        {
                employees = Companies.find(companyID - 1)->data.get()->CompanyEmployees;
        }
        else
        {
            employees = AllEmployees;
        }

       *((int*)sumBumpGrade) = employees.EmployeesBySalary.getValSumByIndex(m);
    }
    catch(KeyNotFound)
    {
            return FAILURE;
    }

    return SUCCESS;
    
}

StatusType Manager::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void* averageBumpGrade)
{
    if(companyID > Companies.getCapacity())
            return INVALID_INPUT;
    
    try
    {
        EmployeesInfo employees;
        if(companyID > 0)
        {
                employees = Companies.find(companyID - 1)->data.get()->CompanyEmployees;
        }
        else
        {
            employees = AllEmployees;
        }

        EmployeeTag minTag(0,lowerSalary);
        EmployeeTag maxTag(INT_MAX,higherSalary);

        int totalGrades = employees.EmployeesBySalary.getValSumInArea(minTag,maxTag);
        int totalWorkers = employees.EmployeesBySalary.getNumOfNodesInArea(minTag,maxTag);
        if(lowerSalary == 0)
        {
            totalGrades += employees.apprentices_total_grade;
            totalWorkers += employees.Apprentices.getSize();
        }


        double average = (double)totalGrades/totalWorkers;
        *((double*)averageBumpGrade) = average;
            
       
    }
    catch(KeyNotFound)
    {
            return FAILURE;
    }

    return SUCCESS;
}


StatusType Manager::CompanyValue(int companyID, void* standing)
{
    logAssist = 0;
    Companies.inOrderHelper(sumCompaniesVal,&logAssist,companyID - 1);
    (*(int*)standing) = logAssist;
    return SUCCESS;
}
/********************************************************************************
                            support functions
********************************************************************************/
 void Manager::logPrep()
{
    logAssist = 0;
}

 void Manager::sumCompaniesVal( Company company,int* sum )
{
    (*sum) += company.getValue();
} 

 void Manager::sumGrades(Employee emp)
{
    logAssist+= emp.getGrade();
}

bool Manager::verifyInputIntegrity(int a, int b)
{
    return a > 0 && b >0;
}

bool IsBiggerGradeSalary(Employee emp, int MinSalary, int MinGrade) {
    return emp.getSalary() >= MinSalary && emp.getGrade() >= MinGrade;
}

int returnID(Employee emp) {
    return emp.getID();
}

void writeID(std::shared_ptr<Employee> employee)
{
    int salary = employee.get()->getID();
    (logAssist) = salary;
    logAssist++;
}

bool filterEmployee(std::shared_ptr<Employee> employee)
{
    int grade = employee.get()->getGrade();
    int salary = employee.get()->getSalary();
    return grade >= (minGradeAssist) && salary >= (minSalaryAssist);
}



//end noa








