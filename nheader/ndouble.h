#ifndef NDOUBLE_H
#define NDOUBLE_H

void rand_shuffle(double *array, int size)
{
	int randnum;
	double temp;
	for(int i = size - 1; i > 1; i--){
		randnum = genrand_int32()%i;
		temp = array[randnum];
		array[randnum] = array[i];
		array[i] = temp;
	}
}

void nlist_setparam_dbl(nlist_List *list, int index, double n, int before, int after)
{

	/* for debugging */
	// nlist_print_param(index, n, before, after);
	if(n > INT_MIN){
		list->data[index].ditem = n;
	}
	if(before > INT_MIN){
		list->data[index].before = before;
	}
	if(after > INT_MIN){
		list->data[index].after = after;
	}
}

void nlist_simple_print_dbl(nlist_List *list){
	int j = 0; // Safety
	printf("[");
	if (list->size > 0){
		for(int i = list->start; i != INT_MAX; i = list->data[i].after){
			assert(j < list->size);
			printf("%.8lf ", list->data[i].ditem);
			j++;
		}
	}
	printf("\b]");
}

void nlist_print_dbl(nlist_List *list)
{
	printf("\nsize:%3d, double list\n", list->size);
	nlist_simple_print_dbl(list);
	printf("\n");
}

void nlist_append_dbl(nlist_List *list, double n)
{
	if(list->end > 0){
		list->data[list->end].after = list->size;
	} else {
		list->data[0].after = list->size;
	}

	nlist_setparam_dbl(list, list->size, n, list->end, INT_MAX);
	list->data[list->size].idx = list->size;
	
	list->end = list->size;
	list->size++;

	assert(list->size < STACK_SIZE);
}

void ndict_print_dbl(ndict_Dict *dict, int idx, int idx2, int idx3){
	assert(idx == 0 || idx == 1);
	assert(idx2 == 0 || idx2 == 1);
	assert(idx3 == 0 || idx3 == 1);
	// flag idx = i, idx2 = j, idx3 = size
	if (dict->size == 0) {
		printf("\n** empty dict **\n");
	} else {
		printf("\nsize:%3d, dict w/ double list\n", dict->size);
		if (idx == 1) { printf("  i,"); }
		if (idx2 == 1) { printf("  j,"); }
		if (idx3 == 1) { printf(" size,"); }
		if (idx == 1 || idx2 == 1 || idx3 == 1) { printf("list"); }
		printf("\n");
		if(dict->size != 0){
			int j = 0;
			for(int i = dict->start; i != INT_MAX; i = dict->data[i].after){
				if (idx == 1) printf("%3d,",i);
				if (idx2 == 1) printf("%3d,",j);
				if (idx3 == 1) printf("%5d,",dict->data[i].list->size);
				nlist_simple_print_dbl(dict->data[i].list);
				printf("\n");
				j++;
			}
		}
	}
}

void nlist_trans_dbl(nlist_List *from, nlist_List *to){
	nlist_clear(to);
	for(int i = from->start;
			i != INT_MAX;
			i = from->data[i].after){
		nlist_append_dbl(to, from->data[i].ditem);
	}
}
#endif
