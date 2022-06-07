#include <iostream>
#include "Manager.h"
int main(int, char**) {
  Manager manager(10);
  int value;
  manager.AddEmployee(1,1,5);
  manager.CompanyValue(1,(void*)(&value));
  std::cout << value<<std::endl;
  manager.AcquireCompany(1,2,0.7);
  manager.RemoveEmployee(1);
  
  manager.CompanyValue(1,(void*)(&value));
  std::cout << value<<std::endl;
  std::cout<< "hello";
}
