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

	//Modulacja
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

	std::vector<double> PSK(bool plot = true) {
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

	std::vector<double> FSK(bool plot = true) {
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

//Demodulacja
void demASK(std::vector<double> signal, int bity, int fn, int fs, double N, double Tb, bool plot = true) {
	std::vector<double> xt;
	int Tbp = (int)(fs * Tb);
	double t =0.0;
	for (int n = 0; n < N; n++) {
		t = (float)n / fs;
		xt.push_back(signal[n] * sin(2 * M_PI * fn * t));
	}

	double suma = 0.0;
	std::vector<double> pt;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += xt[j];
			pt.push_back(suma);
		}
	}

	std::vector<double> ct;
	for (int i = 0; i < pt.size(); i++) {
		if (pt[i] > 999) ct.push_back(1);
		else ct.push_back(0);
	}

	std::vector<std::string> bits;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += ct[j];
		}
		//std::cout << suma << std::endl;
		if ((double)(suma/Tbp) > 0.5) bits.push_back("1");
		else bits.push_back("0");
	}
	for (int i = 0; i < size(bits); i++) std::cout << bits[i] << " ";
	
	if (plot == true){
		plt::plot(signal);
		plt::title("zt");
		plt::show();
		plt::plot(xt);
		plt::title("xt");
		plt::show();
		plt::plot(pt);
		plt::title("pt");
		plt::show();
		plt::plot(ct);
		plt::title("ct");
		plt::show();
	}
}

void demPSK(std::vector<double> signal, int bity, int fn, int fs, double N, double Tb, bool plot = true) {
	std::vector<double> xt;
	int Tbp = (int)(fs * Tb);
	double t = 0.0;
	for (int n = 0; n < N; n++) {
		t = (float)n / fs;
		xt.push_back(signal[n] * sin(2 * M_PI * fn * t));
	}

	double suma = 0.0;
	std::vector<double> pt;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += xt[j];
			pt.push_back(suma);
		}
	}

	std::vector<double> ct;
	for (int i = 0; i < pt.size(); i++) {
		if (pt[i] < 0) ct.push_back(1);
		else ct.push_back(0);
	}

	std::vector<std::string> bits;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += ct[j];
		}
		//std::cout << suma << std::endl;
		if ((double)(suma / Tbp) > 0.5) bits.push_back("1");
		else bits.push_back("0");
	}
	for (int i = 0; i < size(bits); i++) std::cout << bits[i] << " ";

	if (plot == true) {
		plt::plot(signal);
		plt::title("zt");
		plt::show();
		plt::plot(xt);
		plt::title("xt");
		plt::show();
		plt::plot(pt);
		plt::title("pt");
		plt::show();
		plt::plot(ct);
		plt::title("ct");
		plt::show();
	}
}

void demFSK(std::vector<double> signal, int bity, int fn, int fs, double N, double Tb, int W, bool plot = true) {
	std::vector<double> xt1;
	std::vector<double> xt2;
	int Tbp = (int)(fs * Tb);
	double t = 0.0;
	double fn1 = (W + 1) / Tb;
	double fn2 = (W + 2) / Tb;
	
	for (int n = 0; n < N; n++) {
		t = (float)n / fs;
		xt1.push_back(signal[n] * sin(2 * M_PI * fn1 * t));
		xt2.push_back(signal[n] * sin(2 * M_PI * fn2 * t));
	}

	double suma1 = 0.0;
	double suma2 = 0.0;
	std::vector<double> pt1;
	std::vector<double> pt2;
	for (int i = 0; i < bity; i++) {
		suma1 = 0.0;
		suma2 = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma1 += xt1[j];
			suma2 += xt2[j];
			pt1.push_back(suma1);
			pt2.push_back(suma2);
		}
	}
	std::vector<double> pt;
	for (int i = 0; i < size(pt1); i++) {
		pt.push_back(pt1[i] - pt2[i]);
	}

	std::vector<double> ct;
	for (int i = 0; i < pt.size(); i++) {
		if (pt[i] > 0) ct.push_back(1);
		else ct.push_back(0);
	}
	double suma;
	std::vector<std::string> bits;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += ct[j];
		}
		//std::cout << suma << std::endl;
		if ((double)(suma / Tbp) < 0.5) bits.push_back("1");
		else bits.push_back("0");
	}
	for (int i = 0; i < size(bits); i++) std::cout << bits[i] << " ";

	if (plot == true) {
		plt::plot(signal);
		plt::title("zt");
		plt::show();
		plt::plot(xt1);
		plt::title("xt1");
		plt::show();
		plt::plot(xt2);
		plt::title("xt2");
		plt::show();
		plt::plot(pt1);
		plt::title("pt1");
		plt::show();
		plt::plot(pt2);
		plt::title("pt2");
		plt::show();
		plt::plot(pt);
		plt::title("pt");
		plt::show();
		plt::plot(ct);
		plt::title("ct");
		plt::show();
	}
}

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
	//std::vector<double> ask = signal->ASK(false);
	//std::vector<double> psk = signal->PSK(false);
	std::vector<double> fsk = signal->FSK(false);
	//demASK(ask, size(bity), fn, fs, N, Tb);
	//demPSK(psk, size(bity), fn, fs, N, Tb);
	demFSK(fsk, size(bity), fn, fs, N, Tb, W);
	//Zadanie 3
	//widmo(N, fs, ask, "Widmo ASK");
	//widmo(N, fs, psk, "Widmo PSK");
	//widmo(N, fs, fsk, "Widmo FSK");

	return 0;
}
