# RAM and CPU Cache Measurement
This program implements to measure the size of RAM and measure the characteristics of CPU Cache.

## Compute the size of RAM

The main method is to continuously call malloc() and memset() to ask memory from OS and trigger page swaping. When the physical memory is nearly full, the major amount of CPU work is to swap page and the whole system will go into a bad circumstance called Thrashing. We will detect the time of memset() between current time and last time. The program will finish when there is no success malloc() call or the time is two times larger than the last time. Till that the total asked memory is the approximated size of RAM.

## Measure the characteristics of Cache

### Method and Design
The measurement method is followed Saacadra & Smith's paper, the detail information can see [here](http://ieeexplore.ieee.org.ezproxy.neu.edu/stamp/stamp.jsp?arnumber=467697).
The program sets a bunch of byte arrays to implement measurement. The size of arrays is from 1KB to 64MB.

There are plenty of simple plus operations for some elements in each array.  The program will run 4 different STRIDE from 8 to 64 and for each STRIDE the slot whose index is associated with STRIDE will do the plus operations.

To enhance the accuracy, each round with different size of array and STRIDE will run 10 times to calculate the average time cost as the final result.

Since the CPU has different caches, the time will be different dramatically when the size of array is bigger one specific cache size.

### Result

The results are listed as two pictures, first one is the result from Macbook Pro personal laptop, second one is from CCIS linux server.

For the first one(result1.jpg), the first fast increase is in x = 5, so the L1 cache is 32KB; the second fast increase is in x = 8, so the L2 cache is 256KB; the third fast increase is in x = 12, so the L3 cache is 4MB.

For the second one(result2.jpg), the first fast increase is in x = 5, so the L1 cache is 32KB; the second fast increase is in x = 8, so the L2 cache is 256KB; the third fast increase is in x = 14, so the L3 cache is 16MB.

As we can see when STRIDE is larger than 16, the time is obviously bigger than STRIDE that is 8. Since 16 ints take up 64 bytes, once the STRIDE is larger than 16, we need more cache lines, so hence the cache line is 64 bytes.

Cache associativity is calculated by the division of array size and STRIDE while the array size is that the line in figure stop increasing.

## Build and Test

To run the RAM measurement:
```
make ramTest
```

To run the Cache measurement:
```
make cacheTest
```

