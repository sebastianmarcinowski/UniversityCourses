
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <random>
#include <vector>
using namespace std;


bool wariant = false;
double timeHeap = 0.0;
double timeCount = 0.0;
double timeBucket = 0.0;
char litery[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

//template<typename T>
struct Obiekt {
	double klucz;
	char data;
};


bool kompInt(int a, int b) {
	return a < b;
}

bool kompObj(Obiekt* obj1, Obiekt* obj2) {
	if (obj1->klucz < obj2->klucz) {
		return true;
	}
	else if (obj1->klucz > obj2->klucz) {
		return false;
	}
	else {
		if (obj1->data <= obj2->data) {
			return true;
		}
		else if (obj1->data > obj2->data) {
			return false;
		}
	}
}

int lvl = 0;
template <typename H>
class Heap {
public:
	H data;
	int pojemnosc;
	int rozmiar;
	H* heap = NULL;
	H root;
	template <typename T>
	void addTable(H* tablica, int rt, bool wariant, T komp) {
		heap = tablica;
		if (wariant == true) {
			for (int i = 0; i < rt; i++) {
				BottomUp(i, komp);
			}
		}
		else {
			for (int i = 0; i < rt; i++) {
				TopDown(i, komp);
			}
		}
		rozmiar = rt;
		while (pojemnosc < rozmiar) {
			pojemnosc = pojemnosc * 2;
		}
	}
	template <typename T>
	void TopDown(int index, T komp) {
		if (index <= 0) {
			return;
		}
		else {
			int parent = (index - 1) / 2;
			if (komp(heap[parent], heap[index])) {
				H bufor = heap[index];
				heap[index] = heap[parent];
				heap[parent] = bufor;
				index = parent;
				TopDown(index, komp);
			}
			else {
				return;
			}
		}
	}
	template <typename T>
	void BottomUp(int index, T komp) {
		if (index <= 0) {
			return;
		}
		else {
			int parent = (index - 1) / 2;
			if (komp(heap[parent], heap[index])) {
				H bufor = heap[index];
				heap[index] = heap[parent];
				heap[parent] = bufor;
				index = parent;
				BottomUp(index, komp);
			}
			else {
				return;
			}
		}
	}
	template <typename T>
	void maxHeap(int index, int n, T komp) {
		int maxEl = index;
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		if (leftChild <= (n - 1) && !(komp(heap[leftChild], heap[maxEl]))) {
			maxEl = leftChild;
		}
		if (rightChild <= (n - 1) && !(komp(heap[rightChild], heap[maxEl]))) {
			maxEl = rightChild;
		}
		if (maxEl != index) {
			H bufor = heap[maxEl];
			heap[maxEl] = heap[index];
			heap[index] = bufor;
			maxHeap(maxEl, n, komp);
		}
	}
	template <typename T>
	void minHeap(int index, int n, T komp) {
		int minEl = index;
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		if (leftChild <= (n - 1) && !(komp(heap[leftChild], heap[minEl]))) {
			minEl = leftChild;
		}
		if (rightChild <= (n - 1) && !(komp(heap[rightChild], heap[minEl]))) {
			minEl = rightChild;
		}
		if (minEl != index) {
			H bufor = heap[minEl];
			heap[minEl] = heap[index];
			heap[index] = bufor;
			minHeap(minEl, n, komp);
		}
	}
	template <typename T>
	void sort(bool wariant, T komp) {
		if (wariant == true) {
			for (int i = (rozmiar - 1); i >= 0; i--) {
				H bufor = heap[0];
				heap[0] = heap[i];
				heap[i] = bufor;
				maxHeap(0, i, komp);
			}
		}
		else {
			for (int i = (rozmiar - 1); i >= 0; i--) {
				H bufor = heap[0];
				heap[0] = heap[i];
				heap[i] = bufor;
				minHeap(0, i, komp);
			}
		}

	}
	Heap() {
		rozmiar = 0;
		pojemnosc = 1;
		heap = new H[pojemnosc];
		root = heap[0];
	}
};

const int array_multiplier = 2;

template <typename T>
struct DynamicTable {
	int pojemnosc;
	int rozmiar;
	T data;
	T* test;
	T& operator[](size_t index) {
		return test[index];
	}
	void dodaj(T data);
	void czysc();
	template <typename C>
	void sort(C kom);
	void get_r() {
		return rozmiar;
	}

	DynamicTable(T* t = nullptr, int r = 0, int p = 1) {
		rozmiar = r;
		pojemnosc = p;
		test = t;
		if (!test) {
			test = new T[pojemnosc];
		}
	}
	~DynamicTable() {
		if (test != nullptr)
			delete[] test;
	}
};

template <typename T>
void DynamicTable<T>::dodaj(T data) {
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
}
template <typename T>
void DynamicTable<T>::czysc() {
	test[1];
	rozmiar = 0;
	pojemnosc = 1;
}
template <typename T>
template <typename C>
void DynamicTable<T>::sort(C kom) {
	T temp;
	for (int i = 0; i < rozmiar; i++) {
		bool flaga = false;
		for (int j = 0; j < rozmiar - 1; j++) {
			if (!(kom(test[j], test[j + 1]))) {
				temp = test[j + 1];
				test[j + 1] = test[j];
				test[j] = temp;
				flaga = true;
			}
		}
		if (flaga == false) {
			break;
		}
	}
}

void HeapSort(int tablica[], int rozTab, bool wariant) {
	Heap<int>* heap = new Heap<int>;
	heap->addTable(tablica, rozTab, wariant, kompInt);
	clock_t t1 = clock();
	heap->sort(wariant, kompInt);
	clock_t t2 = clock();
	timeHeap = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "Heap sort time (int): " << timeHeap << endl;
}

template<typename T>
void HeapSortObj(T tablica[], int rozTab, bool wariant) {
	Heap<Obiekt*>* heap = new Heap<Obiekt*>;
	heap->addTable(tablica, rozTab, wariant, kompObj);
	clock_t t1 = clock();
	heap->sort(wariant, kompObj);
	clock_t t2 = clock();
	timeHeap = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "Heap sort time (objects): " << timeHeap << endl;
}


void CountingSort(int tablica[], int rozTab, int m) {
	clock_t t1 = clock();
	int*counts = new int[m];
	for (int i = 0; i < m; i++) {
		counts[i] = 0;
	}
	for (int i = 0; i < rozTab; i++) {
		counts[tablica[i]]++;
	}
	int k = 0;
	for (int i = 0; i < m; i++){
		for (int j = 0; j < counts[i]; j++) {
			tablica[k++] = i;
		}
	}
	clock_t t2 = clock();
	timeCount = (double)(t2 - t1) / CLOCKS_PER_SEC;

	cout << "Counting sort time: " << timeCount <<endl;
	delete [] counts;
}

void BucketSort(int tab[], int n, int m) {
	clock_t t1 = clock();
	DynamicTable<int>* BucketsInt = new DynamicTable<int>[n];
	for (int i = 0; i < n; i++) {
		BucketsInt[tab[i]/(m/n)].dodaj(tab[i]);
	}
	//for (int i = 0; i < n; i++) cout << wiadra[i].rozmiar << endl;
	for (int i = 0; i < n; i++) {
		if (BucketsInt[i].rozmiar > 0) {
			BucketsInt[i].sort(kompInt);
		}
	}
	int k = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < BucketsInt[i].rozmiar; j++) {
			tab[k] = BucketsInt[i][j];
			k++;
		}
	}
	clock_t t2 = clock();
	timeBucket = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "Bucket sort (int* array) time: " << timeBucket << endl;
}


template <typename C>
void BucketSortObj(Obiekt** tab, int n, float m, C kom) {
	clock_t t1 = clock();
	DynamicTable<Obiekt*>* BucketsObj = new DynamicTable<Obiekt*>[n];
	for (int i = 0; i < n; i++) {
		int id = tab[i]->klucz / (m/(float)n);
		BucketsObj[id].dodaj(tab[i]);
	}
	for (int i = 0; i < n; i++) {
		if (BucketsObj[i].rozmiar > 0) {
			BucketsObj[i].sort(kompObj);
		}
	}
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < BucketsObj[i].rozmiar; j++) {
			tab[k] = BucketsObj[i][j];
			k++;
		}
	}
	clock_t t2 = clock();
	timeBucket = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "Bucket sort (T* array) time: " << timeBucket <<endl;
}


template <typename T>
void printout(T* tab, int rozmiar) {
	if (rozmiar < 201) {
		for (int i = 0; i < rozmiar; i++) {
			cout << i << ": " << tab[i] << endl;
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			cout << i << ": " << tab[i] << endl;
		}
		for (int i = 0; i < 3; i++) {
			cout << "." << endl;
		}
		for (int i = 5; i > 0; i--) {
			cout << rozmiar-i << ": " << tab[rozmiar - i] << endl;
		}
	}
 }



void tableComparison(int tab1[], int tab2[], int rozmiar) {
	bool tableCompare = true;
	for (int i = 0; i < rozmiar; i++) {
		if (tab1[i] != tab2[i]) {
			tableCompare = false;
			break;
		}
	}
	if (tableCompare == true) cout << "Tablice sa identyczne" << endl;
	else cout << "Tablice sa rozne" << endl;
}

void tableComparisonObj(Obiekt* tab1[], Obiekt* tab2[], int rozmiar) {
	bool tableCompare = true;
	for (int i = 0; i < rozmiar; i++) {
		if (tab1[i]->klucz != tab2[i]->klucz) {
			tableCompare = false;
			break;
		}
		else if (tab1[i]->data != tab2[i]->data) {
			tableCompare = false;
			break;
		}
	}
	if (tableCompare == true) cout << "Tablice sa identyczne" << endl;
	else cout << "Tablice sa rozne" << endl;
}


void printobj(Obiekt** tab, int rozmiar) {
	if (rozmiar < 201) {
		for (int i = 0; i < rozmiar; i++) {
			cout << i << ": " << tab[i]->klucz << ":" << tab[i]->data << endl;
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			cout << i << ": " << tab[i]->klucz << ":" << tab[i]->data << endl;
		}
		for (int i = 0; i < 3; i++) {
			cout << "." << endl;
		}
		for (int i = 5; i > 0; i--) {
			cout << rozmiar - i << ": " << tab[rozmiar - i]->klucz << ":" << tab[rozmiar - i]->data << endl;
		}
	}
}


int main() {
	srand(0);
	const int len =1000000;
	const int m = 100000000;
	const double m_double = (double)pow(2, 30);
	//Tworzenie tablic liczb calkowitych
	int* tab1 = new int[len];
	int* tab2 = new int[len];
	int* tab3 = new int[len];
	for (int i = 0; i < len; i++) {
		tab1[i] = ((rand()<<15)+rand())%m;
	}
	memcpy(tab2, tab1, len*sizeof(int));
	memcpy(tab3, tab1, len*sizeof(int));
	//Znalezenie max i min elementu do sortowania przez zliczanie
	int minValue = tab2[0];
	int maxValue = tab2[0];
	for (int i = 0; i < len; i++) {
		if (tab2[i] < minValue) minValue = tab2[i];
		if (tab2[i] > maxValue) maxValue = tab2[i];
	}


	//Tworzenie tablic obiektow
	Obiekt** Ftab1 = new Obiekt*[len];
	Obiekt** Ftab2 = new Obiekt*[len];
	for (int i = 0; i < len; i++) {
		Obiekt* temp = new Obiekt();
		temp->klucz = ((rand() << 15) + rand()) / m_double;
		temp->data = 'a' + rand() % 26;
		Ftab1[i] = temp;
	}
	memcpy(Ftab2, Ftab1, len * sizeof(Obiekt*));
	

	cout << "Wyniki sortowania dla: " << len << " elementow" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Sortowanie intow" << endl;
	cout << "------------------------------------------------------" << endl;
	//Dla intow
	printout(tab1, len);
	HeapSort(tab1, len, true);
	printout(tab1, len);
	cout << "\n";
	CountingSort(tab2, len, m+1);
	printout(tab2, len);
	cout << "\n";
	BucketSort(tab3, len, m);
	printout(tab3, len);
	tableComparison(tab1, tab2, len);
	tableComparison(tab1, tab3, len);
	cout << endl;
	cout << "Wyniki sortowania dla: " << len << " elementow" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Sortowanie biektow" << endl;
	cout << "------------------------------------------------------" << endl;
	//Dla obiektow
	printobj(Ftab1, len);
	BucketSortObj(Ftab1, len, (float)1.0, kompObj);
	printobj(Ftab1, len);
	HeapSortObj(Ftab2, len, true);
	printobj(Ftab2, len);
	tableComparisonObj(Ftab1, Ftab2, len);
	cout << "------------------------------------------------------" << endl;
	return 0;
}