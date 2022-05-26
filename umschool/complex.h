#pragma once
#include <ostream>
class complex
{
private:
	double Re, Im;
public:
	complex(double, double);
	complex();
	complex(double);
	double getRe();
	double getIm();
	double GetAbs();
	complex operator +(complex);
	complex operator -(complex);
	complex operator /(complex);
	complex operator *(complex);
	void operator +=(complex);
	void operator -=(complex);
	void operator *=(complex);
	void operator /=(complex);
	bool operator!=(complex);
	bool operator==(complex);
	bool operator>(complex);
	bool operator<(complex);
	friend std::ostream& operator <<(std::ostream&, complex&);
};

