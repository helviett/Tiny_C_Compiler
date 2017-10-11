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
for file in $(ls tests/tokenizer/ -1 | sort -n) 
do
	j=$(($j + 1))
	eval "./$tccpath -t tests/tokenizer/$file > tests/tokenizerEtalons/temp.txt"
	cmp -s "tests/tokenizer/$file" "tests/tokenizerEtalons/temp"
	if [ $? -eq 1 ]; then
		echo "$file test failed"
	else
		echo "$file test succed"
		i=$(($i + 1))
	fi
done
rm tests/tokenizerEtalons/temp.txt

echo "passed $i/$j"