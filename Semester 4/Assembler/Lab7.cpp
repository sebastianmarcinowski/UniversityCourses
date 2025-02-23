#include <iostream>
using namespace std;
int main()
{
    typedef union {
        unsigned char BYTE;
        struct {
            unsigned char a : 2;
            unsigned char b : 3;
            unsigned char c : 3;
        }bits;
    }un_X;

    un_X x;
    x.BYTE = 0;
    //x.bits.a = 2;
    //x.bits.b = 2;
    //x.bits.c = 2;

    //for (int i = 0; i <= 255; i++) {
    //    x.BYTE = i;
    //    cout << hex << "0x" << (int)x.BYTE << "\t";
    //    x.bits.a = x.bits.c;
    //    cout << hex << "0x" << (int)x.BYTE << "\t";
    //    x.BYTE = i;
    //    x.BYTE = (x.BYTE & 0xfc) | ((x.BYTE & 0x60) >> 5);
    //    cout << hex << "0x" << (int)x.BYTE << "\t";

    //    __asm { 
    //        mov al, x.BYTE;
    //        mov bl, al;
    //        and al, 0xfc;
    //        and bl, 0x60;
    //        shr bl, 5;
    //        or al, bl;
    //        mov x.BYTE, al;
    //    }
    //    cout << hex << "0x" << (int)x.BYTE << endl;

    //}


    /*for (int i = 0; i <= 255; i++) {
        x.BYTE = i;
        cout << hex << (int)x.BYTE << "\t";
        x.bits.c = 0;
        x.bits.c = x.bits.a + x.bits.b;
        cout << hex << (int)x.BYTE << "\t";
        x.BYTE = i;
        x.BYTE = (x.BYTE & 0x1f) | ((x.BYTE & 0x3) + ((x.BYTE & 0x1c) >> 2)) << 5;
        cout << hex << (int)x.BYTE << "\t";
        x.BYTE = i;
        __asm {
            mov cl, x.BYTE;
            mov al, cl;
            mov bl, cl;
            and cl, 0x1f;
            and al, 0x3;
            and bl, 0x1c;
            shr bl,2
            add al, bl;
            shl al, 5;
            or cl, al;
            mov x.BYTE, cl;
        }
        cout << hex << (int)x.BYTE << "\n";
    }*/




    
    //Zadanie 13
    for (int i = 0; i <= 255; i++) {
        x.BYTE = i;
        cout << hex << (int)x.BYTE << "\t";
        if (x.bits.c == 1) x.bits.a = x.bits.b;
        cout << hex << (int)x.BYTE << "\t";
        x.BYTE = i;
        if ((x.BYTE & 0xe0) == 0x20) x.BYTE = (x.BYTE & 0xfc) | ((x.BYTE & 0x0c) >> 2);
        cout << hex << (int)x.BYTE << "\t";
        x.BYTE = i;
        __asm {
            mov al, x.BYTE;
            mov bl, al;
            mov cl, al;
            and cl, 0xe0;
            sub cl, 0x20;
            jnz koniec;
            and al, 0xfc;
            and bl, 0x0c;
            shr bl, 2;
            or al,bl
            koniec:
            mov x.BYTE, al;
        }
        cout << hex << (int)x.BYTE << "\n";
    }



}