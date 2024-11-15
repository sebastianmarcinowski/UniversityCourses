#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <cmath>
#include <string>
#include <random>
#include <time.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double x(int f, double t, int fi) {
	double w = ((0.45 * cos(2 * M_PI * f * t + fi)) / (t + 0.101)) + cos(2 * M_PI * (f / 4) * t + 2.5 * fi);
	return w;
}

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

double funkcja7(double t, int H) {
	double bt = 0.0;
	for (int h = 1; h <= H; h++) {
		bt += (sin(M_PI * t * (2 * pow(h, 2) + h))) / ((2 * pow(h, 2) * (2.5 + cos(h * M_PI) - 1)));
	}
	return bt;
}


void widmo(int N, double fs, std::vector<double> xn, std::string nazwa) {
	std::vector<double> IM;
	std::vector<double> RE;
	double a = 0.0;
	double b = 0.0;
	//std::cout << x[0];
	//DFT
	for (int k = 0; k < N; k++) {
		for (int n = 0; n < N; n++) {
			b += (xn[n] * (sin((-2.0 * M_PI * k * n) / N)));
			a += (xn[n] * (cos((-2.0 * M_PI * k * n) / N)));
		}
		IM.push_back(b);
		RE.push_back(a);
		a = 0;
		b = 0;
	}

	
	//Widmo amplitudowe
	std::vector<double> mk;
	
	for (int k = 0; k < (N / 2); k++) {
		mk.push_back(sqrt(pow(RE[k], 2) + pow(IM[k], 2)));
	}

	//Zamiana na skale decybelową
	std::vector<double> mkdb;
	for (int k = 0; k < (N/2); k++) {
		mkdb.push_back(10 * log10(mk[k]));
	}

	//Skala częstotliwości
	std::vector<int> fk;
	for (int k = 0; k < N / 2; k++) {
		fk.push_back(k * (fs / N));
	}
	//Wykres widma amplitudowego
	plt::plot(fk, mkdb);
	plt::title(nazwa);
	plt::xlabel("Czestotliwosc [Hz]");
	plt::ylabel("Amplituda [dB]");

	plt::show();

}

int main() {
	int f = 100;
	double fs = 10000;
	double Tc = 1;
	int fi = 1;
	int N = Tc * fs;
	int fmax = fs / 2;
	double t;

	std::vector<double> tabx;
	std::vector<double> taby;
	std::vector<double> tabz;
	std::vector<double> tabv;
	std::vector<double> tabu;
	std::vector<double> tabb1;
	std::vector<double> tabb2;
	std::vector<double> tabb3;
	for (int n = 0; n < N; n++) {
		t = n / fs;
		tabx.push_back(x(f, t, fi));
		taby.push_back(y(f, t, fi));
		tabz.push_back(z(f, t, fi));
		tabv.push_back(v(f, t, fi));
		tabu.push_back(u(t));
		tabb1.push_back(funkcja7(t, 2));
		tabb2.push_back(funkcja7(t, 4));
		tabb3.push_back(funkcja7(t, 20));
	}

	widmo(N, fs, tabx, "Widmo funkcji x");
	widmo(N, fs, taby, "Widmo funkcji y");
	widmo(N, fs, tabz, "Widmo funkcji z");
	widmo(N, fs, tabv, "Widmo funkcji v");
	widmo(N, fs, tabu, "Widmo funkcji u");
	widmo(N, fs, tabb1, "Widmo funkcji b1");
	widmo(N, fs, tabb2, "Widmo funkcji b2");
	widmo(N, fs, tabb3, "Widmo funkcji b3");

	return 0;
}