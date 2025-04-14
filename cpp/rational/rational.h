#ifndef RATIONAL_H
#define RATIONAL_H

class Rational {
private: // implemetation
    int p;        // real part
    int q;        // imaginary part

public:  // interface
    Rational(int p, int q);       // constructor
    Rational(int q);
    // Complex(double im);  사용불가, 둘 중 하나만 사용 가능
    Rational();  
    ~Rational();      // destructor

    int numerator();   // get
    int denominator();   // get

    void numerator(int p);   // set
    void denominator(int q);   // set


};

#endif