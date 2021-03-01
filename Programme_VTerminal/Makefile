run: compil
	./exe

compil: main.o ArbreB.o Sommet.o huffman.o
	g++ -Wall main.o ArbreB.o Sommet.o huffman.o -o exe

Sommet.o : Sommet.cc Sommet.hh
	g++ -c Sommet.cc

ArbreB.o : ArbreB.cc ArbreB.hh
	g++ -c ArbreB.cc

huffman.o : huffman.cc huffman.hh
	g++ -c huffman.cc

main.o : main.cc ArbreB.hh huffman.hh
	g++ -c main.cc

zip : 
	tar -zcvf prog.tar.gz main.cpp Sommet.cc ArbreB.cc ArbreB.hh Sommet.hh Makefile

clean:
	rm -f exe
	rm -f *.o



