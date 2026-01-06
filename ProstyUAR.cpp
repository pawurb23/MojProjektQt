#include "ProstyUAR.h"

ProstyUAR::ProstyUAR() : model({-1.0}, {1.0}, 1, 0.0), regulator(1.0, 0.0, 0.0) {

	y_ost = 0.0;
}

double ProstyUAR::symuluj(double y_zad) {

	double uchyb = y_zad - y_ost;
	double u_wej = regulator.symuluj(uchyb);
	double y_wyj = model.symuluj(u_wej);

	y_ost = y_wyj;
	return y_wyj;
}