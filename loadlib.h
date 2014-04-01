#ifndef FLOADERLIB

#define FLOADERLIB


#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



#define PGMSIZE 22000
#define FRAMELOAD(N_SIZE)   fillbuff(malloc(sizeof(char)*N_SIZE),argv[1]);

/*DO NOT use fillbuff by itself! Call the preprocessor macro FRAMELOAD instead. This is to
avoid having to keep track of pointers.
*/





char *fillbuff(char *MatrixBuffer, char* Fname){
	struct stat buffile;
	int buffile_desc = open(Fname,O_RDONLY);
	fstat(buffile_desc,&buffile);
	void *temp_buff = alloca(sizeof(char)*22000);
	assert(0<read(buffile_desc,temp_buff,22000));
	strcpy(MatrixBuffer,temp_buff);
	return MatrixBuffer;
}


#endif 
//FLOADERLIB