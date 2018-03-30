#include "header.h"

void list_ver(){
	int size = 10;
	nlist_List *list = nrand_pick(100, 8);
	nlist_print(list);
	nlist_del_hack(list, 1);
	nlist_del_hack(list, 2);
	nlist_print(list);
	free(list);
}

void dict_ver(){
	ndict_Dict *dict = ndict_init();
	int rep[10] = {2, 3, 8, 2, 3, 9, 2, 2, 3, 8};
	for(int i = 0; i < 10; i ++){
		nlist_List *list = nrand_pick(100, rep[i]);
		ndict_append(dict, list);
	}
	ndict_print(dict);
	ndict_print(dict);
}

void nrand_ver(){
	double coef[9] = {0.0, 0.0, 0.5, 0.28, 0.0, 0.0, 0.0, 0.0, 0.22};
	int coef_size = sizeof(coef)/sizeof(double);
	nlist_List *poly = npoly_init(coef, coef_size, 0);
	ndict_Dict *dict = ndict_init();
	nrand_dist_check(poly);
}

void npoly_ver(){
	double coef[4];
	coef[3] = 4.0;
	int coef_size = sizeof(coef)/sizeof(double);
	nlist_List *poly = npoly_init(coef, coef_size, 1);
	npoly_print(poly);
	printf("%lf\n",npoly_subs(poly, 2.0));
	npoly_integ(poly, 0.0, 1.0);
	npoly_deriv(poly); npoly_print(poly);
}

int main(){
	init_genrand((unsigned)time(NULL));
	//dict_ver();
	list_ver();
	//nrand_ver();
	//npoly_ver();
	return 0;
}
