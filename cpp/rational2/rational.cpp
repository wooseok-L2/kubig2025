#include "rational.h"
#include <iostream>
#include <cassert>

Rational::Rational(int p, int q)
{
    this->p = p;
    this->q = q;
    assert(q != 0);
}

Rational::Rational(int p)
{
    this->p = p;
    this->q = 1;
    assert(q != 0);
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

void Rational::operator = (const Rational &rr)
{
    this->p = rr.p;
    this->q = rr.q;
}

bool Rational::operator == (const Rational &rr)
{
    // if (this->p == rr.p && this->q == rr.q){
    //     return true;
    // }
    // else {
    //     return false;
    // }

    return (this->p == rr.p && this->q == rr.q);
}

int Rational::getnumerator()
{
    return this->p;
}

int Rational::getdenominator()
{
    return this->q;
}

void Rational::setnumerator(int p)
{
    this->p = p;
}

void Rational::setdenominator(int q)
{
    this->q = q;
    assert(q != 0);
}
