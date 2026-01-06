#include "Generator.h"

Generator::Generator() {

	typ = TypSygnalu::Staly;
	A = 1.0;
	S = 0.0;
	Trz = 10.0;
	p = 0.5;
	Tt = 200;
}

void Generator::setTyp(TypSygnalu nowyTyp) {typ = nowyTyp; }
void Generator::setA(double a) { A = a; }
void Generator::setS(double s) { S = s; }
void Generator::setTrz(double trz) { Trz = trz; }
void Generator::setp(double nowep) { p = nowep; }
void Generator::setTt(int tt) { Tt = tt; }

double Generator::generuj(int krok) {

	if (typ == TypSygnalu::Staly) { return S; }

	int kroki = static_cast<int>((Trz * 1000.0) / Tt);
	if (kroki < 1) kroki = 1;

	int pozycja = krok % kroki;

	if (typ == TypSygnalu::Prostokatny) {

		int prog = static_cast<int>(p * kroki);

		if (pozycja < prog) { return A + S; }
		else { return S; }
	}
	else if (typ == TypSygnalu::Sinusoidalny) {

		double postep = static_cast<double>(pozycja) / kroki;
		return A * sin(postep * 2.0 * M_PI) + S;
	}

	return 0.0;
}