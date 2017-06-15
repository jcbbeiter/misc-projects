#!/bin/sh

# function to show usage message
usage()
{
    echo "Usage: zipcode.sh"
    echo
    echo "  -h              Show this message"
    echo "  -c      CITY    Which city to search"
    echo "  -f      FORMAT  Which format (text, csv)"
    echo "  -s      STATE   Which state to search (Indiana)"
    exit $1
}

# Set defaults
STATE="Indiana"
FORMAT="text"
CITY='.*'

# reads flags from user
while [ $# -gt 0 ]
do
    # If there's only one flag, show usage message
    if [ $# -eq 1 ]; then
        usage 1 
    fi

    case $1 in
        -c) CITY=$2;; 
        -f) FORMAT=$2
            if [ "$FORMAT" != "text" ] && [ "$FORMAT" != "csv" ]; then
                echo "Error: invalid format $FORMAT."
                echo "Valid formats: text, csv"
                echo ""
                usage 1
            fi;;
        -s) STATE=$2;;
        *)  usage 1;;
    esac
    shift
    shift
done

# get data
HTML=`curl -s "http://www.zipcodestogo.com/$STATE/"`

# Scrape zip codes from HTML
ZIPCODES=`echo "$HTML" | grep "zipcodestogo.com/$CITY/" | egrep -o '[0-9]{5}' | uniq`

# If format is 'text', just print codes
if [ $FORMAT == 'text' ]; then
    echo "$ZIPCODES"
else # otherwise, print in csv format
    echo `echo $ZIPCODES | sed 's/\s/,/g'` 
fi


