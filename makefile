CFLAGS=		-g -Wall -O2 -ftree-vectorize
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE

kmerTableGen: kmerTableGen.o 
	g++ $(CFLAGS) $(DFLAGS) kmerTableGen.o -lz -pthread -lstdc++ -o kmerTableGen

kmerTableGen.o: kmerTable.cpp
	g++ $(CFLAGS) $(DFLAGS) -c kmerTableGen.cpp

clean:
	rm -f kmerTableGen
	rm -f kmerTableGen.o
	rm -f kmerTableGenhelper.o
