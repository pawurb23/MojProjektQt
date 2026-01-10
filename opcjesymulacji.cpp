#include "opcjesymulacji.h"
#include "ui_opcjesymulacji.h"

opcjeSymulacji::opcjeSymulacji(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::opcjeSymulacji)
{
    ui->setupUi(this);
}

opcjeSymulacji::~opcjeSymulacji()
{
    delete ui;
}

std::vector<double> opcjeSymulacji::parsujWektor(QString tekst) const {

    std::vector<double> wynik;
    QStringList lista = tekst.split(","); // Dzielimy po przecinku
    for(const QString &str : lista) {

        bool ok;
        double val = str.toDouble(&ok);
        if(ok) wynik.push_back(val);
    }

    return wynik;
}

std::vector<double> opcjeSymulacji::getA() const {

    return parsujWektor(ui->lineA->text());
}

std::vector<double> opcjeSymulacji::getB() const {

    return parsujWektor(ui->lineB->text());
}

int opcjeSymulacji::getK() const {

    return ui->spinK->value();
}

double opcjeSymulacji::getZ() const {

    return ui->spinZ->value();
}

void opcjeSymulacji::setParametry(std::vector<double> a, std::vector<double> b, int k, double z) {

    QString strA;
    for(double val : a) strA += QString::number(val) + ",";
    if(!strA.isEmpty()) strA.chop(1);

    QString strB;
    for(double val : b) strB += QString::number(val) + ",";
    if(!strB.isEmpty()) strB.chop(1);

    ui->lineA->setText(strA);
    ui->lineB->setText(strB);
    ui->spinK->setValue(k);
    ui->spinZ->setValue(z);
}

void opcjeSymulacji::on_buttonBox_accepted()
{

}


void opcjeSymulacji::on_buttonBox_rejected()
{

}

