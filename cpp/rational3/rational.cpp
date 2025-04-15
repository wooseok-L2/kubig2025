#include "rational.h"
#include <iostream>
#include <cassert>

std::ostream& operator << (std::ostream& out, const Rational &rr)
{
    out << "(" << rr.p << "/" << rr.q << ")";

    return out;
}

Rational::Rational(int p, int q)
{
    this->p = p;
    this->q = q;
    assert(q != 0);
}

Rational::~Rational()
{
    // 동적할당 안하면 소멸자 사용 안해도 딤
}

Rational::Rational(const Rational &rr)
{
    this->p = rr.p;
    this->q = rr.q;
    assert(q != 0);
}

Rational& Rational::operator = (const Rational &rr)
{
    this->p = rr.p;
    this->q = rr.q;

    return *this;
}

bool Rational::operator == (const Rational &rr)
{
    return (this->p == rr.p && this->q == rr.q);
}

const Rational Rational::operator + (const Rational &rr)
{
    Rational result(this->p + rr.p, this->q + rr.q);

    return result;
}

const Rational Rational::operator - (const Rational &rr)
{
    Rational result(this->p - rr.p, this->q - rr.q);

    return result;
}