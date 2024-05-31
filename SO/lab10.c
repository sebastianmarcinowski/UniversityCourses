//SO IS1 224A LAB10
//Sebastian Marcinowski
//ms53692@zut.edu.pl
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<ctype.h>
#include<time.h>
double suma = 3.0;

typedef struct {
	int rozmiar;
	int poczatek;
	double reszta;
	pthread_mutex_t* muteks;
}Maciek;
double piWoT(int n) {
	double w2 = 3.0;
	for (int i = 1; i < n; i++) {
		if (i % 2 == 1) {
			w2 += 4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
		}
		else {
			w2 += -4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
		}
	}
	return w2;
}
void* thread(void* data) {
	Maciek* dane = (Maciek*)data;
	double value = 0.0;
	int t = dane->poczatek + dane->rozmiar;
	for (int i = dane->poczatek; i < t; i++) {
		if (i == 0) {
			value += 0.0;
			//printf("error1\n %f", value);
		}
		else if ((i % 2) == 1) {
			value += 4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
			//printf("error2\n %f", value);
		}
		else if ((i % 2) == 0) {
			value += -4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
			//printf("error3\n %f", value);
		}
	}
	pthread_mutex_lock(dane->muteks);
	suma = suma + value;
	pthread_mutex_unlock(dane->muteks);
	pthread_t self = pthread_self();
	srand(self);
	dane->reszta = value;
	printf("Thread %lxd size = %d first = %d\n", self, dane->rozmiar, dane->poczatek);
	return (void*)self;
}
int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Not enough arguments");
		return 1;
	}
	else if (argc > 3) {
		printf("Too many arguments");
		return 1;
	}
	int n = atoi(argv[1]);
	int w = atoi(argv[2]);
	if (n < 1 || n>1000000 || w > 100 || w > n) {
		printf("Wrong number of threads");
	}
	pthread_t threads[w];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	Maciek data[w];
	double ulamek[w];
	int pierwszy = 0;
	clock_t t1 = clock();
	for (int i = 0; i < w; i++) {
		data[i].rozmiar = n / w;
		data[i].poczatek = pierwszy;
		data[i].muteks = &mutex;
		pthread_create(&threads[i], NULL, thread, (void*)&data[i]);
		pierwszy += n / w;
	}
	if (n % w != 0) {
		data[w - 1].rozmiar += n % w;
	}
	for (int i = 0; i < w; i++) {
		pthread_t retval;
		pthread_join(threads[i], (void*)&retval);
		printf("Thread %lxd sum=%.20f\n", retval, data[i].reszta);
	}
	clock_t t2 = clock();
	double timewt = (double)(t2 - t1) / CLOCKS_PER_SEC;
	clock_t t3 = clock();
	double w2 = piWoT(n);
	clock_t t4 = clock();
	double timewot = (double)(t4 - t3) / CLOCKS_PER_SEC;
	printf("w/Threads PI = %.20f Time: %f\n", suma, timewt);
	printf("wo/Threads PI = %.20f Time: %f\n", w2, timewot);
	return 0;
}