#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
private: // implemetation
    double re;        // real part
    double im;        // imaginary part

public:  // interface
    Complex(double re, double im);       // constructor
    Complex(double re);
    // Complex(double im);  사용불가, 둘 중 하나만 사용 가능
    Complex();  
    ~Complex();      // destructor

    double real();   // get
    double imag();   // get

    void real(double re);   // set
    void imag(double im);   // set


};

#endif