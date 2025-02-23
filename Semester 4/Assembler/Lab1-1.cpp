
#include <iostream>

int main()
{
    unsigned char a = 3;
    unsigned short y;

    _asm {
        //wersja a
        /*mov AX, 0
        mov AL, a
        mov BX, 0
        mov BL, a
        shl AX, 4
        shl BX, 2
        add AX,BX
        mov y, AX*/

        //wersja b
        /*mov AX, 0
        mov AL, a
        mov BX,0
        mov BL,a
        mov CX,0
        mov CL, a
        shl AX,5
        shl BX,3
        shl CX,2
        sub AX, BX
        sub AX,CX
        mov y, AX*/

        //wersja c
        mov ax,0
        mov al, a
        add ax, ax
        add ax,ax
        mov bx,0
        mov bx,ax
        add ax,ax
        add ax,ax
        add ax,bx
        mov y,ax
    }
    std::cout << y;
}
