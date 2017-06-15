Reading 05
==========
1: echo.py
    1. 'import sys' imports the module that allows python to access system-specific information -- in this case, the arguments that the script was called with.
    2. 'for arg in sys.argv[1:]:' iterates through the arguments of sys.argv starting with index 1 (the second element), and going to the end. The trailing ':' simply tells to indent after the line.
    3. The trailing ',' in "print arg," suppresses the newline that is usually printed after each print statement (i.e. makes the script print all arguments on one line).

2: cat.py
    1. The loop runs while all three of these are true: a) the "args" list has a non-zero length b) The first argument (args[0]) starts with '-' (is a flag), and c) The first element has length greater than 1 (i.e. is more than just a dash).
    The loop reads the argument using the 'pop' command, which removes the element when it reads it.
    2. Once all of the command line arguments have been read, a '-' is appended to the args list if it is empty (i.e. if no path was specified). The second code block reads each of the remaining arguments and uses each as the 'stream' object to read from the file. If the path argument is a '-' (set by the first code block), then it uses the default input: stdin.
    3. 'line = line.rstrip()' strips all of the trailing whitespace from the line before printing. It isn't strictly necessary for a cat function, but it is useful so that the '$' will appear at the end of the important characters of each line, not the end of the whitespace.
