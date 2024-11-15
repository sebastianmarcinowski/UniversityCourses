//SO IS1 224A LAB11
//Sebastian Marcinowski
//ms53692@zut.edu.pl
#include<stdio.h>
#include<sys/types.h>
#include<windows.h>
#include<process.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<string.h>

float sumaWT = 0.0;

typedef struct {
	int rozmiar;
	int poczatek;
	float suma_czesciowa;
	int retval;
	float* tab;
	HANDLE muteks;
}Watek;

float SWoT(int n, float tablica[]) {
	float sumawot = 0.0;
	for (int i = 0; i < n; i++) {
		sumawot += tablica[i];
	}
	return sumawot;
}

DWORD thread(LPVOID data) {
	Watek* dane = (Watek*)data;
	float wartosc = 0.0;
	for (int i = dane->poczatek; i < (dane->poczatek + dane->rozmiar); i++) {
		wartosc += dane->tab[i];
	}
	dane->muteks = CreateMutex(NULL, false, NULL);
	WaitForSingleObject(dane->muteks, INFINITE);
	sumaWT += wartosc;
	ReleaseMutex(dane->muteks);
	DWORD self = GetCurrentThreadId();
	srand(self);
	dane->suma_czesciowa = wartosc;
	dane->retval = self;
	printf("Thread %lxd size = %d\n", self, dane->rozmiar);
	return wartosc;
}

int main(int argc, char* argv[]) {
	if (argc <  3) {
		printf("Not enough arguments");
		return 1;
	}
	else if (argc > 3) {
		printf("Too many arguments");
		return 1;
	}
	int n = atoi(argv[1]);
	int w = atoi(argv[2]);
	if (n < 0 || n>1000000 || w<0 || w>=n) {
		printf("Invalid arguments");
		return 1;
	}
	HANDLE* threads = (HANDLE*) malloc(w * sizeof(HANDLE));
	DWORD* threadID = (DWORD*) malloc(w * sizeof(DWORD));
	float* tablica = (float*) malloc(n * sizeof(float));
	srand(0);
	for (int i = 0; i < n; i++) {
		tablica[i] = 1000. * rand() / RAND_MAX;
	}
	int pierwszy = 0;
	Watek* data = (Watek*) malloc(w * sizeof(Watek));
	clock_t t1 = clock();
	for (int i = 0; i < w; i++) { 
		data[i].rozmiar = n / w;
		data[i].poczatek = pierwszy;
		data[i].tab = tablica;
		if (i == (w - 1) && (n % w) != 0) {
			data[w - 1].rozmiar += n % w;
		}
		threads[i] = CreateThread(NULL, 0, thread, &data[i],0,&threadID[i]);
		pierwszy += n / w;
	}
	for (int i = 0; i < w; i++) {
		WaitForSingleObject(threads[i], INFINITE); 
		printf("Thread %lxd sum = %f \n", data[i].retval, data[i].suma_czesciowa);
	}
	clock_t t2 = clock();
	double time = (double)(t2 - t1) / CLOCKS_PER_SEC;

	clock_t t3 = clock();
	float wypisz = SWoT(n, tablica);
	clock_t t4 = clock();
	double timeWoT = (double)(t4 - t3) / CLOCKS_PER_SEC;
	printf("w/Threads: sum = %f, time = %f\n", sumaWT, time);
	printf("wo/Threads: sum = %f, time = %f\n", wypisz, timeWoT);
	free(threads);
	free(threadID);
	free(tablica);
	free(data);
	return 0;
}