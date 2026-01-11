#pragma once
#include <cmath>

class RegulatorPID {
public:

	enum class LiczCalk { Wew, Zew };

private:

	//nastawy regulatora
	double Kp;
	double Ti;
	double Td;

	//pamiec regulatora
	double suma_uchybow;
	double poprzedni_uchyb;

	//tryb calkowania
	LiczCalk tryb_calkowania;

	//skladowe sterowania
	double up, ui, ud;

public:

	RegulatorPID(double k, double ti = 0.0, double td = 0.0);

	double symuluj(double uchyb);
	void zresetujCalke();

	void setStalaWzm(double k);
	void setStalaCalk(double ti);
	void setStalaRoz(double td);
	void setNastawy(double k, double ti, double td);
	void setLiczCalk(LiczCalk tryb);
	void resetPamieci();

	double getStalaWzm() { return Kp; }
	double getStalaCalk() { return Ti; }
	double getStalaRoz() { return Td; }
	LiczCalk getLiczCalk() { return tryb_calkowania; }
	double getUp() const { return up; }
	double getUi() const { return ui; }
	double getUd() const { return ud; }
};
