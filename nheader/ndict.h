/* ndict.h */
/* fake dict structure in C */
#ifndef NDICT_H
#define NDICT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "nlist.h"

typedef struct{
	nlist_List *list;
	int before;
	int after;
} ndict_Item;

typedef struct{
	ndict_Item data[STACK_SIZE];
	int end;
	int start;
	int size;
} ndict_Dict;

ndict_Dict *ndict_init()
{
	ndict_Dict *dict = malloc(sizeof(ndict_Dict));
	dict->start = 0;
	dict->end = -1;
	dict->size = 0;
	return dict;
}

void ndict_setparam(ndict_Dict *dict, int index, nlist_List *list, int before, int after)
{
	if(list->size > 0){
		dict->data[index].list = list;
	}
	if(before > INT_MIN){
		dict->data[index].before = before;
	}
	if(after > INT_MIN){
		dict->data[index].after = after;
	}
}

void ndict_sizecheck(ndict_Dict *dict)
{
	if(dict->size == 0){
		printf("**empty dict**\n");
		assert(0);
	}
}
void ndict_param(ndict_Dict *dict)
{
	// For Debugging
	printf("dict->size:%d, ", dict->size);
	printf("dict->start:%d, ", dict->start);
	printf("dict->end:%d\n", dict->end);
	for(int i = 0; i < dict->size; i++){
		printf("i:%5d", i);
		nlist_print(dict->data[i].list);
		printf(" | before:%5d <- ", dict->data[i].before);
		if (dict->data[i].after != INT_MAX) {
			printf(" -> after:%5d", dict->data[i].after);
		} else {
			printf(" -> END");
		}
		if(i == dict->start) printf("\tSTART");
		printf("\n");
	}
}

void ndict_append(ndict_Dict *dict, nlist_List *list){
	if(dict->end > 0){
		dict->data[dict->end].after = dict->size;
	} else {
		dict->data[0].after = dict->size;
	}

	ndict_setparam(dict, dict->size, list, dict->end, INT_MAX);

	dict->end = dict->size;
	dict->size++;
}
	

void ndict_print(ndict_Dict *dict){
	if(dict->size == 0){
		printf("empty");
	} else {
		int j = 0;
		printf("\nsize:%3d, int dict w/ int list\n", dict->size);
		for(int i = dict->start; i != INT_MAX; i = dict->data[i].after){
			printf("%3d:", j);
			nlist_simple_print(dict->data[i].list);
			printf("\n");
			j++;
		}
	}
}

void ndict_printd(ndict_Dict *dict){
	if(dict->size == 0){
		printf("empty");
	} else {
		int j = 0;
		printf("\nsize:%3d, int dict w/ int list\n", dict->size);
		for(int i = dict->start; i != INT_MAX; i = dict->data[i].after){
			printf("i:%3d,j:%3d:", i,j);
			nlist_simple_print(dict->data[i].list);
			printf("\n");
			j++;
		}
	}
}
ndict_Dict *ndict_range(int n){
	/* compromised edition */
	/* task: append empty list instead of range */
	ndict_Dict *dict = ndict_init();
	for (int i = 0; i < n; i++){
		nlist_List *list = nlist_range(1);
		ndict_append(dict, list);
	}
	return dict;
}


int ndict_index(ndict_Dict *dict, int index)
{
	/* transfered from nlist_index */
	assert(dict->size > 0);
	assert(index < dict->size);
	int i, j;
	if (index < dict->size / 2){
		j = 0; i = dict->start;
		while(j != index){
			assert(j < dict->size);
			i = dict->data[i].after; j++;
		}
	} else {
		j = dict->size - 1; i = dict->end;
		while(j != index){
			assert(j > 0);
			i = dict->data[i].before; j--;
		}
	}
	return i;
}

ndict_Dict *ndict_delete(ndict_Dict *dict, int index)
{
	/* transfered from nlist_delete */
	nlist_List *list = nlist_range(1);
	list->size = 0;
	if (index == dict->start){
		ndict_setparam(dict, dict->data[index].after, list, -1, INT_MIN);
		dict->start = dict->data[index].after;
	} else if (index == dict->end){
		ndict_setparam(dict, dict->data[index].before, list, INT_MIN, INT_MAX);
		dict->end = dict->data[index].before;
	} else {
		ndict_setparam(dict, dict->data[index].before, list, INT_MIN, dict->data[index].after);
		ndict_setparam(dict, dict->data[index].after, list, dict->data[index].before, INT_MIN);
	}
	dict->size --;
	return dict;
}

#endif
