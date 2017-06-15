Reading 02
==========
1. Even though it's not executable, you can still run the script 'exists.sh' with source: 'source exists.sh'
2. 'chmod 755 exists.sh' will make the script executable.
3. Once it's executable, simply type 'exists.sh' to run it (followed by any arguments)
4. The line '#!/bin/sh' means that this script should be run in a bash shell, even if the script is run from a different shell, like csh. More precisely, it runs a subshell to execute the script in.
5. If the script is run with the argument '*', the output is 'exists.sh exists!'. Even though '*' expands to all the files in the current directory, the $1 in the script only pays attention to the first one.
6. The '$1' in the script represents the first argument passed to the script.
7. 'test -e "$1"' tests to see if the string passed in the first argument refers to a valid file.
8. This script tests to see if a specified file exists and prints whether or not it does to the user.
