#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
    
public:  // interface
    Complex();       // constructor
    ~Complex();      // destructor
    Complex(double re, double im);       
    Complex(double re);
    // Complex(double im);  사용불가, 둘 중 하나만 사용 가능

    // void operator = (Complex c);
    // void operator = (const Complex *pc);
    void operator = (const Complex &rc);
    
    bool operator == (const Complex &rc);

    double getreal();   // get
    double getimag();   // get
    
    void setreal(double re);   // set
    void setimag(double im);   // set
    
private: // implemetation
    double re;        // real part
    double im;        // imaginary part

};

#endif