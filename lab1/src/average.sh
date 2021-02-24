#!/bin/sh

echo Number od arguments: $#
av=0
for param in $@
do
av=$(($av + $param))
done
echo $(($av / $#))
