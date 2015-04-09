#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

typedef std::map <uint64_t, uint32_t> mapKmer;

void printbits(uint64_t binStr, int len){
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

void file_to_map(const char* fname, mapKmer& hist){
	std::ifstream file;
    uint64_t kmer;
    uint64_t pos;
    uint64_t map_size;

	file.open(fname, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
       printf("file_to_map: Cannot open the hist file %s!\n", fname);
       exit(1);
    }

    file.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for (int i = 0; i < map_size; i++) {
    	file.read(reinterpret_cast<char*>(&kmer), sizeof(kmer));
        file.read(reinterpret_cast<char*>(&pos), sizeof(pos));
        hist[kmer] = pos;
    }
	file.close();
}



int main(int argc, char* argv[]){
    char* fName;
    if ( argc == 2 ) {
            fName  = argv[1] ;
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

	mapKmer uniqueKmers;
	file_to_map(fName, uniqueKmers); // load uniqueKmerMap
    printf("MapSize:\t%d\n",(int)uniqueKmers.size());
    for ( mapKmer::iterator it = uniqueKmers.begin(); it != uniqueKmers.end(); ++it) {
        uint64_t kmer = it->first;
        uint64_t val = it->second;
        printbits(kmer,64);
        printf("\t%d\n",(int)val);
    }
}