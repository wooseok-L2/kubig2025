#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape{
private:
    int width_;
    int height_;

public: 
    Rectangle(int x, int y, int w, int h);
    virtual ~Rectangle() {}
    // Rectangle(const Rectangle& ) {}
    // Rectangle& operator=(const Rectangle& ) {}

    virtual double area() const;
    double getDiagonal() const;
};

#endif