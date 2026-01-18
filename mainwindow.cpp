#include <QDebug>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    symulacja = new Symulacja(this);

    seriaY = new QLineSeries();
    seriaYzad = new QLineSeries();
    seriaU = new QLineSeries();
    seriaE = new QLineSeries();
    seriaP = new QLineSeries();
    seriaI = new QLineSeries();
    seriaD = new QLineSeries();

    stylizujSerie(seriaY, Qt::blue, "Wyjście y(t)");
    stylizujSerie(seriaYzad, Qt::red, "Wartość zadana y_zad(t)");
    stylizujSerie(seriaE, Qt::magenta, "Uchyb e(t)");
    stylizujSerie(seriaU, Qt::darkGreen, "Sterowanie u(t)");
    stylizujSerie(seriaP, Qt::red, "P");
    stylizujSerie(seriaI, Qt::green, "I");
    stylizujSerie(seriaD, Qt::blue, "D");

    QChart *chart1 = new QChart();
    QChartView *chartViewY = new QChartView(chart1);
    chart1->addSeries(seriaY);
    chart1->addSeries(seriaYzad);
    chart1->setTitle("Regulacja (y vs y_zad)");
    ui->horizontalLayout_2->addWidget(chartViewY);
    przygotujWykres(chartViewY, chart1, {seriaY, seriaYzad}, 0);

    QChart *chart2 = new QChart();
    QChartView *chartViewYzad = new QChartView(chart2);
    chart2->addSeries(seriaE);
    chart2->setTitle("Uchyb e(t)");
    ui->horizontalLayout_2->addWidget(chartViewYzad);
    przygotujWykres(chartViewYzad, chart2, {seriaE}, 1);

    QChart *chart3 = new QChart();
    QChartView *chartViewU = new QChartView(chart3);
    chart3->addSeries(seriaU);
    chart3->setTitle("Sterowanie u(t)");
    ui->horizontalLayout_3->addWidget(chartViewU);
    przygotujWykres(chartViewU, chart3, {seriaU}, 2);

    QChart *chart4 = new QChart();
    QChartView *chartViewE = new QChartView(chart4);
    chart4->addSeries(seriaP);
    chart4->addSeries(seriaI);
    chart4->addSeries(seriaD);
    chart4->setTitle("Składowe PID");
    ui->horizontalLayout_3->addWidget(chartViewE);
    przygotujWykres(chartViewE, chart4, {seriaP, seriaI, seriaD}, 3);

    connect(symulacja, &Symulacja::noweDane, this, &MainWindow::aktualizujWykresy);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::przygotujWykres(QChartView *view, QChart *chart, const QList<QLineSeries*> &serieLista, int index) {

    osX[index] = new QValueAxis();
    osX[index]->setRange(0, 5);
    chart->addAxis(osX[index], Qt::AlignBottom);
    osX[index]->setTitleText("Czas [s]");

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
    pen.setWidthF(1.5);
    series->setPen(pen);
    series->setName(nazwa);
    //series->setUseOpenGL(true);
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

    const int maxProbki = 400;

    while (seriaY->count() > maxProbki) {

        seriaY->remove(0);
        seriaYzad->remove(0);
        seriaU->remove(0);
        seriaE->remove(0);
        seriaP->remove(0);
        seriaI->remove(0);
        seriaD->remove(0);
    }

    if (seriaY->count() > 1) {

        double minX = seriaY->at(0).x();
        double maxX = seriaY->at(seriaY->count()-1).x();

        for(int i=0; i<4; i++) {

            if(osX[i]) osX[i]->setRange(minX, maxX);
        }
    }

    dopasujZakresY(osY[0], {seriaY, seriaYzad});
    dopasujZakresY(osY[1], {seriaE});
    dopasujZakresY(osY[2], {seriaU});
    dopasujZakresY(osY[3], {seriaP, seriaI, seriaD});

    if (seriaY->count() > 0) {

        double minX = seriaY->at(0).x();
        double maxX = seriaY->at(seriaY->count()-1).x();

        for(int i=0; i<4; i++) {

            if(osX[i]) osX[i]->setRange(minX, maxX);
        }
    }
}

void MainWindow::dopasujZakresY(QValueAxis *os, const QList<QLineSeries*> &serie) {

    double minVal = 1e9;
    double maxVal = -1e9;
    bool znalezionoDane = false;

    for (QLineSeries *seria : serie) {

        if (seria->count() == 0) continue;

        const auto &punkty = seria->pointsVector();

        for (const QPointF &p : punkty) {

            if (p.y() < minVal) minVal = p.y();
            if (p.y() > maxVal) maxVal = p.y();
            znalezionoDane = true;
        }
    }

    if (!znalezionoDane) return;

    if (std::abs(maxVal - minVal) < 0.0001) {

        maxVal += 1.0;
        minVal -= 1.0;
    }

    double margines = (maxVal - minVal) * 0.05;
    if (margines == 0) margines = 0.1;

    os->setRange(minVal - margines, maxVal + margines);
}

void MainWindow::on_btnStart_clicked() {

    przeslijNastawy();
    symulacja->ustawInterwalTimer(ui->spinInterwal->value());
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

void MainWindow::on_btnKonfiguracja_clicked() {

    opcjeSymulacji okno(this);

    std::vector<double> aktA = symulacja->pobierzA();
    std::vector<double> aktB = symulacja->pobierzB();
    int aktK = symulacja->pobierzK();
    double aktZ = symulacja->pobierzZ();
    double aktUmin = symulacja->pobierzUmin();
    double aktUmax = symulacja->pobierzUmax();
    double aktYmin = symulacja->pobierzYmin();
    double aktYmax = symulacja->pobierzYmax();
    bool aktAktywne = symulacja->pobierzOgr();

    okno.setParametry(aktA, aktB, aktK, aktZ, aktUmin, aktUmax, aktYmin, aktYmax, aktAktywne);

    if (okno.exec() == QDialog::Accepted) {

        std::vector<double> noweA = okno.getA();
        std::vector<double> noweB = okno.getB();
        int noweK = okno.getK();
        double noweZ = okno.getZ();
        double noweUmin = okno.getUmin();
        double noweUmax = okno.getUmax();
        double noweYmin = okno.getYmin();
        double noweYmax = okno.getYmax();
        bool noweAktywne = okno.getOgr();

        symulacja->ustawModel(noweA, noweB, noweK, noweZ);
        symulacja->ustawOgraniczeniaModelu(noweUmin, noweUmax, noweYmin, noweYmax, noweAktywne);
    }
}

void MainWindow::on_spinKp_valueChanged(double) { przeslijNastawy(); }
void MainWindow::on_spinTi_valueChanged(double) { przeslijNastawy(); }
void MainWindow::on_spinTd_valueChanged(double) { przeslijNastawy(); }
void MainWindow::on_comboTrybCalk_currentIndexChanged(int index) { symulacja->ustawTrybPID(index); }
void MainWindow::on_btnResetCalki_clicked() { ui->spinTi->setValue(0.0); symulacja->zresetujCalkePID(); }

void MainWindow::on_comboTyp_currentIndexChanged(int) { przeslijNastawy(); }
void MainWindow::on_spinAmp_valueChanged(double)      { przeslijNastawy(); }
void MainWindow::on_spinS_valueChanged(double)        { przeslijNastawy(); }
void MainWindow::on_spinOkres_valueChanged(double)    { przeslijNastawy(); }
void MainWindow::on_spinWyp_valueChanged(double)      { przeslijNastawy(); }

void MainWindow::on_spinInterwal_valueChanged(int arg1) { if(symulacja) symulacja->ustawInterwalTimer(arg1); }

void MainWindow::przeslijNastawy()
{

    double kp = ui->spinKp->value();
    double ti = ui->spinTi->value();
    double td = ui->spinTd->value();
    symulacja->ustawPID(kp, ti, td);

    int typ = ui->comboTyp->currentIndex();
    double amp = ui->spinAmp->value();
    double S = ui->spinS->value();
    double okres = ui->spinOkres->value();
    double p = ui->spinWyp->value();
    symulacja->ustawGenerator(typ, amp, S, okres, p);
}

void MainWindow::on_actionZapisz_konfiguracj_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz konfigurację", "", "Pliki JSON (*.json)");
    if (fileName.isEmpty()) return;

    QJsonObject config = symulacja->zapiszKonfiguracje();
    QJsonDocument doc(config);

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {

        file.write(doc.toJson());
        file.close();
        statusBar()->showMessage("Zapisano konfigurację: " + fileName, 3000);
    } else {

        QMessageBox::critical(this, "Błąd", "Nie udało się zapisać pliku!");
    }
}


void MainWindow::on_actionWczytaj_konfiguracj_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj konfigurację", "", "Pliki JSON (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {

        QMessageBox::critical(this, "Błąd", "Nie udało się otworzyć pliku!");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {

        QMessageBox::critical(this, "Błąd", "Niepoprawny format JSON!");
        return;
    }

    symulacja->wczytajKonfiguracje(doc.object());

    const QSignalBlocker blocker1(ui->spinKp);
    const QSignalBlocker blocker2(ui->spinTi);
    const QSignalBlocker blocker3(ui->spinTd);
    const QSignalBlocker blocker4(ui->comboTrybCalk);
    const QSignalBlocker blocker5(ui->spinAmp);
    const QSignalBlocker blocker6(ui->spinS);
    const QSignalBlocker blocker7(ui->spinOkres);
    const QSignalBlocker blocker8(ui->spinWyp);
    const QSignalBlocker blocker9(ui->comboTyp);
    const QSignalBlocker blocker10(ui->spinInterwal);

    ui->spinKp->setValue(symulacja->pobierzKp());
    ui->spinTi->setValue(symulacja->pobierzTi());
    ui->spinTd->setValue(symulacja->pobierzTd());
    ui->comboTrybCalk->setCurrentIndex(symulacja->pobierzTryb());

    ui->comboTyp->setCurrentIndex(symulacja->pobierzTypGeneratora());
    ui->spinAmp->setValue(symulacja->pobierzAmplituda());
    ui->spinS->setValue(symulacja->pobierzOffset());
    ui->spinOkres->setValue(symulacja->pobierzOkres());
    ui->spinWyp->setValue(symulacja->pobierzWypelnienie());

    ui->spinInterwal->setValue(symulacja->pobierzInterwal());

    QMessageBox::information(this, "Sukces", "Wczytano parametry.");
}

