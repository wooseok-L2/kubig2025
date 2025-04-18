#include <iostream>
#include <typeinfo>
#include "shape.h"
#include "rectangle.h"
#include "circle.h"

void printShape(const Shape *ps)
{
    //std::cout << "area : " << ps->area() << std::endl;
    if (typeid(*ps) == typeid(Rectangle)){          // RTTI(RunTime Type Identification)
        std::cout << "rectangle ";
    }
    else if (typeid(*ps) == typeid(Circle)){
        std::cout << "circle "; 
    }
}


int main()
{
    // Shape s;
    Shape *ps;
    Rectangle r1(0, 0, 10, 10);
    Circle c1(10, 10, 50);

    Shape *pShapes[5];
    pShapes[0] = new  Rectangle(10, 10, 100, 20);
    pShapes[1] = new  Circle(50, 50, 20);
    pShapes[2] = new  Rectangle(0, 0, 10, 10);
    pShapes[3] = new  Circle(100, 100, 50);
    pShapes[4] = new  Circle(100, 150, 20);

    for (int i = 0; i < 5; i++)
    {
        printShape(pShapes[i]);
    }

    for (int i = 0; i < 5; i++){
        delete pShapes[i];
    }



    return 0;
}