#ifndef UTIL_H
#define UTIL_H

void pass(){
	;
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

#endif
