## BENCHMARK

#### Pure `Python`
```bash
$ python
Python 3.6.2 |Anaconda custom (64-bit)| (default, Jul 20 2017, 13:14:59)
[GCC 4.2.1 Compatible Apple LLVM 6.0 (clang-600.0.57)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>>
```
#### `C`
```bash
gcc -O3 -mtune=native -march=native
```
## `range`

##### Python Code
```python
[i for i in range(10000)]
```

##### C Code
```c
// narray.h
narray_Array *array = narray_range(1, 10000);
free(array)

// nlist.h
nlist_List *list = nlist_range(10000);
free(list)
```

##### Result

| Type | `real` | `user` | `sys` |
|-:-|-:-|:-|:-|
| `python` | 0.062 [s]| 0.041 [s]| 0.014 [s] |
| `narray.h` | 0.006 [s]| 0.001 [s]| 0.002 [s] |
| `nlist.h` | 0.007 [s]| 0.002 [s]| 0.002 [s] |



