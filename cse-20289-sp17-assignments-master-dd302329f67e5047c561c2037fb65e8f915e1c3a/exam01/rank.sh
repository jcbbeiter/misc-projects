#!/bin/sh

# function to show usage message
usage()
{
    echo "Usage: rank.sh [-n N -D]"
    echo
    echo "    -n N        Return N items (default is 5)."
    echo "    -D          Rank in descending order."
exit $1
}

# Set default number
NUMBER=5

# reads flags from user
while [ $# -gt 0 ]
do
    case $1 in
    -h) usage 0;;
    -n)
        if [ $# -eq 1 ]; then
            usage 1 #usage if didn't specify number
        fi
        NUMBER=$2
        shift;;
    -D) DESCEND=r;;
    *) usage 1;;
    esac
    shift
done
    
# if descending, DESCEND resolves to the r flag. Otherwise, it's blank
sort "-g$DESCEND" | head -n "$NUMBER"
