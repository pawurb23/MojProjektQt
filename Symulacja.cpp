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

double Symulacja::pobierzKp() const { return uar ? uar->getRegulator().getStalaWzm() : 0; }
double Symulacja::pobierzTi() const { return uar ? uar->getRegulator().getStalaCalk() : 0; }
double Symulacja::pobierzTd() const { return uar ? uar->getRegulator().getStalaRoz() : 0; }

void Symulacja::zresetujCalkePID() {

    if(uar) {

        uar->resetCalki();
        double y = uar->getModel().getWyjscie();
        double y_zad = generator->generuj(numerKroku);
        double u = uar->getSterowanie();
        double e = uar->getUchyb();

        double p = uar->getP();
        double i = uar->getI();
        double d = uar->getD();

        emit noweDane(czasSymulacji, y, y_zad, u, e, p, i, d);
    }
}

void Symulacja::ustawModel(std::vector<double> A, std::vector<double> B, int k, double z) {

    if (uar) uar->setModel(A, B, k, z);
}

void Symulacja::ustawOgraniczeniaModelu(double umin, double umax, double ymin, double ymax, bool aktywne) {

    if(uar) uar->setOgraniczenia(umin, umax, ymin, ymax, aktywne);
}

std::vector<double> Symulacja::pobierzA() const {

    if (uar) return uar->getModelA();
    return {};
}

std::vector<double> Symulacja::pobierzB() const {

    if (uar) return uar->getModelB();
    return {};
}

int Symulacja::pobierzK() const {

    if (uar) return uar->getModelK();
    return 1;
}

double Symulacja::pobierzZ() const {

    if (uar) return uar->getModelZ();
    return 0.0;
}

double Symulacja::pobierzUmin() const { return uar ? uar->getModelUmin() : -10.0; }
double Symulacja::pobierzUmax() const { return uar ? uar->getModelUmax() : 10.0; }
double Symulacja::pobierzYmin() const { return uar ? uar->getModelYmin() : -10.0; }
double Symulacja::pobierzYmax() const { return uar ? uar->getModelYmax() : 10.0; }
bool Symulacja::pobierzOgr() const { return uar ? uar->getModelOgr() : true; }

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

QJsonObject Symulacja::zapiszKonfiguracje() const {

    QJsonObject json;

    QJsonObject jsonARX;
    QJsonArray arrayA, arrayB;
    for(double v : pobierzA()) arrayA.append(v);
    for(double v : pobierzB()) arrayB.append(v);

    jsonARX["A"] = arrayA;
    jsonARX["B"] = arrayB;
    jsonARX["k"] = pobierzK();
    jsonARX["z"] = pobierzZ();

    jsonARX["u_min"] = pobierzUmin();
    jsonARX["u_max"] = pobierzUmax();
    jsonARX["y_min"] = pobierzYmin();
    jsonARX["y_max"] = pobierzYmax();
    jsonARX["ograniczenia_aktywne"] = pobierzOgr();

    json["ModelARX"] = jsonARX;

    QJsonObject jsonPID;
    if(uar) {

        jsonPID["Kp"] = uar->getRegulator().getStalaWzm();
        jsonPID["Ti"] = uar->getRegulator().getStalaCalk();
        jsonPID["Td"] = uar->getRegulator().getStalaRoz();
        jsonPID["tryb"] = (int)uar->getRegulator().getLiczCalk();
    }
    json["PID"] = jsonPID;

    QJsonObject jsonGen;
    jsonGen["typ"] = pobierzTypGeneratora();
    jsonGen["amplituda"] = pobierzAmplituda();
    jsonGen["offset"] = pobierzOffset();
    jsonGen["okres"] = pobierzOkres();
    jsonGen["wypelnienie"] = pobierzWypelnienie();
    json["Generator"] = jsonGen;

    json["interwal_timer"] = timer->interval();

    return json;
}

void Symulacja::wczytajKonfiguracje(const QJsonObject &json) {

    if (json.contains("ModelARX")) {

        QJsonObject j = json["ModelARX"].toObject();

        std::vector<double> A, B;
        QJsonArray arrA = j["A"].toArray();
        QJsonArray arrB = j["B"].toArray();

        for(auto v : arrA) A.push_back(v.toDouble());
        for(auto v : arrB) B.push_back(v.toDouble());

        ustawModel(A, B, j["k"].toInt(), j["z"].toDouble());

        ustawOgraniczeniaModelu(j["u_min"].toDouble(), j["u_max"].toDouble(),
                                j["y_min"].toDouble(), j["y_max"].toDouble(),
                                j["ograniczenia_aktywne"].toBool());
    }


    if (json.contains("PID")) {

        QJsonObject j = json["PID"].toObject();

        ustawPID(j["Kp"].toDouble(), j["Ti"].toDouble(), j["Td"].toDouble());
    }

    if (json.contains("Generator")) {

        QJsonObject j = json["Generator"].toObject();

        ustawGenerator(j["typ"].toInt(), j["amplituda"].toDouble(),
                       j["offset"].toDouble(), j["okres"].toDouble(),
                       j["wypelnienie"].toDouble());
    }

    if (json.contains("interwal_timer")) {

        ustawInterwalTimer(json["interwal_timer"].toInt());
    }
}
