/* npoly.h */
/* headerfile dedicated to polynomial */

#ifndef NPOLY_H
#define NPOLY_H

typedef struct{
	double coeff[STACK_SIZE];
	int dim[STACK_SIZE];
	int size;
	int start;
	int end;
} nrand_Poly;

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
	if (d_check == 0) assert(sum == 1.0);
	return poly;
}

void npoly_print(nlist_List *poly)
{
	assert( poly->size > 1);
	int j = 0; // Safety
	int k = 0;
	printf("f(x)=");
	for(int i = poly->start; i != INT_MAX; i = poly->data[i].after){
		assert(j <= poly->size);
		if (poly->data[i].ditem != 0.0){
			if(k == 0 ){
				k++;
				if (poly->data[i].ditem > 0){
					printf("%.3lfx^{%d}", poly->data[i].ditem, j);
				} else {
					printf("-%.3lfx^{%d}", poly->data[i].ditem, j);
				}
			} else {
				printf("%+.3lfx^{%d}", poly->data[i].ditem, j);
			}
		}
		j++;
	}
	printf("\n");
}

double npoly_subs(nlist_List *poly, double num)
{
	int j = 0; int k = 0; double dnum = 0.0;
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

#endif
