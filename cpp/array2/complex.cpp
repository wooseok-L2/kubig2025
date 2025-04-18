#include "complex.h"


std::ostream& operator<<(std::ostream& out, const Complex& rhs)
{
    return out << "(" << rhs.re_ << ", " << rhs.im_ << "i)";
}

Complex::Complex(double re, double im)
: re_(re), im_(im)          //생성자에서만 가능  constructor init list
{
    // this->re_ = re;  
    // re_ = re;            // 멤버 변수와 매게변수 이름이 똑같을 때는 this 생략 불가능
    // this->im_ = im;
}

Complex& Complex::operator+=(const Complex& rhs)
{
    this->re_ += rhs.re_;
    this->im_ += rhs.im_;

    return *this;
}

bool Complex::operator==(const Complex& rhs) const
{
    return this->re_ == rhs.re_ && this->im_ == rhs.im_;
}

bool Complex::operator!=(const Complex& rhs) const
{
    // return !(this->re_ == rhs.re_ && this->im_ == rhs.im_);
    return !this->operator==(rhs);
    // return !(*this == rhs);
    // return this->re_ != rhs.re_ || this->im_ != rhs.im_;
}

const Complex Complex::operator+(const Complex& rhs) const
{
    Complex result(this->re_ + rhs.re_, this->im_ + rhs.im_);

    return result;
}

const Complex Complex::operator-(const Complex& rhs) const
{
    Complex result(this->re_ - rhs.re_, this->im_ - rhs.im_);

    return result;
}

Complex& Complex::operator++()   // prefix  ++i
{        
    re_ += 1.0;

    return *this;
}

Complex Complex::operator++(int )    // postfix   i++   int는 후위 증감연산자 라는 것을 명시 하기 위한 것
{
    Complex tmp = *this;
    re_ += 1.0;

    return tmp;
}

double Complex::real() const
{
    return re_;
}

double Complex::imag() const
{
    return im_;
}

void Complex::real(double re)
{
    re_ = re;
}

void Complex::imag(double im)
{
    im_ = im;
}
