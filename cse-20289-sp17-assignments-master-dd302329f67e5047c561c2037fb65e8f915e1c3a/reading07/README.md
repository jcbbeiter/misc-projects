Reading 07
==========

--- Activity 1 ---
1.
    1. read_numbers reads numbers from stdin until it reaches the end of file. In the highlighted line, the & in front of numbers[i] returns the memory address of that array location, because scanf() takes a pointer to store the read input. After reading each number, it compares the read input to the constant EOF (END OF FILE). If the most recent read number is equal to EOF, the while loop stops execution -- there are no more numbers to read.
    2. No, we could not have used sizeof() to get the size of the array inside the function. When you pass an array to a function, it's just the head pointer (in this case, a pointer to an int). The function doesn't necessarily know that numbers is an array instead of just a pointer to an int, so sizeof(numbers) will return the size of the int data type.
    
2.
    1. The two versions of cat parse command line arguments pretty similarly. They both ignore the basename, then check the subsequent arguments while they begin with '-' for flags. After all the flags have been checked, the remaining arguments are all the files to cat. The program gets the command line arguments in two variables: argc, which is an int representing the number of command line arguments, and argv[], an array of char*s that contains all of the command line arguments.
    2. "while (argind < argc)", combined with the incrementing of argind in the next line, iterates through the remaining command line arguments and operates on each.
        "char* path = argv[argind++];" reads the next command line argument into a string variable that represents the path to the file, and increments argind so that the next iteration looks at the next argument.
        Next, the strcmp comparison checks to see if the argument is a string exactly equal to the string "-": in that case, read input from stdin instead of a file.
        Otherwise, read the file represented by path usign the cat_file() function.
    3. cat_stream() is a function that takes a stream and outputs its contents to stdout. It works using two functions: fgets() and fputs(). It uses fgets() to read input from the stream and store it in a buffer (whose size is BUFSIZ, a value chosen on each system to make I/O efficient). Next, it uses fputs() to put the content of the buffer out in stdout. This repeats until there's nothing more to get from the stream using fgets().
    4. The cat_file() function in essence is an intermediary for cat_stream() - it opens the file from the provided path, and calls cat_stream() on that filestream.
        The highlighted if statement is the error handling for this function. If the file is unable to be opened (so fs is NULL instead of a valid stream), it prints an error message. "errno" is the numerical identifier of the last error that has occurred (here, it would be when trying to open an invalid file). Since that is not very helpful to the user, it is passed through strerror(), a function that takes a numerical identifier and returns a string description of the error.

Note - my Makefile is structured slightly differently for ease of use (clean also removes test scripts, and test also checks for the executables), but it still does everything needed.
