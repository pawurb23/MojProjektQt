#include "ProstyUAR.h"

ProstyUAR::ProstyUAR(ModelARX& m, RegulatorPID& r) {

	model = &m;
	regulator = &r;
	reset();
}

double ProstyUAR::symuluj(double y_zad) {

	double uchyb = y_zad - y_ost;
	double u_wej = regulator->symuluj(uchyb);
	double y_wyj = model->symuluj(u_wej);

	y_ost = y_wyj;

	return y_wyj;
}

void ProstyUAR::reset() {
	y_ost = 0.0;
}