/* nlist.h */
/* list structure in C */
#ifndef NLIST_H
#define NLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

typedef struct{
	int item;
	int idx;
	double ditem;
	int before;
	int after;
} nlist_Item;

typedef struct{
	nlist_Item data[STACK_SIZE]; // This also has to change to malloc()
	int size;
	int start;
	int end;
} nlist_List;

void nlist_clear(nlist_List *list){
	list->size = 0;
	list->start = 0;
	list->end = -1;
	list->data[0].before = -1;
	list->data[0].after = INT_MAX;
}

nlist_List *nlist_init()
{
	nlist_List *list = (nlist_List*)malloc(sizeof(nlist_List));
	list->size = 0;
	list->start = 0;
	list->end = -1;
	return list;
}

void printt(int item){
	if (item > INT_MIN) printf("%3d\t", item);
	else printf("XXX\t");
}

void nlist_print_param(int index, int n, int before, int after){
	printf("index:");printt(index);
	printf("n:");printt(n);
	printf("before:");printt(before);
	printf("after:");printt(after);
	printf("\n");
}

static void nlist_setparam(nlist_List *list, int index, int n, int before, int after)
{

	/* for debugging */
	// nlist_print_param(index, n, before, after);
	if(n > INT_MIN){
		list->data[index].item = n;
	}
	if(before > INT_MIN){
		list->data[index].before = before;
	}
	if(after > INT_MIN){
		list->data[index].after = after;
	}
}

void nlist_sizecheck(nlist_List *list)
{
	if(list->size == 0){
		printf("**empty list**\n");
		assert(0);
	}
}

void nlist_append(nlist_List *list, int n)
{
	if(list->end > 0){
		list->data[list->end].after = list->size;
	} else {
		list->data[0].after = list->size;
	}

	nlist_setparam(list, list->size, n, list->end, INT_MAX);
	list->data[list->size].idx = list->size;
	
	list->end = list->size;
	list->size++;

	assert(list->size < STACK_SIZE);
}



nlist_List *nlist_range(int n){
	nlist_List *list = (nlist_List*)malloc(sizeof(nlist_List));
	list->size = n;
	list->end = n-1;
	list->start = 0;
	for(int i = 0; i < n; i++){
		nlist_setparam(list, i, i, i-1, i+1);
		list->data[i].idx = i;
	}
	list->data[list->end].after = INT_MAX;
	return list;
}

nlist_List *nlist_zeros(int n){
	nlist_List *list = (nlist_List*)malloc(sizeof(nlist_List));
	list->size = n;
	list->end = n-1;
	list->start = 0;
	for(int i = 0; i < n; i++){
		nlist_setparam(list, i, 0, i-1, i+1);
	}
	list->data[list->end].after = INT_MAX;
	return list;
}

nlist_List *nlist_ones(int n){
	nlist_List *list = (nlist_List*)malloc(sizeof(nlist_List));
	list->size = n;
	list->end = n-1;
	list->start = 0;
	for(int i = 0; i < n; i++){
		nlist_setparam(list, i, 1, i-1, i+1);
	}
	list->data[list->end].after = INT_MAX;
	return list;
}


int nlist_pop(nlist_List *list)
{
	assert (list->size > 0);
	int retnum = list->data[list->end].item;
	list->size--;
	list->data[list->data[list->end].before].after = INT_MAX;
	list->end = list->data[list->end].before;
	return retnum;
}

int nlist_len(nlist_List *list)
{
	return list->size;
}

void nlist_simple_print(nlist_List *list){
	int j = 0; // Safety
	printf("[");
	if (list->size > 0){
		for(int i = list->start; i != INT_MAX; i = list->data[i].after){
			assert(j < list->size);
			printf("%3d ", list->data[i].item);
			j++;
		}
	}
	printf("]");
}

void nlist_print(nlist_List *list)
{
	printf("\nsize:%3d, int list\n", list->size);
	nlist_simple_print(list);
	printf("\n");
}

void nlist_param(nlist_List *list)
{
	// for debugging
	printf("list->size:%d, ", list->size);
	printf("list->start:%d, ", list->start);
	printf("list->end:%d\n", list->end);
	for(int i = 0; i < list->size; i++){
		printf("i:%5d", i);
		printf(" | before:%5d <- ", list->data[i].before);
		printf("[ data:%5d ]", list->data[i].item);
		if (list->data[i].after != INT_MAX) {
			printf(" -> after:%5d", list->data[i].after);
		} else {
			printf(" -> end");
		}
		if(i == list->start) printf("\tstart");
		printf("\n");
	}
}

int *nlist_to_array(nlist_List *list)
{	
	assert(list->size > 0);
	int *array = (int*)malloc(list->size);
	int j = 0; // Safety
	for(int i = list->start; i != INT_MAX; i = list->data[i].after){
		assert(j < list->size);
		array[j] = list->data[i].item;
		j++;
	}
	return array;
}
	
nlist_List *array_to_nlist(int *array, int size)
{
	nlist_List *list = nlist_init();
	int array_size = size;
	for(int i = 0; i < array_size; i++){
		nlist_append(list, array[i]);
	}
	list->start = 0;
	list->end = array_size;
	list->size = array_size;
	return list;
}


int nlist_index(nlist_List *list, int index)
{
	assert(list->size > 0);
	assert(index < list->size);
	int i, j;
	if (index < list->size / 2){
		j = 0; i = list->start;
		while(j != index){
			assert(j < list->size);
			i = list->data[i].after; j++;
		}
	} else {
		j = list->size - 1; i = list->end;
		while(j != index){
			assert(j > 0);
			i = list->data[i].before; j--;
		}
	}
	return i;
}

void nlist_insert(nlist_List *list, int index, int n)
{
	assert(index < list->size);
	if (index == 0){
		nlist_setparam(list, list->size, n, list->data[list->end].before, list->end);
		if(list->size == 0){
			list->data[list->size].after = INT_MAX;
			list->end = 0;
		} else {
			list->data[list->size].after = list->start;
			if(list->size == 1){
				list->data[list->size].before = -1;
				nlist_setparam(list, list->end, INT_MIN, list->size, INT_MIN); 
			} else {
				list->data[list->size].before = -1;
				list->data[list->start].before = list->size;
			}
		}
		list->start = list->size;
	} else {
		int i = list->start; int k = 0;
		for(int j = 1; j < index; j++){
			assert(j < STACK_SIZE);
			i = list->data[i].after;
		}
		if (index == list->size) {
			k = i;
		} else {
			k = list->data[i].after;
		}
		nlist_setparam(list, list->size, n, list->data[k].before, k);
		//INT_MIN -> NO CHANGE
		nlist_setparam(list, list->data[k].before, INT_MIN, INT_MIN, list->size);
		nlist_setparam(list, k, INT_MIN, list->size, INT_MIN);

	}
	int j; j = 0;
	for(int i = list->size;
			i != INT_MAX;
			i = list->data[i].after){
		list->data[i].idx = index + j;
		j++;
	}
	list->size++;
	assert(list->size < STACK_SIZE);
}
void nlist_substitute(nlist_List *list, int index, int n){
	assert(list->size > 0);
	assert(index < list->size);
	int j = nlist_index(list, index);
	list->data[j].item = n;
}


nlist_List *nlist_delete(nlist_List *list, int index)
{
	//assert(index < list->size);
	if (list->size == 1){
		nlist_clear(list);
	} else {
		if (index == list->start){
			nlist_setparam(list, list->data[index].after, INT_MIN, -1, INT_MIN);
			list->start = list->data[index].after;
		} else if (index == list->end){
			nlist_setparam(list, list->data[index].before, INT_MIN, INT_MIN, INT_MAX);
			list->end = list->data[index].before;
		} else {
			nlist_setparam(list, list->data[index].before, INT_MIN, INT_MIN, list->data[index].after);
			nlist_setparam(list, list->data[index].after, INT_MIN, list->data[index].before, INT_MIN);
		}
		list->size --;
	}
	return list;
}

nlist_List *nlist_linspace(int start, int end, int step){
	assert (start > INT_MIN);
	assert (end < INT_MAX);
	/* size check */
	double size; size = (double)(end - start)/step;
	assert (size < STACK_SIZE);

	/* step check */
	if (start > end){
		assert( step < 0 );
	} else {
		assert( step > 0 );
	} 

	nlist_List *list = nlist_init();
	if (start != end){
		for(int i = start; i < end; i += step){
			nlist_append(list, i);
		}
	} else {
		nlist_clear(list);
	}
	return list;
}

#endif
