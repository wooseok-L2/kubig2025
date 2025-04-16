#include "rational.h"
#include <iostream>
#include <cassert>

int gcd(int a, int b)    //유클리드 호제법
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::ostream& operator<<(std::ostream& out, const Rational &rr)
{
    out << "(" << rr.p << "/" << rr.q << ")";

    return out;
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

    divisorF(*this);
}

Rational& Rational::operator+=(const Rational &rr)
{
    this->p = (this->p * rr.q) + (rr.p * this->q);
    this->q = this->q * rr.q;
    divisorF(*this);

    return *this;
}

bool Rational::operator==(const Rational &rr) const
{
    return (this->p == rr.p && this->q == rr.q);
}

bool Rational::operator!=(const Rational &rr) const
{
    return !(this->p == rr.p && this->q == rr.q);
    // return !this->operator==(rr);
}

const Rational Rational::operator+(const Rational &rr)
{
    Rational result((this->p * rr.q) + (rr.p * this->q), this->q * rr.q);

    return result;
}

const Rational Rational::operator-(const Rational &rr)
{
    Rational result((this->p * rr.q) - (rr.p * this->q), this->q * rr.q);

    return result;    
}

Rational& Rational::operator++()
{
    this->p += this->p;

    return *this;
}

Rational Rational::operator++(int)
{
    Rational tmp = *this;
    this->p += this->p;

    return tmp;
}