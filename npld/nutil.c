#include <stdio.h>

#include "../npld.h"

void flagprint(int flag){
	if (flag == 0){
		printf("ON");
	} else if (flag == 1){
		printf("OFF");
	} else {
		assert(0);
	}
}

void double_init(double *array, int size){
	for(int i = 0; i < size; i++){
		array[i] = 0.0;
	}
}

void int_print(int *array, int size){
	printf("\n[");
	for(int i = 0; i < size; i++){
		printf("%d,", array[i]);
	}
	printf("\b]\n");
}

void dbl_print(double *array, int size){
	printf("\n[");
	for(int i = 0; i < size; i++){
		printf("%.3lf,", array[i]);
	}
	printf("\b]\n");
}
