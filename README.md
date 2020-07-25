# dstring

A dead simple dynamic string implementation that uses pre-allocated memory.



### Usage

------

Just copy the `dstring.h` and `dstring.c` files from the `src/` folder and use it.



### Change pre-allocation size

------

Define `DS_MAX_PREALLOC` at the start of your file and the library will automatically use the defined amount when allocating memory.

```c
#define DS_MAX_PREALLOC 512

#include <stdio.h>
#include <dstring.h>

int main() {
	dstring hello = ds_new("Hello world");    
}
```

**Note**: `DS_MAX_PREALLOC` defaults to 1024



### TODO

------

- Handle all `malloc` and `realloc` errors



### Goals

------

- Add a dstring viewer(in theory it can only read the memory and cannot perform any write operations)
- Use jemalloc for allocations to improve memory usage patters in multi-threaded programs
- Add more utility functions