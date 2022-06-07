#include "EmployeeTag.h"

 bool EmployeeTag::operator<(EmployeeTag& other)
    {
        if(id == other.id)
            return false;
        if(salary<other.salary)
        {
            return true;
        }
        else if(salary==other.salary)
        {
            return id < other.id;
        }
        return false;
    }

    bool EmployeeTag::operator>(EmployeeTag& other)
    {
        if(id == other.id)
            return false;
        if(salary<other.salary)
        {
            return false;
        }
        else if(salary==other.salary)
        {
            return id > other.id;
        }
        return true;
    }

     bool EmployeeTag::operator==(EmployeeTag& other)
    {
      return (salary == other.salary) && (id == other.id);
    }

      bool EmployeeTag::operator!=(EmployeeTag& other)
    {
      return !(*this == other);
    }

      bool EmployeeTag::operator>=(EmployeeTag& other)
    {
      return !(*this < other);
    }

      bool EmployeeTag::operator<=(EmployeeTag& other)
    {
      return !(*this > other);
    }