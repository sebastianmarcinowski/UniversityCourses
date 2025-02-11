#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double u(double t) {
	double ut = 0.0;
	if (t >= 0 && t < 0.5) {
		ut = t * sqrt(-t + 0.7) * sin(22 * M_PI * t * cos(pow(t, 2)));
	}
	else if (t >= 0.5 && t < 1.3) {
		ut = log10((t + 1) * abs(sin(20 * pow(t, 3)))) - 0.4;
	}
	else if (t >= 1.3 && t < 2.2) {
		ut = (pow(t, 2) + 1) * sin(2 * M_PI * cos(4 * t));
	}
	else if (t >= 2.2 && t < 2.7) {
		ut = 0.5 * sin(20 * M_PI * t + (t / 3) + 2.3);
	}
	return ut;
}

int main() {

	//Zadanie 3 -> funkcja 5
	std::vector<double> tab1;
	int f = 50;
	double fs = 10000;
	double Tc = 1;
	int fi = 1;
	int N = fs*Tc;
	double t;

	for (int n = 0; n < N; n++) {
		t = n / fs;
		tab1.push_back(u(t));
	}

	plt::plot(tab1);
	plt::title("u(t)");
	plt::show();

	return 0;
}