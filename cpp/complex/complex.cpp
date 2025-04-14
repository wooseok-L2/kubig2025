#include "complex.h"

Complex::Complex(double re, double im)
{
    this->re = re;
    this->im = im;
}

Complex::Complex(double re)
{
    this->re = re;
    this->im = 0.0;
}

Complex::Complex()
{
    this->re = 0.0;
    this->im = 0.0;
}

Complex::~Complex()
{
    // 동적할당 안하면 소멸자 사용 안해도 딤
}

double Complex::real()
{
    return this->re;
}

double Complex::imag()
{
    return this->im;
}

void Complex::real(double re)
{
    this->re = re;
}

void Complex::imag(double im)
{
    this->im = im;
}
