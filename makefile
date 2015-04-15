CFLAGS=		-g -Wall -O2 -ftree-vectorize -std=c++0x
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE

kmerTableGen: kmerTableGen.o 
	gcc $(CFLAGS) $(DFLAGS) kmerTableGen.o -lz -pthread -lstdc++ -o kmerTableGen

kmerTableGen.o: kmerTableGen.cpp
	gcc $(CFLAGS) $(DFLAGS) -c kmerTableGen.cpp

findAnchors: findAnchors.o 
	gcc $(CFLAGS) $(DFLAGS) findAnchors.o -lz -pthread -lstdc++ -o findAnchors
	
findAnchors.o: findAnchors.cpp
	gcc $(CFLAGS) $(DFLAGS) -c findAnchors.cpp



clean:
	rm -f kmerTableGen
	rm -f kmerTableGen.o
	rm -f findAnchors
	rm -f findAnchors.o
