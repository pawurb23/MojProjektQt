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

    void aktualizujWykresy(double t, double y, double y_zad, double u, double e, double up, double ui, double id);
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void on_btnReset_clicked();
    void on_btnKonfiguracja_clicked();

    void on_spinKp_valueChanged(double);
    void on_spinTi_valueChanged(double);
    void on_spinTd_valueChanged(double);
    void on_comboTrybCalk_currentIndexChanged(int index);
    void on_btnResetCalki_clicked();

    void on_comboTyp_currentIndexChanged(int index);
    void on_spinAmp_valueChanged(double);
    void on_spinS_valueChanged(double);
    void on_spinOkres_valueChanged(double);
    void on_spinWyp_valueChanged(double);

    void on_spinInterwal_valueChanged(int arg1);

    void on_actionZapisz_konfiguracj_triggered();

    void on_actionWczytaj_konfiguracj_triggered();

private:
    Ui::MainWindow *ui;
    Symulacja* symulacja;

    double minY = -1.0, maxY = 1.0;

    QLineSeries *seriaY;
    QLineSeries *seriaYzad;
    QLineSeries *seriaU;
    QLineSeries *seriaE;
    QLineSeries *seriaP;
    QLineSeries *seriaI;
    QLineSeries *seriaD;

    QValueAxis *osX[4];
    QValueAxis *osY[4];

    void przygotujWykres(QChartView *view, QChart *chart, const QList<QLineSeries*> &serieLista, int index);
    void stylizujSerie(QLineSeries *series, QColor color, QString nazwa);
    void przeslijNastawy();
};
#endif // MAINWINDOW_H
