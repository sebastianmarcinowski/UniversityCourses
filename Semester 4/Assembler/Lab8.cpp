#include <iostream>
using namespace std;
int main() {

	//Zadanie 14
	//typedef union {
	//	unsigned char BYTE;
	//	struct {
	//		unsigned char a : 1;
	//		unsigned char b : 3;
	//		unsigned char c : 4;
	//	}bits;
	//}un_X;
	//un_X x;

	///*if (x.bits.a) {
	//	x.bits.c = x.bits.b;
	//}
	//else {
	//	x.bits.c = 0;
	//}*/


	//for (int i = 0; i <= 255; i++) {
	//	x.BYTE = i;
	//	cout << hex << "0x" << (int)x.BYTE << "\t";
	//	x.bits.c = x.bits.a * x.bits.b;
	//	cout << hex << "0x" << (int)x.BYTE << "\t";
	//	x.BYTE = i;
	//	//x.bits.c = 0;
	//	if ((x.BYTE & 0x1)) {
	//		x.BYTE =(x.BYTE & 0x0f) | ((x.BYTE & 0x0e) << 3);
	//	}
	//	else {
	//		x.BYTE = x.BYTE & 0x0f;
	//	}
	//	cout << hex << "0x" << (int)x.BYTE << "\t";
	//	x.BYTE = i;
	//	__asm {
	//		mov al, x.BYTE;
	//		mov bl, al;
	//		mov cl, al;
	//		and cl, 0x1;
	//		jz inny;
	//		and al, 0x0f;
	//		and bl, 0x0e;
	//		shl bl, 3;
	//		or al, bl;
	//		sub cl, cl;
	//		jz koniec;
	//	inny:
	//		and al, 0x0f;
	//	koniec:
	//		mov x.BYTE, al;
	//	}
	//	cout << hex << "0x" << (int)x.BYTE << "\n";
	//}


	//Zadania dodatkowe 
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 3;
			unsigned char b : 2;
			unsigned char c : 3;
		}bits;
	}un_X;
	un_X x;

	//while(x.bits.a != x.bits.c) x.bits.c += x.bits.a++;

	for (int i = 0; i <= 255; i++) {
		x.BYTE = i;
		cout << hex << "0x" << (int)x.BYTE << "\t";
		while (x.bits.a != x.bits.c) x.bits.c += x.bits.a++;
		cout << hex << "0x" << (int)x.BYTE << "\t";
		x.BYTE = i;
		while ((x.BYTE & 0x07) != (x.BYTE >> 5)) {
			x.BYTE = x.BYTE + (x.BYTE << 5);
			if ((x.BYTE & 0x07) == 0x07) x.BYTE = x.BYTE - 7;
			else {
				x.BYTE = x.BYTE + 1;
			}
		}
		cout << hex << "0x" << (int)x.BYTE << "\t";
		x.BYTE = i;
		__asm {
			mov al, x.BYTE;
		petla:
			mov bl, al;
			mov cl, al;
			mov dl, al;
			and cl, 0x07;
			shr dl, 5;
			cmp cl, dl;
			jz koniec;
			shl bl, 5;
			add al, bl;
			mov dl, al;
			and dl, 0x07;
			cmp dl, 0x07;
			jz odejmij;
			add al, 1;
			jmp petla;
		odejmij:
			sub al, 0x07;
			jmp petla;
		koniec:
			mov x.BYTE, al;
		}
		cout << hex << "0x" << (int)x.BYTE << "\n";
	}


	return 0;
}