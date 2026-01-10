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

    przygotujWykres(ui->chartViewY, seriaY, "Wyjście obiektu y(t)", 0);
    przygotujWykres(ui->chartViewYzad, seriaYzad, "Wartość zadana y_zad(t)", 1);
    przygotujWykres(ui->chartViewU, seriaU, "Sterowanie u(t)", 2);
    przygotujWykres(ui->chartViewE, seriaE, "Uchyb e(t)", 3);

    connect(symulacja, &Symulacja::noweDane, this, &MainWindow::aktualizujWykresy);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::przygotujWykres(QChartView *view, QLineSeries *series, QString tytul, int index) {

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tytul);
    chart->legend()->hide();

    osX[index] = new QValueAxis();
    osX[index]->setRange(0, 10);
    chart->addAxis(osX[index], Qt::AlignBottom);
    series->attachAxis(osX[index]);

    osY[index] = new QValueAxis();
    osY[index]->setRange(-2, 2);
    chart->addAxis(osY[index], Qt::AlignLeft);
    series->attachAxis(osY[index]);

    view->setChart(chart);
    view->setRenderHint(QPainter::Antialiasing);
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

void MainWindow::aktualizujWykresy(double t, double y, double y_zad, double u, double e) {

    seriaY->append(t, y);
    seriaYzad->append(t, y_zad);
    seriaU->append(t, u);
    seriaE->append(t, e);

    double oknoCzasu = 10.0;
    if (t > oknoCzasu) {

        for(int i=0; i<4; i++) {

            osX[i]->setRange(t - oknoCzasu, t);
        }
    }

    osY[0]->setRange(-5, 5);
}

void MainWindow::on_btnStart_clicked() {

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

    for(int i=0; i<4; i++) {

        if(osX[i]) osX[i]->setRange(0, 10);
    }
}

void MainWindow::on_spinKp_valueChanged(double arg1)
{

    double k = ui->spinKp->value();
    double ti = ui->spinTi->value();
    double td = ui->spinTd->value();

    symulacja->ustawPID(k, ti, td);
}
