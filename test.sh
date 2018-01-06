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
for file in $(ls tests/generator/ | sort -n)
do
	cj=$(($cj + 1))
	prefix=$( echo "$file" | sed -e "s/\.cpp//g" )
	eval "./$tccpath tests/generator/$file > tests/generator/asm.s"
	eval "gcc -m32 tests/generator/asm.s -o tests/generator/a.out"
	eval "./tests/generator/a.out > tests/generator/tcc.res"
	eval "gcc -m32 tests/generator/$file -o tests/generator/a.out"
	eval "./tests/generator/a.out > tests/generator/gcc.res"
	cmp -s "tests/generator/tcc.res" "tests/generator/gcc.res"
	if [ $? -eq 1 ]; then
		echo "$file test failed"
	else
		echo "$file test succed"
		ci=$(($ci + 1))
	fi
	rm tests/generator/tcc.res tests/generator/gcc.res tests/generator/a.out
	rm tests/generator/asm.s
done
echo "Generator: passed $ci/$cj"
echo "Total:  passed $(($pi+$ti+$ci))/$(($tj+$pj+$cj))"



