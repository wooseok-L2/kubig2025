#include "rational.h"
#include <iostream>

Rational::Rational(int p, int q)
{
    this->p = p;
    this->q = q;
    if (q == 0){
        std::cout << "q cannot have 0" << std::endl;
    }
}

Rational::Rational(int q)
{
    this->p = 0;
    this->q = q;
    if (q == 0){
        std::cout << "q cannot have 0" << std::endl;
    }
}

Rational::Rational()
{
    this->p = 0;
    this->q = 1;
}

Rational::~Rational()
{
    // 동적할당 안하면 소멸자 사용 안해도 딤
}

int Rational::numerator()
{
    return this->p;
}

int Rational::denominator()
{
    return this->q;
}

void Rational::numerator(int p)
{
    this->p = p;
}

void Rational::denominator(int q)
{
    this->q = q;
    if (q == 0){
        std::cout << "q cannot have 0" << std::endl;
    }
}
