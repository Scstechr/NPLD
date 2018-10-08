#include <time.h>
#include <stdio.h>

#include "npld.h"

void list_ver(){
	nlist_List *a = nlist_linspace(1, 4, 1);
	nlist_List *b = nlist_linspace(4, 8, 1);
	nlist_print(a); nlist_print(b);
	nlist_trans(b, a);
	nlist_print(a); nlist_print(b);
	
}

void dict_ver(){
	ndict_Dict *dict = ndict_init();
	int rep[10] = {2, 3, 8, 2, 3, 9, 2, 2, 3, 8};
	for(int i = 0; i < 10; i ++){
		nlist_List *list = nrand_pick(100, rep[i]);
		ndict_append(dict, list);
	}
}

void nrand_ver(){
	double coef[9] = {0.0, 0.0, 0.5, 0.28, 0.0, 0.0, 0.0, 0.0, 0.22};
	int coef_size = sizeof(coef)/sizeof(double);
	nlist_List *poly = npoly_init(coef, coef_size, 0);
	ndict_Dict *dict = ndict_init();
	nrand_dist_check(poly);
	for(int i = 0; i < 30; i ++){
		nlist_List *list = nrand_pick(1000, nrand_dist_pick(poly));
		ndict_append(dict, list);
	}
	ndict_print(dict, 0, 0, 0);
}

void npoly_ver(){
	double coef[4];
	double_init(coef, 4);
	coef[0] = 3.0; coef[1] = 2.8; coef[3] = 4.0;
	int coef_size = sizeof(coef)/sizeof(double);
	nlist_List *poly = npoly_init(coef, coef_size, 1);
	npoly_print(poly);
	double_init(coef, 4);
	coef[0] = 0.235; coef[2] = 0.810; coef[3] = 2.19;
	npoly_trans(poly, coef, 4);
	npoly_print(poly);
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
