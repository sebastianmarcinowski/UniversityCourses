//SO IS1 224A LAB09
//Sebastian Marcinowski
//ms53692@zut.edu.pl
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<windows.h>
#include<process.h>
#include<stdlib.h>

int main(int argc, char **argv) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi1[3];
	PROCESS_INFORMATION pi2[3];
	memset(&pi1, 0, sizeof(pi1));
	memset(&pi2, 0, sizeof(pi2));
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	if (argc != 2) {
		printf("Missing Argument");
		return 1;
	}
	int d = strlen(argv[1]);
	char x[26] = {0};
	if (d > 25 || d < 1) {
		printf("Wrong argument");
		return 1;
	}
	strcpy_s(x, argv[1]);
	if (d == 1) {
		return atoi(x);
	}
	char s1[13] = { 0 };
	char s2[13] = { 0 };
	for (int i = 0; i <(d/2); i++) {
		s1[i] = x[i];
		s2[i] = x[i + d / 2];
	}
	if (d % 2 != 0) s2[(d/2)] = x[d-1];
	//printf("%s\n", s1);
	//printf("%s\n", s2);
	char cmd1[100], cmd2[100];
	sprintf_s(cmd1, "%s %s", argv[0], s1);
	sprintf_s(cmd2, "%s %s", argv[0], s2);
	if (CreateProcessA(NULL, cmd1, NULL, NULL, 0, 0, NULL, NULL, &si, pi1) == 0) {
		printf("Error 1");
		return 1;
	}
	if(CreateProcessA(NULL, cmd2, NULL, NULL, 0, 0, NULL, NULL, &si, pi2) == 0){
		printf("Error 2");
		return 1;
	}
	WaitForSingleObject(pi1->hProcess, INFINITE);
	WaitForSingleObject(pi2->hProcess, INFINITE);
	DWORD exitcode1;
	GetExitCodeProcess(pi1->hProcess, &exitcode1);
	DWORD exitcode2;
	GetExitCodeProcess(pi2->hProcess, &exitcode2);
	printf_s("\n%d %d\t%s %d", GetCurrentProcessId(),GetProcessId(pi1->hProcess),s1, exitcode1);
	printf_s("\n%d %d\t%s %d", GetCurrentProcessId(), GetProcessId(pi2->hProcess), s2, exitcode2);
	return exitcode1+exitcode2;
}