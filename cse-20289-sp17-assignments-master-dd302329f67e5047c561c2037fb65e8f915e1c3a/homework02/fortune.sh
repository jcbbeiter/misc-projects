#!/bin/sh 
# /afs/nd.edu/user15/pbui/pub/bin/cowsay 

# traps for signal handling
trap "/afs/nd.edu/user15/pbui/pub/bin/cowsay -f tux \"Fine, see if I answer the phone next time\"; exit 1" SIGHUP
trap "/afs/nd.edu/user15/pbui/pub/bin/cowsay -f tux \"You could have at least said goodbye first \"; exit 1" SIGTERM
trap "echo "";/afs/nd.edu/user15/pbui/pub/bin/cowsay -f tux \" Didn't your mother ever teach you that it's rude to interrupt?\"; exit 1" SIGINT


# lets user ask question, reprompting if it's empty
QUESTION=""
while [ -z "$QUESTION" ]
do
    # randomly chooses a prompt for the user
    case $((RANDOM % 10)) in
        0)
            PROMPT="Hello $USER, what question do you have for me today?" ;; 
        1)
            PROMPT="You have a question for me, $USER, I can see it in your eyes." ;;
        2)
            PROMPT="Can I help you, $USER?" ;;
        3)
            PROMPT="What is it, $USER?" ;;
        4)
            PROMPT="Why, $USER, what is on your mind?" ;;
        5)
            PROMPT="Welcome, $USER. What fortune shall I tell?" ;;
        6)
            PROMPT="What is your question, $USER?" ;;
        7)
            PROMPT="Ask me anything, $USER." ;;
        8)
            PROMPT="Hello, $USER. What is your question?" ;;
        9)
            PROMPT="What question do you have for me, $USER?" ;;
    esac

    # prompt with initial question
    /afs/nd.edu/user15/pbui/pub/bin/cowsay -f tux "$PROMPT"

    # gets input - if this is blank, will reprompt
    read QUESTION
done

# randomly chooses a response
case $((RANDOM % 20)) in
    0) 
        RESPONSE="It is certain" ;;
    1) 
        RESPONSE="It is decidedly so" ;;
    2) 
        RESPONSE="Without a doubt" ;;
    3) 
        RESPONSE="Yes, definitely" ;;
    4) 
        RESPONSE="You may rely on it" ;;
    5) 
        RESPONSE="As I see it, yes" ;;
    6) 
        RESPONSE="Most likely" ;;
    7) 
        RESPONSE="Outlook good" ;;
    8)
        RESPONSE="Yes" ;;
    9)
        RESPONSE="Signs point to yes" ;;
    10)
        RESPONSE="Reply hazy -- try again" ;;
    11)
        RESPONSE="Ask again later" ;;
    12)
        RESPONSE="Better not tell you now" ;;
    13)
        RESPONSE="Cannot predict now" ;;
    14)
        RESPONSE="Concentrate and ask again" ;;
    15)
        RESPONSE="Don't count on it" ;;
    16)
        RESPONSE="My reply is no" ;;
    17)
        RESPONSE="My sources say no" ;;
    18)
        RESPONSE="Outlook not so good" ;;
    19)
        RESPONSE="Very doubtful" ;;
esac

# gives response
/afs/nd.edu/user15/pbui/pub/bin/cowsay -f tux "$RESPONSE"


