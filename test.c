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

// maximum was 10836
// may differ from machine to machine
#define STACK_SIZE 10836

#include "MT.h"
//#include "narray.h"
#include "nlist.h"

//void array_ver(){
//	narray_Array *array = narray_range(1,10000);
//	//narray_print(array);
//	free(array);
//}

void list_ver(){
	int size = 100;
	nlist_List *list = nlist_init();
	nlist_append(list, 2);
	nlist_append(list, 4);
	nlist_append(list, 9);
	nlist_append(list, 6);
	nlist_append(list, 7);
	nlist_print(list);
	nlist_delete(list, 3);
	nlist_print(list);
	free(list);
}

int main(){

	init_genrand((unsigned)time(NULL));
	list_ver();
	return 0;
}
