#ifndef PMF_H
#define PMF_H

void crdsa(double *pmf, int size, int rep){
	assert(rep < 17);
	double_init(pmf, size);
	pmf[rep] = 1.0;
}

void irsa(double *pmf, int size, int rep){
	assert(rep < 17);
	double_init(pmf, size);
	pmf[rep] = 1.0;
	if (rep == 4){
		pmf[2] = 0.5102; pmf[4] = 0.4898;
	} else if (rep == 5){
		pmf[2] = 0.5361; pmf[4] = 0.0436; pmf[5] = 0.3933;
	} else if (rep == 6){
		pmf[2] = 0.5465; pmf[4] = 0.1623; pmf[6] = 0.2912;
	} else if (rep == 8){
		pmf[2] = 0.5; pmf[3] = 0.22; pmf[8] = 0.28;
	} else if (rep == 16){
		pmf[2] = 0.4977; pmf[3] = 0.2207; pmf[4] = 0.0381;
		pmf[5] = 0.0756; pmf[6] = 0.0398; pmf[7] = 0.0009;
		pmf[8] = 0.0088; pmf[9] = 0.0068; pmf[11]= 0.0030;
		pmf[14]= 0.0429; pmf[15]= 0.0081; pmf[16]= 0.0576;
	} else {
		printf("rep:%2d is not defined\n", rep);
		assert(0);
	}
}
#endif
