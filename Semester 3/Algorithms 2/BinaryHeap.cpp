
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <random>
#include <string>
using namespace std; 

const int array_multiplier = 2;
int lvl = 0;

template <typename T>
class Heap{
public:
	T data;
	int pojemnosc;
	int rozmiar;
	T* test = NULL;
	T root = NULL;
	int size = 0;
	void add(T data);
	void deleteRoot();
	void clear();
	void printout();
	void BottomUp(int index);
	void TopDown(int index);
	void addTest(int number);
	Heap() {
		rozmiar = 0;
		pojemnosc = 1;
		test = new T[pojemnosc];
		root = test[1];
	}
};

template <typename T>
void Heap<T>::add(T data) {
	if (pojemnosc <= rozmiar) {
		pojemnosc = pojemnosc * array_multiplier;
		T* temp = new T[pojemnosc];
		for (int i = 0; i < rozmiar; i++) {
			temp[i] = test[i];
		}
		delete[] test;
		test = temp;
	}
	test[rozmiar] = data;
	rozmiar++;
	BottomUp(rozmiar-1);
}

template <typename T>
void Heap<T>::deleteRoot() {
	test[0] = test[rozmiar - 1];
	test[rozmiar-1] = NULL;
	if ((pojemnosc/2) >= rozmiar) {
		pojemnosc = pojemnosc / array_multiplier;
		T* temp = new T[pojemnosc];
		for (int i = 0; i < rozmiar; i++) {
			temp[i] = test[i];
		}
		delete[] test;
		test = temp;
	}
	TopDown(0);
	rozmiar--;
}

template <typename T>
void Heap<T>::clear() {
	test[0];
	rozmiar = 0;
	pojemnosc = 1;
}

template <typename T>
void Heap<T>::printout() {
	int id = 0;
	cout << "Capacity: " << pojemnosc << endl;
	cout << "Number of elements: " << rozmiar << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "Id." <<  id << ". " << "Data: " << test[i] << endl;
		id++;
	}
}

template <typename T>
void Heap<T>::BottomUp(int index) {
	if (index <= 0) {
		return;
	}
	else {
		int parent = (index - 1) / 2;
		if (test[parent] < test[index]) {
			T bufor = test[index];
			test[index] = test[parent];
			test[parent] = bufor;
			index = parent;
			BottomUp(index);
		}
		else {
			return;
		}
	}
	
}

template <typename T>
void Heap<T>::TopDown(int index) {
	if (lvl == int(log2(pojemnosc))) {
		lvl = 0;
		return;
	}
	else {
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		if (leftChild >= rozmiar) test[leftChild] = NULL;
		if (rightChild >= rozmiar) test[rightChild] = NULL;
		if (test[index] > test[rightChild] && test[index] > test[leftChild]) {
			return;
		}
		if (test[rightChild] != NULL && test[index] < test[rightChild] && test[rightChild] >= test[leftChild]) {
			T bufor = test[index];
			test[index] = test[rightChild];
			test[rightChild] = bufor;
			index = rightChild;
		}
		else if (test[leftChild] != NULL && test[index] < test[leftChild] && test[rightChild] < test[leftChild]) {
			T bufor = test[index];
			test[index] = test[leftChild];
			test[leftChild] = bufor;
			index = leftChild;
		}
		lvl++;
		TopDown(index);
	}
}

template <typename T>
void Heap<T>::addTest(int number) {
	for (int i = 0; i < number; i++) {
		add((rand() % 1000) * (rand() % 1000));
	}
}

int main() {
	Heap<int> test;
	//test.add(1);
	//test.add(2);
	//test.add(3);
	//test.add(4);
	//test.add(5);
	//test.add(6);
	//test.add(7);
	int wybor;
	for (;;) {
		cout << "1.Add node" << endl;
		cout << "2.Delete" << endl;
		cout << "3.Printout" << endl;
		cout << "4.Clear" << endl;
		cout << "5.Add many nodes" << endl;
		cout << "0.Exit" << endl;
		cout << "\n Choice: ";
		cin >> wybor;
		if (wybor == 1) {
			cout << "Enter value you want to add to heap: ";
			cin >> test.data;
			clock_t t1 = clock();
			test.add(test.data);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (wybor == 2) {
			clock_t t1 = clock();
			test.deleteRoot();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (wybor == 3) {
			clock_t t1 = clock();
			test.printout();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (wybor == 4) {
			clock_t t1 = clock();
			test.clear();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (wybor == 5) {
			int number = 0;
			cout << "Enter number of nodes to add: ";
			cin >> number;
			clock_t t1 = clock();
			test.addTest(number);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else {
			test.clear();
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}