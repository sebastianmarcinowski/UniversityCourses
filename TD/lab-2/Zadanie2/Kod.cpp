#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <random>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main() {

	std::vector<double> IM;
	std::vector<double> RE;
	std::vector<double> x;
	for (int i = 0; i < 1000; i++) {
		x.push_back(rand()%50);
	}
	for (int i = 0; i < 400; i++) {
		x[rand() % size(x)] *= -1;
	}
	int N = size(x);
	int fs = 1000;
	double a = 0.0;
	double b = 0.0;
	//std::cout << x[0];
	//Wzór DFT
	for (int k = 0; k < N; k++) {
		for (int n = 0; n < N; n++) {
			b += (x[n] * (sin((-2.0 * M_PI * k * n) / N)));
			a += (x[n] * (cos((-2.0 * M_PI * k * n) / N)));
		}
		IM.push_back(b);
		RE.push_back(a);
		a = 0;
		b = 0;
	}

	//Widmo amplitudowe
	std::vector<double> mk;
	for (int k = 0; k < N / 2; k++) {
		mk.push_back(sqrt(pow(RE[k], 2) + pow(IM[k], 2)));
	}

	//Zamiana na skale decybelową
	std::vector<double> mkdb;
	for (int i = 0; i < size(mk); i++) {
		mkdb.push_back(10 * log10(mk[i]));
	}

	//Skala częstotliwości
	std::vector<int> fk;
	for (int i = 0; i < N / 2; i++) {
		fk.push_back(i * (fs / N));
	}

	//Wykres widma amplitudowego
	plt::plot(fk,mkdb);
	plt::xlabel("Czestotliwosc [Hz]");
	plt::ylabel("Amplituda [dB]");
	plt::show();
	
	
	return 0;
}