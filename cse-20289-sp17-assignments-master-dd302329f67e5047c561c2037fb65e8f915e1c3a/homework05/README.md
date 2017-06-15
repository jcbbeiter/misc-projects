Homework 05
===========

--- Activity 1: hulk.py ---
1.  - I generated all the password combinations using itertools' Cartesian product function:
    >>> perms = itertools.product(alphabet,repeat=length)
    - The candidates were filtered to only contain valid passwords using the smash function. Given the whole list candidates, smash() returns only the ones whose md5sum hash is in the hashes file.
    - I handled processing with multiple cores using the multiprocessing module. I declared a Pool with the number of cores specified by the user, and then used its member function imap() to perform the smashing.
    - I verified that my code works properly in a few different ways. When implementing the functions I made sure that their output was correct for the provided examples inside the codes. Once the whole script was finished I used the doctests and small cherrypicked inputs (e.g. the only hash input is md5sum('a') to make sure it got the expected output). And once I tested it on the full hashes.txt, it output many passwords -- doesn't necessarily mean it was exactly right, but it's definitely consistent with a working script.
    I also used testhulk.py to make sure everything was in order.

2.
Runtime for passwords of length 6:
x-----------x------x
| Processes | Time |
x-----------x------x
|         1 | 198m |
|         2 | 99 m |
|         4 | 29 m |
|         8 | 33 m |
|        16 | 63 m |
x-----------x------x

3. Both more complex alphabet and longer passwords increase the time it takes to brute force, but password length increases the time much more quickly. Time increases multiplicatively with alphabet length (more possibilities per character), but exponentially with password length (another character, with every possibility - multiplies time by 26+).

--- Activity 2: Inverted Index ---
iv_map.py keeps track of the line numbers by using an enumerate() to iterate through stdin - As it reads each line, it also keeps track of the line number.
iv_map.py removes undesirable characters using a list comprehension:
len = [char.lower() for char in line if char.lower() in 'abcdefghijklmnopqrstuvwxyz-' or char.isspace()]
    This line converts all characters to lowercase, and discards them if they're not in the set of desired characters. It also preserves whitespace, for word delimiting.

if_reduce.py nests two data structures to solve the problem: it uses a dict with string keys that point to set values. The script reads in each line, and separates it into a key and a value. If that key is not yet in the dict, it creates a new entry whose value is a set with the line's value. If they key is in the set, it just adds that value to the set.
To print the output, iv_reduce.py iterates through the dict and prints each key followed by the set of values, which are sorted based on their int value.
