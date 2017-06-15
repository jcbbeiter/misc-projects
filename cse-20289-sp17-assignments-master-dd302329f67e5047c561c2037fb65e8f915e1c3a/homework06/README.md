Homework 06
===========

--- Activity 1 ---
1. My string_reverse_words function first reverses the entire string using the string_revese function - this part is O(n) in time and O(1) in space: it only uses 2 pointers and one char of extra memory. Then, it steps through the now reversed string with two pointers - wordStart and wordEnd. It finds the bounds of words and reverses them back to their original spelling.
    Overall, the function has time complexity O(n) - it just reads through the array, and performs an operation along it - and space complexity O(1) - regardless of input size, the amount of extra memory used is constant.

2. My string_translate function has a slightly higher time complexity. It steps through each character of the input string and, for each one, steps through the "from" string to see if that character is present. If it is, it steps through the "to" string, and if the "to" string is long enough replaces the character in the original message with the corresponding character in the "to" string.
If the length of the input string and "from" string are n and m respectively, this algorithm has a time complexity of O(nm). The size of the "to" string isn't in the expression, because the algorithm will never step farther into "to" than the length of "from".
The space complexity of this algorithm is O(1) - it doesn't use any extra memory to store variables.

3. My string_to_integer function steps through the input string once, and for each digit adds the proper amount to a rolling sum. Depending on the ASCII value of the digit, it shifts it by a certain amount (varies for digits, upper-, and lowercase letters) to its numerical value, then multiplies that by the base raised to the proper power before incrementing the sum. If the character is not recognized as a digit, it ignores it.
    This algorithm has a time complexity of O(n) - it steps through the input array once.
    This algorith has a space complexity of O(1) - regardless of input size, it only stores the same two variables in memory.

4. libstringutils.so (the shared library) is slightly larger (14K vs 12K). Shared libraries are pretty self-contained: the programs that use them just make references to the code in it at runtime. In a static library, however, any program that uses it copies the code and makes it part of the program. This allows static libraries to be slightly smaller, as they just get copied in at compile-time instead of having to interface at runtime.

--- Activity 2 ---
1. The command line parsing in translate.c works pretty simply. While there are still more arguments that begin with a '-' and have another character following, it reads them and does a switch statement on the second character. If it's recognized, a flag is enabled, otherwise the usage function is called.
    The translation is very simple -- I was able to just use the string_translate function that I wrote in the stringutils library - the input string, source, and target.
    The post-processing filters were implemented using the mode bitmask. There is an enum in translate.c that effectively aliases names like STRIP, UPPER, etc. to different powers of 2. The command line arguments set those corresponding bits in an integer to enable filters (e.g. mask |= LOWER to enable the lowercase filter). Those filters are tested for in translate_stream using e.g. if(mode & LOWER), and if they are true the corresponding stringutils function is called on the input.

2. translate-static is over 500 times larger than translate-dynamic (885K vs. 14K). The dramatic size difference is due to the fact that translate-static has the libraries compiled into it, while translate-dynamic has to load them at runtime. translate-static gains portabilty at the expense of size in memory and updatability.
    translate-static never had any problems for me.
    translate-dynamic didn't work initially - I had to set LD_LIBRARY_PATH so that it knew where to search for the library at runtime.


--- Guru Point ---
I have an Ubuntu VM that I've been using this year for my undergraduate research, but I can't make it to office hours this week to show it because I'm travelling with the band to the Women's Sweet 16. I'll try to come in early next week; hopefully that isn't a problem.
