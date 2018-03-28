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

nlist_List *npoly_init(double *coeff, int coeff_size, int d_check){
	nlist_List *poly= (nlist_List*)malloc(sizeof(nlist_List));
	for(int i = 0; i < coeff_size; i++){
		poly->data[i].ditem = coeff[i];
		nlist_append(poly, INT_MAX); 
	}
	int i = poly->start;
	int j = 0;
	double sum = 0.0;
	while(1){
		assert(j <= poly->size);
		if (poly->data[i].ditem != 0.0){
			assert(poly->data[i].ditem > 0);
			sum += poly->data[i].ditem;
		}
		i = poly->data[i].after;
		if(i == INT_MAX) break; 
		j++;
	}
	if (d_check == 0) assert(sum == 1.0);
	return poly;
}

void npoly_print(nlist_List *poly)
{
	if(poly->size == 0){
		printf("\n[]\n");
	} else {
		int i = poly->start;
		int j = 0; // Safety
		int k = 0;
		printf("f(x)=");
		while(1){
			assert(j <= poly->size);
			if (poly->data[i].ditem != 0.0){
				if(k == 0 ){
					k++;
					if (poly->data[i].ditem > 0){
						printf("%.2lfx^{%d}", poly->data[i].ditem, j);
					} else {
						printf("-%.2lfx^{%d}", poly->data[i].ditem, j);
					}
				} else {
					printf("%+.2lfx^{%d}", poly->data[i].ditem, j);
				}
			}
			i = poly->data[i].after;
			if(i == INT_MAX) break; 
			j++;
		}
		printf("\n");
	}
}

double npoly_subs(nlist_List *poly, double num)
{
	int i = poly->start;
	int j = 0;
	int k = 0;
	double dnum = 0.0;
	while(1){
		assert(j <= poly->size);
		if (poly->data[i].ditem != 0.0){
			dnum += poly->data[i].ditem * pow(num, j);
		}
		i = poly->data[i].after;
		if (i == INT_MAX) break;
		j++;
	}
	return dnum;
}
#endif
