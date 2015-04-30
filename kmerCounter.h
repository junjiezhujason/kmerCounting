#ifndef KMERCOUNTER_H
#define KMERCOUNTER_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
//#include <bitset>
#include <vector>

// for testing
#include <ctime>
#include <list>


typedef std::unordered_map <uint64_t, int64_t> mapKmer;
typedef std::vector<bool> bitvec;
//typedef std::bitset<3137161264> bitsethg;


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
int file_to_bitvec(const char* fname, const int k, bitvec& b);
int bitvec_to_file(const char* fname, const int k, bitvec& b); // TO DO LATER
 

//int file_to_bitset(const char* fname, const int k, bitsethg b);

// printer.cpp - used for testing and displaying
int printbits(uint64_t binStr, int len);
int printbits32(uint32_t binStr);
int printbits64(uint64_t binStr);
int printMapInfo(mapKmer &m);
int printTwoArrays(int* a1, int* a2, const int binNum, const int binLen);
int printbitvec(bitvec& b, const uint32_t len);

//template <size_t bitsetsize> int bitset_to_file(const char* fname, std::bitset<bitsetsize>& b);
//template <size_t bitsetsize> int file_to_bitset(const char* fname, const int k, std::bitset<bitsetsize>& b);
//template <size_t bitsetsize> int printbitset(std::bitset<bitsetsize>& b, const uint32_t len);







// templete implementation must be in the header :(
//template <uint32_t bitsetsize> // templatize size of bitset

#endif