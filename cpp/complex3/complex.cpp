#include "complex.h"

std::ostream& operator << (std::ostream& out, const Complex& rhs)
{
    out << '(' << rhs.re << ", " << rhs.im << "i)";         // re, im is private, and this fuction is not member fuction

    return out;
}

Complex::Complex(double re, double im)  // 0.0 is default value
{
    this->re = re;
    this->im = im;
}

Complex::~Complex()
{
    // 동적할당 안하면 소멸자 사용 안해도 딤
}

Complex::Complex(const Complex &rhs)    // right hand side
{
    this->re = rhs.re;
    this->im = rhs.im;
}

Complex& Complex::operator = (const Complex &rhs)
{
    this->re = rhs.re;
    this->im = rhs.im;

    return *this;
}
    
bool Complex::operator == (const Complex &rhs)
{
    return this->re == rhs.re && this->im == rhs.im;
}

const Complex Complex::operator+(const Complex& rhs)
{
    Complex result(this->re + rhs.re, this->im + rhs.im);

    return result;
}

const Complex Complex::operator-(const Complex& rhs)
{
    Complex result(this->re - rhs.re, this->im - rhs.im);

    return result;
}

