#include "Symulacja.h"

Symulacja::Symulacja(QObject *parent) : QObject(parent) {

    krokCzasu = 0.01;
    int Tt_ms = 200;

    uar = new ProstyUAR();

    generator = new Generator();
    generator->setTt(Tt_ms);

    timer = new QTimer(this);
    timer->setInterval(Tt_ms);
    connect(timer, &QTimer::timeout, this, &Symulacja::wykonajKrok);

    czasSymulacji = 0.0;
    numerKroku = 0;
}

void Symulacja::start() {

    if (!timer->isActive())
        timer->start();
}

void Symulacja::stop() {

    timer->stop();
}

void Symulacja::reset() {

    stop();
    czasSymulacji = 0.0;
    numerKroku = 0;
    if (uar) uar->reset();
}

bool Symulacja::czyDziala() const {

    return timer->isActive();
}

void Symulacja::wykonajKrok() {

    double y_zad = generator->generuj(static_cast<int>(numerKroku));

    double y_wyj = uar->symuluj(y_zad);

    double u_ster = uar->getSterowanie();
    double e_uchyb = uar->getUchyb();

    emit noweDane(czasSymulacji, y_wyj, y_zad, u_ster, e_uchyb);

    czasSymulacji += krokCzasu;
    numerKroku++;
}

void Symulacja::ustawPID(double k, double ti, double td) {

    if (uar) uar->setPID(k, ti, td);
}

void Symulacja::ustawModel(std::vector<double> A, std::vector<double> B, int k, double z) {

    if (uar) uar->setModel(A, B, k, z);
}

void Symulacja::ustawGenerator(int typIndex, double amp, double T, double p) {

    Generator::TypSygnalu typ = Generator::TypSygnalu::Staly;

    if (typIndex == 1) typ = Generator::TypSygnalu::Prostokatny;
    else if (typIndex == 2) typ = Generator::TypSygnalu::Sinusoidalny;

    generator->setTyp(typ);
    generator->setA(amp);
    generator->setTrz(T);
    generator->setp(p);
}
