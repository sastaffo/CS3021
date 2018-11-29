## Q1.

Compute the number of hits and misses if the following list of hexadecimal addresses is
applied to caches with the following organisations.
1. 128 byte 1-way cache with 16 bytes per line (direct mapped)
2. 128 byte 2-way set associative cache with 16 bytes per line
3. 128 byte 4-way set associative cache with 16 bytes per line
4. 128 byte 8-way associative cache with 16 bytes per line (fully associative)

```
0000 -> 0004 -> 000c -> 2200 -> 00d0 -> 00e0 -> 1130 -> 0028 ->
113c -> 2204 -> 0010 -> 0020 -> 0004 -> 0040 -> 2208 -> 0008 ->
00a0 -> 0004 -> 1104 -> 0028 -> 000c -> 0084 -> 000c -> 3390 ->
00b0 -> 1100 -> 0028 -> 0064 -> 0070 -> 00d0 -> 0008 -> 3394
```
Assume that the first 4 bits of the address is used as the offset within the cache line, the next log 2 (N) bits select the set and the remaining bits form the tag. Furthermore, assume that the all cache lines are initially invalid and that a LRU replacement policy is used.

## Q2.

Write a program (in C, C++, Java, ...) to solve Q1 (should be less than 200 lines of code). Make sure you can create a generalised cache object with parameters L, K and N.
