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
    void ustawModel(std::vector<double> A, std::vector<double> B, int k, double z);
    void ustawGenerator(int typ, double A, double T, double wypelnienie);

signals:

    void noweDane(double czas, double y_obiektu, double y_zadane, double sterowanie_u, double uchyb_e);

private slots:

    void wykonajKrok();

private:

    QTimer *timer;

    ProstyUAR *uar;
    Generator *generator;

    double czasSymulacji;
    double krokCzasu;
};

