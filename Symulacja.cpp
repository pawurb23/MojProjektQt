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
    double p = uar->getP();
    double i = uar->getI();
    double d = uar->getD();

    emit noweDane(czasSymulacji, y_wyj, y_zad, u_ster, e_uchyb, p, i, d);

    czasSymulacji += krokCzasu;
    numerKroku++;
}

void Symulacja::ustawPID(double k, double ti, double td) {

    if (uar) uar->setPID(k, ti, td);
}

void Symulacja::ustawTrybPID(int index) {

    auto tryb = (index == 0) ? RegulatorPID::LiczCalk::Zew : RegulatorPID::LiczCalk::Wew;
    if(uar) uar->setTrybPID(tryb);
}

void Symulacja::zresetujCalkePID() {

    if(uar) uar->resetCalki();
}

void Symulacja::ustawLimityCalki(double min, double max) {

    if (uar) { uar->setLimityCalki(min, max); }
}

void Symulacja::ustawAntiWindup(bool aktywne) {

    if (uar) uar->setAntiWindup(aktywne);
}

void Symulacja::ustawModel(std::vector<double> A, std::vector<double> B, int k, double z) {

    if (uar) uar->setModel(A, B, k, z);
}

void Symulacja::ustawOgraniczeniaModelu(double umin, double umax, double ymin, double ymax, bool aktywne) {

    if(uar) uar->setOgraniczenia(umin, umax, ymin, ymax, aktywne);
}

void Symulacja::ustawGenerator(int typIndex, double amp, double S, double T, double p) {

    Generator::TypSygnalu typ = Generator::TypSygnalu::Staly;

    if (typIndex == 1) typ = Generator::TypSygnalu::Prostokatny;
    else if (typIndex == 2) typ = Generator::TypSygnalu::Sinusoidalny;

    generator->setTyp(typ);
    generator->setA(amp);
    generator->setS(S);
    generator->setTrz(T);
    generator->setp(p);
}

void Symulacja::ustawInterwalTimer(int ms) {

    timer->setInterval(ms);
}
