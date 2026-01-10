#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

#include "Symulacja.h"
#include "opcjesymulacji.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void aktualizujWykresy(double t, double y, double y_zad, double u, double e);
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void on_btnReset_clicked();
    void on_btnKonfiguracja_clicked();
    void on_spinKp_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    Symulacja* symulacja;

    double minY = -1.0, maxY = 1.0;

    QLineSeries *seriaY;
    QLineSeries *seriaYzad;
    QLineSeries *seriaU;
    QLineSeries *seriaE;

    QValueAxis *osX[4];
    QValueAxis *osY[4];

    void przygotujWykres(QChartView *view, QLineSeries *series, QString tytul, int index);
    void przeslijNastawy();
};
#endif // MAINWINDOW_H
