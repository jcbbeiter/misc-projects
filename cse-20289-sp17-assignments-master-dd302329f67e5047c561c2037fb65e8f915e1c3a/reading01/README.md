Reading 01
==========
1. a) The '|' is the pipe character, used to pipe the output of one command to the input of another.
b) 2> /dev/null has the effect of suppressing error output. The file descriptor 2 is the same as standard error, and it is redirected to /dev/null - a bit bucket that takes the input and does nothing with it.
c) "> output.txt" redirects the output of the final command to a file named output.txt
d) The 'h' in the "-h" flags stands for "human readable"; it changes the output to more easily read by humans by, in this case, listing memory usage with larger units (e.g. 2K 1G) instead of just the number of bytes.
e) This command is not the same as the previous. Because the error suppression is at the end, it applies to the sort command, and the error output from the du command (mostly about lacking permissions) are printed.

2. a) cat 2002-{01..12}
b) cat {2002..2006}-12
c) cat *-{01..06} | less
d) cat *[24680]-?[13579] | less
e) cat {2002..2004}-{09..12} | less

3. a) Files Huxley and Tux are executable by the owner.
b) Files Huxley and Tux are readable by members of the users group.
c) None of the files are writeable by the world.
d) chmod 755 Tux
e) chmod 600 Tux

4. a) press ctrl-z
b) type "fg" and move the process to the foreground, with the proper jobspec if there are multiple jobs (e.g. %1)
c) press ctrl-d to signal end of file
d) type "kill" followed by the proper jobspec (e.g. %1)
e) run the command "ps aux | grep $USER | grep bc". The results should be two lines: the currently open terminal (self-match from "grep bc") and the other terminal running bc. The second entry (after the username) is the PID. Simply type "kill" followed by the PID (e.g: kill 21249) to kill the process. 
