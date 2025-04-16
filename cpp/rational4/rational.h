#ifndef RATIONAL_H
#define RATIONAL_H

#include <ostream>

class Rational {
friend std::ostream& operator << (std::ostream& out, const Rational &rr);
private: // implemetation
    int p;        // real part
    int q;        // imaginary part
    void divisorF(Rational &rr);    //helper function

public:  // interface
    Rational(int p = 0, int q = 1);       // constructor 
    Rational& operator+=(const Rational &rr);
    bool operator != (const Rational &rr) const;
    bool operator == (const Rational &rr) const;
    const Rational operator + (const Rational &rr);
    const Rational operator - (const Rational &rr);
    Rational& operator ++ ();
    Rational operator ++ (int);

    // 없는 경우 자동생성
    // Complex()    {}
    // Complex(const Complex& ) {}
    // ~Complex()
    // Complex& operator=(const Complex& ){}   // +=, -=, *=, /= (O) // %=, &=. |=, ^=  (X)
    // Complex *operator&(){return this;}
    // const Complex *operator&() const{return this;}

};

#endif