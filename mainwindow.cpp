#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    symulacja = new Symulacja(this);

    seriaY = new QLineSeries();
    seriaYzad = new QLineSeries();
    seriaU = new QLineSeries();
    seriaE = new QLineSeries();
    seriaP = new QLineSeries();
    seriaI = new QLineSeries();
    seriaD = new QLineSeries();

    stylizujSerie(seriaY, Qt::blue, "Wyjście y(t)");
    stylizujSerie(seriaYzad, Qt::red, "Zadana y_zad(t)");
    stylizujSerie(seriaE, Qt::magenta, "Uchyb e(t)");
    stylizujSerie(seriaU, Qt::darkGreen, "Sterowanie u(t)");
    stylizujSerie(seriaP, Qt::red, "P");
    stylizujSerie(seriaI, Qt::green, "I");
    stylizujSerie(seriaD, Qt::blue, "D");

    QChart *chart1 = new QChart();
    chart1->addSeries(seriaY);
    chart1->addSeries(seriaYzad);
    chart1->setTitle("Regulacja (y vs y_zad)");
    przygotujWykres(ui->chartViewY, chart1, {seriaY, seriaYzad}, 0);

    QChart *chart2 = new QChart();
    chart2->addSeries(seriaE);
    chart2->setTitle("Uchyb e(t)");
    przygotujWykres(ui->chartViewYzad, chart2, {seriaE}, 1);

    QChart *chart3 = new QChart();
    chart3->addSeries(seriaU);
    chart3->setTitle("Sterowanie u(t)");
    przygotujWykres(ui->chartViewU, chart3, {seriaU}, 2);

    QChart *chart4 = new QChart();
    chart4->addSeries(seriaP);
    chart4->addSeries(seriaI);
    chart4->addSeries(seriaD);
    chart4->setTitle("Składowe PID");
    przygotujWykres(ui->chartViewE, chart4, {seriaP, seriaI, seriaD}, 3);

    connect(symulacja, &Symulacja::noweDane, this, &MainWindow::aktualizujWykresy);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::przygotujWykres(QChartView *view, QChart *chart, const QList<QLineSeries*> &serieLista, int index) {

    osX[index] = new QValueAxis();
    osX[index]->setRange(0, 10);
    chart->addAxis(osX[index], Qt::AlignBottom);

    osY[index] = new QValueAxis();
    osY[index]->setRange(-10, 10);
    chart->addAxis(osY[index], Qt::AlignLeft);

    for(auto s : serieLista) {
        s->attachAxis(osX[index]);
        s->attachAxis(osY[index]);
    }

    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(chart);
}

void MainWindow::stylizujSerie(QLineSeries *series, QColor color, QString nazwa) {

    QPen pen(color);
    pen.setWidthF(1.0);
    series->setPen(pen);
    series->setName(nazwa);
}

void MainWindow::on_btnKonfiguracja_clicked() {

    opcjeSymulacji okno(this);

    if (okno.exec() == QDialog::Accepted) {

        std::vector<double> A = okno.getA();
        std::vector<double> B = okno.getB();
        int k = okno.getK();
        double z = okno.getZ();

        symulacja->ustawModel(A, B, k, z);
    }
}

void MainWindow::aktualizujWykresy(double t, double y, double y_zad, double u, double e, double up, double ui, double ud) {

    qDebug() << "Czas:" << t << " Zad:" << y_zad << " Wyj:" << y << " U:" << u;

    seriaY->append(t, y);
    seriaYzad->append(t, y_zad);
    seriaU->append(t, u);
    seriaE->append(t, e);
    seriaP->append(t, up);
    seriaI->append(t, ui);
    seriaD->append(t, ud);

    double obecnyMax = std::max({y, y_zad, u, e});
    double obecnyMin = std::min({y, y_zad, u, e});

    bool zmianaSkali = false;
    if (obecnyMax > maxY) { maxY = obecnyMax + 1.0; zmianaSkali = true; }
    if (obecnyMin < minY) { minY = obecnyMin - 1.0; zmianaSkali = true; }

    if (zmianaSkali) {
        for(int i=0; i<4; i++) {

            osY[i]->setRange(minY, maxY);
        }
    }

    double oknoCzasu = 10.0;
    if (t > oknoCzasu) {

        for(int i=0; i<4; i++) {

            osX[i]->setRange(t - oknoCzasu, t);
        }
    } else {

        for(int i=0; i<4; i++) osX[i]->setRange(0, 10);
    }
}

void MainWindow::on_btnStart_clicked() {

    przeslijNastawy();
    symulacja->start();
}

void MainWindow::on_btnStop_clicked()
{
    symulacja->stop();
}

void MainWindow::on_btnReset_clicked()
{
    symulacja->reset();

    seriaY->clear();
    seriaYzad->clear();
    seriaU->clear();
    seriaE->clear();
    seriaP->clear();
    seriaI->clear();
    seriaD->clear();

    minY = -1.0; maxY = 1.0;

    for(int i=0; i<4; i++) {

        if(osX[i]) osX[i]->setRange(0, 10);
    }
}

void MainWindow::on_spinKp_valueChanged(double)
{

    double k = ui->spinKp->value();
    double ti = ui->spinTi->value();
    double td = ui->spinTd->value();

    symulacja->ustawPID(k, ti, td);
}

void MainWindow::przeslijNastawy()
{

    double kp = ui->spinKp->value();
    double ti = ui->spinTi->value();
    double td = ui->spinTd->value();
    symulacja->ustawPID(kp, ti, td);

    int typ = ui->comboTyp->currentIndex();
    double amp = ui->spinAmp->value();
    double okres = ui->spinOkres->value();
    double p = ui->spinWyp->value();
    symulacja->ustawGenerator(typ, amp, okres, p);
}
