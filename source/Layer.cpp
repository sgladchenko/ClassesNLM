#include "Containers.h"

Layer::Layer(int given_MyCountX, Complex* buffer)
{
	MyCountX = given_MyCountX;
	VectorBuffer = new Vector[MyCountX];

	for (int x = 0; x < MyCountX; ++x)
	{
		VectorBuffer[x].Init(buffer + x*16*N_E);
	}
}

Vector& Layer::operator()(int x)
{
	return VectorBuffer[x];
}

Layer::~Layer()
{
	delete [] VectorBuffer;
}