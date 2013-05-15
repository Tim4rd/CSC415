/*
**	Silberschatz Figure 3.27, modified 9/2010 by MCM to implement a simple write to pipe process
**		Compile/Execute using the Windows command line C compiler (cl)!
**
*/

#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 25

int main(int argc, char *argv[])
{
	HANDLE WriteHandle;
	HANDLE ReadHandle;
	CHAR buffer[BUFFER_SIZE]="Greetings CSC415!\n ";
	DWORD write,read;

fprintf(stderr,"Child Process One Executing\n");

	WriteHandle = GetStdHandle(STD_OUTPUT_HANDLE);

fprintf(stderr, "Child one ready to write to pipe\n");

	if (WriteFile(WriteHandle, buffer, BUFFER_SIZE, &write, NULL))
		fprintf(stderr,"child one wrote to pipe: %s\n",buffer);
	else
		fprintf(stderr, "Child one error writing to Pipe");

fprintf(stderr,"Child Process one done writing to pipe\n");
	
	ReadHandle = GetStdHandle(STD_INPUT_HANDLE);

fprintf(stderr, "Child Process one ready to read from pipe\n");

	if (ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL))
		fprintf(stderr, "child one read from pipe: %s\n",buffer);
	else
		fprintf(stderr, "Child one error reading from pipe\n");
fprintf(stderr, "Child process one done!\n");

	return 0;
}
