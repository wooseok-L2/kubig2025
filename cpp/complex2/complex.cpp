#include "complex.h"

Complex::Complex()
{
    this->re = 0.0;
    this->im = 0.0;
}

Complex::Complex(double re)
{
    this->re = re;
    this->im = 0.0;
}

Complex::Complex(double re, double im)
{
    this->re = re;
    this->im = im;
}

Complex::~Complex()
{
    // 동적할당 안하면 소멸자 사용 안해도 딤
}

// void Complex::operator = (Complex c)
// {
//     this->re = c.re;
//     this->im = c.im;
// }

// void Complex::operator = (const Complex *pc)
// {
//     this->re = pc->re;
//     this->im = pc->im;
// }

void Complex::operator = (const Complex &rc)
{
    this->re = rc.re;
    this->im = rc.im;
}

bool Complex::operator == (const Complex &rc)
{
    // if (this->re == rc.re && this->im == rc.im){
    //     return true;
    // }
    // else {
    //     return false;
    // }

    return (this->re == rc.re && this->im == rc.im);
}

double Complex::getreal()
{
    return this->re;
}

double Complex::getimag()
{
    return this->im;
}

void Complex::setreal(double re)
{
    this->re = re;
}

void Complex::setimag(double im)
{
    this->im = im;
}
