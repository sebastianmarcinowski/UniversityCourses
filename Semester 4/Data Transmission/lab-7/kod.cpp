#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <cmath>
#include <string> 
#include <random> 
#include <time.h>
#include <numeric>
#include "matplotlibcpp.h"
#include "fourier.h"
#include "DFT.h"
#include <Eigen/Dense>
namespace plt = matplotlibcpp;
using namespace Eigen;
class Kluczowanie {
public:
	std::vector<int> bity;
	int fn;
	int fs;
	double N; 
	double Tb; //czas trwania sygnalu dla pojedynczego bitu
	int W; //docelowa czestotliwosc
	std::vector<double> czas;
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
		czas.clear();
		std::vector<double> ask;
		int Tbp = (int)(fs * Tb);
		double t = 0.0;
		float a;
		float A1 = 1.0;
		float A2 = 0.5;
		a = A1;
		int id = 0;
		for (int i = 0; i < N; i++) {
			t = (double)i / fs;
			czas.push_back(t);
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
		//czas.clear();
		std::vector<double> psk;
		double t = 0.0;
		int Tbp = (int)(fs * Tb);
		double p = 0;
		int id = 0;
		for (int n = 0; n < N; n++) {
			t = (double)n / fs;
			czas.push_back(t);
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
		czas.clear();
		double t = 0.0;
		int Tbp = (int)(fs * Tb);
		double fn1 = (W + 1) / Tb;
		double fn2 = (W + 2) / Tb;
		double fn0 = 0;
		int id = 0;
		for (int n = 0; n < N; n++) {
			t = (double)n / fs;
			czas.push_back(t);
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
std::vector<int> demASK(std::vector<double> signal, int bity, int fn, int fs, double N, double Tb, bool plot = true) {
	std::vector<double> xt;
	int Tbp = (int)(fs * Tb);
	double t =0.0;
	for (int n = 0; n < (int)N; n++) {
		t = (double)n/fs;
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
		if (pt[i] < *std::max_element(pt.begin(),pt.end())/2) ct.push_back(1);
		else ct.push_back(0);
	}

	std::vector<int> bits;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += ct[j];
		}
		//std::cout << suma << std::endl;
		if ((double)(suma/Tbp) > 0.5) bits.push_back(1);
		else bits.push_back(0);
	}
	//for (int i = 0; i < size(bits); i++) std::cout << bits[i] << " ";
	
	if (plot == true){
		/*plt::plot(signal);
		plt::title("zt");
		plt::show();
		plt::plot(xt);
		plt::title("xt");
		plt::show();
		plt::plot(pt);
		plt::title("pt");
		plt::show();*/
		plt::plot(ct);
		plt::title("ct");
		plt::show();
	}
	return bits;
}

std::vector<int> demPSK(std::vector<double> signal, int bity, int fn, int fs, double N, double Tb, bool plot = true) {
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

	std::vector<int> bits;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += ct[j];
		}
		//std::cout << suma << std::endl;
		if ((double)(suma / Tbp) > 0.5) bits.push_back(1);
		else bits.push_back(0);
	}
	//for (int i = 0; i < size(bits); i++) std::cout << bits[i] << " ";

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
	return bits;
}

std::vector<int> demFSK(std::vector<double> signal, int bity, int fn, int fs, double N, double Tb, int W, bool plot = true) {
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
	std::vector<int> bits;
	for (int i = 0; i < bity; i++) {
		suma = 0.0;
		for (int j = (i * Tbp); j < ((i + 1) * Tbp); j++) {
			suma += ct[j];
		}
		//std::cout << suma << std::endl;
		if ((double)(suma / Tbp) < 0.5) bits.push_back(1);
		else bits.push_back(0);
	}
	//for (int i = 0; i < size(bits); i++) std::cout << bits[i] << " ";

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
	return bits;
}

//Lab6 - kody Hamminga
//Koder
std::vector<int> Hamming_Koder74(std::vector<int> bity) {
	int n = 7;
	int k = 4;
	int m = 3;
	std::vector<int> inf = { 0,0,0,0,0,0,0 };
	inf[2] = bity[0];
	inf[4] = bity[1];
	inf[5] = bity[2];
	inf[6] = bity[3];
	inf[0] = (((inf[2] + inf[4]) % 2) + inf[6]) % 2;
	inf[1] = (((inf[2] + inf[5]) % 2) + inf[6]) % 2;
	inf[3] = (((inf[4] + inf[5]) % 2) + inf[6]) % 2;

	/*for (int i = 0; i < size(inf); i++) {
		std::cout << inf[i] << " ";
	}*/
	return inf;
}
std::vector<int> Hamming_Dekoder74(std::vector<int> bity) {
	int x1 = bity[0];
	int x2 = bity[1];
	int x4 = bity[3];
	int x1p = (((bity[2] + bity[4]) % 2) + bity[6]) % 2;
	int x2p = (((bity[2] + bity[5]) % 2) + bity[6]) % 2;
	int x4p = (((bity[4] + bity[5]) % 2) + bity[6]) % 2;
	int x1d = (x1 + x1p) % 2;
	int x2d = (x2 + x2p) % 2;
	int x4d = (x4 + x4p) % 2;

	int S = pow(2, 0) * x1d + pow(2, 1) * x2d + pow(2, 2) * x4d;
	if (S != 0) bity[S - 1] = !bity[S - 1];

	std::vector<int> inf = { bity[2],bity[4],bity[5],bity[6] };
	/*for (int i = 0; i < size(inf); i++) {
		std::cout << inf[i] << " ";
	}*/

	return inf;
}

std::vector<int> Hamming_Koder1511(std::vector<int> bity) {
	RowVectorXd b(11);
	for (int i = 0; i < size(bity); i++) {
		b(i) = bity[i];
	}
	MatrixXd P(11, 4);
	MatrixXd I = MatrixXd::Identity(11, 11);
	VectorXd x1 = VectorXd(11);
	VectorXd x2 = VectorXd(11);
	VectorXd x4 = VectorXd(11);
	VectorXd x8 = VectorXd(11);
	x1 << 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1;
	x2 << 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1;
	x4 << 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1;
	x8 << 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1;
	P.col(0) = x1;
	P.col(1) = x2;
	P.col(2) = x4;
	P.col(3) = x8;
	MatrixXd G(11, P.cols() + I.cols());
	G << P, I;
	RowVectorXd c = b * G;
	std::vector<int> c2;
	for (int i = 0; i < 15; i++) {
		c(i) = (int)c(i) % 2;
		c2.push_back(c(i));
	}
	//std::cout << c;
	return c2;
}
std::vector<int> Hamming_Dekoder1511(std::vector<int> c) {
	MatrixXd P(11, 4);
	MatrixXd I = MatrixXd::Identity(4,4);
	VectorXd x1 = VectorXd(11);
	VectorXd x2 = VectorXd(11);
	VectorXd x4 = VectorXd(11);
	VectorXd x8 = VectorXd(11);
	x1 << 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1;
	x2 << 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1;
	x4 << 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1;
	x8 << 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1;
	P.col(0) = x1;
	P.col(1) = x2;
	P.col(2) = x4;
	P.col(3) = x8;
	RowVectorXd s = VectorXd(4);
	MatrixXd H = MatrixXd(4,15);
	//P = P.transpose();
	H << I, P.transpose();
	RowVectorXd c2(15);
	for (int i = 0; i < 15; i++) {
		c2(i) = c[i];
	}
	//H = H.transpose();
	s << c2 * H.transpose();
	for (int i = 0; i < 4; i++) {
		s(i) = (int)s(i) % 2;
	}
	int S = pow(2, 0) * s(0) + pow(2, 1) * s(1) + pow(2, 2) * s(2) + pow(2, 3) * s(3);
	if (S != 0){
		switch (S) {
			case 1:
				c2[0] = !c2[0];
				break;
			case 2:
				c2[1] = !c2[1];
				break;
			case 4:
				c2[2] = !c2[2];
				break;
			case 8:
				c2[3] = !c2[3];
				break;
			case 3:
				c2[4] = !c2[4];
				break;
			case 5:
				c2[5] = !c2[5];
				break;
			case 6:
				c2[6] = !c2[6];
				break;
			case 7:
				c2[7] = !c2[7];
				break;
			default:
				c2[S - 1] = !c2[S - 1];
		}
	}

	
	std::vector<int> slowo;
	for (int i = 0; i < 11; i++) {
		c2(i) = (int)c2(i) % 2;
		slowo.push_back(c2(i));
	}
	std::cout << c2;
	return slowo;
}

std::vector<int> konwerter(std::string zdanie) {
	std::vector<int> bity;
	int temp;
	std::string temp2;
	for (int i : zdanie) {
		for (int j = 0; j < 7; j++) {
			bity.push_back((i & 0x40) >> 6);
			i = i << 1;
		}
	}
	return bity;
}

std::vector<double> szum_bialy(std::vector<double> signal, float alfa) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> noise(-3.0, 3.0);
	for (auto& x : signal) {
		x += (alfa * noise(gen));
	}
	return signal;
}

std::vector<double> wytlumianie(std::vector<double> signal, std::vector<double> czas, float beta) {
	/*double sum = std::accumulate(czas.begin(), czas.end(), 0.0);
	sum = sum / czas.size();*/
	for (int i = 0; i < size(signal); i++) {
		signal[i] = signal[i] * exp((double)(- beta * czas[i]));
	}
	return signal;
}

int main() {
	//Lab 7
	std::string slowo = "Kocham Transmisje Danych";
	std::vector<int> slowo_bity = konwerter(slowo);
	//std::vector<int> slowo_bity = { 1,1,1,0,1,0,1,0,1,0,1,0 };
	
	//Dodanie zer jeżeli wektor bitowy nie jest podzielny przez 4
	if (size(slowo_bity) % 4 != 0) {
		for (int i = 0; i < (size(slowo_bity) % 4); i++) {
			slowo_bity.push_back(0);
		}
	}

	//Kodowanie
	std::vector<int> b1;
	for (int i = 0; i < (size(slowo_bity) / 4); i++) {
		std::vector<int> temp(slowo_bity.begin() + (i * 4), slowo_bity.begin() + ((i + 1) * 4));
		std::vector<int> temp2 = Hamming_Koder74(temp);
		b1.insert(b1.end(), temp2.begin(), temp2.end());
	}

	//Parametry sygnału
	double Tc = 1;
	double fs = 20000;
	int N = Tc * fs;
	int W = 2;
	int M = size(b1);
	double Tb = Tc / M;
	double fn = (double)(W * (1 / Tb));
	int Tbp = (int)(fs * Tb);

	//Modulacja
	Kluczowanie* signal = new Kluczowanie(b1, fn, fs, N, Tb, W);
	std::vector<double> sigASK = signal->ASK(false);
	std::vector<double> czasASK = signal->czas;
	std::vector<double> sigPSK = signal->PSK(false);
	std::vector<double> czasPSK = signal->czas;
	std::vector<double> sigFSK = signal->FSK(false);
	std::vector<double> czasFSK = signal->czas;

	std::vector<double> BERvalASK;
	std::vector<double> BERvalPSK;
	std::vector<double> BERvalFSK;
	std::vector<double> czynnikAlfa;
	std::vector<double> czynnikBeta;

	const int samples = 21;
	for (int i = 0; i < samples; i++) {
		for (int j = 0; j < samples; j++) {
			sigASK = signal->ASK(false);
			sigPSK = signal->PSK(false);
			sigFSK = signal->FSK(false);
			//Wytłumianie sygnału - zadanie 3
			double beta = (double)10 / 20 * i;
			sigASK = wytlumianie(sigASK, czasASK, beta);
			sigPSK = wytlumianie(sigPSK, czasPSK, beta);
			sigFSK = wytlumianie(sigFSK, czasFSK, beta);
			//Dodanie szumu białego - zadanie 2
			double alfa = (double)1 / 20 * j;
			sigASK = szum_bialy(sigASK, alfa);
			sigPSK = szum_bialy(sigPSK, alfa);
			sigFSK = szum_bialy(sigFSK, alfa);


			//Demodulacja
			std::vector<int> b2ASK = demASK(sigASK, size(b1), fn, fs, N, Tb, false);
			std::vector<int> b2PSK = demPSK(sigPSK, size(b1), fn, fs, N, Tb, false);
			std::vector<int> b2FSK = demFSK(sigFSK, size(b1), fn, fs, N, Tb, W, false);

			//Dekodowanie
			std::vector<int> b3;
			b3.clear();
			for (int i = 0; i < (b2ASK.size() / 7); i++) {
				std::vector<int> temp(b2ASK.begin() + (i * 7), b2ASK.begin() + ((i + 1) * 7));
				std::vector<int> temp2 = Hamming_Dekoder74(temp);
				b3.insert(b3.end(), temp2.begin(), temp2.end());
			}
			std::vector<int> b3p;
			b3p.clear();
			for (int i = 0; i < (b2PSK.size() / 7); i++) {
				std::vector<int> temp(b2PSK.begin() + (i * 7), b2PSK.begin() + ((i + 1) * 7));
				std::vector<int> temp2 = Hamming_Dekoder74(temp);
				b3p.insert(b3p.end(), temp2.begin(), temp2.end());
			}
			std::vector<int> b3f;
			b3f.clear();
			for (int i = 0; i < (b2FSK.size() / 7); i++) {
				std::vector<int> temp(b2FSK.begin() + (i * 7), b2FSK.begin() + ((i + 1) * 7));
				std::vector<int> temp2 = Hamming_Dekoder74(temp);
				b3f.insert(b3f.end(), temp2.begin(), temp2.end());
			}

			//Obliczanie bitowej stopy błędów w sygnale wyjściowym
			int bledy = 0;
			int bledy2 = 0;
			int bledy3 = 0;
			for (int i = 0; i < size(b3); i++) {
				if (b3[i] != slowo_bity[i]) bledy++;
			}
			for (int i = 0; i < size(b3p); i++) {
				if (b3p[i] != slowo_bity[i]) bledy2++;
			}
			for (int i = 0; i < size(b3f); i++) {
				if (b3f[i] != slowo_bity[i]) bledy3++;
			}
			double BER = (double)bledy / (double)size(b3);
			double BER2 = (double)bledy2 / (double)size(b3p);
			double BER3 = (double)bledy3 / (double)size(b3f);
			//std::cout << BER << ' ' << BER2 << ' ' << BER3 << endl;
			BERvalASK.push_back(BER);
			BERvalPSK.push_back(BER2);
			BERvalFSK.push_back(BER3);

		}
		czynnikAlfa.push_back(1 / 20 * i);
		czynnikBeta.push_back(10 / 20 * i);
	}
	//Wykres porównawczy
	/*plt::named_plot("ASK",ASK,BERvalASK,"red");
	plt::named_plot("PSK",PSK, BERvalPSK, "blue");
	plt::named_plot("FSK",FSK, BERvalFSK, "green");
	std::map<std::string, std::string> dane;
	dane["loc"] = "upper left";
	plt::title("Wykres porownujacy wartosci BER miedzy modulacjami - tlumienie");
	plt::legend(dane);
	plt::show();*/

	for (int i = 0; i < size(BERvalASK); i++) {
		std::cout << BERvalASK[i] << " ";
	}
	std::cout << "\nd\n";
	for (int i = 0; i < size(BERvalPSK); i++) {
		std::cout << BERvalPSK[i] << " ";
	}
	std::cout << "\nd\n";
	for (int i = 0; i < size(BERvalFSK); i++) {
		std::cout << BERvalFSK[i] << " ";
	}
	return 0;
}