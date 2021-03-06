#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "npld.h"

void list_ver(){
	// linspace(start, end, step)
	nlist_List *a = nlist_linspace(1, 4, 1); //-> [1,2,3]
	nlist_List *b = nlist_linspace(4, 8, 1); //-> [4,5,6,7]
	nlist_print(a); nlist_print(b);
	nlist_trans(b, a);                       //-> a = [1,2,3]
	nlist_print(a); nlist_print(b);
}

void dict_ver(){
	// initializing dict (empty dict)
	ndict_Dict *dict = ndict_init();

	// some random sequence
	int rep[10] = {2, 3, 8, 2, 3, 9, 2, 2, 3, 8};

	for(int i = 0; i < 10; i ++){
		// random pick number of numerals with in range of 0 and 100
		nlist_List *list = nrand_pick(100, rep[i]);
		ndict_append(dict, list);
	}
	// print out
	ndict_print(dict, 0, 0, 0);
}

void nrand_ver(){
	// initialize double sequence with 0
	double coef[9]; double_init(coef, 9);

	// realize distribution function
	// l(x) = 0.5 x^2 + 0.28 x^3 + 0.22 x^8
	coef[2] = 0.5; coef[3] = 0.28; coef[8] = 0.22;

	int coef_size = sizeof(coef)/sizeof(double);

	// initialize poly with above distribution function
	nlist_List *poly = npoly_init(coef, coef_size, 0);


	// initialize dict
	ndict_Dict *dict = ndict_init();
	// check if distribution is serving correctly
	nrand_dist_check(poly);

	for(int i = 0; i < 30; i ++){
		nlist_List *list = nrand_pick(1000, nrand_dist_pick(poly));
		ndict_append(dict, list);
	}
	// print out
	ndict_print(dict, 0, 0, 0);
}

void coefrand(double *coef, int size){
	for(int i = 0; i < size; i++) coef[i] = genrand_real1();
}

void npoly_ver(){
	init_genrand((unsigned)time(NULL));
	int size1 = 0; int size2 = 3;
	while((size1 < 2)||(size2 < 2)||(size1 == size2)){
		size1 = genrand_int31()%6;
		size2 = genrand_int31()%6;
	}

	double coef[size1]; coefrand(coef, size1);
	nlist_List *poly = npoly_init(coef, size1, 1);

	double coef2[size2]; coefrand(coef2, size2);
	nlist_List *poly2 = npoly_init(coef2, size2, 1);

	double res = npoly_kl(poly, poly2);
	printf("res: %lf\n", res);
	free(poly);free(poly2);
}

int main(){
	init_genrand((unsigned)time(NULL));
	printf("\n nlist:test \n");
	list_ver();
	printf("\n ndict:test \n");
	dict_ver();
	printf("\n nrand:test \n");
	nrand_ver();
	printf("\n npoly:test \n");
	npoly_ver();
	return 0;
}
