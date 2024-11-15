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

namespace plt = matplotlibcpp;

void pasmo(std::vector<int> fk, std::vector<double> ampli, int X) {
	// X -> wartoœæ okreœlaj¹ca o ile dB "ni¿ej" szukam pr¹¿ków
	double max_value = *std::max_element(ampli.begin(), ampli.end());
	std::cout << "Wartosc X: " << X << std::endl;
	std::cout << "Wartosc maksymalna wsrod wektora wejsciowego:" << max_value << std::endl;
	std::vector<int> points;
	for (int i = 0; i < size(fk); i++) {
		if (ampli[i] >= (max_value - X)) points.push_back(i);
		//plt::axvline(i);
	}
	if (points.size() == 1) {
		std::cout << "Szerokosc pasma jest rowna: 0" << std::endl;
	}
	else if (points.size() == 2) {
		if(ampli[points[0]] < ampli[points[1]])
			std::cout << "Szerokosc pasma jest rowna: " << points[0] << std::endl;
		else
			std::cout << "Szerokosc pasma jest rowna: " << points[1] << std::endl;
	}
	else {
		std::cout << "Szerokosc pasma jest rowna: " << points[size(points)-1] - points[0] << std::endl;
		std::cout << "Wartosc ostatniego punktu: " << points[size(points) - 1] << std::endl;
		std::cout << "Wartosc pierwszego punktu: " << points[0] << std::endl;
	}
	std::cout << "Dlugosc wektora z punktami spelniajacymi warunek: " << size(points) << std::endl;
	if (size(points) > 2) {
		std::cout << "Pierwszy punkt spelniajacy warunek: " << points[0] << std::endl;
		std::cout << "Ostatni punkt spelniajacy warunek: " << points[size(points) - 1] << std::endl;
	}
	std::cout << std::endl;
	////Wykres szerokoœci pasma widma amplitudowego
	//plt::semilogx(fk, ampli); //skala czestotliwosci
	////plt::plot(fk, mkdb); //skala liniowa
	//plt::title("Wykres szerokoœci pasma dla:" + std::to_string(X));
	//plt::plot({(double)points[0], (double)points[size(points)-1]}, {max_value-X, max_value-X}, "r"); //rysowanie prostej do szerokosci pasma
	//plt::axvline(points[0]);
	//plt::axvline(points[size(points)-1]);
	////plt::axhline(max_value - X);
	//plt::xlabel("Czestotliwosc [Hz]");
	//plt::ylabel("Amplituda [dB]");
	//plt::show();
}

//FFTW
#define REAL 0
#define IMAG 1
void fft(int N, fftw_complex *in, fftw_complex *out){
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();
}
void displayComplex(int N,fftw_complex* y) {
	for (int i = 0; i < N; i++) {
		if (y[i][IMAG] < 0)
			std::cout << y[i][IMAG] << "-" << abs(y[i][REAL]) << "i" << std::endl;
		else
			std::cout << y[i][IMAG] << "+" << abs(y[i][REAL]) << "i" << std::endl;
	}
}
void displayReal(int N, fftw_complex* y) {
	for (int i = 0; i < N; i++) {
		std::cout << y[i][REAL] << std::endl;
	}
}

void widmo(int N, double fs, std::vector<double> xn, std::string nazwa) {
	std::vector<double> IM;
	std::vector<double> RE;
	double a = 0.0;
	double b = 0.0;
	
	
	//DFT
	/*clock_t dft1 = clock();
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
	clock_t dft2 = clock();
	double timeDFT = (dft2 - dft1) / (double)CLOCKS_PER_SEC;
	std::cout << "Czas wykonania DFT dla " << nazwa << ": " << timeDFT << std::endl;*/
	
	
	//FFT
	fftw_complex* wejscie = new fftw_complex[N];
	fftw_complex *wyjscie = new fftw_complex[N];
	for (int i = 0; i < size(xn); i++) {
		wejscie[i][REAL] = xn[i];
		wyjscie[i][IMAG] = 0;
	}
	//clock_t fft1 = clock();
	fft(N, wejscie, wyjscie);
	/*clock_t fft2 = clock();
	double timeFFT = (fft2 - fft1) / (double)CLOCKS_PER_SEC;
	std::cout << "Czas wykonania FFT dla " << nazwa << ": " << timeFFT <<  std::endl;*/

	//Widmo amplitudowe
	std::vector<double> mk;
	
	for (int k = 0; k < (N / 2); k++) {
		mk.push_back(sqrt(pow(wyjscie[k][REAL], 2) + pow(wyjscie[k][IMAG], 2)));
	}

	//Zamiana na skale decybelow¹
	std::vector<double> mkdb;
	for (int k = 0; k < (N/2); k++) {
		mkdb.push_back(10 * log10(mk[k]));
	}

	//Skala czêstotliwoœci
	std::vector<int> fk;
	for (int k = 0; k < N / 2; k++) {
		fk.push_back(k * (fs / N));
	}

	//Szacowanie szerokosci pasma
	pasmo(fk, mkdb, 3);
	pasmo(fk, mkdb, 6);
	pasmo(fk, mkdb, 12);

	//Wykres widma amplitudowego1
	plt::semilogx(fk, mkdb); //skala czestotliwosci
	//plt::plot(fk, mkdb); //skala liniowa
	//plt::plot({ max_value-X, (double)points[size(points) - 1] }, {ampli[points[0]], ampli[points[0]] }, "r"); //rysowanie prostej do szerokosci pasma
	plt::title(nazwa);
	plt::xlabel("Czestotliwosc [Hz]");
	plt::ylabel("Amplituda [dB]");
	plt::show();
}
