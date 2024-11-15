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

int main() {
	//Wartosci dla a
	double Ka = 0.5;
	double Kp = 0.8;
	double Kf = 0.8;
	//Wartosci dla b
	//double Ka = 4.8;
	//double Kp = 2.14;
	//double Kf = 1.79;
	//Wartosci dla c
	/*double Ka = 45;
	double Kp = 8.5;
	double Kf = 9.9;*/



	double fs = 20000;
	double Tc = 1;
	int fi = 1;
	double N = Tc * fs;

	//Parametry do zadania 4
	double fm = 250;
	double fn = 1000;

	//Parametry dla za i zp
	/*double fm = 15;
	double fn = 1000;*/

	//Parametry dla zf
	/*double fm = 25;
	double fn = 80;*/

	std::vector<double> sinus;
	std::vector<double> MAmpli;
	std::vector<double> MFaza;
	std::vector<double> MCzest;

	for (int n = 0; n < N; n++) {
		double t = n / fs;
		//Zwykly sinus
		double mt = sin(2 * M_PI * fm * t);
		sinus.push_back(mt);
		//Modulacja amplitudowa
		double Za = (Ka * mt + 1) * cos(2 * M_PI * fn * t);
		MAmpli.push_back(Za);
		//Modulacja fazy
		double Zp = cos(2 * M_PI * fn * t + Kp * mt);
		MFaza.push_back(Zp);
		//Modulacja czestotliwosci
		double Zf = cos(2 * M_PI * fn * t + ((Kf / fm) * mt));
		MCzest.push_back(Zf);
	}
	plt::plot(sinus);
	plt::title("Sinus");
	plt::show();
	plt::plot(MAmpli);
	plt::title("Modulacja Amplitudy");
	plt::show();
	plt::plot(MFaza);
	plt::title("Modulacja Fazy");
	plt::show();
	plt::plot(MCzest);
	plt::title("Modulacja Czestotliwosci");
	plt::show();


	//widmo(N, fs, sinus, "Sinus");
	widmo(N, fs, MAmpli, "Widmo modulacji amplitudy");
	widmo(N, fs, MFaza, "Widmo modulacji fazy");
	widmo(N, fs, MCzest, "Widmo modulacji czestotliwosci");

	return 0;
}