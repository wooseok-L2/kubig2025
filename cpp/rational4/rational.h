#ifndef RATIONAL_H
#define RATIONAL_H

#include <ostream>

class Rational {
friend std::ostream& operator << (std::ostream& out, const Rational &rr);
private: // implemetation
    int p;        // real part
    int q;        // imaginary part

public:  // interface
    Rational(int p = 0, int q = 1);       // constructor 
    void divisorF(Rational &rr);
    Rational& operator+=(const Rational &rr);
    bool operator != (const Rational &rr);
    bool operator == (const Rational &rr);
    const Rational operator + (const Rational &rr);
    const Rational operator - (const Rational &rr);
    Rational& operator ++ ();
    Rational operator ++ (int);

};

#endif