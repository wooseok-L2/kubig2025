#include "rational.h"
#include <iostream>
#include <cassert>

std::ostream& operator << (std::ostream& out, const Rational &rr)
{
    out << "(" << rr.p << "/" << rr.q << ")";

    return out;
}

int gcd(int a, int b) 
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Rational::divisorF(Rational &rr) {
    
    int divisor = gcd(rr.p, rr.q); // 최대공약수 계산
    rr.p /= divisor;  // 분자를 최대공약수로 나눔
    rr.q /= divisor; // 분모를 최대공약수로 나눔
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
    Rational result((this->p * rr.q) + (rr.p * this->q), this->q * rr.q);
    divisorF(result);

    return result;
}

const Rational Rational::operator - (const Rational &rr)
{
    Rational result((this->p * rr.q) - (rr.p * this->q), this->q * rr.q);
    divisorF(result);
    return result;
}