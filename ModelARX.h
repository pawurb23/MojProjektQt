#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <random>

using namespace std;

class ModelARX {
private:

	//parametry
	vector<double> wspA;
	vector<double> wspB;
	int opoznienie_k;
	double zaklocenia;

	//ograniczenia
	double u_min = -10.0, u_max = 10.0;
	double y_min = -10.0, y_max = 10.0;
	bool ograniczenia = true;

	double saturacja(double wartosc, double min, double max);

	//pamiêæ
	deque<double> historiaU;
	deque<double> historiaY;
	deque<double> buforOpoznienia;

	//generator zaklóceñ
	default_random_engine generator;
	normal_distribution<double> dystrybucja;

public:

	ModelARX(vector<double> A, vector<double> B, int k = 1, double z = 0.0);

	double symuluj(double u_wej);

	void setWspA(vector<double> noweA);
	void setWspB(vector<double> noweB);
	void setOpoznienie(int noweK);
	void setZaklocenia(double noweZ);
	void setOgraniczeniaU(double min, double max) { u_min = min, u_max = max; }
	void setOgraniczeniaY(double min, double max) { y_min = min, y_max = max; }
	void setOgraniczenia(bool aktywne) { ograniczenia = aktywne; }

	vector<double> getWspA() { return wspA; }
	vector<double> getWspB() { return wspB; }
	int getOpoznienie() { return opoznienie_k; }
	double getZaklocenie() { return zaklocenia; }
	double getUmin() { return u_min; }
	double getUmax() { return u_max; }
	double getYmin() { return y_min; }
	double getYmax() { return y_max; }
	double getWyjscie() const;
	bool getOgraniczeniaAktywne() { return ograniczenia; }
};