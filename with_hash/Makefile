country: country.o list.o map.o
	gcc country.o list.o map.o -o country
country.o: country.c
	gcc -c country.c
list.o: list.c list.h
	gcc -c list.c
map.o: map.c map.h
	gcc -c map.c
clean:     
	rm country.o list.o map.o country
p:
	cat countries.csv
test:
	clear
	make country
	echo
	./country
	echo
	cat countries.csv
	echo
	rm country.o list.o map.o country