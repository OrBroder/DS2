#include "Company.h"

 std::shared_ptr<Company> Company::companyPtrAssist;
int Company::getID() const {
    return this->CompanyID;
}
int Company::getValue() const {
    return this->Value;
}
EmployeesInfo& Company::getEmployees() {
    return this->CompanyEmployees;
}
int Company::getCounter() const {
    return this->CompanyEmployees.EmployeesById.getSize();
}


void Company::setID(int new_ID) {
    this->CompanyID = new_ID;
}
void Company::setValue(int new_value) {
    this->Value = new_value;
}

void Company::increaseValue(int increment)
{
    Value += increment;
}

void Company::addEmployee(std::shared_ptr<Employee> new_employee)
{
    CompanyEmployees.AddEmployeeToInfo(new_employee);

}

void Company::removeEmployee(int employeeId)
{
    CompanyEmployees.removeEmployeeFromInfo(employeeId);
}


void Company::mergeCompany(std::shared_ptr<Company> other)
{
    if(other.get()->getCounter() > 0)
    {
        this->CompanyEmployees.EmployeesById.merge(other.get()->CompanyEmployees.EmployeesById);
        this->CompanyEmployees.EmployeesBySalary.merge(other.get()->CompanyEmployees.EmployeesBySalary);
        other.get()->emptyEmployees();
//        finalHireEmployeesById();
    }
}

void Company::emptyEmployees()
{
    this->CompanyEmployees.EmployeesById.root = nullptr;
    this->CompanyEmployees.EmployeesBySalary.root = nullptr;
}
/*
void setCompanyAssist(std::shared_ptr<Employee> employee)
{
    employee.get()->setCompany(Company::companyPtrAssist.get());
}


*/



