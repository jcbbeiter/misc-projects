#!/bin/sh

# ethnic.sh

URL=https://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/csv/demographics.csv
DATA=`curl -s "$URL"`

count_ethnic() {
    column=$((($1-2012)*2))	# TODO: Determine appropriate column from first argument
    ethnic=$2	# TODO:	Ethnic group is second argument
     COUNT=`echo "$DATA" | cut -d ',' -f "$column" | grep "$ethnic" | wc -l`
    # TODO extract ethnic data for specified year and group
    echo "$COUNT"
}

for year in $(seq 2013 2019); do
    echo $year $(count_ethnic $year C) \
    	       $(count_ethnic $year O) \
    	       $(count_ethnic $year S) \
    	       $(count_ethnic $year B) \
    	       $(count_ethnic $year N) \
    	       $(count_ethnic $year T) \
    	       $(count_ethnic $year U)
done
