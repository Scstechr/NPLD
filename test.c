#include "header.h"

void list_ver(){
	int size = 100;
	nlist_List *list = nlist_range(7);
	nlist_insert(list, 0, 1);
	int index = nlist_index(list, 0);
	printf("index:%d\n", index);
	nlist_print(list);
	nlist_List *rand_list = nrand_pick(100, 8);
	nlist_print(rand_list);
	free(list);
	free(rand_list);
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
	ndict_print(dict);
}

void npoly_ver(){
	double coef[5];
	coef[2] = 4.53;
	coef[3] = 2.34;
	coef[4] = 3.42;
	int coef_size = sizeof(coef)/sizeof(double);
	nlist_List *poly = npoly_init(coef, coef_size, 1);
	printf("%lf\n",npoly_subs(poly, 2.0));
	npoly_print(poly);
	npoly_deriv(poly); npoly_print(poly);
	npoly_deriv(poly); npoly_print(poly);
	npoly_deriv(poly); npoly_print(poly);
}

int main(){


	init_genrand((unsigned)time(NULL));
	//list_ver();
	//dict_ver();
	//nrand_ver();
	npoly_ver();
	return 0;
}
