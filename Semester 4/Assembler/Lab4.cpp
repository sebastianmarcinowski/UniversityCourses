#include <iostream>

int main()
{

    unsigned char a = 0x12;
    unsigned char x = 0;
    // Zadanie 6 zliczanie ilosci 0 w liczbach
    //a = a ^ 0xff;
    //while (a != 0) {
    //    x += a & 0x01;
    //    a >>= 1;
    //}
    //_asm {
        // wersja A
        /*mov al, a
        xor al,0xff
        mov bl,0
        mov cl,al
        and cl,0x01
        add bl,cl
        shr al,1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al,1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov x,bl*/

        // wersja B
        /*mov al, a
        xor al, 0xff
        mov bl, 0
        petla:
        mov dl, al
        sub dl,0
        jz koniec
        mov cl, al
        and cl,1
        add bl, cl
        shr al,1
        jmp petla
        koniec:
        mov x,bl*/

        //wersja C
        /*mov al, a
        mov bl, 0
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov dl, 0x08
        sub dl, bl
        mov x,dl */

    //}
 

    // Zadanie 7 zliczanie ilosci jedynek i sprawdzanie czy jest ona parzysta
    /*while (a != 0) {
        x += a * 0x01;
        a >>= 1;
    }
    x = (x & 0x01) ^ 0x01;
    */
    _asm{
        // wersja A
        /*mov al, a
        mov bl, 0
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        and bl,1
        xor bl,1
        mov x,bl*/
        
        // wersja B
        /*mov al, a
        mov bl, 0
        petla:
        mov dl, al
        sub dl, 0
        jz koniec
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        jmp petla
        koniec :
        and bl,1
        xor bl,1
        mov x, bl*/

        //wersja C
        /*mov al, a
        mov bl, 0
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov cl, al
        and cl, 0x01
        add bl, cl
        shr al, 1
        mov dl, 0x08
        sub dl, bl
        add bl,1
        and bl,1
        mov x, bl*/
    }
    unsigned char c = 0x12;
    unsigned char b = 0x12;
    unsigned char y;
    unsigned char i;
    // Zadanie 8 zamiana kolejnosci bitow w bajcie
    _asm {
        mov al, c
        mov bl,0
        mov cl,al
        and cl,1
        add bl,cl
        shr al,1
        shl bl,1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        shl bl, 1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        shl bl, 1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        shl bl, 1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        shl bl, 1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        shl bl, 1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        shl bl, 1
        mov cl, al
        and cl, 1
        add bl, cl
        shr al, 1
        mov y,bl

        //wersja C
        mov al, b
        xor bl, bl
        petla:
        test al,1
        shr al, 1
        jz koniec
        shl bl,1
        jmp petla
        koniec:
        mov i,bl
    }
    std::cout << (int)y <<std::endl;
    std::cout << (int)i;
}
