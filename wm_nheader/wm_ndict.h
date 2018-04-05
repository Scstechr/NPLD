/* ndict.h */
/* fake dict structure in C */
#ifndef WM_NDICT_H
#define WM_NDICT_H

#include "../header.h"

void wm_ndict_range(ndict_Dict *dict, int n){
	/* compromised edition */
	/* task: append empty list instead of range */
	for (int i = 0; i < n; i++){
		nlist_List *list = nlist_range(1);
		ndict_append(dict, list);
	}
}

#endif
