#include <iostream>

int main()
{
    unsigned char a = 128;
    unsigned char b = 128;
    unsigned short c;
    unsigned short c1;

 

    /*
    *  c = a + b;
    std::cout << c << std::endl;
   
    _asm //dodawanie 2 liczb 8 bitowych i wyswietlenie jej za pomoca 16 bitow
    {
        mov AX, 0 // 1-szy argument - gdzie, 2-gi argument - co
        mov AL, a
        mov BX, 0
        mov BL, b
        add AX,BX // wynik zostanie zapisany w AX
        mov c1, AX
    }
    std::cout << c1;
    */

    //c = a * 4;
    //std::cout << c << std::endl;

    _asm //mnożenie  
    {
        mov AX, 0
        mov AL, a
        shl AX, 2
        mov c1, AX
    }
    std::cout << c1;
}
