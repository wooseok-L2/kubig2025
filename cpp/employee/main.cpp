#include <iostream>
#include "employee.h"

void printEmployee(Employee *p)
{
    std::cout << "employeeID: " << p->getId() << ", name: " << p->getName() << ", manager: ";
    std::cout << (p->isManager() ? "**Chief**" : p->getManager()->getName()) << std::endl;
}

int main()
{
    Employee e1(1, "Park Jung Seok", NULL);
    Employee e2(2, "Sung Young Ho", &e1);
    Employee e3(3, "Choi Su Gil", &e1);
    Employee e4(4, "Cho Min Sung", &e1);
    Employee e5(5, "Min Byung Hun", &e4);

    // Employee e6 = e1;
    // e2 = e1;

    // Employee employees[10];      // X default constructor is called.
    Employee* pEmployees[10];
    pEmployees[0] = new Employee(1, "Park Jung Seok", NULL);
    pEmployees[1] = new Employee(2, "Sung Young Ho", pEmployees[0]);
    pEmployees[2] = new Employee(3, "Choi Su Gil", pEmployees[0]);
    pEmployees[3] = new Employee(4, "Cho Min Sung", pEmployees[0]);
    pEmployees[4] = new Employee(5, "Min Byung Hun", pEmployees[3]);

    for (int i = 0; i < 5; i++)
    {
        printEmployee(pEmployees[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        delete pEmployees[i];   
    }

    return 0;
}