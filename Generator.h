#pragma once
#define _USE_MATH_DEFINES

#include <cmath>

using namespace std;

class Generator {
public:

	enum class TypSygnalu { Staly, Prostokatny, Sinusoidalny };

private:

	TypSygnalu typ;
	double A;
	double S;
	double Trz;
	double p;
	int Tt;

public:

	Generator();

	double generuj(int krok);

	void setTyp(TypSygnalu nowyTyp);
	void setA(double a);
	void setS(double s);
	void setTrz(double trz);
	void setp(double nowep);
	void setTt(int tt);

	TypSygnalu getTyp() { return typ; }
	double getA() { return A; }
	double getS() { return S; }
	double getTrz() { return Trz; }
	double getp() { return p; }
};