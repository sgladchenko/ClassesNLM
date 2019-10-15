#include "BaseScheme.h"
#include "BaseBin.h"

#include "InitialSpectra.h"
#include "Segmentation.h"
#include "Constants.h"

class AdiabaticScheme: public BaseScheme
// The implementation of the numerical scheme with
// included adiabaticity
{
	public:
		AdiabaticScheme(int given_MyRank, int given_CommSize);

		void Initialise();
		void Process();

		~AdiabaticScheme();

	protected:
		// Energy spectra to be used in the integrals etc.
		InitialSpectra Sp;

		// X-chunck of this node
		int MyCountX, MyLeftX, MyRightX;

		// The particular values of the X coordinates
		double Xleft, Xright;

		// Initial Z-coordinate
		double Z_init;

		// Buffer of the initial scattering
		Complex* ScatterBuffer;

		// Buffer of the gathering (for saving a new line of data)
		Complex* GatherBuffer;

		// Array of the harmonics of inhomogeneity 
		double* Harmonics;

		// Something for the scattering
		int* ScatterCounts;
		int* ScatterDisplacements;

		// Data to be used in the calculational process
		Matrix* p_even;
		Matrix* m_even;
		Matrix* antip_even;
		Matrix* antim_even;

		Matrix* p_odd;
		Matrix* m_odd;
		Matrix* antip_odd;
		Matrix* antim_odd;

		// These arrays will become 'actual' ones in RK main cycle
		Matrix* p; Matrix* antip;
		Matrix* m; Matrix* antim;

		// and these will become 'old' ones
		Matrix* old_p; Matrix* old_antip;
		Matrix* old_m; Matrix* old_antim;
};