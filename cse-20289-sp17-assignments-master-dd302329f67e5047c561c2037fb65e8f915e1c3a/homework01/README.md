Homework 01
===========

--- Activity 1: Permissions & ACLs ---
1. a) HOME and PUBLIC have the same rights: Normal rights for nd_campus, system:administrators, system:authuser, jbeiter (me), and rlidwka (a sysadmin). The only difference between HOME and PUBLIC is that HOME has "l" following nd_campus and authuser, while PUBLIC has "rlk". I'm not sure what it means, if anything. PRIVATE only gives rights to system:administrators and jbeiter.
b) The nd_campus entry on the ACL for the PUBLIC directory makes it public, and the lack of it in the PRIVATE directory makes that directory private.

2. a) The result of the command is a "Permission denied" message -- I was not able to create the file.
b) ls -l in /afs/nd.edu lists the permissions for the web directory as "rwxrwxrwx" - full permissions for everyone. Because I cannot enter the web directory, even though the Unix permissions say I can, the ACLs must take precedence on AFS.

--- Activity 2: File Operations ---
| Command                             | Elapsed Time      |
|-------------------------------------|-------------------|
| cp /usr/share/pixmaps ~/images -r   | 3.058 seconds     |
| mv ~/images ~/pixmaps               | 0.004 seconds     |
| mv ~/pixmaps /tmp/jbeiter-pixmaps   | 2.998 seconds     |
| rm /tmp/jbeiter-pixmaps -r          | 0.010 seconds     |

1. Renaming the pixmaps folder is significantly faster than moving it, because renaming it simply modifies an attribute of the existing directory, while moving it has to create a new directory somewhere else with all the same data. Renaming only needs to interact with the file that governs the directy, while moving the directory must interact with (and copy) all of the data inside it.
2. Removing the /tmp/jbeiter-pixmaps operation is faster than moving it somewhere else, because it does much less. Moving the directory consists of reading it, writing it somewhere else, and then moving the original, while removing the directory only needs the third task.

--- Activity 3: Redirection ---
1. bc < math.txt
2. bc < math.txt > output.txt
3. bc < math.txt > output.txt 2> /dev/null
4. cat math.txt | bc
    This is less efficient than using I/O redirection because it uses an extra command that isn't necessary. There isn't any real reason to use the cat command, so it is very slightly slower because of its inclusion.

--- Activity 4: Pipelines ---
1. cat /etc/passwd | grep /sbin/nologin -c
2. w | cut -d' ' -f1 | uniq | grep -v 'USER' -c
3. ls -l /etc | awk '{print $5,$9}' | sort -gr | head -n 5 | awk '{print $2}'
4. ps -e | grep pts/ | grep bash -c

--- Activity 5: Processes & Signals ---
1. a) Ctrl-C failed to terminate the process (worth a try, right?). bg didn't put it into the background, but Ctrl-Z manages to pause it. Running the kill command (sending the TERM signal) only starts the program back up again.
b) Using Ctrl-Z to exit to the bash terminal and then sending the hard KILL command (kill -9) successfully terminated the process.

2. a)  kill -9 $(ps -U 'jbeiter' | grep pts/ | grep TROLL | awk '{print $1}')
b) The command "pkill -9 -u 'jbeiter' TROLL" kills all instances of the TROLL program being run by me on any terminal.

3. Passing it the HUP signal (-1) appears to result in song lyrics (Call Me Maybe, Say My Name, No Doubt-Spiderwebs, etc.) 
Passing it the BUS signal (-7) leads to phrases about motor vehicles (trains, Magic Bus, Speed Racer, etc.) 
The USR2 signal (-12) supposedly opens a connection to 'towel.blinkenlights.nl'. I can't get it to do anything further through the TROLL program, but if you run 'telnet towel.blinkenlights.nl' it plays ASCII Star Wars.
The ALRM signal leads to song lyrics about waking up, time, etc.

--- Guru Point ---
~/.bashrc changes: set history to not record duplicate commands
set bash prompt to "[\s \w \$" ex. [bash ~/systemsProgramming $]
set default editor to vim
set an alias for ls to use the auto coloring

I also made the ~/.cshrc change to launch into bash by default.
