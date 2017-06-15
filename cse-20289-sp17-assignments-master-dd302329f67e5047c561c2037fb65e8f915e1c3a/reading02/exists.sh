#!/bin/sh

outcode=0

if [ $# = 0 ]; then
    echo "ERROR: no arguments supplied"
    outcode=1
fi

for name in "$@"
do
    if test -e "$name"; then
        echo "$name exists!"
    else
        echo "$name does not exist!"
        outcode=1
    fi
done

exit $outcode
