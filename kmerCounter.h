#ifndef KMERCOUNTER_H
#define KMERCOUNTER_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <bitset>

// for testing
#include <ctime>
#include <list>


typedef std::unordered_map <uint64_t, int64_t> mapKmer;


// faReader.cpp
class faReader{ // a file reader that goes through kmers
    FILE *fastaFile;
    uint32_t len;  // length of the kmer
    uint64_t lengthfilter;
    int setLenFilt();  
    uint64_t encode(char base);
    bool ambiguousBase(char base); 
    int getFirstKmer(); // *** to be incoporated in construction
    // following used to determine if kmer is_ambiguous
    void determineKmerAmbiguity(char base);
    int recChr(void);
    int countDown; 
    char c; 

public:
    bool is_ambiguous; // whether the kmer has ambigous bases or not
    bool eos;          // whether the kmer is the last one or not
    char *kmerChar;
    uint64_t kmer;
    int64_t pos;
    faReader(char* fastaFname, uint32_t _len); // constructor
    ~faReader();       // destructor
    int getNextKmer(); 
    uint64_t revKmer();// returns reverse complement of the kmer 
    void printKmers();
};

// io.cpp 
//void unimap_fromfastaFilesta(const char* fastaFname, const int length, mapKmer& kmerAll, mapKmer& kmerUni, mapKmer& kmerStr)
int unimap_to_file(const char* refFname, const int length, mapKmer& hist, const char* histName);
int file_to_unimap(const char* fname, mapKmer& m, const int k);
int binstats_to_file(char* fName, int* a1, int* a2, const int binNum, const int binLen);



// printer.cpp - used for testing and displaying
int printbits(uint64_t binStr, int len);
int printbits32(uint32_t binStr);
int printbits64(uint64_t binStr);
int printMapInfo(mapKmer &m);
int printTwoArrays(int* a1, int* a2, const int binNum, const int binLen);


//template <size_t bitsetsize> int bitset_to_file(const char* fname, std::bitset<bitsetsize>& b);
template <size_t bitsetsize> int file_to_bitset(const char* fname, const int k, std::bitset<bitsetsize>& b);
template <size_t bitsetsize> int printbitset(std::bitset<bitsetsize>& b, const uint32_t len);





// templete implementation must be in the header :(
template <size_t bitsetsize> // templatize size of bitset
int printbitset(std::bitset<bitsetsize>& b, const uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)   
    {
        if (b[i]) 
        {
            printf("1");
        }
        else 
        {
            printf("0");
        }
    }
    printf("\n");
    return 0;
}

// templete implementation must be in the header :(
template <size_t bitsetsize> // templatize size of bitset
int file_to_bitset(const char* fname, const int k, std::bitset<bitsetsize>& b)
{
    std::ifstream file;
    uint64_t kmer;
    int64_t pos;
    uint64_t map_size;
    uint32_t unikmer_size = 0;
    file.open(fname, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
       printf("file_to_unimap: Cannot open the file %s!\n", fname);
       exit(1);
    }

    file.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for (uint64_t i = 0; i < map_size; i++) {
        file.read(reinterpret_cast<char*>(&kmer), sizeof(kmer));
        file.read(reinterpret_cast<char*>(&pos), sizeof(pos));
        if (pos > -1) {
            b[ (uint32_t) pos] = true;
            unikmer_size ++;
        }
    }

    file.close();
    printf("Finished loading file %s!\n", fname);
    printf("Total number of distinct kmers:\t%lld\n", (long long int) map_size);
    printf("Distinct kmers that are unique:\t%u\n", unikmer_size);
    return 0;
}

#endif