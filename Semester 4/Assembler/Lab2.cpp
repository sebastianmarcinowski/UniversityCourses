// Lab2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.


#include <iostream>

int main()
{
	unsigned char a = 5;
	unsigned char b = 7;
	unsigned char c = 4;
	unsigned char y;

	/* zadanie 2
	if (a == 0x32) {
		y = 0;
	}
	else 
		y = 1;
	std::cout << (int)y << std::endl;
	*/

	_asm {
		//Zadanie 2
		
		//Wersja a
		/*MOV AL, a
		SUB AL, 0x32
		JZ BODY
		MOV y, 1
		JMP endif
		BODY:
		MOV y, 0
		endif:*/

		//wersja b
		/*mov AL, a
		cmp AL, 0x32
		jz body
		mov y,1
		jmp endif
		body:
		mov y, 0
		endif:*/

		//wersja c
		/*mov al,a
		add al,-0x32
		jz body
		mov y,1
		jmp endif
		body:
		mov y, 0
		endif:*/


		// Zadanie 2.1 if(a==5) && (b==7)
		/*mov al,a 
		cmp al,0x5
		jnz elseif
		mov bl, b
		cmp bl,0x7
		jnz elseif
		mov y,0
		jmp endif
		elseif:
		mov y,1
		endif:*/

		// Zadanie 2.2 if(a==5) || (b==7)
		/*mov al,a 
		cmp al, 0x5
		jz endif
		mov bl,b
		cmp bl, 0x7
		jz endif
		mov y,1
		jmp elseif
		endif:
		mov y,0
		elseif:*/

		// zadanie 2.3 if (a==5) && (b==7) || (c==4)
		mov cl, c
		cmp cl, 0x4
		jz elseif
		mov al,a
		cmp al, 0x5
		jnz elseif2
		mov bl, b
		cmp bl, 0x7
		jnz elseif2
		elseif :
		mov y, 0
		jmp endif
		elseif2:
		mov y,1
		endif:
	}
	std::cout << "ASM:" << (int)y << std::endl;
}
