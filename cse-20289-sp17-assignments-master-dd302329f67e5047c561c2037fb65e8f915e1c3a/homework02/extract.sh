#!/bin/sh

if [ $# '-eq' 0 ]
then
    echo "Usage: extract.sh archive1 archive2..."
    exit 1
fi

EXITSTATUS='0'

while [ $# '-gt' 0 ]
do
    case "$1" in
        *.tgz | *.tar.gz)
            tar xfvz "$1"
        ;;
        *.tbz | *.tar.bz2)
            tar xfvj "$1"
        ;;
        *.txz | *.tar.xz)
            tar xfvJ "$1"
        ;;
        *.zip | *.jar)
            unzip "$1"
        ;;
        *) 
        echo "$1 is not a supported archive."
        EXITSTATUS='1'
    esac
    shift
done    

exit $EXITSTATUS
