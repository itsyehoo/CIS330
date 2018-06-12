#include <stdio.h>
#include <stdlib.h>
#include <printf.h>


int main(int argc, char* argv[])
{
	if (argc != 3) //no arguments
    	{
        	printf("Usage: %s <file1> <file2> \n", argv[0]);
    	}	

	FILE *f_in, *f_out;
	int buffSize;
	int *buffer;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");

	if(!f_in)
	{
		printf("File could not open \n");
	}

	buffSize = 100;
	buffer = malloc(buffSize);
	 
	for(int i = 0; i < 5; i++)
	{
		fread(buffer, sizeof(int), 5, f_in);
		fseek(f_in, 20, SEEK_CUR);
		buffer = buffer + 5;
	}

	buffer = buffer - 25;

	for(int i = 0; i < 25; i++)
	{
		fprintf(f_out, "%d \n", buffer[i]); //%d \n
		//printf("%d \n", buffer[i]);
		
	}

	fclose(f_in);
	fclose(f_out);
    free(buffer);


	return 0;
}
