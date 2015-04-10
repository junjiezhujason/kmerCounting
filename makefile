CFLAGS=		-g -Wall -O2 -ftree-vectorize -std=c++11
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE

kmerTableGen: kmerTableGen.o 
	gcc $(CFLAGS) $(DFLAGS) kmerTableGen.o -lz -pthread -lstdc++ -o kmerTableGen

kmerTableGen.o: kmerTable.cpp
	gcc $(CFLAGS) $(DFLAGS) -c kmerTableGen.cpp

clean:
	rm -f kmerTableGen
	rm -f kmerTableGen.o
	rm -f kmerTableGenhelper.o
