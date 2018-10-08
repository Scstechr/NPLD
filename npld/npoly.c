#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "../npld.h"

nlist_List *npoly_init(double *coeff, int coeff_size, int d_check)
{
	nlist_List *poly = nlist_init();
	for(int i = 0; i < coeff_size; i++){
		poly->data[i].ditem = coeff[i];
		nlist_append(poly, INT_MAX); 
	}
	int j = 0;
	double sum = 0.0;
	for(int i = poly-> start; i != INT_MAX; i = poly->data[i].after){
		assert(j <= poly->size);
		if (poly->data[i].ditem != 0.0){
			assert(poly->data[i].ditem > 0);
			sum += poly->data[i].ditem;
		}
		j++;
	}
	if (d_check == 0) {
		if (sum <= 0.99999999 && sum >= 1.00000001){
			printf("\tNPOLY_INIT ERROR SUM: %.16lf\n", sum);
			assert(0);
		}
	}
	return poly;
}

void npoly_print(nlist_List *poly)
{
	int j = 0; // Safety
	int k = 0;
	double temp;
	printf("f(x)=");
	if ( poly->size > 1){
		for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
			assert(j <= poly->size);
			temp = poly->data[i].ditem;
			if (temp > 0.0){
				if(k == 0 ){
					k++;
					if (poly->data[i].ditem > 0){
						printf("%.5lfx^{%d}", poly->data[i].ditem, j);
					} else {
						printf("-%.5lfx^{%d}", poly->data[i].ditem, j);
					}
				} else {
					printf("%+.5lfx^{%d}", poly->data[i].ditem, j);
				}
			}
			j++;
		}
		printf("\n");
	} else {
		printf("0.0");
	}
}

double npoly_subs(nlist_List *poly, double num)
{
	int j = 0; 
	double dnum = 0.0;
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		assert(j <= poly->size);
		if (poly->data[i].ditem != 0.0){
			dnum += poly->data[i].ditem * pow(num, j); 
		}
		j++;
	}
	return dnum;
}

void npoly_copy(nlist_List *poly1, nlist_List *poly2)
{
	assert (poly1->size <= poly2->size);
	for(int i = 0; i < poly2->size; i++){
		poly2->data[i].ditem = poly1->data[i].ditem;
	}
}

void npoly_deriv(nlist_List *poly)
{
	assert( poly->size > 1 );
	double coef[poly->size];
	for(int i = 0; i < poly->size; i++) coef[i] = 0.0; 
	nlist_List *ret = npoly_init(coef, poly->size, 1);
	int j = 0;
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		assert(j <= poly->size);
		if (poly->data[i].ditem != 0.0){
			ret->data[poly->data[i].before].ditem = i*poly->data[i].ditem;
		}
		j++;
	}
	npoly_copy(ret, poly);
	poly->size --;
	poly->data[poly->size].after = INT_MAX;
}

double npoly_integ(nlist_List *poly, double a, double b)
{
	/* using Simpson's rule */
	assert( b > a);
	double value = 0.0;
	double fa = npoly_subs(poly, a);
	double ff = 4 * npoly_subs(poly, (a + b)/2.0);
	double fb = npoly_subs(poly, b);
	value = ( (b - a) / 6.0 ) * ( fa + ff + fb);
	return value;
}

void npoly_zeros(nlist_List *poly){
	for(int i = poly->start;
			    i != INT_MAX;
					i = poly->data[i].after){
		poly->data[i].ditem = 0.0;
	}
	poly->size = 0;
}

void npoly_zeros_quick(nlist_List *poly, int *array, int size){
	for(int i = 0; i < size; i++){
		poly->data[array[i]].ditem = 10.0;
	}
	//poly->size = 0;
}

void npoly_trans(nlist_List *poly, double *array, int size){
	assert(poly->size == size);
	int j = 0;
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		poly->data[i].ditem = array[j];
		j++;
	}
}

//Kullback-Leibler divergence
double npoly_kl_sum(nlist_List *poly, nlist_List *poly2){
	// size of poly >= poly2
	double p, q, res = 0.0;
	for(int i = 0; i < poly2->size; i++){
		p = poly2->data[i].ditem;
		q = poly->data[i].ditem;
		if ((p != 0.0)&&(q != 0.0)){
			res += p*log2(p / q);
		} 
	}
	if (res < 0.0) res *= -1;
	return res;
}

double npoly_kl(nlist_List *poly, nlist_List *poly2){
	double res;
	if (poly->size > poly2->size){
		res = npoly_kl_sum(poly, poly2);
	} else {
		res = npoly_kl_sum(poly2, poly);
	}
	return res;
}
#endif
