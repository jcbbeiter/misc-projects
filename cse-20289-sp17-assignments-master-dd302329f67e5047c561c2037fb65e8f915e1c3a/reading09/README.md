Reading 09
==========
1.  1. The size of s is 16 bytes. This is larger than the sum of its constituent parts (8 bytes and 4 bytes), so the extra memory is a result of either overhead for the struct object, or padding done by the system for spacing.
    The size of u is 8 bytes. This is the size of its largest member value - a char*, which is 8 bytes in size.

    2. A struct is an object that can contain different members, whose types can be different, each with their own memory and values. A union, on the other hand, has different names that all point to the same memory. The different types are just different ways of interpreting the same bits.

2.  1. This program outputs the message "fate is inexorable!"
    2. After the second assignment (the one that uses the |= operator), all of the assignment operations result in the same bits. They are all just different ways to interpret those same bits that correspond to the mesage.
    3. All data/memory is stored in binary. Data types only tell the program how many bits to read and how to interpret them. When we cast values in C we aren't really changing them, just telling C to interpret them differently.

3.  1. In a hash table, a collision occurs when two different inputs hash to the same value, and so get assigned to the same index in the hash table.
    2. In a hash table that uses separate chaining, each location in the hash table is a list. If two things collide, then the second object is simply also added to the list -- that location in the hash table will contain both items.
    3. In a hash table that uses open addressing, when a collision occurs (i.e. an entry is to be inserted in a location that already has an entry), the second entry is placed in the next open spot in one direction. To look for an entry, a search algorithm has to check the hash location, and has to search each next position (if it's not found) until it finds an empty spot before it can be sure that the entry is not present (linear probing).

4.

Given the hash function h(x) = x%10, adding the following entries:
7,3,2,78,56,72,79,68,13,14
results in the following tables:


Using separate chaining:
x--------x-------x
| Bucket | Value |
| ------ | ----- |
|      0 |       |
|      1 |       |
|      2 | 2,72  |
|      3 | 3,13  |
|      4 | 14    |
|      5 |       |
|      6 | 56    |
|      7 | 7     |
|      8 | 78,68 |
|      9 | 79    |
x--------x-------x

Using open addressing and linear probing:
x--------x-------x
| Bucket | Value |
| ------ | ----- |
|      0 | 68    |
|      1 | 14    |
|      2 | 2     |
|      3 | 3     |
|      4 | 72    |
|      5 | 13    |
|      6 | 56    |
|      7 | 7     |
|      8 | 78    |
|      9 | 79    |
x--------x-------x




