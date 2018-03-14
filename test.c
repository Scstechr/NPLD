#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/* STACK_SIZE
Defines: Maximum row&column size
Caution: Use malloc to avoid segmentation fault 
	e.g.
	narray_Array *array;
	array = (narray_Array*)malloc(sizeof(narray_Array));
*/

// maximum was 10836 as I tested
// may differ from machine to machine
#define STACK_SIZE 10000

#include "MT.h"
//#include "narray.h"
#include "nlist.h"

void list_ver(){
	int size = 100;
	nlist_List *list = nlist_range(4);
	nlist_print(list);
	nlist_delete(list, 2);
	nlist_print(list);
	free(list);
}

int main(){

	init_genrand((unsigned)time(NULL));
	list_ver();
	return 0;
}
