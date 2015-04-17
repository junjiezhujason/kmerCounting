#include "findAnchors.h"


int file_to_map(const char* fname, umapKmer& m, const int k){
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
    return 0;
}