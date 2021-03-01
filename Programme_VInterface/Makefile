all: compil run

run:
	./Huffman

compil :
	cd src; qmake
	cd src; make
	cd src; mv Huffman ..

clean:
	@rm -f Huffman
	cd src; make clean
	cd src; rm -f .qmake.stash
	cd src; rm -f Makefile
