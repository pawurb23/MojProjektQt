#pragma once

#include "ModelARX.h"
#include "RegulatorPID.h"

class ProstyUAR {
private:

	ModelARX* model;
	RegulatorPID* regulator;
	double y_ost;

public:

	ProstyUAR(ModelARX& m, RegulatorPID& r);

	double symuluj(double y_zad);
	void reset();
};
