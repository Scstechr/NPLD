/* nrandom.h */
/* Header Dedicated to Random Related Subjects */
/* requires nlist.h */
#ifndef NRANDOM_H
#define NRANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "nlist.h"
#include "npoly.h"

int nrand_dist_pick(nlist_List *poly)
{
	int j = 0; double sum = 0.0; double min = 0.0; double max = 0.0;
	double rand = genrand_real1();
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		if (poly->data[i].ditem != 0.0){
			sum += poly->data[i].ditem;
			max = sum;
			if (min < rand && rand < max) break; 
			min = sum;
		}
		j++;
	}
	return j;
}

void nrand_dist_check(nlist_List *poly)
{
	nlist_List *list = nlist_zeros(poly->size);
	printf("objective:\t");
	npoly_print(poly);
	int j = 0;
	int sum = 0;
	int trial = 1000000;
	printf("trial:\t\t%d\nresult:\n", trial);
	for(int i = 0; i < trial; i++){
		j = nrand_dist_pick(poly);
		sum = list->data[j].item + 1;
		nlist_substitute(list, j, sum);  
	}
	j = 0; // Safety
	int k = 0;
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		assert(j <= poly->size);
		sum = list->data[j].item;
		if (sum > 0){
			printf("\t\t%2d=>%.6lf",j,(double)sum/trial);
			printf("\t%+.6lf\n",poly->data[j].ditem - (double)sum/trial);
		}
		j++;
	}
}

nlist_List *nrand_pick(int size, int num)
{
	/* implementation of slower version */
	assert(size >= num && size > 0 && num > 0);
	nlist_List *list = nlist_init();
	int range_list[size];
	for(int i = 0; i < size; i++) range_list[i] = i;

	for(int i = size - 1; i >= size - num; i--){
		int randnum = genrand_int32()%i;
		int temp = range_list[randnum];
		range_list[randnum] = range_list[i];
		nlist_append(list, temp);
	}
	return list;
}	

nlist_List *nrand_shuffle(nlist_List *list)
{
	assert (list->size > 0);
	int *array = nlist_to_array(list);
	for(int i = list->size - 1; i > 1; i--){
		int randnum = genrand_int32()%i;
		int temp = array[randnum];
		array[randnum] = array[i];
		array[i] = temp;
	}
	return array_to_nlist(array, list->size);
}

#endif
