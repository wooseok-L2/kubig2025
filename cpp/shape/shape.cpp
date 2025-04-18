#include "shape.h"

Shape::Shape(int x, int y)
: x_(x), y_(y)
{

}

Shape::Shape()
: x_(0), y_(0)
{

}

void Shape::move(int x, int y)
{
    x_ += x;
    y_ += y;
}
