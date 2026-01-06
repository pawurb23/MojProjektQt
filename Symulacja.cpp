#include "Symulacja.h"

Symulacja::Symulacja(QObject *parent) : QObject(parent)
{

    std::vector<double> startA = { -0.5, 1.0, -2.0 };
    std::vector<double> startB = { 0.5, -1.0, 2.0 };

    // Tworzymy obiekty (pamiętaj o #include w .h)
    // UWAGA: Tutaj zakładam, że ProstyUAR ma odpowiedni konstruktor.
    // Jeśli nie, musisz stworzyć osobno ModelARX i RegulatorPID i przekazać je tutaj.
    uar = new ProstyUAR(/* tu parametry jeśli są potrzebne */);
    generator = new Generator(/* tu parametry */);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Symulacja::wykonajKrok);

    czasSymulacji = 0.0;
    krokCzasu = 0.01; // np. 10ms (100Hz)
}

void Symulacja::start()
{
    timer->start(10);
}

void Symulacja::stop()
{
    timer->stop();
}

void Symulacja::reset()
{
    stop();
    czasSymulacji = 0.0;
    // Tu zresetuj pamięć modelu i regulatora, jeśli masz takie metody w backendzie
    // np. systemUAR->reset();
}

bool Symulacja::czyDziala() const
{
    return timer->isActive();
}

// --- Główna pętla symulacji ---
void Symulacja::wykonajKrok()
{
    // 1. Pobierz wartość zadaną z generatora dla aktualnego czasu
    double y_zad = generator->generuj(czasSymulacji);

    double y_wyj = uar->symuluj(y_zad);

    // Jeśli ProstyUAR nie udostępnia 'u' i 'e', musisz dodać gettery w ProstyUAR,
    // żeby je tu pobrać do wykresów.
    double u_ster = uar->getSterowanie(); // (Wymaga dopisania w ProstyUAR)
    double e_uchyb = uar->getUchyb();     // (Wymaga dopisania w ProstyUAR)

    emit noweDane(czasSymulacji, y_wyj, y_zad, u_ster, e_uchyb);

    czasSymulacji += krokCzasu;
}

// --- Metody przesyłające nastawy (Fasada) ---

void Symulacja::ustawPID(double k, double ti, double td)
{
    uar->setPID(k, ti, td); // (Musisz mieć taką metodę w ProstyUAR)
}

void Symulacja::ustawModel(std::vector<double> A, std::vector<double> B, int k, double z)
{
    uar->setModel(A, B, k, z); // (Wymaga dopisania w ProstyUAR)
}

void Symulacja::ustawGenerator(TypSygnalu typ, double A, double T, double p)
{
    generator->setTyp(typ);
    generator->setA(A);
    generator->setTrz(T);
    generator->setp(p);
}
