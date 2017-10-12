#!/bin/bash
tccpath=$(find -name "tcc" -print0)
if [ "$tccpath" = "" ];
then
	echo "tcc executable not found"
	echo "Trying to compile it by myself"
	mkdir build
	cd build
	cmake .. && make
	cd ..
	tccpath=$(find -name "tcc" -print0)
else
	echo "tcc was found"
fi
i=0
j=0
for file in $(ls tests/tokenizer/ --ignore=*.out | sort -n) 
do
	j=$(($j + 1))
	prefix=$( echo "$file" | sed -e "s/\.cpp//g" )
	eval "./$tccpath -t tests/tokenizer/$file > tests/tokenizer/temp.txt"
	cmp -s "tests/tokenizer/$prefix.out" "tests/tokenizer/temp.txt"
	if [ $? -eq 1 ]; then
		echo "$file test failed"
	else
		echo "$file test succed"
		i=$(($i + 1))
	fi
done
rm tests/tokenizer/temp.txt
echo "passed $i/$j"






