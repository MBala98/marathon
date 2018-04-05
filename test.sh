#!/bin/bash

	for f in $1/*.in
	do
		DIFF=$(<$f valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./$2 2> /dev/null | diff - ${f%in}out)	
		DIFF2=$(<$f ./$2 2>&1 1> /dev/null | diff - ${f%in}err)
		if [ "$DIFF" == "" ] && [ "$DIFF2" == "" ] && [ $? == 0 ]
		then echo "Dla pliku $f test zakonczyl sie powodzeniem"
		else echo "Dla pliku $f test zakonczyl sie niepowodzeniem"
		fi
	done
	
