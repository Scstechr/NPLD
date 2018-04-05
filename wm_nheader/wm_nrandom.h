/* nrandom.h */
/* Header Dedicated to Random Related Subjects */
/* requires nlist.h */
#ifndef WM_NRANDOM_H
#define WM_NRANDOM_H

#include "../header.h"

void wm_nrand_loop(nlist_List *list, nlist_List *poly, int trial){
	wm_nlist_zeros(list, poly->size);
	int j = 0; int sum = 0;
	for(int i = 0; i < trial; i++){
		j = nrand_dist_pick(poly);
		sum = list->data[j].item + 1;
		nlist_substitute(list, j, sum);  
	}
}

void wm_nrand_loop2(nlist_List *list, nlist_List *poly,
		                double *max, double *min, double *sum,
						int trial){
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		assert(i <= poly->size);
		if (list->data[i].item > 0){
			double result = (double)list->data[i].item/trial;
			sum[i] += result;
			if (max[i] < result) max[i] = result;
			if (min[i] > result) min[i] = result;
		}
	}
}

void nrand_dist_check(nlist_List *poly)
{
	int trial = 10000; nrand_dist_head(poly, trial);
	double max[poly->size]; double min[poly->size]; double sum[poly->size];
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		max[i]= 0.0; min[i] = 1.0; sum[i] = 0.0;
	}
	for(int _ = 0;  _ < trial; _++){
		nlist_List *list = nrand_loop(poly, trial);
		nrand_loop2(list, poly, max, min, sum, trial);
	}
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		if (sum[i] > 0){
			double result = sum[i]/trial;
			printf("\t\t%2d=>%.6lf(±%.6lf)", i, result, max[i] - min[i]);
			printf("\t%+.6lf\n", poly->data[i].ditem - result);
		}
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

nlist_List *nrand_pick_a(int size, int num, int *range)
{
	/* implementation of slower version */
	assert(size >= num && size > 0 && num > 0);
	nlist_List *list = nlist_init();
	for(int i = size - 1; i >= size - num; i--){
		int randnum = genrand_int32()%i;
		int temp = range[randnum];
		range[randnum] = range[i];
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
