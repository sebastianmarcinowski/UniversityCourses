#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double funkcja7(double t, int H) {
	double bt =0.0;
	for (int h = 1; h <= H; h++) {
		bt += (sin(M_PI * t * (2 * pow(h, 2) + h))) / ((2 * pow(h, 2) * (2.5 + cos(h * M_PI) - 1)));
	}
	return bt;
}

int main() {
	//Zadanie 4 -> funkcja nr 7
	std::vector<double> tab1;
	std::vector<double> tab2;
	std::vector<double> tab3;

	double fs = 22050;
	double Tc = 1;
	int N = Tc * fs;
	int fmax = fs / 2;
	double t;
	for (int n = 0; n < N; n++) {
		t = n / fs;
		tab1.push_back(funkcja7(t, 2));
		tab2.push_back(funkcja7(t, 4));
		tab3.push_back(funkcja7(t, 20));
	}

	plt::plot(tab1);
	plt::title("b1(t)");
	plt::show();
	plt::plot(tab2);
	plt::title("b2(t)");
	plt::show();
	plt::plot(tab3);
	plt::title("b3(t)");
	plt::show();
	return 0;
}