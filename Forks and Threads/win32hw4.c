#include <windows.h>
#include <stdio.h>

char mybuf[59];

int main (int argc, char *argv[])
{
PROCESS_INFORMATION pi;
STARTUPINFO si;
int i;

for(i=1; i<=10; i++)
{
GetStartupInfo(&si);
sprintf(mybuf, "fork.exe %d", i);
ZeroMemory(&si,sizeof(si));
ZeroMemory(&pi,sizeof(pi));
HANDLE errorh =  GetStdHandle(STD_ERROR_HANDLE);
if(!CreateProcess(NULL,mybuf, NULL, NULL,TRUE, 0, NULL, NULL, &si, &pi))
{
	fprintf(errorh, "Create process failed \n");
	return -1;
}

}
WaitForSingleObject(pi.hProcess,INFINITE);

}
