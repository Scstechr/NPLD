/* narray.h */
/* goal: replace most of numpy functions */
#ifndef NARRAY_H
#define NARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Struct narray_Array */
/* in future: make it avaiable for float and double */
typedef struct{
	int data[STACK_SIZE][STACK_SIZE];
	int row_size;
	int column_size;
} narray_Array;
	
narray_Array *narray_zeros(int n, int m){
	// Creates n*m narray_Array with all the elements set to 0
	assert(n <= STACK_SIZE && m <= STACK_SIZE);
	narray_Array *array = (narray_Array*)malloc(sizeof(narray_Array));
	array->column_size = n;
	array->row_size = m;

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			array->data[i][j] = 0;
		}
	}
	return array;
}

narray_Array *narray_ones(int n, int m){
	// Creates n*m narray_Array with all the elements set to 1
	assert(n <= STACK_SIZE && m <= STACK_SIZE);
	narray_Array *array = (narray_Array*)malloc(sizeof(narray_Array));
	array->column_size = n;
	array->row_size = m;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			array->data[i][j] = 1;
		}
	}
	return array;
}

narray_Array *narray_unformat(int n, int m){
	// Creates n*m narray_Array with all the elements unformatted
	// Use with caution
	assert(n <= STACK_SIZE && m <= STACK_SIZE);
	narray_Array *array = (narray_Array*)malloc(sizeof(narray_Array));
	array->column_size = n;
	array->row_size = m;
	return array;
}

void narray_print(narray_Array *array){
	// Prints out all the elements
	int n = array->column_size;
	int m = array->row_size;
	printf("\n[%4d * %4d] int array\n", n, m);
	for(int i = 0; i < n; i++){
		printf("| ");
		for(int j = 0; j < m; j++){
			printf("%4d ", array->data[i][j]);
		}
		printf("|\n");
	}
}

void narray_insert(narray_Array *array, int n, int m, int num){
	// Insert num into specific location (n,m) of narray_Array
	assert(n < array->column_size && m < array->row_size);
	array->data[n][m] = num;
}

narray_Array *narray_vsum(narray_Array *array){
	// Vertically sums all the elements
	// Returns 1*m narray_Array
	int n = array->column_size;
	int m = array->row_size;
	int sum;
	narray_Array *ret_array = narray_unformat(1, m);
	for(int row = 0; row < m; row ++){
		sum = 0;
		for(int column = 0; column < n; column ++){
			sum += array->data[column][row];
		}
		narray_insert(ret_array, 0, row, sum);
	}
	return ret_array;
}

narray_Array *narray_hsum(narray_Array *array){
	// Horizontally sums all the elements
	// Returns n*1 narray_Array
	int n = array->column_size;
	int m = array->row_size;
	int sum;
	narray_Array *ret_array = narray_unformat(n, 1);
	for(int column = 0; column < n; column ++){
		sum = 0;
		for(int row = 0; row < n; row ++){
			sum += array->data[column][row];
		}
		narray_insert(ret_array, column, 0, sum);
	}
	return ret_array;
}

narray_Array *narray_vstack(narray_Array *array1, narray_Array *array2){
	assert(array1->row_size == array2->row_size);
	int column_size = array1->column_size + array2->column_size;
	int row_size = array1->row_size;
	narray_Array *array = narray_unformat(column_size,row_size);
	for(int column = 0; column < column_size; column++){
		for(int row = 0; row < row_size; row++){
			if(column < array1->column_size){
				narray_insert(array, column, row, array1->data[column][row]);
			} else {
				narray_insert(array, column, row, array2->data[column-array1->column_size][row]);
			}
		}
	}
	return array;
}

narray_Array *narray_hstack(narray_Array *array1, narray_Array *array2){
	assert(array1->column_size == array2->column_size);
	int column_size = array1->column_size;
	int row_size = array1->row_size + array2->row_size;
	narray_Array *array = narray_unformat(column_size,row_size);
	for(int row = 0; row < row_size; row++){
		for(int column = 0; column < column_size; column++){
		if(row < array1->row_size){
				narray_insert(array, column, row, array1->data[column][row]);
			} else {
				narray_insert(array, column, row, array2->data[column][row-array1->row_size]);
			}
		}
	}
	return array;
}

narray_Array *narray_range(int n, int m){
	assert(n <= STACK_SIZE && m <= STACK_SIZE);
	assert(n == 1 || m == 1);
	narray_Array *array = (narray_Array*)malloc(sizeof(narray_Array));
	array->column_size = n;
	array->row_size = m;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(n==1){
				array->data[i][j] = j;
			} else {
				array->data[i][j] = i;
			}
		}
	}

	return array;
}

void narray_shuffle(narray_Array *array){
	assert(array->column_size == 1);
	int m = array->row_size;
	for(int i = m - 1; i > 1; i--){
		int rand = genrand_int32()%i;
		int temp = array->data[0][rand];
		array->data[0][rand] = array->data[0][i];
		array->data[0][i] = temp;
	}
}

narray_Array *narray_pick(narray_Array *array, int num){
	assert(array->column_size == 1 && num < array->row_size);
	narray_Array *ret_array = narray_unformat(1, num);
	
	int m = array->row_size;
	for(int i = m - 1; i >= m - num; i--){
		int rand = genrand_int32()%i;
		int temp = array->data[0][rand];
		array->data[0][rand] = array->data[0][i];
		array->data[0][i] = temp;
		narray_insert(ret_array, 0, m - i - 1, temp); 
	}
	return ret_array;
}

narray_Array *narray_pick_new(int size, int num){
	/* definately slower than w/o _new version. */
	/* advantage: does not need to prepare narray_Array for random generation */
	assert(size < STACK_SIZE && num < size);
	narray_Array *ret_array = narray_unformat(1, num);
	narray_Array *array = narray_range(1, size);
	int m = array->row_size;
	for(int i = m - 1; i >= m - num; i--){
		int rand = genrand_int32()%i;
		int temp = array->data[0][rand];
		array->data[0][rand] = array->data[0][i];
		narray_insert(ret_array, 0, m - i - 1, temp); 
	}
	return ret_array;
}
#endif
