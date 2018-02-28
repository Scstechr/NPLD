/* debugg.h */
/* extra g for redundancy */
#ifndef DEBUGG_H
#define DEBUGG_H

void dm(int n){
	printf("\n------------------------------------------------\n");
	printf("\t\tDEBUG MESSAGE! %d", n);
	printf("\n------------------------------------------------\n");
}

void strong(int n){
	printf("\n>>>>> %d \n", n);
}

#endif

