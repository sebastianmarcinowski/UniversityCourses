//SO IS1 224A LAB13
//Sebastian Marcinowski
//ms53692@zut.edu.pl
#include<stdio.h>
#include<sys/types.h>
#include<windows.h>
#include<process.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MEM_SIZE 200
typedef struct {
	char player_move;
	char flaga_ruch1;
	char flaga_ruch2;
	char flaga_p1;
	char flaga_p2;
	char plansza[9];
}Ruch;
bool pm;

bool WinCon(Ruch* buf) {
	if (buf->plansza[0] != NULL) {
		if (buf->plansza[0] == buf->plansza[1] && buf->plansza[0] == buf->plansza[2]) return true;
		else if (buf->plansza[0] == buf->plansza[3] && buf->plansza[0] == buf->plansza[6]) return true;
		else if (buf->plansza[0] == buf->plansza[4] && buf->plansza[0] == buf->plansza[8]) return true;
	}
	if (buf->plansza[1] != NULL) {
		if (buf->plansza[1] == buf->plansza[4] && buf->plansza[1] == buf->plansza[7]) return true;
	}
	if (buf->plansza[2] != NULL) {
		if (buf->plansza[2] == buf->plansza[4] && buf->plansza[2] == buf->plansza[6]) return true;
		else if (buf->plansza[2] == buf->plansza[5] && buf->plansza[0] == buf->plansza[8]) return true;
	}
	if (buf->plansza[3] != NULL) {
		if (buf->plansza[3] == buf->plansza[4] && buf->plansza[3] == buf->plansza[5]) return true;
	}
	if (buf->plansza[6] != NULL) {
		if (buf->plansza[6] == buf->plansza[7] && buf->plansza[6] == buf->plansza[8]) return true;
	}
	return false;
}

void show_board(Ruch* Buf) {
	printf(" %c | %c | %c \n", Buf->plansza[0], Buf->plansza[1], Buf->plansza[2]);
	printf("-----------\n");
	printf(" %c | %c | %c \n", Buf->plansza[3], Buf->plansza[4], Buf->plansza[5]);
	printf("-----------\n");
	printf(" %c | %c | %c \n", Buf->plansza[6], Buf->plansza[7], Buf->plansza[8]);
}

void move(Ruch* Buf, bool pm) {
	int numer = 0;
	if (pm == true) {
		if (Buf->flaga_p1 == 'w') {
			printf("Twoj ruch\n");
			printf("Podaj numer pola [1-9]: ");
			scanf_s("%d", &numer);
			if (numer > 9 || numer < 1) {
				printf("Zly numer pola\n");
				move(Buf,pm);
			}
		}
		else if (Buf->flaga_p1 == 'q') {
			printf("Ruch przeciwnika\n");
			while (Buf->flaga_ruch1 != 'a') {
				Sleep(1);
			}
			return;
		}
	}
	else {
		if (Buf->flaga_p2 == 'w') {
			printf("Twoj ruch\n");
			printf("Podaj numer pola [1-9]: ");
			scanf_s("%d", &numer);
			if (numer > 9 || numer < 1) {
				printf("Zly numer pola\n");
				move(Buf, pm);
			}
		}
		else if (Buf->flaga_p2 == 'q') {
			printf("Ruch przeciwnika\n");
			while (Buf->flaga_ruch2 != 'a') {
				//printf("%c", Buf->flaga_ruch);
				Sleep(1);
			}
			return;
		}
	}
	if (Buf->plansza[numer - 1] != NULL) {
		printf("To pole jest juz zajete\n");
		move(Buf, pm);
	}
	if (Buf->player_move == 'x') {
		Buf->plansza[numer - 1] = 'x';
		Buf->player_move = 'o';
		Buf->flaga_p1 = 'q';
		Buf->flaga_p2 = 'w';
		Buf->flaga_ruch1 = 's';
		Buf->flaga_ruch2 = 'a';
	}
	else if(Buf->player_move == 'o') {
		Buf->plansza[numer - 1] = 'o';
		Buf->player_move = 'x';
		Buf->flaga_p2 = 'q';
		Buf->flaga_p1 = 'w';
		Buf->flaga_ruch1 = 'a';
		Buf->flaga_ruch2 = 's';
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Argument error\n");
		return 1;
	}
	HANDLE MapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MEM_SIZE, (LPCWSTR)argv[1]);
	if (MapFile == NULL) {
		printf("Error create file mapping\n");
		return 1;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (LPCWSTR)argv[1]);
		if (MapFile == NULL) {
			printf("Error open file mapping\n");
			return 1;
		}
		pm = false;
		//printf("2");
	}
	else {
		//printf("1");
		pm = true;
	}
	Ruch* Buf = (Ruch*)MapViewOfFile(MapFile, FILE_MAP_ALL_ACCESS, 0, 0, MEM_SIZE);
	if (Buf == NULL) {
		printf("Could not map view of file\n");
		CloseHandle(MapFile);
		return 1;
	}
	for (int i = 0; i < 9; i++) {
		Buf->plansza[i] = NULL;
	}
	Buf->player_move = 'x';

	if (pm == false && Buf->player_move == 'x') {
		Buf->flaga_p2 = 'q';
	}
	else if (pm == false && Buf->player_move == 'o') {
		Buf->flaga_p2 = 'w';
	}
	else if (pm == true && Buf->player_move == 'o') {
		Buf->flaga_p1 = 'q';
	}
	else if (pm == true && Buf->player_move == 'x') {
		Buf->flaga_p1 = 'w';
	}

	while (WinCon(Buf) != true) {
		show_board(Buf);
		move(Buf, pm);
	}
	show_board(Buf);
	if (Buf->player_move == 'x') {
		printf("Wygral gracz O");
	}
	else {
		printf("Wygral gracz X");
	}

	if (!UnmapViewOfFile(Buf)) {
		printf("Could not unmap view of file\n");
		CloseHandle(MapFile);
		return 1;
	}

	CloseHandle(MapFile);
	return 0;
}