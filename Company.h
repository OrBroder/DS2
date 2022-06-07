#ifndef COMPANY_H
#define COMPANY_H

#include "EmployeesInfo.h"

class Company { 
    int CompanyID;
    int Value; 
    public: 
    EmployeesInfo CompanyEmployees;

    

    
    Company(int CompanyID, int Value) : CompanyID(CompanyID), Value(Value) {
    } //should move to the cpp file?

    Company(int CompanyID):CompanyID(CompanyID),Value(CompanyID){}
    ~Company() = default;

    /**
     * getters
     */
    int getID() const;
    int getValue() const;
    EmployeesInfo& getEmployees();
    int getCounter() const;

    /**
     * setters
     */
    void setID(int new_ID);
    void setValue(int new_value);
    void increaseValue(int increment);
    void addEmployee(std::shared_ptr<Employee> employee);
    void removeEmployee(int employeeId);
    void mergeCompany(std::shared_ptr<Company> other);
    void finalHireEmployees();
    std::shared_ptr<Employee> getHighestEarner();
    void emptyEmployees();
    static std::shared_ptr<Company> companyPtrAssist;
    void setHighestEarner();
    
};



    void setCompanyAssist(std::shared_ptr<Employee>);




#endif