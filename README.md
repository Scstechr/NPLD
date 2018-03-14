## HOW TO USE

#### Basis:
```C
include <stdio.h>
include <stdlib.h>
include <assert.h>
include <time.h>

// not-List Implementation
include "nlist.h"

// Mersenne Twister (MT19937) library
// (C) 1997 - 2002, M. Matsumoto & T. Nishimura
// www.sat.t.u-tokyo.ac.jp/~omi/random_variables_generation.html
include "MT.h"

// The maximum value for my machine
// May differ in every environment
#define STACK_SIZE 10836

int main(){
	/* SOME CODES */
	return 0;
}
```

#### `nlist_init()`
```C
nlist_List *list = nlist_init();
free(list);
```
###### In Python:
```python
# In python:
l = []
```

#### `nlist_range(int num)`
Similar to `range` function in `Python`.

```C
nlist_List *list = nlist_range(10);
nlist_print(list);
free(list);
```
```bash
$./a.out

size: 10, int list
[   0   1   2   3   4   5   6   7   8   9 ]
```
###### In Python:
```python
l = list(range(10))
```

#### `nlist_append(nlist_List *list, int num)`
Similar to `append` function in `Python`.

```C
nlist_List *list = nlist_range(4);
nlist_print(list);
nlist_append(list, 4);
nlist_print(list);
free(list);
```
```bash
$./a.out

size:  4, int list
[   0   1   2   3 ]

size:  5, int list
[   0   1   2   3   4 ]
```
###### In Python:
```python
l = list(range(4))
print(l)
l.append(4)
print(l)
```

#### `nlist_insert(nlist_List *list, int index, int num)`
```C
nlist_List *list = nlist_range(4);
nlist_print(list);
nlist_insert(list, 0, -1);
nlist_print(list);
free(list);
```
```bash
$./a.out

size:  4, int list
[   0   1   2   3 ]

size:  5, int list
[  -1   0   1   2   3 ]
```
###### In Python:
```python
l = list(range(4))
print(l)
l.insert(0,-1)
print(l)
```
#### `nlist_pop(nlist_List *list)`
```C
nlist_List *list = nlist_range(4);
nlist_print(list);
int pop = nlist_pop(list);
printf("popped:%d\n", pop);
nlist_print(list);
free(list);
```
```bash
$./a.out

size:  4, int list
[   0   1   2   3 ]

poped:3

size:  3, int list
[   0   1   2 ]
```
###### In Python:
```python
l = list(range(4))
print(l)
pop = l.pop()
print(f'popped:{pop}')
print(l)
```
#### `nlist_delete(nlist_List *list, int index)`
```C
nlist_List *list = nlist_range(4);
nlist_print(list);
nlist_delete(list, 2);
nlist_print(list);
free(list);
```
```bash
$./a.out

size:  4, int list
[   0   1   2   3 ]

size:  3, int list
[   0   1   3 ]
```
###### In Python:
```python
l = list(range(4))
print(l)
del l[2]
print(l)
```