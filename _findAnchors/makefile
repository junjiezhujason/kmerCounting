CFLAGS=		-g -Wall -O2 -ftree-vectorize -std=c++0x
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE
#IFLAGS= 	-I /scail/u/junjiezhu/tools/bamtools/include/ 
#LFLAGS=	-L /scail/u/junjiezhu/tools/bamtools/lib/ -lbamtools
IFLAGS=		-I ~/Shannon/bamtools/include/
LFLAGS=		-L ~//Shannon/bamtools/lib/

help:
	grep -Eo "^\w(.*):" makefile


kmerTableGen: kmerTableGen.o 
	gcc $(CFLAGS) $(DFLAGS) kmerTableGen.o -lz -pthread -lstdc++ -o kmerTableGen

kmerTableGen.o: kmerTableGen.cpp
	gcc $(CFLAGS) $(DFLAGS) -c kmerTableGen.cpp


findAnchors: findAnchors.o io.o readwKmer.o printer.o 
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) findAnchors.o io.o readwKmer.o printer.o \
	-lz -lbamtools -pthread -lstdc++ -o findAnchors
	
findAnchors.o: findAnchors.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c findAnchors.cpp

printer.o: printer.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c printer.cpp

readwKmer.o: readwKmer.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c readwKmer.cpp

io.o: io.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c io.cpp


clean:
	rm -f kmerTableGen
	rm -f kmerTableGen.o
	rm -f findAnchors
	rm -f findAnchors.o
	rm -f printer.o
	rm -f io.o
