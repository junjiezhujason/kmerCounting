#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

typedef std::unordered_map <uint32_t, uint32_t> umapKmer;

// 

void printbits(uint64_t binStr, int len){
    // TO DO: make this work for uint64_t and uint32_t
    uint64_t dd;
    int buffer[len];
    dd = binStr;
    int i = 1;
    while (i <= len) {
        buffer[len-i] = dd%2;
        dd = dd / 2;       
        i++;
    }
    for (i = 0; i < len;i++){
        printf("%d",buffer[i]);
    }
}

void printbits32(uint32_t binStr){
    uint32_t dd;
    int len = 32;
    int buffer[len];
    dd = binStr;
    int i = 1;
    while (i <= len) {
        buffer[len-i] = dd%2;
        dd = dd / 2;       
        i++;
    }
    for (i = 0; i < len;i++){
        printf("%d",buffer[i]);
    }
}

void printbits64(uint64_t binStr){
    uint64_t dd;
    int len = 64;
    int buffer[len];
    dd = binStr;
    int i = 1;
    while (i <= len) {
        buffer[len-i] = dd%2;
        dd = dd / 2;       
        i++;
    }
    for (i = 0; i < len;i++){
        printf("%d",buffer[i]);
    }
}

void printMapinfo(umapKmer m) { // print all kmers in an unordered map 
    uint32_t kmer;
    uint32_t val;

    printf("(Unordered) Map Size: %d.\n",(int)m.size());
    for ( umapKmer::iterator it = m.begin(); it != m.end(); ++it) {
        kmer = it->first;
        val = it->second;
        printbits32(kmer);
        printf("\t%u\n", val);
    }
}

void file_to_map(const char* fname, umapKmer& m, const int k){
	std::ifstream file;
    uint64_t kmer64;
    uint32_t kmer;
    uint64_t pos64;
    uint64_t pos;
    uint64_t map_size;


	file.open(fname, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
       printf("file_to_map: Cannot open the file %s!\n", fname);
       exit(1);
    }

    if (k > 16){
        printf("file_to_map: k must be no more than 16");
        exit(1);
    }

    file.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for (uint64_t i = 0; i < map_size; i++) {
    	file.read(reinterpret_cast<char*>(&kmer64), sizeof(kmer64));
        file.read(reinterpret_cast<char*>(&pos64), sizeof(pos64));
        kmer = kmer64 & 0xFFFFFFFF; // convert 64 to 32
        pos = pos64 & 0xFFFFFFFF; // convert 64 to 32
        m[kmer] = pos;
    }
	file.close();
}

int main(int argc, char* argv[]){
    char* fName;
    int k; 
    if ( argc == 3 ) {
            fName  = argv[1] ;
            k = atoi(argv[2]); // specify k for error control
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    umapKmer uniqueKmers;

    std::clock_t start;
    double duration;

    start = std::clock();

    // load the unique kmers into an unordered map 
	file_to_map(fName, uniqueKmers, k); // load uniqueKmerMap

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Duration: \n"<< duration <<' s.\n';

    printMapinfo(uniqueKmers);

}