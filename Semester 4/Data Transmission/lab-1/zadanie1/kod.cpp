#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double funkcja11(int f, double t, int fi) {
	double w = ((0.45 * cos(2 * M_PI * f * t + fi)) / (t + 0.101)) + cos(2 * M_PI * (f / 4) * t + 2.5 * fi);
	return w;
}

int main() {

	//Zadanie 1 -> funkcja 11
	std::vector<double> tab1;
	int f = 50;
	double fs = 10000;
	double Tc = 1;
	int fi = 1;
	int N = Tc * fs;
	int fmax = fs / 2;
	double t;
	for (int n = 0; n < N; n++) {
		t = n / fs;
		tab1.push_back(funkcja11(f, t, fi));
	}
	plt::plot(tab1);
	plt::show();
	return 0;
}