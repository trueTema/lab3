#include "complex.h"
#include <ostream>
complex complex::operator +(complex c) {
	return complex(this -> getRe() + c.getRe(), this -> getIm() + c.getIm());
}
complex complex::operator -(complex c) {
	return complex(this->getRe() - c.getRe(), this->getIm() - c.getIm());
}
complex complex::operator *(complex c) {
	return complex(this->getRe() * c.getRe() - this->getIm() * c.getIm(), 
		this -> getRe()*c.getIm() + this -> getIm() * c.getRe());
}
complex complex::operator /(complex c) {
	complex cur(c.getRe(), -c.getIm());
	complex znam = c * cur;
	complex chisl = (*this) * cur;
	return complex(chisl.getRe() / znam.getRe(), chisl.getIm() / znam.getRe());
}

void complex::operator +=(complex c) {
	*this = *this + c;
}
void complex::operator -=(complex c) {
	*this = *this - c;

}
void complex::operator *=(complex c) {
	*this = *this * c;

}
void complex::operator /=(complex c) {
	*this = *this / c;

}

bool complex::operator!=(complex c) {
	return !((this->getIm() == c.getIm()) && (this->getRe() == c.getRe()));
}
bool complex::operator==(complex c) {
	return (this->getIm() == c.getIm()) && (this->getRe() == c.getRe());
}

bool complex::operator>(complex c) {
	return this -> GetAbs() > c.GetAbs();
}

bool complex::operator<(complex c) {
	return this->GetAbs() < c.GetAbs();
}

std::ostream& operator <<(std::ostream& os, complex& c) {
	os << c.getRe();
	if (c.getIm() != 0) {
		os << " + " << c.getIm() << "i";
	}
	return os;
}

complex::complex(double x, double y) {
	this->Re = x;
	this->Im = y;
}

complex::complex(double x) {
	this->Re = x;
	this->Im = 0;
}

complex::complex() {
	this->Re = 0;
	this->Im = 0;
}

double complex::getRe() {
	return this->Re;
}
double complex::getIm() {
	return this->Im;
}

double complex::GetAbs() {
	return sqrt(pow(this->Im,2) + pow(this->Re,2));
}