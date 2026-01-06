#include "ModelARX.h"
#include <numeric>
#include <algorithm>

ModelARX::ModelARX(vector<double> A, vector<double> B, int k, double z)
	: wspA(A), wspB(B), opoznienie_k(k), zaklocenia(z), dystrybucja(0.0, z > 0.0 ? z : 1.0) {

	historiaU.resize(B.size(), 0.0);
	historiaY.resize(A.size(), 0.0);
	buforOpoznienia.resize(k, 0.0);
}

double ModelARX::saturacja(double wartosc, double min, double max) {

	if (!ograniczenia) return wartosc; 

	if (wartosc > max) { return max; }
	else if (wartosc < min) { return min; }
	else return wartosc;
}

void ModelARX::setWspA(std::vector<double> noweA) {
	
	if (noweA.empty()) { return; }
	wspA = noweA;
	historiaY.resize(wspA.size(), 0.0);
}

void ModelARX::setWspB(std::vector<double> noweB) {
	
	if (noweB.empty()) { return; }
	wspB = noweB;
	historiaU.resize(wspB.size(), 0.0);
}

void ModelARX::setOpoznienie(int noweK) {
	
	if (noweK < 1) noweK = 1;
	opoznienie_k = noweK;
	buforOpoznienia.resize(opoznienie_k, 0.0);
}

void ModelARX::setZaklocenia(double noweZ) {
	
	zaklocenia = noweZ;
	using param_t = normal_distribution<double>::param_type;
	dystrybucja.param(param_t(0.0, noweZ > 0.0 ? noweZ : 1.0));
}

double ModelARX::symuluj(double u_wej) {

	double u = saturacja(u_wej, u_min, u_max);

	double u_do_obliczen = buforOpoznienia.front();
	buforOpoznienia.pop_front();
	buforOpoznienia.push_back(u);

	historiaU.push_front(u_do_obliczen);
	if (historiaU.size() > wspB.size()) { historiaU.pop_back(); }

	double suma_B = 0.0;
	for (size_t i = 0; i < wspB.size(); ++i) {

		suma_B += wspB[i] * historiaU[i];
	}

	double suma_A = 0.0;
	for (size_t i = 0; i < wspA.size(); ++i) {

		suma_A += wspA[i] * historiaY[i];
	}

	double y_nowe = suma_B - suma_A;

	if (zaklocenia > 0.0001) { y_nowe += dystrybucja(generator); }

	double y_wyj = saturacja(y_nowe, y_min, y_max);

	historiaY.push_front(y_wyj);
	if (historiaY.size() > wspA.size()) { historiaY.pop_back(); }

	return y_wyj;
}

double ModelARX::getWyjscie() const {
	
	if (historiaY.empty()) return 0.0;
	return historiaY.front();
}