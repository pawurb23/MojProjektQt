#include "ProstyUAR.h"

//#include <QtGlobal>

ProstyUAR::ProstyUAR(ModelARX& m, RegulatorPID& r) {

    model = &m;
    regulator = &r;
    czyWlasciciel = false;
    reset();
}

ProstyUAR::ProstyUAR() {

    model = new ModelARX({ -1.0 }, { 1.0 }, 1, 0.0);
    regulator = new RegulatorPID(1.0, 0.0, 0.0);
    czyWlasciciel = true;
    reset();
}

ProstyUAR::~ProstyUAR() {

    if (czyWlasciciel) {
        if (model) delete model;
        if (regulator) delete regulator;
    }
}

double ProstyUAR::symuluj(double y_zad) {

    double uchyb = y_zad - y_ost;
    double u_wej = regulator->symuluj(uchyb);
    double y_wyj = model->symuluj(u_wej);

    y_ost = y_wyj;
    u_akt = u_wej;
    e_akt = uchyb;

    return y_wyj;
}

void ProstyUAR::reset() {

    y_ost = 0.0;
    u_akt = 0.0;
    e_akt = 0.0;
    if (regulator) regulator->resetPamieci();
}

void ProstyUAR::resetCalki() { if (regulator) regulator->zresetujCalke(); }

void ProstyUAR::setPID(double k, double ti, double td) {

    if (regulator) regulator->setNastawy(k, ti, td);
}

void ProstyUAR::setTrybPID(RegulatorPID::LiczCalk tryb) {

    if (regulator) regulator->setLiczCalk(tryb);
}

void ProstyUAR::setModel(std::vector<double> A, std::vector<double> B, int k, double z) {

    if (model) {

        model->setWspA(A);
        model->setWspB(B);
        model->setOpoznienie(k);
        model->setZaklocenia(z);
    }
}

void ProstyUAR::setOgraniczenia(double umin, double umax, double ymin, double ymax, bool aktywne) {

    if (czyWlasciciel || model) {

        model->setOgraniczeniaU(umin, umax);
        model->setOgraniczeniaY(ymin, ymax);
        model->setOgraniczenia(aktywne);
    }
}
