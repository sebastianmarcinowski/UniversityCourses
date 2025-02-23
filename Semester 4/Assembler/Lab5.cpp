#include <iostream>

int main()
{
    
    //short z;
    //unsigned char a;

    //__asm {
    //    xor ax, ax // zerowanie rejestru -> szybsze niz mov ax,0
    //    mov al, -2
    //    cbw
    //    mov z, ax
    //}
    //std::cout << (int)a << std::endl;
    //std::cout << (int)z << std::endl;


    //Zadanie 9
    unsigned char a=136;
    unsigned char b=255;
    unsigned short y =0;
    /*std::string bin = "";
    while (a > 0) {
        if (a % 2 == 1) bin += '1';
        else bin += '0';
        a /= 2;
    }
    for (int i = 0; i < 8; i++) {
        if (bin[i] == '1') {
            y += b << i;
        }
    }*/
    
    /*for (int i = 0; i < 8; i++) {
        if (a % 2 == 1) y += b << i;
        a /= 2;
    }*/



    __asm {
        //Wersja A
        /*mov ax, 0;
        mov bx, 0;
        mov al, 128;
        mov bl, 4;
        mov cx, 0;
        sprawdz:
        mov dl, bl;
        and dl, 1;
        jz przesun;
        add cx, ax;
        przesun:
        shl ax, 1;
        shr bx, 1;
        jnz sprawdz
        mov y, cx;*/

        //Wersja B
        /*mov ax, 0;
        mov bx, 0;
        mov al, 128;
        mov bl, 4;
        mov cx, 0;
        sprawdz:
        test bl, 1;
        jz przesun;
        add cx, ax;
        przesun:
        shl ax, 1;
        shr bx, 1;
        jnz sprawdz
        mov y, cx;*/
        
        // Wersja E (dodatkowa)  MOV, ADD, SHL, SHR, JZ, JNZ, JC, JNC
        mov ax, 0;
        mov bx, 0;
        mov al, a;
        mov bl, b;
        mov cx, 0;
        sprawdz:
        shr bx, 1;
        jnc przesun;
        add cx,ax
        przesun:
        shl ax, 1;
        jnz sprawdz
        mov y, cx

    }
    
    std::cout << (int)y;
}
