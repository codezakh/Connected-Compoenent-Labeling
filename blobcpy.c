#include <stdio.h>
#include "loadlib.h"
#define TRUE -5
#define FALSE -10
#define X_OFFSET(i)  (i%161)
#define ROW_OFFSET(i) ((int)((i)/160))
#define OBJOFFSET(n)  n-97
struct object {
	int y_max;
	int y_min;
	int x_max;
	int x_min;
	char oflag;
};

int check_neighbors(int *current_position,char *FRef){
	int check_table[13];
	check_table[0] = (*current_position) - 1; //left
	check_table[1] = (*current_position) - 161;     //assigns search positions in a 3x3 grid outside the 
	check_table[3] = (*current_position) - 162; //top left
	check_table[2] = (*current_position) - 160; //top right
	
	check_table[4] = (*current_position) -322; //
	check_table[5] = (*current_position) -323;
	check_table[6] = (*current_position) -321;
	check_table[7] = (*current_position) -463; //right
	check_table[8] = (*current_position) -2;
	check_table[9] = (*current_position) -159;
	check_table[10] = (*current_position) - 463;
	check_table[11] = (*current_position) - 461;
	check_table[12] = (*current_position) - 460;
	int i; //for loop variable
	int b_count = 0; //will hold sum of all the 1s
	for(i=0;i<13;i++){ //iterates through all locations to be searched
		if(check_table[i]<0 || check_table[i] > 19320 || FRef[check_table[i]] == '\n') continue; //bounds checking
		switch (FRef[check_table[i]]){ //if there is a 1, counts it, 0, does nothing, flag found, returns it
			case '1':
				b_count++;
				break;
			case '0':
				break;
			default:
				return FRef[check_table[i]];
				break;
		}
		if(b_count>3) return 1;
	}
	
	return 0;
}





int main(int argc, char *argv[]){ //filename must be specified as command line arg
	struct object object_array[50];
	char *FRef = FRAMELOAD(PGMSIZE) //loads the file into the fref
	int i = 0;
	int sweep_flag;
	char obj = 'a';
	while(FRef[i] != '\0'){
		if(FRef[i] == '1'){
			sweep_flag = check_neighbors(&i,FRef);
			switch (sweep_flag){
				case 0:
					break;
				case 1:
					FRef[i] = obj; //starts a new object
					object_array[obj-97].x_min = i;
					object_array[obj-97].y_min = i;
					object_array[obj-97].x_max = i;
					object_array[obj-97].y_max = i;
					object_array[obj-97].oflag = obj;
					obj++;
					break;
				default:
					FRef[i] = sweep_flag; //adds to an old object
					if(X_OFFSET(i) < X_OFFSET(object_array[sweep_flag-97].x_min)) object_array[sweep_flag-97].x_min = i; 
					if(X_OFFSET(i) > X_OFFSET(object_array[sweep_flag-97].x_max)) object_array[sweep_flag-97].x_max = i; 
					if(ROW_OFFSET(i) > ROW_OFFSET(object_array[sweep_flag-97].y_max)) object_array[sweep_flag-97].y_max = i; 
					if(ROW_OFFSET(i) < ROW_OFFSET(object_array[sweep_flag-97].y_min)) object_array[sweep_flag-97].y_min = i; 

					break;
			}
		}
	i++;
	}

	int q = 0;
	while(FRef[q] != '\0'){
		printf("%c",FRef[q]);
		q++;
	}


return 0;
}
