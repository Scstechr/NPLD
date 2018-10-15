#ifndef NPLD_H
#define NPLD_H

#define STACK_SIZE 20000

// MT.c
/* initializes mt[MT_N] with a seed */
void init_genrand(unsigned long s);
/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length);
/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void);
/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void);
/* generates a random number on [0,1]-real-interval */
double genrand_real1(void);
/* generates a random number on [0,1)-real-interval */
double genrand_real2(void);
/* generates a random number on (0,1)-real-interval */
double genrand_real3(void);
/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void);

// nutils.c
void flagprint(int flag);
void double_init(double *array, int size);
void int_print(int *array, int size);
void dbl_print(double *array, int size);

// nlist.c
typedef struct{
	int item;
	int idx;
	double ditem;
	int before;
	int after;
	int flag;
} nlist_Item;

typedef struct{
	nlist_Item data[STACK_SIZE]; // This also has to change to malloc()
	int size;
	int start;
	int end;
} nlist_List;

void nlist_clear(nlist_List *list);
nlist_List *nlist_init();
void printt(int item);
void nlist_print_param(int index, int n, int before, int after);
void nlist_sizecheck(nlist_List *list);
void nlist_append(nlist_List *list, int n);
nlist_List *nlist_range(int n);
nlist_List *nlist_zeros(int n);
nlist_List *nlist_ones(int n);
int nlist_pop(nlist_List *list);
int nlist_len(nlist_List *list);
void nlist_simple_print(nlist_List *list);
void nlist_print(nlist_List *list);
void nlist_param(nlist_List *list);
int *nlist_to_array(nlist_List *list);
nlist_List *array_to_nlist(int *array, int size);
int nlist_index(nlist_List *list, int index);
void nlist_insert(nlist_List *list, int index, int n);
nlist_List *nlist_delete(nlist_List *list, int index);
nlist_List *nlist_linspace(int start, int end, int step);
void nlist_conc(nlist_List *a, nlist_List *b);
void nlist_trans(nlist_List *from, nlist_List *to);

//ndict.c
typedef struct{
	nlist_List *list;
	int before;
	int after;
} ndict_Item;

typedef struct{
	ndict_Item data[STACK_SIZE];
	int end;
	int start;
	int size;
} ndict_Dict;

void ndict_clear(ndict_Dict *dict);
ndict_Dict *ndict_init();
void ndict_setparam(ndict_Dict *dict, int index, nlist_List *list, int before, int after);
void ndict_setparam_nolist(ndict_Dict *dict, int index, int before, int after);
void ndict_sizecheck(ndict_Dict *dict);
void ndict_append(ndict_Dict *dict, nlist_List *list);
void ndict_append_nolist(ndict_Dict *dict);
void ndict_clear_size(ndict_Dict *dict, int size, int flag);
void ndict_print(ndict_Dict *dict, int idx, int idx2, int idx3);
ndict_Dict *ndict_range(int n);
int ndict_index(ndict_Dict *dict, int index);
void nlist_substitute(nlist_List *list, int index, int n);
ndict_Dict *ndict_delete(ndict_Dict *dict, int index);

//npoly.c
nlist_List *npoly_init(double *coeff, int coeff_size, int d_check);
void npoly_print(nlist_List *poly);
double npoly_subs(nlist_List *poly, double num);
void npoly_copy(nlist_List *poly1, nlist_List *poly2);
void npoly_deriv(nlist_List *poly);
double npoly_integ(nlist_List *poly, double a, double b);
void npoly_zeros(nlist_List *poly);
void npoly_zeros_quick(nlist_List *poly, int *array, int size);
void npoly_trans(nlist_List *poly, double *array, int size);
double npoly_kl_sum(nlist_List *poly, nlist_List *poly2);
double npoly_kl(nlist_List *poly, nlist_List *poly2);

//ndouble.c
void rand_shuffle(double *array, int size);
void nlist_setparam_dbl(nlist_List *list, int index, double n, int before, int after);
void nlist_simple_print_dbl(nlist_List *list);
void nlist_print_dbl(nlist_List *list);
void nlist_append_dbl(nlist_List *list, double n);
void ndict_print_dbl(ndict_Dict *dict, int idx, int idx2, int idx3);
void nlist_trans_dbl(nlist_List *from, nlist_List *to);

//nrandom.c
int nrand_dist_pick(nlist_List *poly);
void nrand_dist_check(nlist_List *poly);
nlist_List *nrand_pick(int size, int num);
void nrand_pick_void(nlist_List *list, int size, int num, int *range);
nlist_List *nrand_shuffle(nlist_List *list);
void nrand_shuffle_void(nlist_List *list);
void nrand_shuffle_ex(nlist_List *list, int *array, int size, int ex);
void nrand_shuffle_ex_simple(nlist_List *list, int ex);

#endif
