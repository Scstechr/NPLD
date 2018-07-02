#include "header.h"
#include "math.h"

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

double npoly_kl_sum(nlist_List *poly, nlist_List *poly2){
	// size of poly >= poly2
	double p, q;
	for(int i = 0; i < poly->size; i++){
		p = poly->data[i].ditem;
		if (i <= poly2->size) {
			q = poly2->data[i].ditem;
		} else {
			q = 0.0;
		}
		printf("p = %lf ", p);
		printf("q = %lf ", q);
		printf("\n");
	}
	printf("\n");
}

double npoly_kl(nlist_List *poly, nlist_List *poly2){
	printf("size:%d,", poly->size); printf("size2:%d", poly2->size); printf("\n");
	npoly_print(poly); npoly_print(poly2);
	if (poly->size > poly2->size){
		npoly_kl_sum(poly, poly2);
	} else {
		npoly_kl_sum(poly2, poly);
	}
	double a = 0.0;
	return a;
}

void coefrand(double *coef, int size){
	for(int i = 0; i < size; i++) coef[i] = genrand_real1();
}

void npoly_ver(){
	init_genrand((unsigned)time(NULL));
	int size1 = 0;
	while(size1 < 1) size1 = genrand_int31()%6;
	int size2 = 0;
	while(size2 < 1) size2 = genrand_int31()%6;

	double coef[size1]; coefrand(coef, size1);
	nlist_List *poly = npoly_init(coef, size1, 1);

	double coef2[size2]; coefrand(coef2, size2);
	nlist_List *poly2 = npoly_init(coef2, size2, 1);

	npoly_kl(poly, poly2);
	free(poly);free(poly2);
}

int main(){
	init_genrand((unsigned)time(NULL));
	//list_ver();
	//dict_ver();
	//nrand_ver();
	npoly_ver();
	return 0;
}
