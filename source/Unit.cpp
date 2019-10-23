#include "Containers.h"

Unit::Unit(Complex* buffer)
{
	// Each of our matrices consists of four elememts (2x2)
	for (int i = 0; i < 4; ++i)
	{
		ComplexBuffer[i] = buffer[i];
	}
}

Unit::Unit(Complex e0, Complex e1, Complex e2, Complex e3)
{
	// Must be suitable for some tasks, e.g. when we're posing the Pauli matrices
	ComplexBuffer[0] = e0;
	ComplexBuffer[1] = e1;
	ComplexBuffer[2] = e2;
	ComplexBuffer[3] = e3;
}

Unit::Unit()
{
	for (int i = 0; i < 4; ++i)
	{
		ComplexBuffer[i] = 0;
	}	
}

Unit::Unit(const Unit& u)
{
	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] = u.ComplexBuffer[k];
	}
}

void Unit::Init(Complex e0, Complex e1, Complex e2, Complex e3)
{
	// Must be suitable for some tasks, e.g. after allocations
	ComplexBuffer[0] = e0;
	ComplexBuffer[1] = e1;
	ComplexBuffer[2] = e2;
	ComplexBuffer[3] = e3;	
}

void Unit::Init(Complex* buffer)
{
	for (int i = 0; i < 4; ++i)
	{
		ComplexBuffer[i] = buffer[i];
	}
}

Unit Unit::operator+(const Unit& u) const
{
	return Unit(ComplexBuffer[0] + u.ComplexBuffer[0],
				ComplexBuffer[1] + u.ComplexBuffer[1],
				ComplexBuffer[2] + u.ComplexBuffer[2],
				ComplexBuffer[3] + u.ComplexBuffer[3]);
}

Unit Unit::operator-(const Unit& u) const
{
	return Unit(ComplexBuffer[0] - u.ComplexBuffer[0],
				ComplexBuffer[1] - u.ComplexBuffer[1],
				ComplexBuffer[2] - u.ComplexBuffer[2],
				ComplexBuffer[3] - u.ComplexBuffer[3]);
}

Unit Unit::operator*(const Unit& u) const
{
	return Unit(ComplexBuffer[0]*u.ComplexBuffer[0] + ComplexBuffer[1]*u.ComplexBuffer[2],
				ComplexBuffer[0]*u.ComplexBuffer[1] + ComplexBuffer[1]*u.ComplexBuffer[3],
				ComplexBuffer[2]*u.ComplexBuffer[0] + ComplexBuffer[3]*u.ComplexBuffer[2],
				ComplexBuffer[2]*u.ComplexBuffer[1] + ComplexBuffer[3]*u.ComplexBuffer[3]);
}

Unit Unit::operator/(const Complex& z) const
{
	return Unit(ComplexBuffer[0] / z,
				ComplexBuffer[1] / z,
				ComplexBuffer[2] / z,
				ComplexBuffer[3] / z);
}

// Right multiplication on a Complex number
Unit Unit::operator*(const Complex z) const
{
	return Unit(ComplexBuffer[0] * z,
				ComplexBuffer[1] * z,
				ComplexBuffer[2] * z,
				ComplexBuffer[3] * z);
}

// Left multiplication on a Complex number
Unit operator*(const Complex& z, const Unit& u)
{
	return Unit(u.ComplexBuffer[0] * z,
				u.ComplexBuffer[1] * z,
				u.ComplexBuffer[2] * z,
				u.ComplexBuffer[3] * z);
}

void Unit::operator+=(const Unit& u)
{
	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] += u.ComplexBuffer[k];
	}
}

void Unit::operator-=(const Unit& u)
{
	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] -= u.ComplexBuffer[k];
	}
}

void Unit::operator*=(const Complex& z)
{
	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] *= z;
	}
}

void Unit::operator/=(const Complex& z)
{
	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] /= z;
	}	
}

void Unit::operator=(const Unit& u)
{
	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] = u.ComplexBuffer[k];
	}
}

Complex Unit::Tr() const
{
	return ComplexBuffer[0] + ComplexBuffer[3];
}

void Unit::normalise()
{
	// Recover Hermitance
	Complex o0, o1, o2, o3; // old ones

	o0 = ComplexBuffer[0];
	o1 = ComplexBuffer[1];
	o2 = ComplexBuffer[2];
	o3 = ComplexBuffer[3];

	ComplexBuffer[0] = 0.5*(o0 + std::conj(o0));
	ComplexBuffer[1] = 0.5*(o1 + std::conj(o2));
	ComplexBuffer[2] = 0.5*(o2 + std::conj(o1));
	ComplexBuffer[3] = 0.5*(o3 + std::conj(o3));

	// Recover trace = 1
	Complex tr = ComplexBuffer[0] + ComplexBuffer[3];

	for (int k = 0; k < 4; ++k)
	{
		ComplexBuffer[k] /= tr;
	}
}

Complex& Unit::operator()(int i, int j)
{
	return ComplexBuffer[i*2 + j];
}

Complex& Unit::operator[](int k)
{
	return ComplexBuffer[k];
}