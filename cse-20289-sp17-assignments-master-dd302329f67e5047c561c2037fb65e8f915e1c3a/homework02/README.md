Homework 02
===========
--- Activity 1 ---
1. The handling for no arguments is pretty simple. It's a single if statement: if $# is 0, then display the usage message and exit with code 1.
2. I determined which command to use for each argument by using a case structure. It looked like this:
case "$1" in
    *.tgz | *.tar.gz)
        #extract...
    *.tbz | *.tar.bz2)
        ...
    etc.
3. The most challenging aspect of the script to me was figuring out how exactly to extract the files. I haven't had any experience with files like these yet, and in particular the distinction between the compression tools and archival tools tripped me up for a bit - I thought I had to use gunzip, bunzip, etc. I got past it by looking more into the archival formats, and realized that I had to just use the tar command with different flags for each one. (except the zip/jar files, that tripped me up at first too.) 

--- Activity 2 ---
1. I displayed a random message to the user by using a switch statement on $((RANDOM % 10)). Depending on the number generated, the script selects one of ten prewritten prompts.
2.kSignals were handled with three 'trap' statements right at the start of the program. They each had the structure 'trap " #cowsay something; exit 1" SIGNAL
3. I read input from the user simply by using the 'read' command. The user input was at the end of a while loop that tests the input's length (zero at the start). If the user's question is of zero length, the while loop runs again and the user is re-prompted for their question.
4. The most difficult part of this script for me was to get the signals working. I had my trap statements at the end, and they didn't seem to be catching the signals properly. Moving them to the beginning fixed that, but I'm not positive if that's the way you're "supposed" to do it. It works for me, though. 

--- Activity 3 ---
1. The first step is to scan xavier.h4x0r.space for an HTTP port:
   > nmap -v -Pn xavier.h4x0r.space
   Notable output: port number followed by service
   port 22 is open: ssh
   port 8888: sun-answerbook
   port 9111: DragonIDSConsole
   port 9876: sd

2. The assignment says to look for HTTP ports - only 9111 and 9876 are in that range. sd looks like it could be a command or service name. Let's try...
    > man sd
    Looks like it's a "Driver for SCSI Disk Drives". Not sure what I would do with this.

3. Let's poke around port 9111. Let's use netstat to listen.
    > netstat xavier.h4x0r.space 9111
    Whoa, that printed out a lot of stuff! Let's try again, with a bit more forethought
    > netstat xavier.h4x0r.space 9111 | less
    Hmm... this appears to be "Active Internet Connections". There's a ton of stuff here. I'm on here too - 'jacobshp.dhcp.nd.edu:57540.

4. Y'know, looking at my notes, I'm using the wrong command. Professor Bui used nc (netcat) to talk to google, not netstat. Let's try that instead.
    > nc xavier.h4x0r.space 9111
    Ooh, that's promising! An Ascii dragon appears and asks me my name.
    > Jacob
    He asks me for a message. Let's go for broke.
    > Where is the Oracle?
    He doesn't understand and recommends I go back to the DOORMAN or BOBBIT, and closes my connection. Well, that's a start, with those two keywords.

5. Let's use netcat to look at the other port.
    > nc xavier.h4xor.space 9876
    It just hangs. I don't know the protocol to talk to it. (probably because it's used to mount disk drives). 

6. So I poked at both of the ports, and am only left with two keywords: DOORMAN and BOBBIT. What if DOORMAN and BOBBIT are the information to ssh in? Let's try that.
    > ssh DOORMAN@xavier.h4x0r.space
    Password 'BOBBIT' doesn't work. Maybe they're swapped.
    > ssh BOBBIT@xavier.h4x0r.space
    Password 'DOORMAN' doesn't work. Well, it was worth a try.

7. Maybe there's a file with DOORMAN or BOBBIT in the name? My guess is that it would be in Professor Bui's directory. Let's search all of the files (that we can access) beneath that directory for DOORMAN or BOBBIT.
    > ls /afs/nd.edu/user15/pbui -RU | grep DOORMAN
    I got the path to the pbui directory from the path to cowsay. This takes a long time, Professor Bui must have a lot of stuff. This probably isn't how we're supposed to solve this -- I exited while it was still searching (without a match).

8. The first port seems to be something I can't do yet. The way forward must be on the other port that I haven't gotten a response from. I've been tipped off to try wget. Let's do that.
    > wget xavier.h4x0r.space 9876
    Looks like that wasn't the right syntax.
    > wget xavier.h4x0r.space:9876
    There we go. It saved it to a file - let's take a look. Aha! I need to _request_ the DOORMAN at /{NETID}/{PASSCODE}. I need to _find_ my LOCKBOX in ~pbui/pub/oracle/lockboxes, then bruteforce it. Neat!

9. First, let's go to that directory and have a look around.
    > cd ~pbui/pub/oracle/lockboxes
    > ls

10. Looks like a bunch of hexadecimal strings. Let's see the general layout.
    > tree | less
    Each one seems to have a few layers, then a bunch of files with a netid on them.

11. I need to find which one is mine.
    Well... this probably isn't how you're supposed to do it, but I can just scroll through the tree real fast and find mine. It helps that there's ~100 files with my netid all on top of each other.
    I'm in /26aa3a18/84c7ce49/09d00616/e26fcac0

12. Let's go there and have a look around.
    > cd 26aa3a18/84c7ce49/09d00616/e26fcac0
    > ls
    Okay, there's jbeiter.{1..100} and jbeiter.lockbox

13.
    > jbeiter.lockbox
    Usage: lockbox password
    Okay, so I need the right password.

14. Let's investigate the {1..100} files.
    > ls -l
    They all have a file size of zero? They don't appear to be links or anything, either. Maybe they themselves are the possible passwords to bruteforce with? Worth a try.

15. I need a good way to try all of these possible passwords. 'jbeiter.lockbox \*' (asterisk escaped because it was making vim highlight), won't work, I need to try them individually, not all together. I need to do a loop, but I don't have editing rights here. What's stopping me from making the script somewhere else, though?
    > DIR=`pwd`
    Save the directory in a variable for later.
    > cd # to my assignments/homework02 folder
    > export DIR
    let's make DIR available for use in the script

16. I wrote a quick script to bruteforce it:
    #!/bin/sh
    for PW in $@
    do
        echo "Trying $PW"
        $DIR/jbeiter.lockbox "$PW"
    done

    > bruteforce.sh `ls $DIR`
    Hmm... that didn't seem to work.

17. Alright, I caved and looked at the hints. Apparently the 'strings' command will show me the possible passwords - it wasn't the number files.
    > strings jbeiter.lockbox
    Alright, yeah, a bunch of text. To be honest... how was I supposed to know to do that? That's a bit frustrating.

18. Well, the good thing is my script can still be used!
    > bruteforce.sh `strings $DIR/jbeiter.lockbox`
    that didn't seem to do anything, but come to think of it, if it printed output it would be flooded away by the "trying..." messages.
    I removed that line and tried again.
    > bruteforce.sh `strings $DIR/jbeiter.lockbox`
    Aha! It printed something: 330479aba1f92350b658e7ca57d5cf43

19. So this is the passcode, huh? It said earlier I need to "_request_ the DOORMAN at /{NETID}/{PASSCODE}"
    > wget xavier.h4x0r.space:9876/jbeiter/330479aba1f92350b658e7ca57d5cf43
    (I had an unsuccessful first with a space after the port number. Whoops.)
    Okay, it downloaded something like before...
    > less < 3304...
    Awesome! I need to talk to Bobbit.

20. On slack...
    > !verify jbeiter 330479aba1f92350b658e7ca57d5cf43
    I need to tell the oracle 'd29ydmdyZT0xNDg2MTAzOTg3'

21. Back to the oracle...
    > nc xavier.h4x0r.space 9111
    > jbeiter
    > d29ydmdyZT0xNDg2MTAzOTg3
    I'm smarter than the oracle thought -- she can see why the instructor likes me.
    Then Matrix stuff.
    Neat.


--- Oracle reflection ---

Well, that was definitely interesting, to say the least. I think I learned a bit about how to think about scripts and doing things in the shell.  I didn't have the access inside my lockbox folder to write a script, but... so? I can just write the script somewhere else. Though, I did hit two roadblocks that were sort of frustrating. 'nc' works fine to talk to port 9111, but you need to use wget for port 9876. That, and needing to use 'strings' on the lockbox. ...How was I supposed to know to do that? Other than that, though, I enjoyed it.
