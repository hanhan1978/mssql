
#include <stdio.h>
#include <stdlib.h>


int * get_val(int * max_col, int cols);

int main(){


	int cols = 10;

    int * max_col;
    get_val(&max_col, cols);

    int i;
	for( i=0; i< cols; i++){
        printf("max_col = %d \n", max_col[i]);
	}
}


int * get_val(int * max_col, int cols){

    * max_col = (int *) malloc(sizeof(int) * cols);
    int i= 0;
	for( i =0; i < cols ; i++){
	    max_col[i] = i+3;
	}
	return max_col;
}
