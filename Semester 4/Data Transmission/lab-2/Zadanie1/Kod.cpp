#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main() {
	std::vector<double> IM;
	std::vector<double> RE;
	std::vector<double> x;
	x.push_back(1);
	x.push_back(-1);
	x.push_back(1);
	x.push_back(-1);
	x.push_back(5);
	x.push_back(4);
	x.push_back(3);
	x.push_back(2);
	int N = size(x);
	double a = 0.0;
	double b = 0.0;
	//std::cout << x[0];
	//Wzór DFT
	for (int k = 0; k < N; k++) {
		for (int n = 0; n < N; n++) {
			 b+=(x[n] * (sin((-2.0 * M_PI * k * n) / N)));
			 a+=(x[n] * (cos((-2.0 * M_PI * k * n) / N)));
		}
		IM.push_back(b);
		RE.push_back(a);
		a = 0;
		b = 0;
	}
	for (int i = 0; i < N; i++) {
		std::cout << "a=" << RE[i] << " b=" << IM[i] << std::endl;
	}

	return 0;
}