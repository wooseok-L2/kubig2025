#ifndef RATIONAL_H
#define RATIONAL_H

class Rational {
private: // implemetation
    int p;        // real part
    int q;        // imaginary part

public:  // interface
    Rational(int p, int q);       // constructor
    Rational(int p);
    // Complex(double im);  사용불가, 둘 중 하나만 사용 가능
    Rational();  
    ~Rational();      // destructor

    int getnumerator();   // get
    int getdenominator();   // get

    void setnumerator(int p);   // set
    void setdenominator(int q);   // set


};

#endif