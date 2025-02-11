#include <iostream>
#include<chrono>
#include<xmmintrin.h>
using namespace std;

int main()
{
	float a[4][4] = { {2.0,1.0,3.0,2.0},{5.0,3.0,4.0,3.0},{3.0,-4.0,2.0,6.0},{4.0,5.0,2.0,-4.0} };
	float b[4][4] = { {3.0,0.0,1.0,2.0},{2.0,4.0,2.0,1.0},{0.0,-2.0,3.0,0.0},{1.0,4.0,-2.0,-1.0} };
	float c[4][4] = { 0 };
	float d[4][4] = { 0 };
	float e[4][4] = { 0 };
	// Mnozenie macierzy w C
	auto start1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {		
			for (int k = 0; k < 4; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	auto stop1 = chrono::high_resolution_clock::now();
	auto czas1 = chrono::duration_cast<chrono::nanoseconds>(stop1 - start1);
	printf("Czas w C: %.8f [s]\n", czas1.count() * 1e-9);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf(" %.2f ", c[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//Mnozenie macierzy w assemblerze
	auto start2 = chrono::high_resolution_clock::now();
	__asm {
		mov al, 0;
		mov ecx, 0;
	petla:
		movups xmm0, [a + ecx];
		movups xmm2, xmm0;
		movups xmm3, xmm0;
		movups xmm4, xmm0;
		movups xmm5, xmm0;
		movups xmm1, [b];

		shufps xmm2, xmm0, 0x00;
		shufps xmm3, xmm0, 0x55;
		shufps xmm4, xmm0, 0xaa;
		shufps xmm5, xmm0, 0xff;

		mulps xmm2, xmm1;
		movups xmm1, [b + 16];
		mulps xmm3, xmm1;
		movups xmm1, [b + 32];
		mulps xmm4, xmm1;v
		movups xmm1, [b + 48];

		mulps xmm5, xmm1;
		addps xmm2, xmm3;
		addps xmm2, xmm4;
		addps xmm2, xmm5;
		movups [d + ecx], xmm2;
		cmp al, 3;
		jz koniec;
		add al, 1;
		add ecx, 16;
		jmp petla;
	koniec:
	}
	auto stop2 = chrono::high_resolution_clock::now();
	auto czas2 = chrono::duration_cast<chrono::nanoseconds>(stop2 - start2);
	printf("Czas w assemblerze: %.8f [s]\n", czas2.count() * 1e-9);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf(" %.2f ", d[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	return 0;

}