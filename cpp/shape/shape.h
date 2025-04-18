#ifndef SHAPE_H
#define SHAPE_H

class Shape {
protected:
    int x_;
    int y_;
public:
    Shape();
    Shape(int x, int y);
    // Shape(const Shape& ) {}
    // Shape& operator=(const Shape& ) {}

    void move(int x, int y);
    virtual double area() const = 0;             // cannot be implemented, --> pure virtual func.  => do overriding


};

#endif