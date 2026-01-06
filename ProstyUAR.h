#pragma once

#include "ModelARX.h"
#include "RegulatorPID.h"

class ProstyUAR {
private:

	ModelARX model;
	RegulatorPID regulator;
	double y_ost;

public:

	ProstyUAR();

	double symuluj(double y_zad);

	ModelARX& getModel() { return model; }
	RegulatorPID& getRegulator() { return regulator; }
};
