/*
**	Modified 9/2010 by MCM from Silberschatz Figures 3.12 & 3.26 
**		Compile/execute using the Windows Command Line C Compiler (cl)
**		Creates a pipe and forks off two children with stdout/stdin connected to the write & read ends of the pipe
**		and then forks of two children -- first child writes to stdout, second child reads from stdin
**
**		Note that the StdErr handle is passed to the children to allow debugging/diagnostic output!
**		Note also that parameter 5 of the CreateProcess call must be TRUE, not FALSE for child to inherit handles!
**		Finally, in Windows it does not matter which order the processes are created in
*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
int Output;
STARTUPINFO si;
PROCESS_INFORMATION pi;
STARTUPINFO si2;
PROCESS_INFORMATION pi2;
HANDLE ReadHandle, WriteHandle;
HANDLE ReadHandle2,WriteHandle2;
SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof (pi));
	ZeroMemory(&si2, sizeof(si2));
	si2.cb = sizeof(si2);
	ZeroMemory(&pi2, sizeof (pi2));


Output = CreateFile("mytypescript.txt", GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
si.hStdOutput = Output;
	//si.dwFlags = STARTF_USESTDHANDLES;

	if (!CreateProcess("C:\\Windows\\System32\\cmd.exe", "dir",
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{

		fprintf(stderr, "Create Process directly has Failed\n");
		return -1;
	}



	if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0)){
		fprintf(stderr, "Create Pipe Failed\n");
		return 1;
	}
	if (!CreatePipe(&ReadHandle2, &WriteHandle2, &sa, 0)){
		fprintf(stderr, "Create Pipe 2 Failed\n");
		return 1;
	}

	GetStartupInfo(&si);
	GetStartupInfo(&si2);


	si.hStdOutput = WriteHandle2;
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.hStdInput = ReadHandle;
	si.dwFlags = STARTF_USESTDHANDLES;
	
//

	si2.hStdInput = ReadHandle2;
	si2.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si2.hStdOutput = WriteHandle;
	si2.dwFlags = STARTF_USESTDHANDLES;




	
	WaitForSingleObject(pi2.hProcess, INFINITE);
	printf ("parent:Child one Completed\n");

	WaitForSingleObject(pi.hProcess, INFINITE);
	printf ("parent:Child two Completed\n");
	
 
	
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);

}

		
