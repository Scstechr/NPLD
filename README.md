## HOW TO USE

### Basis:
```C
/* Include header files below */
/* or just include "header.h" */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "./define.h"
#include "./debugg.h"
#include "./nheader/nheader.h"

// Mersenne Twister (MT19937)
// (C) 1997 - 2002, M. Matsumoto & T. Nishimura
// www.sat.t.u-tokyo.ac.jp/~omi/random_variables_generation.html
include "MT.h"

// The maximum value for my machine
// May differ in every environment
#define STACK_SIZE 10836

int main(){
	/* SOME CODES */
	/* please free(list) afterwards */
	return 0;
}
```

### List of headerfiles:

#### `nlist.h`

- List structure implementation in `C`. 
- Attempts to imitate capability of `list` in `Python`.
- Fundamental of other header files.

#### `ndict.h`

- ___List with in a List___ structure implementation in `C`. 
- Requires `nlist.h`.

#### `nrandom.h`

- Header file for handling random variables.
- Requires `nlist.h`.

#### `npoly.h`

- Header file for handling polynomial equiations.
- Requires `nlist.h`.