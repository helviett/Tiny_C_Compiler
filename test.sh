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
ti=0
tj=0
for file in $(ls tests/tokenizer/ --ignore=*.res | sort -n)
do
	tj=$(($tj + 1))
	prefix=$( echo "$file" | sed -e "s/\.cpp//g" )
	eval "./$tccpath -t tests/tokenizer/$file > tests/tokenizer/temp.txt"
	cmp -s "tests/tokenizer/$prefix.res" "tests/tokenizer/temp.txt"
	if [ $? -eq 1 ]; then
		echo "$file test failed"
	else
		echo "$file test succed"
		ti=$(($ti + 1))
	fi
done
rm tests/tokenizer/temp.txt
echo "Tokenizer: passed $ti/$tj"
pi=0
pj=0
for file in $(ls tests/parser/ --ignore=*.res | sort -n)
do
	pj=$(($pj + 1))
	prefix=$( echo "$file" | sed -e "s/\.cpp//g" )
	eval "./$tccpath -p tests/parser/$file > tests/parser/temp.txt"
	cmp -s "tests/parser/$prefix.res" "tests/parser/temp.txt"
	if [ $? -eq 1 ]; then
		echo "$file test failed"
	else
		echo "$file test succed"
		pi=$(($pi + 1))
	fi
done
rm tests/parser/temp.txt
echo "Parser: passed $pi/$pj"
ci=0
cj=0
for folder in "expr" "stmt";
do
	for file in $(ls $"tests/generator/$folder" | sort -n)
	do
		cj=$(($cj + 1))
		prefix=$( echo "$file" | sed -e "s/\.c//g" )
		eval "./$tccpath tests/generator/$folder/$file > tests/generator/$folder/asm.s"
		eval "gcc -m32 tests/generator/$folder/asm.s -o tests/generator/$folder/a.out"
		eval "./tests/generator/$folder/a.out > tests/generator/$folder/tcc.res"
		eval "gcc -m32 -w tests/generator/$folder/$file -o tests/generator/$folder/a.out"
		eval "./tests/generator/$folder/a.out > tests/generator/$folder/gcc.res"
		cmp -s "tests/generator/$folder/tcc.res" "tests/generator/$folder/gcc.res"
		if [ $? -eq 1 ]; then
			echo "$folder\\$file test failed"
		else
			echo "$folder\\$file test succed"
			ci=$(($ci + 1))
		fi
		rm $"tests/generator/$folder/tcc.res" $"tests/generator/$folder/gcc.res" $"tests/generator/$folder/a.out"
		rm $"tests/generator/$folder/asm.s"
	done	
done

echo "Generator: passed $ci/$cj"
echo "Total:  passed $(($pi+$ti+$ci))/$(($tj+$pj+$cj))"



