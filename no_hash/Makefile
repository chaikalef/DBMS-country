country: country.o list.o
	gcc country.o list.o -o country
country.o: country.c
	gcc -c country.c
list.o: list.c list.h
	gcc -c list.c
clean:     
	rm country.o list.o country
a:
	./country add Greece 1999 33223
c:
	./country count
du:
	./country dump
v:
	./country view Greece
de:
	./country delete Greece
p:
	cat countries.csv
test:
	clear
	make country
	echo
	./country add Greece 1999 33223
	echo
	./country count
	echo
	./country dump
	echo
	./country view Greece
	echo
	cat countries.csv
	echo
	./country delete Greece
	echo
	rm country.o list.o country