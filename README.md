# bloomfilters-c

* `bitutil.c`, `bitutil.h` contain a simplified bit-vector, used for the implementation of the bloomfilter;
* `hashf.c`, `hashf.h` contain hash functions;
* `bloom.c`, `bloom.h` contain a simple bloom filter implementation;

Compiling and running the code:

```sh
gcc -Wall -std=c99 -pedantic main.c bloom.c bitutil.c hashf.c && ./a.out
```
Alternatively, `make bloom` and then `./main.out`.

You can read more about the code and its technical aspects on this [blog post](https://www.andreinc.net/2022/03/01/on-implementing-bloom-filters-in-c)
