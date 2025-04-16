#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "string.h"

class Employee
{
private:
    int id;
    String name;
    Employee *pManager;

    // 사용하지않을 생성자 또는 연산을 private에 선언.
    Employee(const Employee& rhs);
    Employee& operator=(const Employee& rhs);

public:
    Employee(int id, String name, Employee *pManager);
    // ~Employee() {}
    
    // Employee() {}                                                                    is not generated!
    // Employee(const Employee& rhs) { /* memberwise copy */ }                          is not generated!
    // Employee& operator=(const Employee& rhs) { /* memberwise copy */ return *this; } is not generated!

    // Employee* operator&() { return this; }
    // const Employee* operator&() const { return this; }

    int getId();
    String getName();
    Employee *getManager();

    bool isManager();



};

#endif