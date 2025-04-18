#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
friend std::ostream& operator<<(std::ostream& out, const Complex& rhs);

private:
    double re_;
    double im_;        // 가독성을 위해 멤버변수 표현

public:
    Complex(double re = 0.0, double im = 0.0);

    // Complex()    {}
    // Complex(const Complex& ) {}
    // ~Complex()
    // Complex& operator=(const Complex& ){}   // +=, -=, *=, /= (O) // %=, &=. |=, ^=  (X)
    Complex& operator+=(const Complex& rhs);
    // Complex *operator&(){return this;}
    // const Complex *operator&() const{return this;}

    bool operator==(const Complex& rhs) const;       // !=, >, <, >=, <=  (O)

    bool operator!=(const Complex& rhs) const;

    const Complex operator+(const Complex& rhs) const;    // -, *, /  (O)   // %, ++, --  (X)

    const Complex operator-(const Complex& rhs) const; 

    Complex& operator++();        // prefix
    Complex operator++(int );    // postfix


    /*
    Complex 에서 사용가능한 연산자 분류
    +=, -=, *=, /= (O) // %=, &=. |=, ^=  (X)
    !=, >, <, >=, <=  (O)
    -, *, /  (O)   // %, ++, --  (X)
    &, |, -, ^  (X)
    type casting(X)
    */

    double real() const;
    double imag() const;

    void real(double re);
    void imag(double im);
    
};

#endif