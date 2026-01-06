#include "RegulatorPID.h"

RegulatorPID::RegulatorPID(double k, double ti, double td)
	: Kp(k), Ti(ti), Td(td) {

	suma_uchybow = 0.0;
	poprzedni_uchyb = 0.0;
	tryb_calkowania = LiczCalk::Zew;
}

void RegulatorPID::resetPamieci() {

	suma_uchybow = 0.0;
	poprzedni_uchyb = 0.0;
}

void RegulatorPID::setStalaWzm(double k) { Kp = k; }

void RegulatorPID::setStalaCalk(double ti) { Ti = ti; }

void RegulatorPID::setStalaRoz(double td) {	Td = td; }

void RegulatorPID::setNastawy(double k, double ti, double td) {

	setStalaWzm(k);
	setStalaCalk(ti);
	setStalaRoz(td);
}

void RegulatorPID::setLiczCalk(LiczCalk tryb) {

	if (tryb == tryb_calkowania || Ti == 0.0) {

		tryb_calkowania = tryb;
		return;
	}

	if(tryb == LiczCalk::Zew) { suma_uchybow = suma_uchybow * Ti; }
	else { suma_uchybow = suma_uchybow / Ti; }

	tryb_calkowania = tryb;
}

double RegulatorPID::symuluj(double uchyb) {

	double u_p = Kp * uchyb;

	double u_i = 0.0;

	if (abs(Ti) > 0.00001) {

		if (tryb_calkowania == LiczCalk::Zew) {

			suma_uchybow += uchyb;
			u_i = (1.0 / Ti) * suma_uchybow;
		}
		else {

			suma_uchybow += (uchyb / Ti);
			u_i = suma_uchybow;
		}
	}
	else { u_i = 0.0; }

	double u_d = Td * (uchyb - poprzedni_uchyb);
	poprzedni_uchyb = uchyb;

	return u_p + u_i + u_d;
}