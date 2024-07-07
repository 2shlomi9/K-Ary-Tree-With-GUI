#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {

private:

    double _re;
    double _im;

public:

    // Constractor 
    Complex (const double& re= 0.0,
             const double& im= 0.0)
        : _re(re), _im(im) {
    }
    // Copy constructor
    Complex(const Complex& other)
        : _re(other._re), _im(other._im) {
    }

    double re() const {
		return _re;
	}

	double im() const {
		return _im;
	}

// -------------------- Operators --------------------

// --------- Unary operator ---------

    bool operator!() const;

    Complex operator-() const;

// --------- Assignment operator ---------

    Complex& operator=(const Complex& other);


// --------- Binary operators ---------

const Complex operator+(const Complex& other) const;

const Complex operator-(const Complex& other) const;

Complex& operator+=(const Complex& other);

Complex& operator-=(const Complex& other);

Complex& operator*=(const Complex& other);

// --------- Compare operator ---------

const float TOLERANCE = 0.001;

bool operator==(const Complex& c);

bool operator!=(const Complex& c);

bool operator<(const Complex& c);

bool operator>(const Complex& c);

bool operator<=(const Complex& c);

bool operator>=(const Complex& c);

// --------- Prefix & Postfix operator ---------

Complex& operator++(); // Prefix

Complex operator++(int); // Postfix

// --------- Ostream operator ---------

friend std::ostream& operator<< (std::ostream& output, const Complex& c);

};

#endif // COMPLEX_HPP