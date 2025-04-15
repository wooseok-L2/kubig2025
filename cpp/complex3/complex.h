#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

class Complex;     // 클래스 선언
// std::ostream& operator << (std::ostream& out, const Complex& rhs);       // 전역함수

class Complex {
friend std::ostream& operator << (std::ostream& out, const Complex& rhs);   // 프렌드 함수
public:  // interface
    ~Complex();      // destructor
    Complex(double re = 0.0, double im = 0.0);  
    Complex(const Complex &rhs);      // copy constructor

    Complex& operator = (const Complex &rhs);
    
    bool operator == (const Complex &rhs);
    
    const Complex operator+(const Complex& rhs);

    const Complex operator-(const Complex& rhs);

    
private: // implemetation
    double re;        // real part
    double im;        // imaginary part
};

#endif