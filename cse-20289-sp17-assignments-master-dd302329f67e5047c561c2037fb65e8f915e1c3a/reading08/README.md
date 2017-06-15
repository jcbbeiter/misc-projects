Reading 08
==========
1. 4 bytes
2. 20 bytes
3. 8 bytes
4. 16 bytes
5. 8 bytes (size of a pointer)
6. 16 bytes
7. 160 bytes
8. 80 bytes (10 memory addresses for a "struct point")

1. malloc(n) was allocating one byte of memory per int, but ints are bigger than that. Changing it to n*sizeof(int) fixed the problem.

2. The memory error in Task 4 was due to the program not reaching the free() call when a duplicate was found. The test would return true and not free the allocated memory. I fixed this by simply adding another free(randoms) line inside the if block before returning true
