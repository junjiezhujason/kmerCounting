CFLAGS=		-g -Wall -O2 -ftree-vectorize -std=c++0x
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE
#IFLAGS= 	-I /scail/u/junjiezhu/tools/bamtools/include/ 
#LFLAGS=	-L /scail/u/junjiezhu/tools/bamtools/lib/ -lbamtools
#IFLAGS=	-I ~/Shannon/bamtools/include/
#LFLAGS=	-L ~//Shannon/bamtools/lib/

kmerCounter: kmerCounter.o printer.o faReader.o io.o
	gcc $(CFLAGS) $(DFLAGS) kmerCounter.o printer.o faReader.o io.o -lz -pthread -lstdc++ -o kmerCounter

loadMapTest: loadMapTest.o io.o
	gcc $(CFLAGS) $(DFLAGS) loadMapTest.o io.o -lz -pthread -lstdc++ -o loadMapTest


kmerCounter.o: kmerCounter.cpp
	gcc $(CFLAGS) $(DFLAGS) -c kmerCounter.cpp

printer.o: printer.cpp
	gcc $(CFLAGS) $(DFLAGS) -c printer.cpp

faReader.o: faReader.cpp
	gcc $(CFLAGS) $(DFLAGS) -c faReader.cpp

io.o: io.cpp
	gcc $(CFLAGS) $(DFLAGS) -c io.cpp

loadMapTest.o: loadMapTest.cpp
	gcc $(CFLAGS) $(DFLAGS) -c loadMapTest.cpp



clean:
	rm -f kmerCounter
	rm -f loadMapTest
	rm -f kmerCounter.o
	rm -f faReader.o
	rm -f printer.o
	rm -f io.o
	rm -f loadMapTest.o

