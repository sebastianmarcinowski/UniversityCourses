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
#include <Eigen/Dense>
namespace plt = matplotlibcpp;
using namespace Eigen;
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

	for (int i = 0; i < size(inf); i++) {
		std::cout << inf[i] << " ";
	}
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
	for (int i = 0; i < size(inf); i++) {
		std::cout << inf[i] << " ";
	}

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
	VectorXd s = VectorXd(4);
	MatrixXd H = MatrixXd(4,15);
	P = P.transpose();
	H << I, P;
	RowVectorXd c2(15);
	for (int i = 0; i < 15; i++) {
		c2(i) = c[i];
	}
	H = H.transpose();
	s << c2 * H;
	for (int i = 0; i < 4; i++) {
		s(i) = (int)s(i) % 2;
	}

	int S = pow(2, 0) * s(0) + pow(2, 1) * s(1) + pow(2, 2) * s(2) + pow(2, 3) * s(3);
	if (S != 0){
		if (c2(S - 1) == 0) {
			c2(S - 1) = 1;
		}
		else {
			c2(S - 1) = 0;
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

int main(){
std::vector<int> slowo = { 0,1,0,1,1,1,0,0,1,1,1 };
/*slowo = Hamming_Koder74(slowo);
slowo[4] = !slowo[4];
std::cout << "\n";
Hamming_Dekoder74(slowo);*/
slowo = Hamming_Koder1511(slowo);
Hamming_Dekoder1511(slowo);
return 0;
}