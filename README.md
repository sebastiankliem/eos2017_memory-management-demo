# Buddy Allocation using Linked Lists

This is a sample implementation for the buddy memory allocation algorithm using linked lists.  
It is build in the context of the [HPI Embedded Operating Systems lecture 2017](https://www.dcl.hpi.uni-potsdam.de/teaching/EOS17/).

## Building

Run `make`.

## Running the example

Provide the wanted memory pool size in KB as first parameter.
```bash
# e.g. 2048 KB
buddy 2048
```

## Example Output

The example allocates and deallocates memory in the following order:  
    + 120 KB  
    + 128 KB  
    + 40  KB  
    + 356  KB  
    + 359  KB  
    - 359 KB  
    - 356 KB  
    - 40 KB  
    - 128 KB  
    - 120 KB

After each allocation or deallocation the state of all free-lists is printed. An entry in a free-list ist the start address of a free block in that list.

```
BUDDY SYSTEM ALLOCATION
Memory size: 2048 kB
Min block size: 64 kB
Memory begins at: 0x109f16000
Memory status:
64:
128:
256:
512:
1024:
2048: 0x109f16000

request: 120
[1] start addres: 0x109f16000
64:
128: 0x109f35400
256: 0x109f54800
512: 0x109f93000
1024: 0x10a010000
2048:

request: 128
[2] start addres: 0x109f35400
64:
128:
256: 0x109f54800
512: 0x109f93000
1024: 0x10a010000
2048:

request: 40
[3] start addres: 0x109f54800
64: 0x109f64200
128: 0x109f73c00
256:
512: 0x109f93000
1024: 0x10a010000
2048:

request: 356
[4] start addres: 0x109f93000
64: 0x109f64200
128: 0x109f73c00
256:
512:
1024: 0x10a010000
2048:

request: 359
[5] start addres: 0x10a010000
64: 0x109f64200
128: 0x109f73c00
256:
512: 0x10a08d000
1024:
2048:

free [5]: 512KB
64: 0x109f64200
128: 0x109f73c00
256:
512:
1024: 0x10a010000
2048:

free [4]: 512KB
64: 0x109f64200
128: 0x109f73c00
256:
512: 0x109f93000
1024: 0x10a010000
2048:

free [3]: 64KB
64:
128:
256: 0x109f54800
512: 0x109f93000
1024: 0x10a010000
2048:


free [2]: 128KB
64:
128: 0x109f35400
256: 0x109f54800
512: 0x109f93000
1024: 0x10a010000
2048:

free [1]: 128KB
64:
128:
256:
512:
1024:
2048: 0x109f16000
```