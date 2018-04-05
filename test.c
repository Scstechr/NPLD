#include "header.h"
#include "../headerfiles/fstack.h"

#define SLOTSIZE 10

//typedef struct{
//	nlist_List *list;
//	int before;
//	int after;
//} ndict_Item;
//
//typedef struct{
//	ndict_Item data[STACK_SIZE];
//	int end;
//	int start;
//	int size;
//} ndict_Dict;

ndict_Dict *setUserlist(int usernum){
	double coef[9];
	int size = sizeof(coef)/sizeof(double);
	double_init(coef, size);
	//coef[2] = 0.5; coef[3] = 0.22; coef[8] = 0.28;
	coef[2] = 1.0;
	nlist_List *poly = npoly_init(coef, size, 0);
	ndict_Dict *userlist = ndict_init();
	for(int i = 0; i < usernum; i++){
		nlist_List *list = nrand_pick(SLOTSIZE, nrand_dist_pick(poly));
		ndict_append(userlist, list);
	}
	return userlist;
}

ndict_Dict *setSlotstate(ndict_Dict *userlist){
	ndict_Dict *slotstate = ndict_range(SLOTSIZE);
	for(int i = userlist->start;
			i != INT_MAX; 
			i = userlist->data[i].after){
		for(int j = userlist->data[i].list->start;
				j != INT_MAX;
				j = userlist->data[i].list->data[j].after){
			int slot = userlist->data[i].list->data[j].item;
			nlist_append(slotstate->data[slot].list, i);
			int sum = slotstate->data[slot].list->data[0].item;
			nlist_substitute(slotstate->data[slot].list, 0, sum + 1);
		}
	}
	return slotstate;
}

void zigzag(ndict_Dict *userlist, ndict_Dict *slotstate){
	nlist_List *decoded = nlist_init();
	int progress = 0;
	for(int i = 1; i < userlist->size; i++){
		nlist_List *list = userlist->data[i].list;
		for(int j = userlist->data[i].list->start;
				j != INT_MAX;
				j = userlist->data[i].list->data[j].after){
			if(slotstate->data[list->data[j].item].list->data[0].item == 1){
				nlist_append(decoded, i); progress ++; break;
				ndict_delete(slotstate, i);
			}
		}
	}
	if(progress > 0){
		for(int i = decoded->start; i != INT_MAX; i = decoded->data[i].after){
			ndict_delete(userlist, decoded->data[i].item);
			for(int j = userlist->data[decoded->data[i].item].list->start;
					j != INT_MAX;
					j = userlist->data[decoded->data[i].item].list->data[j].after){
				slotstate->data[ userlist->data[
						decoded->data[i].item ].list->data[j].item ].list->data[0].item --;
			}
		}
		nlist_clear(decoded);
	} 
}

int procSimulation(int usernum){
	ndict_Dict *userlist = setUserlist(usernum);
	ndict_Dict *slotstate = setSlotstate(userlist);
	ndict_print(userlist);
	ndict_print(slotstate);
	zigzag(userlist, slotstate);
	int decoded = 0;
	return decoded;
}

int main(){
	init_genrand((unsigned)time(NULL));

	procSimulation(5);

	return 0;
}
