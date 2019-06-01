#include "NRandomGenerator.h"

NRandomGenerator* NRandomGenerator::_theInstance = NULL;

const long double pi = 3.1415926535897932384626433832795;


/*****************************************************************************
 *                          PUBLIC MEMBER FUNCTIONS                          *
 *****************************************************************************/
void NRandomGenerator::randomizeVector(VectorXcd& vec, bool pureReal /*= false*/) const {
	if (vec.size() == 0) return;
	vec[0] = 1;
	for (int i = 1; i < vec.size(); ++i) {
		double thetaHalf = (acos(val()) / 2);
		for (int j = 0; j < i; ++j) {
			vec[j] *= cos(thetaHalf);
		}
		vec[i] = sin(thetaHalf);
		if (!pureReal) {
			double phi = pi * val();
#if defined(linux)
			vec[i].imag() = (vec[i].real() * sin(phi));	// Linux
			vec[i].real() = (vec[i].real() * cos(phi));	// Linux
#else // not linux
			vec[i].imag(vec[i].real() * sin(phi));		// Windows
			vec[i].real(vec[i].real() * cos(phi));		// Windows
#endif // not linux
		}
	}
}

void NRandomGenerator::randomizeProbabilities(VectorXd& vec) const {
	double norm = 0;
	for (int i = 0; i < vec.size(); ++i) {
		norm += vec[i] = rand();
	}
	vec /= norm;
}


/*****************************************************************************
 *                          PRIVATE MEMBER FUNCTIONS                         *
 *****************************************************************************/
NRandomGenerator::NRandomGenerator(uint seed /*= time(0)*/) : _seed(seed) {
	srand(seed);
	NLOGNUM("NRandomGenerator: PRNG started with seed:", _seed);
}
