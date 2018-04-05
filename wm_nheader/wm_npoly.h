/* npoly.h */
/* headerfile dedicated to polynomial */

#ifndef WM_NPOLY_H
#define WM_NPOLY_H

#include "../header.h"

void wm_npoly_init(nlist_List *poly, double *coeff, int coeff_size, int d_check)
{
	nlist_List *poly = nlist_clear();
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
}

#endif
