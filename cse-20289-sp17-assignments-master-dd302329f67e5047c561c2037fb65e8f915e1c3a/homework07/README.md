Homework 07
===========
--- Activity 1 ---
1. In node_create I allocated the memory for the node using malloc(sizeof(struct node)). Additionally, I used strdup() to copy in the string, which also allocates memory. So, in node_delete I had to free (n->string) and (n) for each node n. I handled the "recursive" flag iteratively -- if it was set to true, it read along the node's "next" pointers, freeing as it went, until it found NULL.
2. In list_create, the only memory allocated was the list itself -- malloc(sizeof(struct list)). In list_delete, I just called node_delete with the recursive flag enabled on the head pointer to handle the internal nodes, then freed the list struct itself. 
3. My quick sort algorithm isn't too much more than a wrapper for the quicksort algorithm from cstdlib. It generates an array using list_to_array(), and then calls qsort() on that array. Once sorted, it iterates through the array and updates the pointers to rearrange the list. Finally, it frees the array.
    Since this is an implementation of qsort, the average time complexity is O(n*logn), and the worst case is O(n^2). The space complexity is O(n) -- the function allocates an array that is a copy of all of the inputs.
4. My list_reverse function also copies the list into an array. It sets head and tail to the back and front of the array, respectively, then iterates through it, swapping the relationship between the nodes to reverse the list. Finally, it frees the array.
    The time complexity of this algorithm is O(n) -- both creating the array and reversing the nodes require stepping through the entirety of the input. The space complexity is also O(n): it allocates an array to be the copy of the list.
5. The list_msort function is an implemtation of merge sort. A step of merge sort works by splitting the list into two smaller lists (left and right), calling msort on those halves, and then merging the two sorted lists back into one list. The splits happen all the way down until the lists are of length one, then it merges back up into a sorted list - the merge function merges the two lists in order using two read pointers.
    list_msort is an implementation of merge sort, so its time complexity is O(n*logn) -- it splits in havles (log n), and reads through the lists to merge them (n). The space complexity of this implementation is O(1) -- it only uses a few various local variables the help iterate through the arrays, and changes the "next" pointer of the nodes. No memory is allocated that scales with the input size.

--- Activity 2 ---
| NITEMS   | SORT     | TIME (s)  | SPACE (Mb)|
| -------- | -------- | --------- | --------- |
| 1        |  Merge   | 0.001999  | 0.464844  |
| 1        |  Quick   | 0.000999  | 0.476562  |
| 10       |  Merge   | 0.000999  | 0.464844  |
| 10       |  Quick   | 0.001999  | 0.468750  |
| 100      |  Merge   | 0.001999  | 0.468750  |
| 100      |  Quick   | 0.000999  | 0.476562  |
| 1000     |  Merge   | 0.001999  | 0.523438  |
| 1000     |  Quick   | 0.001998  | 0.609375  |
| 10000    |  Merge   | 0.007998  | 1.078125  |
| 10000    |  Quick   | 0.006998  | 1.285156  |
| 100000   |  Merge   | 0.099984  | 6.566406  |
| 100000   |  Quick   | 0.085986  | 8.156250  |
| 1000000  |  Merge   | 1.870715  | 61.503906 |
| 1000000  |  Quick   | 1.274805  | 76.832031 |
| 10000000 |  Merge   | 27.839767 | 610.816406|
| 10000000 |  Quick   | 16.534485 | 763.476562|

1. For the first several input sizes (until 10000 or so), the time and space don't vary much -- the input sizes are small enough that most of the costs are the static overhead costs. Past that, though, the time goes up by a bit more than a factor of 10 each time (makes sense - ideally, should be 10*log(10)) and the memory also increases by around a factor of 10. These results aren't too surprising -- it seems to scale roughly as I would have expected it to.

2. One thing about translating theoretical complexity to the real workd is that it breaks down at low input sizes; until your inputs get large enough the time and space costs will be roughly constant, due to the overheads associated with running the program. Once the inputs get large enough, though, it seems to translate to the real world reasonably well.
