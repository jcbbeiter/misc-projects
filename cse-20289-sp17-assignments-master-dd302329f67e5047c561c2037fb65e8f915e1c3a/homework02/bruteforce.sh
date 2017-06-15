#!/bin/sh

for PW in $@
do
    $DIR/jbeiter.lockbox "$PW" 
done
