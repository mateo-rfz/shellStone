#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

const char * PROGRAM_NAME;



void
usage ()
{
	perror ("help mesg\n");
	_exit(1);
}


int 
main (int argc , char * argv[])
{
	PROGRAM_NAME = argv[0];
	if (argc > 2)
		usage ();

	mode_t mode;
	int ctn;
	if (argc == 2)
	{
		mode = 777;
		ctn = 1;
	}
	else 
	{
		mode = strtol(argv[1] , NULL , 8);
		ctn = 2;
	}

	char * path = argv[ctn];

	if (mkdir (path , mode) != 0)
		perror("mkdir");
	return 0;
}
