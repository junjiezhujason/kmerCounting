#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
// gcc kmerTableGen.cpp -o kmerTableGen -lstdc++
// ./kmerTableGen 

typedef std::map <uint64_t, uint64_t> mapKmer;

class kmerReader{ // a file reader that goes through kmers
    FILE *_fa;
    const uint32_t _len;
    uint64_t encode(char base);
    // bool _eos; // end of sequence
    int getFirstKmer(); // *** to be incoporated in construction
    int setLenFilt();  
    // following used to determine if kmer is_ambiguous
    void determineKmerAmbiguity(char base);
    bool ambiguousBase(char base);
    int _countDown; 
    uint64_t lengthfilter;
    void printbits(uint64_t binStr, int len);

public:
    char name[300];
    bool is_ambiguous; // whether the kmer has ambigous bases or not
    bool eos;          // whether the kmer is the last one or not
    //char *kmerChar;
    uint64_t kmer;
    uint64_t pos;
    kmerReader(FILE *fa, uint32_t len) 
        :  _fa(fa), _len(len) {
        // kmerChar = (char*) malloc(_len*sizeof(char));
        is_ambiguous = false;   // *** no N until I see N
        _countDown = 0;
        setLenFilt();
        getFirstKmer();
        eos = false;
        pos = 0;
    }
    int getNextKmer(); 
    uint64_t revKmer();// returns reverse complement of the kmer 
};

int kmerReader::setLenFilt() {
    lengthfilter = 0;
    for (uint i = 0; i < 2*_len; i++) {
        lengthfilter = lengthfilter | (1LL << i);
        //printbits(lengthfilter,64); printf("\n");
    }

    return 0; 
}

uint64_t kmerReader::revKmer() {
    uint64_t rKmer = 0;// reverse string
    uint64_t filt = 3; // 0...011

    for (uint i = 0; i < _len; i++) {
        // *** DOUBLE-CHECK
        rKmer = rKmer | ((((filt & kmer) >> uint64_t(2*i) ) << 2*(_len-1)) >> 2*i); 
        filt <<= 2;
    }
    return (~rKmer) & lengthfilter; // reverse complement
}

uint64_t kmerReader::encode(char base) {
    if      (base == 'T' || base == 't') {return 3;} // 11
    else if (base == 'G' || base == 'g') {return 2;} // 10
    else if (base == 'C' || base == 'c') {return 1;} // 01
    else {return 0;} // A and other letters chars are all 0 (but we have hasN to control)
}

void kmerReader::determineKmerAmbiguity(char base){
    if (ambiguousBase(base)) {
        // re-start count down whenever encounter ambiguous base
        _countDown = _len;   
    }
    if (_countDown > 0) {  
        // kmers with ambigous bases at pos: 0 ... _len-2
        // are also ambigous kmers   
        is_ambiguous = true;
        _countDown--; 
    } else {
        is_ambiguous = false;
    }
}

bool kmerReader::ambiguousBase(char base) {
    if (base == 'A' || base == 'T' || base == 'G' || base == 'C' || 
        base == 'a' || base == 't' || base == 'g' || base == 'c') {
        return false;
    }
    else {
        return true;
    }  
}

int kmerReader::getFirstKmer(){
    char c = (char) getc(_fa);
    // sequence description line (> ...)
    while(c != '\n' && !feof(_fa)){
        c = (char) getc(_fa);
    }   
    uint i = 0;
    kmer = 0;
    while(i < _len && c != '>' && !feof(_fa)){ // c must be a base here
        c = (char) getc(_fa);
        determineKmerAmbiguity(c);
        // get the first kmer String in sequence data
        // kmerChar[i] = c;
        // get the frist kmer binary in the sequence data (REMOVE?)
        kmer =  kmer << 2 | encode(c);
        i++;
    }
    kmer = kmer & lengthfilter;
    return 0;
}

int kmerReader::getNextKmer(){
    char c = (char) getc(_fa);
    // get the next base
    while(c == '\n' && !feof(_fa)) {
            c = (char) getc(_fa);
        }
    if (feof(_fa)) {
        eos = true; // NO MORE KMERS
    }
    else {  // update the kmer and keep track of pos
        pos++;
        determineKmerAmbiguity(c);
        // get the next binary kmer in sequence
        kmer =  kmer << 2LL | encode(c);
        kmer = kmer & lengthfilter;
        // get the first kmer String in sequence data (REMOVE?)
        /*
        for (int i = 0; i < _len-1; i++) {
            kmerChar[i] = kmerChar[i+1];
        }
        kmerChar[_len-1] = c;
        */
    }
    return 0;
}

void kmerReader::printbits(uint64_t binStr, int len){
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


// TT:print
void printKmer(char *kmer, uint32_t len){
    for (int i = 0; i < len; i++) {
        printf("%c", kmer[i]);
    }
}

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


//kmerReader::kmerReader (FILE *_fa, uint32_t _len) {
//} TO DO: USE A CONSTURCTOR LATER

void maps_from_fasta(const char* fastaFname, const int length, mapKmer& kmerAll, mapKmer& kmerUni, mapKmer& kmerStr){
    uint64_t total_length;
    uint64_t total_kmers = 0;  // total number of unambigous kmers

    FILE *fastaFile;
    fastaFile = fopen(fastaFname,"r"); 
    if (fastaFile == NULL) {
       printf("fasta2ref: Cannot open FASTA file: %s!\n", fastaFname);
       exit(1);
    }

    kmerReader reader(fastaFile,length); //  initialize the kmer string and kmer
    while (!reader.eos) { 
        if (!reader.is_ambiguous) {
            // keep track of unique kmers and remove keys of non-unique kmers
            kmerAll[reader.kmer] ++;
            if (kmerAll[reader.kmer] == (unsigned)1) { 
                kmerUni[reader.kmer] = reader.pos; // position of kmer
                kmerStr[reader.kmer] = 0;          // on forward strand
            }
            if (kmerAll[reader.kmer] == (unsigned)2) { 
                kmerUni.erase(reader.kmer); 
                kmerStr.erase(reader.kmer); 
            }
            kmerAll[reader.revKmer()] ++;
            if (kmerAll[reader.revKmer()] == (unsigned)1) { 
                kmerUni[reader.revKmer()] = reader.pos; // position of kmer
                kmerStr[reader.revKmer()] = 1;          // on reverse strand
            }
            if (kmerAll[reader.revKmer()] == (unsigned)2) { 
                kmerUni.erase(reader.revKmer());
                kmerStr.erase(reader.revKmer()); 
            }
            // if kmerAll[reader.revKmer()] == kmerAll[reader.kmer], 
            // then this kmer will be removed from the unique list
            total_kmers++;
        }  
        reader.getNextKmer(); 
    } 
    total_length = reader.pos + length;
    total_kmers = 2*total_kmers;
    printf("total length:\t%lld\n",static_cast<long long>(total_length));
    printf("total kmers: \t%lld\n",static_cast<long long>(total_kmers));
    printf("- number of distinct kmers (mapsize):  \t%d\n", (int) kmerAll.size());
    printf("- distinct kmers that uniquely appear: \t%d\n", (int) kmerUni.size());
    fclose(fastaFile);
}


void map_to_file(const char* refFname, const int length, mapKmer hist, const char* histName){
    // modified Victoria's code
    std::string fname(refFname);
    fname += std::string("_");
    fname += std::to_string(static_cast<long long>(length));
    fname += std::string(histName);

    std::ofstream file;
    file.open(fname.c_str(), std::ios::out | std::ios::binary);
    if (!file.is_open()) {
       printf("map_to_file: Cannot open the hist file %s!\n", fname.c_str());
       exit(1);
    }

    uint64_t map_size = hist.size();
    uint64_t kmer;
    uint64_t val;
    file.write(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for ( mapKmer::iterator it = hist.begin(); it != hist.end(); ++it) {
        kmer = it->first;
        val = it->second;
        file.write(reinterpret_cast<char*>(&kmer), sizeof(kmer));
        file.write(reinterpret_cast<char*>(&val),  sizeof(val));
    }
    file.close();
}

int main(int argc, char* argv[]){
    // inputs:
    char* fastaFname;
    int length;
    if ( argc == 3 ) {
            fastaFname  = argv[1] ;
            length = atoi(argv[2]);
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    mapKmer MapAll, MapUni, MapStr; 
    const char MapAllName[] = "allCounts";
    const char MapUniName[] = "uniquePos";
    const char MapStrName[] = "uniqueStd";
    
    maps_from_fasta(fastaFname, length, MapAll, MapUni, MapStr); // create kmer maps from fasta file
    map_to_file(fastaFname, length, MapAll, MapAllName); // save counts map to .fahist file
    map_to_file(fastaFname, length, MapUni, MapUniName); // save unique pos map to .fahist file
    map_to_file(fastaFname, length, MapStr, MapStrName); // save unique pos map to .fahist file
    return 0;
}