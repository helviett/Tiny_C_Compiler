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
for file in $(ls tests/scanner/ --ignore=*.out | sort -n)
do
	j=$(($j + 1))
	prefix=$( echo "$file" | sed -e "s/\.cpp//g" )
	eval "./$tccpath -t tests/scanner/$file > tests/scanner/temp.txt"
	cmp -s "tests/scanner/$prefix.out" "tests/scanner/temp.txt"
	if [ $? -eq 1 ]; then
		echo "$file test failed"
	else
		echo "$file test succed"
		i=$(($i + 1))
	fi
done
rm tests/scanner/temp.txt
echo "passed $i/$j"






