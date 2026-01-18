#ifndef OPCJESYMULACJI_H
#define OPCJESYMULACJI_H

#include <QDialog>
#include <vector>
#include <QString>
#include <QStringList>

namespace Ui {
class opcjeSymulacji;
}

class opcjeSymulacji : public QDialog
{
    Q_OBJECT

public:
    explicit opcjeSymulacji(QWidget *parent = nullptr);
    ~opcjeSymulacji();

    std::vector<double> getA() const;
    std::vector<double> getB() const;
    int getK() const;
    double getZ() const;
    double getUmin() const;
    double getUmax() const;
    double getYmin() const;
    double getYmax() const;
    bool getOgr() const;

    void setParametry(std::vector<double> a, std::vector<double> b, int k, double z,
                      double umin, double umax, double ymin, double ymax, bool active);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::opcjeSymulacji *ui;

    std::vector<double> parsujWektor(QString tekst) const;
};

#endif // OPCJESYMULACJI_H
