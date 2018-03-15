## HOW TO USE

### Basis:
```C
include <stdio.h>
include <stdlib.h>
include <assert.h>
include <time.h>

// not-List Implementation
include "nlist.h"

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
### Implemented Functions:
Please `free(list)` afterwards to free the memory secured by `malloc`.
`nlist_print(list)` is capable of printing out elements.
Two code blocks represents `C`(`nlist_List`) Implementation and equivalent `Python` code respectively.

#### `nlist_init()`
```C
nlist_List *list = nlist_init();
```
```python
l = list()
```
#### `nlist_range(int num)`
```C
nlist_List *list = nlist_range(10);
```
```python
l = list(range(10))
```
#### `nlist_append(nlist_List *list, int num)`
```C
nlist_List *list = nlist_range(4);
nlist_append(list, 4);
```
```python
l = list(range(4))
l.append(4)
```

#### `nlist_insert(nlist_List *list, int index, int num)`
```C
nlist_List *list = nlist_range(4);
nlist_insert(list, 0, -1);
```
```python
l = list(range(4))
l.insert(0,-1)
```
#### `nlist_pop(nlist_List *list)`
```C
nlist_List *list = nlist_range(4);
int pop = nlist_pop(list);
```
```python
l = list(range(4))
pop = l.pop()
```
#### `nlist_delete(nlist_List *list, int index)`
```C
nlist_List *list = nlist_range(4);
nlist_delete(list, 2);
```
```python
l = list(range(4))
del l[2]
```
#### `nlist_random_pick(int size, int num)`
```C
nlist_List *list = nlist_random_pick(10, 2);
```
```python
import random
l = random.choices(range(10), k=2)
```
