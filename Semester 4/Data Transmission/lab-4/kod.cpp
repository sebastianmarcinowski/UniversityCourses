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
#include "fourier.h"
#include "DFT.h"
namespace plt = matplotlibcpp;
class Kluczowanie {
public:
	std::vector<int> bity;
	int fn;
	int fs;
	double N; 
	double Tb; //czas trwania sygnalu dla pojedynczego bitu
	int W; //docelowa czestotliwosc
	Kluczowanie(std::vector<int> bity, int fn, int fs, double N, double Tb, int W) {
		this->bity = bity;
		this->fn = fn;
		this->fs = fs;
		this->N = N;
		this->Tb = Tb;
		this->W = W;
	}
	vector<double> ASK(bool plot = true) {
		std::vector<double> ask;
		int Tbp = (int)(fs * Tb);
		double t = 0.0;
		float a;
		float A1 = 1.0;
		float A2 = 2.0;
		a = A1;
		int id = 0;
		for (int i = 0; i < N; i++) {
			t = (float)i / fs;
			if (i % Tbp == 0) {
				int b = bity[id++];
				if (b == 1) {
					a = A2;
				}
				else {
					a = A1;
				}
			}
			ask.push_back(a * sin(2 * M_PI * fn * t));
		}
		if (plot == true) {
			plt::plot(ask);
			plt::title("ASK");
			plt::axhline(0);
			plt::show();
		}
		return ask;
	}

	vector<double> PSK(bool plot = true) {
		std::vector<double> psk;
		double t = 0.0;
		int Tbp = (int)(fs * Tb);
		double p = 0;
		int id = 0;
		for (int n = 0; n < N; n++) {
			t = (float)n / fs;
			if (n % Tbp == 0) {
				int b = bity[id++];
				if (b == 1) {
					p = M_PI;
				}
				else {
					p = 0;
				}
			}
			psk.push_back(sin(2 * M_PI * fn * t + p));
		}
		if (plot == true) {
			plt::plot(psk);
			plt::title("PSK");
			plt::axhline(0);
			plt::show();
		}
		return psk;
	}

	vector<double> FSK(bool plot = true) {
		std::vector<double> fsk;
		double t = 0.0;
		int Tbp = (int)(fs * Tb);
		double fn1 = (W + 1) / Tb;
		double fn2 = (W + 2) / Tb;
		double fn0 = 0;
		int id = 0;
		for (int n = 0; n < N; n++) {
			t = (float)n / fs;
			if (n % Tbp == 0) {
				int b = bity[id++];
				if (b == 1) {
					fn0 = fn2;
				}
				else {
					fn0 = fn1;
				}
			}
			fsk.push_back(sin(2 * M_PI * fn0 * t));
		}
		if (plot == true) {
			plt::plot(fsk);
			plt::title("FSK");
			plt::axhline(0);
			plt::show();
		}
		return fsk;
	}
};

void konwerter(std::string zdanie) {
	std::vector<int> bity;
	int temp;
	std::string temp2;
	for (int i : zdanie) {
		for (int j = 0; j < 7; j++) {
			bity.push_back((i & 0x40) >> 6);
			i = i << 1;
		}
	}
}


int main() {
	// 
	std::vector<int> bity= { 1,1,0,1,1,1,0,1,0,1 };
	double Tc = 1;
	double fs = 20000;
	int N = Tc * fs;
	int W = 2; //docelowa czestotliwosc
	int M = size(bity);
	double Tb = Tc/M;
	double fn = W * (1/Tb);

	Kluczowanie* signal = new Kluczowanie(bity, fn, fs, N, Tb, W);

	// Zadanie 2
	vector<double> ask = signal->ASK(false);
	vector<double> psk = signal->PSK(false);
	vector<double> fsk = signal->FSK(false);

	//Zadanie 3
	//widmo(N, fs, ask, "Widmo ASK");
	//widmo(N, fs, psk, "Widmo PSK");
	widmo(N, fs, fsk, "Widmo FSK");

	return 0;
}
