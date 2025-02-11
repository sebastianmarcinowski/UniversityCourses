#include <iostream>

int main()
{
    //zadanie 1
    //unsigned char a = 3;
    //unsigned short y;

    //y = a * 20;

    //_asm { /* //wersja a
    //    MOV ax, 0
    //    MOV al, a
    //    MOV bx, 0
    //    MOV bl, a
    //    SHL ax, 4
    //    SHL bx, 2
    //    ADD ax, bx
    //    MOV y, ax*/
    //    /* MOV ax, 0 //wersja b
    //     MOV al, a
    //     MOV bx, 0
    //     MOV bl, a
    //     MOV cx, 0
    //     MOV cl, a
    //     SHL ax, 5
    //     SHL bx, 3
    //     SHL cx, 2
    //     SUB ax, bx
    //     SUB ax, cx
    //     MOV y, ax
    //     */
    //    MOV ax, 0 //wersja c
    //    MOV al, a
    //    ADD ax, ax
    //    ADD ax, ax
    //    MOV bx, 0
    //    MOV bx, ax
    //    ADD ax, ax
    //    ADD ax, ax
    //    add ax, bx
    //    mov y, ax
    //}
    //std::cout << (int)y;

    //zadanie 2
    //unsigned char a = 5;
    //unsigned char b = 7;
    //unsigned char c = 4;
    //unsigned char y;
    ///* if (a == 0x32)
    //      y = 0;
    //  else
    //      y = 1;
    //      */

    //      /*if ((a == 5) || (b == 7))
    //          y = 0;
    //      else
    //          y = 1;
    //          */
    //_asm {
    //    /* MOV AL, a //wersja a
    //     SUB AL, 0x32
    //     JZ BODY
    //     MOV y, 1
    //     JMP ENDIF
    //     BODY:
    //     MOV y, 0
    //     ENDIF:*/

    //     /*MOV AL, a //wersja b
    //     CMP AL, 0x32
    //     JZ BODY
    //     MOV y, 1
    //     JMP ENDIF
    //     BODY:
    //     MOV y, 0
    //         ENDIF: */

    //         /* MOV AL, a //wersja c
    //          ADD AL, 0xCE
    //          JZ BODY
    //          MOV y, 1
    //          JMP ENDIF
    //          BODY :
    //          MOV y, 0
    //              ENDIF :*/

    //              //zadanie 2.1
    //              /*MOV AL, a     //if ((a == 5) && (b == 7)
    //              CMP AL, 0x5
    //              JNZ elseif
    //              MOV BL, b
    //              CMP bl, 0x7
    //              JNZ elseif
    //              MOV y, 0
    //              JMP endif
    //              elseif:
    //              MOV y,1
    //              endif:*/

    //              /*MOV AL, a     //if ((a == 5) || (b == 7)
    //              CMP AL, 0x5
    //              JZ elseif
    //              MOV BL, b
    //              CMP bl, 0x7
    //              JZ elseif
    //              MOV y, 1
    //              JMP endif
    //              elseif :
    //              MOV y, 0
    //                  endif :*/


    //    MOV CL, c //if (((a == 5) && (b == 7) || (c==4))
    //    CMP CL, 0x4
    //    JZ elseif
    //    MOV AL, a
    //    CMP AL, 0x5
    //    JNZ elseif2
    //    MOV BL, b
    //    CMP bl, 0x7
    //    JNZ elseif2
    //    elseif :
    //    MOV y, 0
    //        JMP endif
    //        elseif2 :
    //    MOV y, 1
    //        endif :

    //        _asm { //y = ((a || b) && c))
    //        MOV CL, c
    //        CMP c, 7
    //        JNZ elseif
    //        MOV AL, a
    //        CMP a, 4
    //        JZ body
    //        MOV BL, b
    //        CMP b, 5
    //        JZ body
    //        JMP elseif
    //        body :
    //        MOV y, 0
    //            JMP endif
    //            elseif :
    //        MOV y, 1
    //            endif :
    //    }

    //}

    //std::cout << "ASM: " << (int)y << std::endl;

    //zadanie 3
    /*
    if (a == 0x32)
        y = false;
    else
        y = true;
    */
    /*
   unsigned char a = 0x32;
   bool y;
    _asm {
        MOV AL, a
        SUB AL, 0x32 //może być też XOR
        MOV y, AL
    }
    std::cout << std::boolalpha << y << std::endl;
    */

    //zadanie 4
/*
for (int i = 0; i != 5; i++) y += i;

//wersja w C wygodna do zmiany na asembler
int i = 0;
petla:
if (i == 5) goto koniec;
y += i;
i++;
goto petla;
koniec:
*/

/*
int y = 0;
_asm {
   MOV EAX, y
   MOV EDX, 0
   petla:
   MOV EBX, EDX
   SUB EBX, 5
   JZ koniec
   ADD EAX, EDX
   ADD EDX, 1
   JMP petla
   koniec:
   MOV y, EAX
}
*/

/*
int y = 0;
_asm {
    MOV EAX, y
    MOV EDX, 0
    petla:
    CMP EDX, 5
    JZ koniec
    ADD EAX, EDX
    ADD EDX, 1
    JMP petla
    koniec :
    MOV y, EAX
}
*/

/*
//for( int i=5; i!=0; i-- ) y -= i;
int y = 0;
_asm {
    MOV EAX, y
    MOV EDX, 5
    petla:
    CMP EDX, 0
    JZ koniec
    SUB EAX, EDX
    SUB EDX, 1
    JMP petla
    koniec :
    MOV y, EAX
}
*/

   //zadanie 5
    //while (y != 5) y += 1;
   /*
    int y = 0;
    _asm {
        MOV EAX, y
        petla:
        MOV EBX, EAX
        SUB EBX, 5
        JZ koniec
        ADD EAX, 1
        JMP petla
            koniec:
        MOV y, EAX
    }
    */

    /*
    int y = 0;
    _asm{
        MOV EAX, y
        petla :
            CMP EAX, 5
            JZ koniec
            ADD EAX, 1
            JMP petla
            koniec :
        MOV y, EAX
    }
    */
    /*
    int y = 0;
    _asm {
        MOV EAX, y
        petla:
        ADD EAX, 1
        XOR EAX, 5
        JZ petla
        MOV y, EAX


    }
    std::cout << y << std::endl;
    */

    //zadanie 6 - zliczanie liczby zer w bajcie
//unsigned char a = 0x13;
//unsigned char licznik = 0;
//unsigned char y;

/*
a = a ^ 0xff; //negujemy bity
while (a != 0) {
    licznik += a & 0x01;
    a >>= 1;
}
std::cout << (int)licznik;
*/
/*
_asm {
    MOV al, a
    XOR al, 0xff
    MOV bl, 0
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV y, bl
}
*/
/*
_asm {
    MOV al, a
    XOR al, 0xff
    MOV bl, 0
    petla:
    MOV dl, al
    SUB dl, 0
    JZ koniec
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    JMP petla
    koniec:
    MOV y, bl

}
*/


/*
_asm {
    MOV al, a
    MOV bl, 0
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV cl, al
    AND cl, 1
    ADD bl, cl
    SHR al, 1
    MOV ah, 0x08
    SUB ah, bl
    MOV y, ah
}
*/

    //zadanie 7 - sprawdzenie parzystosci jedynek w bajcie
    /*
while (a != 0) {
    licznik += a & 0x01; //zliczenie ilości jedynek w liczbie
    a >>= 1;
    }
    y = (licznik & 0x01) ^ 0x01; //sprawdzenie parzystosci
    */
    /*
        _asm {
            MOV al, a
            MOV bl, 0
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            AND bl, 1
            XOR bl, 1
            MOV y, bl
        }
        */
        /*
            _asm {
                MOV al, a
                MOV bl, 0
                petla:
                MOV dl, al
                    SUB dl, 0
                    JZ koniec
                    MOV cl, al
                    AND cl, 1
                    ADD bl, cl
                    SHR al, 1
                    JMP petla
                    koniec :
                AND bl, 1
                XOR bl, 1
                   MOV y, bl

        }
        */
        /*
        _asm {
            MOV al, a
            MOV bl, 0
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            ADD bl, 1
            AND bl, 1
            MOV y, bl
        }
        */

        /*
        _asm {
            MOV al, a
            MOV bl, 0
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            SHL bl, 1
            MOV cl, al
            AND cl, 1
            ADD bl, cl
            SHR al, 1
            MOV y, bl

        }
        */

//a = 0x80;
/*
_asm {
    MOV AL, a
    MOV BL, 0
    MOV CL, 8
    ety1:
    SHR AL, 1
    RCL BL, 1
        DEC CL
        JNZ ety1
        MOV y, BL
}
*/
//_asm {
//    MOV AL, a
//    MOV BL, 0
//    petla:
//    TEST AL, 1
//    JZ dodaj
//    OR BL, 1
//        dodaj:
//    OR BL, 0
//    SHL BL, 1
//    SHR AL, 1
//    JNZ petla
//    MOV y, BL
//}
//    std::cout << (int)y << std::endl;

    //zadanie 8 - zamiana kolejnosci bitow
//unsigned char a = 0x12;
//unsigned char y = 0;
//
//
//_asm {
//    MOV al, a;
//    MOV bl, 0;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    SHL bl, 1;
//    MOV cl, al;
//    AND cl, 1;
//    ADD bl, cl;
//    SHR al, 1;
//    MOV y, bl;
//    
//}
//std::cout << (int)y;

    //zadanie 9 - mnożenie bez uzycia mnozenia
//    /*
//    for (int i = 0; i < 8; i++) {
//        if (a % 2 == 1) y += b << i;
//        a /= 2;
//    }*/
//
//_asm {
//    //wersja A
//    /*MOV AX, 0;
//    MOV BX, 0;
//    MOV AL, a;
//    MOV BL, b;
//    MOV CX, 0;
//sprawdz:
//    MOV DL, BL;
//    AND DL, 1;
//    jz przesun;
//    ADD CX, AX
//        przesun :
//    shl ax, 1;
//    shr bx, 1;
//    JNZ sprawdz;
//    MOV y, CX;*/
//
//    //wersja B
//    /*MOV AX, 0
//    MOV BX, 0
//    MOV AL, a;
//    MOV BL, b;
//    MOV CX, 0;
//    sprawdz:
//    TEST bl, 1;
//    jz przesun;
//    ADD CX, AX
//przesun:
//    shl ax, 1;
//    shr bx, 1;
//    JNZ sprawdz;
//    MOV y, CX;
//    */
//
//    //MOV, ADD, SHR, SHL, JZ, JNZ, JC, JNC
//    MOV AX, 0;
//    MOV BX, 0;
//    MOV AL, a;
//    MOV BL, b;
//    MOV CX, 0;
//sprawdz:
//    SHR BX, 1;
//    JNC przesun;
//    ADD CX, AX;
//przesun:
//    SHL AX, 1;
//    JNZ sprawdz;
//    MOV y, CX;
//}
//
//std::cout << (int)y << std::endl;

    //zadanie 10 - mnożenie floatow
   /* unsigned short a=8;
    unsigned short y;
    y = a * 1.125;
    std::cout << y << std::endl;
    y = a + (a >> 3);
    std::cout << y << std::endl;
    
    _asm {
        MOV AX, a;
        MOV BX, AX;
        SHR AX, 3;
        ADD BX, AX;
        MOV y, BX;
    }
    std::cout << (float)y << std::endl;*/

    ////y = 5.25 * a;
    ////y = (a<<2)+a+(a>>2);

    //zadanie 11
   /* unsigned char a=0x06;
    unsigned char y;*/
    /*if(a < 0x05){
        y = 0;
    }
    else {
        y = 1;
    }*/
    //_asm { //WERSJA A
    //    MOV AL, a;
    //    MOV BL, 0;
    //    SUB AL, 0x05;
    //    JC prawda
    //    MOV BL, 1
    //    JMP koniec
    //        prawda:
    //    MOV BL, 0
    //        koniec:
    //        MOV y, BL
    //}

    //_asm { //WERSJA B
    //    MOV AL, a;
    //    MOV BL, 0;
    //    SUB AL, 0x05;
    //    JC prawda;
    //    MOV BL, 1;
    //    STC; //CLC;
    //    JC koniec; //JNC koniec;
    //    prawda:
    //    MOV BL, 0;
    //    koniec:
    //    MOV y, BL;
    //}

    //_asm { //WERSJA C
    //    MOV AL, a;
    //    MOV BL, 0;
    //    CMP AL, 0x05;
    //    JC prawda;
    //    MOV BL, 1;
    //    STC; //CLC;
    //    JC koniec; //JNC koniec;
    //    prawda:
    //    MOV BL, 0;
    //    koniec:
    //    MOV y, BL;
    //}

    //_asm { //WERSJA D
    //        MOV AL, a;
    //        MOV BL, 0;
    //        ADD AL, -0x05;
    //        JNC prawda;
    //        MOV BL, 1;
    //        STC; //CLC;
    //        JC koniec; //JNC koniec;
    //        prawda:
    //        MOV BL, 0;
    //        koniec:
    //        MOV y, BL;
    //}

    //_asm { //WERSJA E a<=0x05
    //   MOV AL, a;
    //   MOV BL, 0;
    //   SUB AL, 0x05;
    //   JZ prawda;
    //   JC prawda;
    //   MOV BL, 1;
    //   STC; //CLC;
    //   JC koniec; //JNC koniec;
    //   prawda:
    //   MOV BL, 0;
    //   koniec:
    //   MOV y, BL;
    //}

    //_asm { //WERSJA F a>0x05
    //    MOV AL, a;
    //    MOV BL, 0;
    //    SUB AL, 0x05;
    //    JZ prawda;
    //    JC prawda;
    //    MOV BL, 0;
    //    JMP koniec;
    //prawda:
    //    MOV BL, 1;
    //koniec:
    //    MOV y, BL;
    //}
    //std::cout << (int)y;

    //zadanie 12
//int i;
//int y = 0;
//for (i = 0; i < 5; i++) {
//    y += i;
//    }

//_asm { //WERSJA A
//    MOV EAX, 0;
//    MOV EBX, 0;
//petla:
//    MOV ECX, EAX;
//    SUB ECX, 0x05;
//    JNC koniec;
//    ADD EBX, EAX;
//    ADD EAX, 1;
//    JMP petla;
//    koniec:
//    MOV y, EBX;
//}

//_asm { //WERSJA B
//    MOV EAX, 0;
//    MOV EBX, 0;
//petla:
//    CMP EAX, 0x05;
//    JNC koniec;
//    ADD EBX, EAX;
//    ADD EAX, 1;
//    JMP petla;
//    koniec:
//    MOV y, EBX;
//}

//_asm { //WERSJA C
//    MOV EAX, 5;
//    MOV EBX, 0;
//petla:
//    CMP EAX, 0x01;
//    JC koniec;
//    SUB EBX, EAX;
//    SUB EAX, 1;
//    JMP petla;
//    koniec:
//    MOV y, EBX;
//}
//std::cout << y;

    //unia
//typedef union {
    //	unsigned char BYTE;
    //	struct {
    //		unsigned char a : 1;
    //		unsigned char b : 3;
    //		unsigned char c : 4;
    //	}bits;
    //}un_X;
    //un_X x;

    ////x.bits.c = x.bits.a * x.bits.b;
    ///*if (x.bits.a) {
    //	x.bits.c = x.bits.b;
    //}
    //else {
    //	x.bits.c = 0;
    //}*/
    //for (int i = 0; i <= 255; i++) {
    //	x.BYTE = i;
    //	std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    //	x.bits.c = x.bits.a * x.bits.b;
    //	std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    //	x.BYTE = i;
    //	if (x.BYTE & 0x1) {
    //		x.BYTE = (x.BYTE & 0x0f) |((x.BYTE&0x0e) << 3);
    //	}
    //	else {
    //		x.BYTE = x.BYTE & 0x0f;
    //	}
    //	std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    //	x.BYTE = i;
    //	_asm {
    //		MOV CL, x.BYTE;
    //		MOV AL, CL;
    //		MOV BL, CL;
    //		AND CL, 0x01;
    //		JZ elseif;
    //		AND AL, 0X0f;
    //		AND BL, 0x0e;
    //		SHL BL, 3;
    //		OR AL, BL;
    //		SUB CL, CL;
    //		JZ koniec;
    //	elseif:
    //		AND AL, 0x0f;
    //	koniec:
    //		MOV x.BYTE, AL;
    //	}
    //	std::cout << std::hex << "0x" << (int)x.BYTE << "\n";
    //}

//typedef union {
//    unsigned char BYTE;
//    struct {
//        unsigned char a : 3;
//        unsigned char b : 2;
//        unsigned char c : 3;
//    }bits;
//}un_X;
//un_X x;
//for (int i = 0; i <= 255; i++) {
//    x.BYTE = i;
//    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
//    while (x.bits.a != x.bits.c) x.bits.c += x.bits.a++;
//    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
//    while ((x.BYTE & 0x07) != ((x.BYTE >> 5))) {
//        x.BYTE = x.BYTE + (x.BYTE << 5);
//        x.BYTE = (x.BYTE & 0xf8) | ((x.BYTE + 1) & 0x07);
//    }
//    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
//    x.BYTE = i;
//    _asm {
//        MOV CL, x.BYTE;
//        MOV BL, CL;
//        MOV AL, CL;
//        MOV DL, CL;
//    petla:
//        MOV CL, AL;
//        MOV BL, AL;
//        MOV DL, AL;
//        AND CL, 0x07;
//        SHR BL, 5;
//        CMP CL, BL;
//        JZ koniec;
//        SHL DL, 5;
//        ADD AL, DL;
//        MOV BL, AL;
//        AND AL, 0xf8;
//        ADD BL, 1;
//        AND BL, 0X07;
//        OR AL, BL;
//        JMP petla;
//    koniec:
//        MOV x.BYTE, AL;
//    }
//    std::cout << std::hex << "0x" << (int)x.BYTE << "\n";

//typedef union {
//    unsigned char BYTE;
//    struct {
//        unsigned char a : 2;
//        unsigned char b : 4;
//        unsigned char c : 2;
//    }bits;
//}un_X;
//un_X x;
//for (int i = 0; i <= 255; i++) {
//    x.BYTE = i;
//    x.bits.a = 0;
//    std::cout << std::hex << "0x" << (int)x.BYTE << "\n";
//}


//Kolos 1
////zadanie 1
    //std::cout << "Zadanie 1:" << std::endl;
    //unsigned short a = 0x8110;
    //unsigned char b = 0;
    //a = a ^ 0xffff;
    //while (a != 0) {
    //    b += a & 0x01;
    //    a >>= 1;
    //}
    //std::cout << (int)b << std::endl;
    //a = 0x8110;
    //_asm{
    //    MOV AX, a
    //    XOR AX, 0xffff
    //    MOV BX, 0
    //    petla:
    //    MOV DX, AX
    //        SUB DX, 0;
    //        JZ koniec;
    //        MOV CX, AX;
    //        AND CX, 1;
    //        ADD BX, CX;
    //        SHR AX, 1;
    //        SUB DX, DX;
    //        JZ petla;
    //    koniec :
    //        MOV b, BL
    //    
    //}
    //std::cout << (int)b << std::endl;

    //zadanie 2
    //std::cout << "Zadanie 2:" << std::endl;
    //typedef union {
    //    unsigned char BYTE;
    //    struct {
    //        unsigned char a : 3;
    //        unsigned char b : 3;
    //        unsigned char c : 2;
    //    }bits;
    //}un_X;

    //un_X x;
    //for (int i = 0; i <= 255; i++) {
    //    x.BYTE = i;   
    //    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    //    while (x.bits.b < 3) x.bits.b = 2 * x.bits.c++;
    //    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    //    x.BYTE = i;
    //    while ((x.BYTE & 0x38) >> 3 < 3) {
    //        //x.bits.b = 2 * x.bits.c++;
    //        x.BYTE = x.BYTE & 0xc7;
    //        x.BYTE = x.BYTE | (((x.BYTE & 0xc0) >> 3)<<1);
    //        x.BYTE += 0x40;
    //    }
    //    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";y
    //    x.BYTE = i;
    //    _asm {
    //        MOV AL, x.BYTE;
    //    petla:
    //        MOV BL, AL;
    //        AND BL, 0x38;
    //        SHR BL, 3;
    //        SUB BL, 3;
    //        JNC koniec;
    //        MOV BL, AL;
    //        AND AL, 0xc7;
    //        AND BL, 0xc0;
    //        SHR BL, 3;
    //        SHL BL, 1;
    //        OR AL, BL;
    //        ADD AL, 0x40;
    //        STC;
    //        JC petla;
    //    koniec:
    //        MOV x.BYTE, AL;
    //    }
    //    std::cout << std::hex << "0x" << (int)x.BYTE << "\n";
    //}

//Kolos 2


un_X x;
for (int i = 0; i < 255; i++) {
    x.BYTE = i;
    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    while (x.bits.c > 3) x.bits.b = x.bits.b + x.bits.c++;
    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    x.BYTE = i;
    while (x.BYTE >> 5 > 3) {
        x.BYTE = (((x.BYTE & 0x18) + ((x.BYTE & 0xe0) >> 2)) & 0x18) | (x.BYTE & 0x07) | ((x.BYTE & 0xe0) + 0x20);
    }
    std::cout << std::hex << "0x" << (int)x.BYTE << "\t";
    x.BYTE = i;
    _asm {
        mov al, x.BYTE;
        mov bl, al;a
        mov cl, al;
        mov dl, al;
    petla:
        mov bl, al;
        mov cl, al;
        mov dl, al;
        shr cl, 5;
        sub cl, 3;
        jc koniec;
        jz koniec;
        and al, 0x18;
        and bl, 0xe0;
        shr bl, 2;
        add al, bl;
        and al, 0x18;
        and dl, 0x07;
        add cl, 3;
        and cl, 0xe0;
        add cl, 0x20;
        or al, dl;
        or dl, cl;
    koniec:
        mov x.BYTE, al;
    }
    std::cout << std::hex << "0x" << (int)x.BYTE << "\n";
}

// zadanie 1 lk
	// unsigned short a = 12;
	// unsigned short y;
	// y = a * 46.25;
	// std::cout << y << std::endl;
	// y = (a << 5 ) + (a << 3) + (a <<2 ) +(a<<1) + (a >> 2);
	// std::cout << y << std::endl;

	// _asm
	// {
	// 	MOV AX, a;
	// 	MOV BX, 0
	// 	SHL AX, 5
	// 	ADD BX, AX
	// 		MOV AX, a;
	// 	SHL AX, 3
	// 	ADD BX, AX
	// 		MOV AX, a;
	// 	SHL AX, 2
	// 	ADD BX, AX
	// 		MOV AX, a;
	// 	SHL AX, 1
	// 	ADD BX, AX
	// 		MOV AX, a;
	// 	SHR AX, 2
	// 	ADD BX, AX

	// 	MOV y, BX

	// }
	// std::cout << (int)y << std::endl;


(x.BYTE & 32){
    x.BYTE = (x.BYTE & 252) + ((x.BYTE & 12)>>2)
}


return 0;

}