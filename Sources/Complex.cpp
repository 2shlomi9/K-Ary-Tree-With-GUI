#include "Complex.hpp"
#include <cmath>

using namespace std;




// --------- Unary operator ---------

    bool Complex::operator!() const{
        return _re==0 && _im==0;
    }
    
    Complex Complex::operator-() const {
        return Complex(-_re , -_im);
    }

// --------- Assignment operator ---------

Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {  // self-assignment check
        _re = other._re;
        _im = other._im;
    }
    return *this;
}
// --------- Binary operators ---------

const Complex Complex::operator+(const Complex& other) const{
    return Complex(_re + other._re, _im + other._im);
}

const Complex Complex::operator-(const Complex& other) const{
    return Complex(_re - other._re, _im - other._im);
}

Complex& Complex::operator+=(const Complex& other){
    _re+= other._re;
    _im+= other._im;
    return *this;
}

Complex& Complex::operator-=(const Complex& other){
    _re-= other._re;
    _im-= other._im;
    return *this;
}

Complex& Complex::operator*=(const Complex& other){
    double new_re = _re*other._re - _im*other._im;
    double new_im = _re*other._im + _im*other._re; 
    _re = new_re;
    _im = new_im;
    return *this;
}

// --------- Compare operator ---------

const float TOLERANCE = 0.001;


bool Complex::operator==(const Complex& c) {
    return ( abs(_re-c._re) <= TOLERANCE && abs(_im-c._im) <= TOLERANCE );
}

bool Complex::operator!=(const Complex& c) {
    return (!(*this == c));
}

bool Complex::operator<(const Complex& c) {
    double magnitude1 = sqrt(_re * _re + _im * _im);
    double magnitude2 = sqrt(c._re * c._re + c._im * c._im);
    return magnitude1 < magnitude2;
}

bool Complex::operator>(const Complex& c) {
    if((*this != c) && !(*this < c))
        return true;
    return false;
}

bool Complex::operator<=(const Complex& c) {
    if((*this == c) || (*this < c))
        return true;
    return false;
}

bool Complex::operator>=(const Complex& c) {
    if((*this == c) || (*this > c))
        return true;
    return false;
}

// --------- Prefix & Postfix operator ---------

Complex& Complex::operator++(){
    _re++;
    return *this;
}

Complex Complex::operator++(int){
    Complex copy = *this;
    _re++;
    return copy;
}

// --------- Ostream operator ---------

ostream& operator<< (ostream& output, const Complex& c) {
    output << c._re << '+' << c._im << 'i';
    return output;
}
