#!/bin/sh

# $1 is pulled here, because if it was in the if statement below it would throw
# an error if none was specified
FLAG=${1:-'none'}

# if too many arguments, display usage
if [ $# -gt 1 ] || [ $FLAG = '-h' ]
then
    echo "Usage: caesar.sh [rotation]"
    echo
    echo "This program will read from stdin and rotate (shift right) the text by the specified rotation. If none is specified, then the default value is 13."
    exit 1
fi

# Shift is 13 by default if not specified
SHIFT=${1:-13}

# Removes multiples of 26 from Shift
SHIFT=$(($SHIFT%26))

# Read input from stdin
INPUT=`cat`

# If shift is zero, repeat input and stop
if [ $SHIFT -eq 0 ]
then
    echo "$INPUT"
    exit 0
fi

# alphabets for constructing sets
LOWER="a b c d e f g h i j k l m n o p q r s t u v w x y z"
UPPER="A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"

# Gets letters for ranges depending on shift
LOWERTARGET="`echo "$LOWER" | cut -d ' ' -f $(($SHIFT+1))`-za-`echo "$LOWER" | cut -d ' ' -f $(($SHIFT))`"
UPPERTARGET="`echo "$UPPER" | cut -d ' ' -f $(($SHIFT+1))`-ZA-`echo "$UPPER" | cut -d ' ' -f $(($SHIFT))`"

# Combine into one target expression
# e.g. for 13 $TARGET is 'n-za-mN-ZA-M'
TARGET="$LOWERTARGET$UPPERTARGET"

# Output shifted text
OUTPUT=`echo "$INPUT" | tr a-zA-Z "$TARGET"`
echo "$OUTPUT"

exit 0
