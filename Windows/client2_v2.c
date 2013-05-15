/*
**	Silberschatz Figure 3.27, modified 9/2010 by MCM to implement a simple pipe read process
**		Compile/execute using the Windows Command Line C Compiler (cl)
**
*/

#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 25

int main(VOID)
{
	HANDLE ReadHandle,WriteHandle;
	CHAR buffer[BUFFER_SIZE];
	DWORD read,write;

fprintf(stderr,"Child Process Two Executing\n");

	ReadHandle = GetStdHandle(STD_INPUT_HANDLE);

fprintf(stderr,"Child ready to read from pipe\n");

	if (ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL))
		fprintf(stderr,"\nchild two read from pipe: %s\n",buffer);
	else
		fprintf(stderr,"Error Reading from Pipe in Child 2\n");

fprintf(stderr,"Child 2 Process done reading from pipe\n");
	WriteHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (WriteFile(WriteHandle, buffer, BUFFER_SIZE,&write,NULL))
		fprintf(stderr,"\nchild two wrote to pipe: %s\n",buffer);
	else
		fprintf(stderr,"Error reading from pipe in child 2\n");
fprintf(stderr, "Child 2 is done\n");

	return 0;
}