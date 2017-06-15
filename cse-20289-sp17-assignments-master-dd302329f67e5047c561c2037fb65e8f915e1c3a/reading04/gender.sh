#!/bin/sh

# gender.sh

URL=https://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/csv/demographics.csv
DATA=`curl -s "$URL"`

count_gender() {
    column=$((($1-2012)*2-1))	# TODO: Determine appropriate column from first argument
    gender=$2	# TODO:	Gender is second argument
    COUNT=`echo "$DATA" | cut -d ',' -f "$column" | grep "$gender" | wc -l` # TODO extract gender data for specified year and group
    echo $COUNT    
}

for year in $(seq 2013 2019); do
    echo $year $(count_gender $year F) $(count_gender $year M)
done
