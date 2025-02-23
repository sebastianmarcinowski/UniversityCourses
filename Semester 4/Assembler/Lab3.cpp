
#include <iostream>

int main()
{
    // Zadanie 3
    // unsigned char a = 0x3;
    // bool y;
    //if (a == 0x32) y = false;
    //else y = true;
    /*_asm {
        mov al, a
        sub al, 0x32 // ewentualnie mozna uzyc XOR
        mov y ,al
    }
    */

    // Zadanie 4
    // for (int i = 0; i != 5; i++) y = y + i;
    // 
    // wersja w C wygodna w zamianie na assemblera
    // int i =0;
    // if (i==5) goto koniec;
    // y += i;
    // i++
    // goto petla:
    // koniec"

    /*int y = 0;
    _asm {
        // wersja a 
        /*
        mov eax, y
        mov edx, 0
            petla:
        mov ebx, edx
        sub ebx, 5
        jz koniec
        add eax, edx
        add edx, 1
        jmp petla
            koniec:
        mov y,eax
    }*/

    /*int y = 0;
    _asm {
        // wersja b
        mov eax, y
        mov ebx, 0
            petla:
        cmp ebx, 5
        jz koniec
        add eax, ebx
        add ebx, 1
        jmp petla
            koniec :
        mov y, eax
    }*/

    /*int y = 0;
    _asm {
        // werscja c for( int i=5; i!=0; i-- ) y -= i;
        mov eax, y
        mov ebx, 4
            petla:
        cmp ebx, 0
        jz koniec
        sub eax, ebx
        sub ebx, 1
        jmp petla
            koniec :
        mov y, eax
    }*/


    // Zadanie 5
    /*int y = 0;
    _asm {
        // wersja a while( y!=5 ) y += 1;
        mov eax, y
        petla:
            mov ebx, eax
            sub ebx, 5
            jz koniec
            add eax, 1
            jmp petla
        koniec :
            mov y, eax
    }*/

    /*int y = 0;
    _asm {
        //wersja b while( y!=5 ) y += 1;
        mov eax, y
        petla:
            cmp eax, 5
            jz koniec
            add eax, 1
            jmp petla
        koniec:
            mov y, eax
    }*/

    int y = 0;
    _asm {
        // wersja c  do{ y += 1; } while( y!=5 );
        mov eax, y
        petla :
            add eax, 1
            XOR eax, 5 
            jnz koniec
            jmp petla
        koniec :
            mov y, eax
    }


    std::cout << y << std::endl;
}
