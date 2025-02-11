#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

//Funkcja z zadania 1 - nr 11
double x(int f, double t, int fi){
	double w = ((0.45 * cos(2 * M_PI * f * t + fi)) / (t + 0.101)) + cos(2 * M_PI * (f / 4) * t + 2.5 * fi);
	return w;
}

//Funkcje z zadania 2, zestaw nr 9
double y(int f, double t, int fi) {
	double xt = x(f, t, fi);
	double yt = abs((pow(xt, 2) / (cos(xt) + 2)) * sin(4 * pow(t, 2)) - 0.12);
	return yt;
}

double z(int f, double t, int fi) {
	double xt = x(f, t, fi);
	double yt = y(f, t, fi);
	double zt = xt * (sqrt(abs(xt + yt)) - cos(10 * xt * yt));
	return zt;
}

double v(int f, double t, int fi) {
	double xt = x(f, t, fi);
	double yt = y(f, t, fi);
	double zt = z(f, t, fi);
	double vt = 1 / 2 * zt * cos(6 * yt / M_PI * t) - t * sin(2 * M_PI * t);
	return vt;
}

int main() {
	//Zadanie 2 -> zestaw funkcji nr 9 | x(t) -> funkcja 11 z zadania 1
	std::vector<double> tabx;
	std::vector<double> taby;
	std::vector<double> tabz;
	std::vector<double> tabv;
	int f = 50;
	double fs = 10000;
	double Tc = 1;
	int fi = 1;
	int N = Tc * fs;
	int fmax = fs / 2;
	double t;
	for (int n = 0; n < N; n++) {
		t = n / fs;
		tabx.push_back(x(f, t, fi));
		taby.push_back(y(f, t, fi));
		tabz.push_back(z(f, t, fi));
		tabv.push_back(v(f, t, fi));
	}
	plt::plot(tabx);
	plt::title("x(t)");
	plt::show();
	plt::plot(taby);
	plt::title("y(t)");
	plt::show();
	plt::plot(tabz);
	plt::title("z(t)");
	plt::show();
	plt::plot(tabv);
	plt::title("v(t)");
	plt::show();
	return 0;
}