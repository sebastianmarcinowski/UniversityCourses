#include <iostream>
using namespace std;
int main()
{

    //Zadanie 10
    /*unsigned short a = 11;
    unsigned short y;
    y = a * 1.125;
    cout << int(y) << endl;
    y = a + (a >> 3); //przesuniecie w prawo umozliwia zrobienie ulamkow
    cout << int(y) << endl;
    
    __asm {
        mov ax, a;
        mov bx, a;
        shr bx, 3;
        add ax, bx;
        mov y, ax;
    }
    y = a * 1.125;
    cout << int(y) << endl;*/

    //Zadanie 11
    //unsigned char a = 0x03;
    //unsigned char y;
    //if (a < 0.5) y = 0;
    //else y = 1;

   //__asm {
        //Wersja A
        /*mov al, a;
        mov bl, 0;
        sub al, 0x05;
        JC zero;
        mov bl, 1;
        jmp koniec;
        zero:
        mov bl, 0;
        koniec:
        mov y, bl;*/

        //Wersja B
        //mov al, a;
        //mov bl, 0;
        //sub al, 0x05;
        //JC zero;
        //mov bl, 1;
        //cnc; // nie potrzebne ale gdy niewiadomo co z flaga to w sumioe git opcja
        //jnc koniec;
        //zero:
        //mov bl, 0;
        //koniec:
        //mov y, bl;

        // Wersja C
        //mov al, a;
        //mov bl, 0;
        //cmp al, 0x05;
        //jc zero;
        //mov bl, 1;
        //cnc; // nie potrzebne ale gdy niewiadomo co z flaga to w sumioe git opcja
        //jnc koniec;
        //zero:
        //mov bl, 0;
        //koniec:
        //mov y, bl;

        //Wersja D
        //mov al, a;
        //mov bl, 0;
        //add al, -0x05;
        //jnc zero;
        //mov bl, 1;
        //jmp koniec;
        //zero:
        //mov bl, 0;
        //koniec:
        //mov y, bl;

        //Wersja E if a<=0x05 y = 0  else y=1
        /*mov al, a;
        mov bl, 0;
        sub al, 0x05;
        jz zero;
        JC zero;
        mov bl, 1;
        jmp koniec;
        zero:
        mov bl, 0;
        koniec:
        mov y, bl;*/

        //Wersja F
        /*mov al, a;
        mov bl, 0;
        sub al, 0x05;
        jz jeden;
        JC jeden;
        mov bl, 0;
        jmp koniec;
        jeden:
        mov bl, 1;
        koniec:
        mov y, bl;*/
    //}
    //cout << int(y);


    //Zadanie 12
    //int y = 0;
    //int i = 5;
    //for (i = 0; i < 5; i++) y += i;
    //__asm {
        //Wersja A
        /*mov eax, i;
        mov ebx, 0;
        petla:
        mov ecx, eax;
        sub ecx, 5;
        jnc koniec;
        add ebx, eax;
        add eax, 1;
        jmp petla;
        koniec:
        mov y, ebx;*/

        //Wersja B
        /*mov eax, 0;
        mov ebx, 0;
        petla:
        cmp eax, i;
        jnc koniec;
        add ebx, eax;
        add eax, 1;
        jc petla;
        koniec:
        mov y, ebx;*/

        //Wersja C
        /*mov eax, i;
        mov ebx, 0;
        petla:
        cmp eax, 1;
        jc koniec;
        sub ebx, eax;
        sub eax, 1;
        jnc petla;
        koniec:
        mov y, ebx;*/
    //}
    //cout << int(y);

    //Zadanie 13
    unsigned char a;
    unsigned char b;
    unsigned char c;
    __asm {

    }
    return 0;
}
