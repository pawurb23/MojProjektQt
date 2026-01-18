#pragma once

#include "ModelARX.h"
#include "RegulatorPID.h"

class ProstyUAR {
private:

	ModelARX* model;
	RegulatorPID* regulator;

	bool czyWlasciciel;

	double y_ost;
	double u_akt;
	double e_akt;

public:

	ProstyUAR(ModelARX& m, RegulatorPID& r);
	ProstyUAR();
	~ProstyUAR();

	double symuluj(double y_zad);
	void reset();
	void resetCalki();

	double getSterowanie() const { return u_akt; }
	double getUchyb() const { return e_akt; }

	ModelARX& getModel() { return *model; }
	RegulatorPID& getRegulator() { return *regulator; }

	void setPID(double k, double ti, double td);
	void setTrybPID(RegulatorPID::LiczCalk tryb);

	void setModel(std::vector<double> A, std::vector<double> B, int k, double z);
	void setOgraniczenia(double umin, double umax, double ymin, double ymax, bool aktywne);

	double getP() { return regulator->getUp(); }
	double getI() { return regulator->getUi(); }
	double getD() { return regulator->getUd(); }

    std::vector<double> getModelA() { return model ? model->getWspA() : std::vector<double>(); }
    std::vector<double> getModelB() { return model ? model->getWspB() : std::vector<double>(); }
    int getModelK() { return model ? model->getOpoznienie() : 1; }
    double getModelZ() { return model ? model->getZaklocenie() : 0.0; }
    double getModelUmin() { return model ? model->getUmin() : -10.0; }
    double getModelUmax() { return model ? model->getUmax() : 10.0; }
    double getModelYmin() { return model ? model->getYmin() : -10.0; }
    double getModelYmax() { return model ? model->getYmax() : 10.0; }
    bool getModelOgr() { return model ? model->getOgraniczeniaAktywne() : true; }
};
