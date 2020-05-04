all:
	gcc *.h *.c -o game -pthread -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

clean:
	rm -Rf *.gch

clear:
	rm -Rf game.out *.gch