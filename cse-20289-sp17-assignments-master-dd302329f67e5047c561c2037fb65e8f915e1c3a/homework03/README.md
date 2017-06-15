Homework 03
===========

--- Activity 1: Caesar Cipher ---
1. I parsed the command line arguments in two areas. First, I read $1 in as FLAG with a default value of 'none'. Then, if $# is greater than 1 or if $FLAG is equal to '-h', the script prints the usage statement. FLAG had to be read in first, because if $1 was directly compared to '-h', there would be an error if none was specified, as = is not a unary operator.
If the usage statement is not triggered, then SHIFT is simply read in with a default value of 13: 'SHIFT=${1:-13}'

2. The source set is the same every time in my script. It is simply 'a-zA-z', the full alphabet of characters to be rotated.

3. The target set shifts each time. As an example of the structure, for the default shift of 13 it looks like this: 'n-za-mN-ZA-M'. The -za-/-ZA- endpoints are always the same, so I only needed to change four values depending on how much the rotation is. I accomplished this by having two environment variables that were simply a space-delimited alphabet, and using cut to extract the letters I wanted out of them (Shift+1 and Shift for the two endpoints).

4. Once I had both these sets (or really had SET2, SET1 is the same each time), the command was 'OUTPUT=`echo "$INPUT" | tr a-zA-Z "$TARGET"`'. In other words, pass INPUT to the tr command, which takes the alphabet and shifts it to the specified target range.

--- Activity 2: Broification ---
1. I handled the command line arguments by using a case statement that examined $1 and ran the 'shift' command after each iteration. If $1 was '-h' or default, it would run the usage function. If '-d' it would store $2 and shift an extra time, and if '-W' it would set the STRIPEMPTY flag to 0.

2. I removed comments using the replace (s/) option in sed. It matched from any whitespace followed by the delimiter to the end of the line (\s*$DELIM.*$)and replaced that with an empty string. This may leave a blank line behind, but it it does it is removed by the stripping whitespace task that comes immediately after.

3. I removed empty lines with the delete (//d) option in sed. It matched lines that had the beginning of the line followed by any amount of whitespace and then the end of the line (^\s*$) and deleted those lines.

4. The command line options (-d and -W) didn't affect my code very much, homestly. To handle delimiter specification I just had a DELIM variable that was '#' by default that the passed delimiter would be read into. And to handle the '-W' option, my line that removes empty lines was just within an if statement. The accomodations for the command line arguments were very simple.

--- Activity 3: Zip Codes ---
1. I handled the command line arguments by using a while loop that ran while the number of arguments was greater than zero, 'shift'ing by two each time. If there was only one argument left (so either -h, or not providing a followup to one of the flags) or if the flag wasn't recognized it would display the usage statement. Otherwise, if it was a -c -f or -s flag, it would read $2 into the proper variable.

2. I extracted the zip codes using the following line:
ZIPCODES=`echo "$HTML" | grep "zipcodestogo.com/$CITY/" | egrep -o '[0-9]{5}' | uniq`
I examined the html and saw that for each zip code there was a line that had 'www.zipcodestogo.com/$CITY/$STATEABBREV/$ZIPCODE/'. First I extracted the lines that had the web address in them (because there may be other 5 digit numbers in the HTML) and from those lines pulled out all the 5 digit numbers, then used uniq to get rid of duplicates.

3. I filtered by state in the line where I download the HTML:
HTML=`curl -s "http://www.zipcodestogo.com/$STATE/"`
The url changes based on which state we're looking for.

I filtered by city in the line that scrapes the zipcodes:
ZIPCODES=`echo "$HTML" | grep "zipcodestogo.com/$CITY/" | egrep -o '[0-9]{5}' | uniq`
CITY is assigned to '.*' before the flags are read, so if the user doesn't specify a city, the grep statement will match any city.

4. I handled the text and csv FORMAT options at the end of the script when the output is printed, with the following lines:

# If format is 'text', just print codes
if [ $FORMAT == 'text' ]; then
    echo "$ZIPCODES"
else # otherwise, print in csv format
    echo `echo $ZIPCODES | sed 's/\s/,/g'`
fi

If the format is text, we can just echo the codes. Otherwise, if it's in csv format (any other format would trigger the usage statement), pipe it through sed first and replace any whitespace with commas.

--- Guru Point: SSH Key ---
I added the SSH key.
