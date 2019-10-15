#include "BaseBin.h"
#include "AdiabaticScheme.h"
#include "Matrix.h"

AdiabaticScheme::AdiabaticScheme(int given_MyRank, int given_CommSize)
{
	MyRank = given_MyRank;
	CommSize = given_CommSize;

	// Determine my neighbour-nodes
	if (MyRank == 0)
	{
		LeftNeighbour  = CommSize - 1;
		RightNeighbour = 1;
	}
	else if (MyRank == CommSize - 1)
	{
		LeftNeighbour  = CommSize - 2;
		RightNeighbour = 0;
	}
	else
	{
		LeftNeighbour  = MyRank - 1;
		RightNeighbour = MyRank + 1;
	}

	// InitialSpectra object to be used in the calculations
	InitialSpectra Sp;

	// My chunck of the X-grid
	Obtain_SegmentX(MyRank, CommSize, MyLeftX, MyRightX);
	MyCountX = MyRightX - MyLeftX + 1;

	Xleft  = Xmin + MyLeftX*dX;
	Xright = Xmin + MyRightX*dX;

	// Allocations of the scattering and gathering buffers
	if (MyRank == 0)
	{
		GatherBuffer  = new Complex[N_X * 16*N_E];
		ScatterBuffer = new Complex[(N_X + 2*CommSize) * 16*N_E];
	}
	else
	{
		GatherBuffer  = new Complex[MyCountX * 16*N_E];
		ScatterBuffer = new Complex[(MyCountX + 2) * 16*N_E];
	}

	// Allocation of the Harmonics array
	if (NUM_HARMONICS > 0)
	{
		Harmonics = new double[NUM_HARMONICS];
	}

	// Arrays for the scattering processes
	Obtain_ScatterCounts(CommSize, ScatterCounts);
	Obtain_ScatterDisplacements(CommSize, ScatterDisplacements);

	// Data to be used in the calculations
	p_even     = new Matrix[(mycountX+2)*N_E];
	m_even     = new Matrix[(mycountX+2)*N_E];
	antip_even = new Matrix[(mycountX+2)*N_E];
	antim_even = new Matrix[(mycountX+2)*N_E];

	p_odd      = new Matrix[(mycountX+2)*N_E];
	m_odd      = new Matrix[(mycountX+2)*N_E];
	antip_odd  = new Matrix[(mycountX+2)*N_E];
	antim_odd  = new Matrix[(mycountX+2)*N_E];
}

void AdiabaticScheme::Initialise()
{
	// Object to operate the binary data
	BaseBin Bin(CommSize);

	// Obtaining data from the binaries
	if (MyRank == 0)
	{
		Bin.InputScatterBuffer(ScatterBuffer);
		Bin.InputZ_init(Z_init);
		Bin.InputHarmonics(Harmonics);
	}

	// Scattering the initial data
	MPI_Scatterv(ScatterBuffer,
				 ScatterCounts,
				 ScatterDisplacements,
				 MPIComplex,
				 ScatterBuffer,
				 (MyCountX + 2) * 16*N_E,
				 MPIComplex,
				 0,
				 MPIWorld);

	MPI_Bcast(&Z_init, 1, MPI_DOUBLE, 0, MPIWorld);
	MPI_Bcast(Harmonics, NUM_HARMONICS, MPI_DOUBLE, 0, MPIWorld);

	// Unpacking the obtained data from scattering
	for (int x = 0; x < mycountX + 2; ++x)
	{
		for (int e = 0; e < N_E; ++e)
		{
			p_odd[x*N_E + e].unpack(scatt_buffer + x*4*4*N_E + e*4*4 + 0*4);
			m_odd[x*N_E + e].unpack(scatt_buffer + x*4*4*N_E + e*4*4 + 1*4);

			antip_odd[x*N_E + e].unpack(scatt_buffer + x*4*4*N_E + e*4*4 + 2*4);
			antim_odd[x*N_E + e].unpack(scatt_buffer + x*4*4*N_E + e*4*4 + 3*4);
		}
	}
}

void AdiabaticScheme::Process()
{
	// Object to operate the binary data
	BaseBin Bin(CommSize);

}

AdiabaticScheme::~AdiabaticScheme()
{
	delete [] GatherBuffer;
	delete [] ScatterBuffer;
	delete [] Harmonics;

	delete [] p_even;
	delete [] m_even;
	delete [] antip_even;
	delete [] antim_even;

	delete [] p_odd;
	delete [] m_odd;
	delete [] antip_odd;
	delete [] antim_odd;	
}