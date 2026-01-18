#pragma once

#include <QObject>
#include <QTimer>
#include <vector>

#include "ModelARX.h"
#include "RegulatorPID.h"
#include "Generator.h"
#include "ProstyUAR.h"

class Symulacja : public QObject
{
    Q_OBJECT

public:
    explicit Symulacja(QObject *parent = nullptr);

    void start();
    void stop();
    void reset();
    bool czyDziala() const;

    void ustawPID(double k, double ti, double td);
    void ustawTrybPID(int index);
    void zresetujCalkePID();

    void ustawModel(std::vector<double> A, std::vector<double> B, int k, double z);
    void ustawOgraniczeniaModelu(double umin, double umax, double ymin, double ymax, bool aktywne);

    std::vector<double> pobierzA() const;
    std::vector<double> pobierzB() const;
    int pobierzK() const;
    double pobierzZ() const;
    double pobierzUmin() const;
    double pobierzUmax() const;
    double pobierzYmin() const;
    double pobierzYmax() const;
    bool pobierzOgr() const;

    void ustawGenerator(int typIndex, double amp, double S, double T, double p);

    void ustawInterwalTimer(int ms);

signals:

    void noweDane(double czas, double y_obiektu, double y_zadane, double sterowanie_u, double uchyb_e, double up, double ui, double ud);

private slots:
    void wykonajKrok();

private:
    QTimer *timer;

    ProstyUAR *uar;
    Generator *generator;

    double czasSymulacji;
    double krokCzasu;
    long long numerKroku;
};
