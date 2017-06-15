#!/bin/sh

# function to show usage message
usage()
{
    echo "Usage: broify.sh"
    echo
    echo "  -h         show this message"
    echo "  -d DELIM    Use this as the comment delimiter."
    echo "  -W          Don't strip empty lines."
    exit $1
}

# Set flag variable defaults
STRIPEMPTY=1
DELIM='#'

# reads flags from user
while [ $# -gt 0 ]
do

    case $1 in
        -h) usage 0;;
        -d) 
            if [ $# -eq 1 ]; then
                usage 1 
            fi
            DELIM=$2
            shift;;
        -W) STRIPEMPTY=0;;
        *)  usage 1;;
    esac
    shift
done

# reads input from STDIN
INPUT=`cat`

# remove comments
INPUT=`echo "$INPUT" | sed -r "s|\s*$DELIM.*$||" `

# strip empty lines if supposed to
if [ $STRIPEMPTY -eq 1 ]
then
    INPUT=`echo "$INPUT" | sed '/^\s*$/d'`
fi

# remove trailing whitespace
INPUT=`echo "$INPUT" | sed -r '$ s/\s*$//'`

echo "$INPUT"

