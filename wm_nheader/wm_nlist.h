/* nlist.h */
/* list structure in C */
#ifndef WM_NLIST_H
#define WM_NLIST_H

#include "../header.h"

void wm_nlist_range(nlist_List *list, int n){
	list->size = n;
	list->end = n-1;
	list->start = 0;
	for(int i = 0; i < n; i++){
		nlist_setparam(list, i, i, i-1, i+1);
	}
	list->data[list->end].after = INT_MAX;
}

void wm_nlist_zeros(nlist_List *list, int n){
	list->size = n;
	list->end = n-1;
	list->start = 0;
	for(int i = 0; i < n; i++){
		nlist_setparam(list, i, 0, i-1, i+1);
	}
	list->data[list->end].after = INT_MAX;
}

void wm_nlist_ones(nlist_List *list, int n){
	list->size = n;
	list->end = n-1;
	list->start = 0;
	for(int i = 0; i < n; i++){
		nlist_setparam(list, i, 1, i-1, i+1);
	}
	list->data[list->end].after = INT_MAX;
}

#endif
