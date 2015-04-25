#include "kmerCounter.h"


faReader::faReader(char* fastaFname, uint32_t _len)   {
    fastaFile = fopen(fastaFname,"r"); 
    if (fastaFile == NULL) {
        printf("fasta2ref: Cannot open FASTA file: %s!\n", fastaFname);
        exit(1);
    } else {
        printf("Start reading <%s>.\n", fastaFname);
    }
    len = _len;
    kmerChar = (char*) malloc(len*sizeof(char));
    kmerChar[len] = '\0';
    is_ambiguous = false;   // *** no N until I see N
    countDown = 0;
    setLenFilt();          // set a filter e.g. 00..0011..11 
    eos = false;
    pos = - (int) len;
    getNextKmer();
}

faReader::~faReader(void){
    free(kmerChar);
    fclose(fastaFile);
    printf("Files closed. \n");
}

int faReader::setLenFilt() { // called only in class construction 
    lengthfilter = 0;
    for (uint32_t i = 0; i < 2*len; i++) {
        lengthfilter = lengthfilter | (1LL << i);
    }
    return 0; 
}

uint64_t faReader::revKmer() {
    uint64_t rKmer = 0;// reverse string
    uint64_t filt = 3; // 0...011
    for (uint i = 0; i < len; i++) {
        rKmer = rKmer | ((((filt & kmer) >> uint64_t(2*i) ) << 2*(len-1)) >> 2*i); 
        filt <<= 2LL;
    }
    return (~rKmer) & lengthfilter; // reverse complement
}

uint64_t faReader::encode(char base) {
    if      (base == 'T' || base == 't') {return 3;} // 11
    else if (base == 'G' || base == 'g') {return 2;} // 10
    else if (base == 'C' || base == 'c') {return 1;} // 01
    else {return 0;} // A and other letters chars are all 0 (but we have hasN to control)
}

void faReader::determineKmerAmbiguity(char base){
    if (ambiguousBase(base)) {
        // re-start count down whenever encounter ambiguous base
        countDown = len;   
    }
    if (countDown > 0) {  
        // kmers w ambigous bases at pos: 0, ... len-2 are also ambigous    
        is_ambiguous = true;
        countDown--; 
    } else {
        is_ambiguous = false;
    }
}

bool faReader::ambiguousBase(char base) {
    if (base == 'A' || base == 'T' || base == 'G' || base == 'C' || 
        base == 'a' || base == 't' || base == 'g' || base == 'c') {
        return false;
    } 
    else {
        return true;
    }  
}

int faReader::getNextKmer(void){
    c = (char) getc(fastaFile);
    while(c == '\n' && !feof(fastaFile)) { // get a valid character
        c = (char) getc(fastaFile);
    } 

    if (feof(fastaFile)) { // indicate end of file
        eos = true; 
    } 
    else {
        if (c == '>') {  // description line
            recChr(); // record the chromosome description
            getFirstKmer();// *** POS
        } 
        else {
            pos++;
            determineKmerAmbiguity(c);
            kmer =  kmer << 2LL | encode(c);
            kmer = kmer & lengthfilter;
            // get the first kmer String in sequence data (REMOVE?)
            for (uint i = 0; i < len-1; i++) {
                kmerChar[i] = kmerChar[i+1];
            }
                kmerChar[len-1] = c;
        }
    }
    return 0;
}

int faReader::getFirstKmer(void){
    // get the first kmer in a chromosome, called only by getNextKmer
    uint i = 0;
    kmer = 0;
    while(i < len) {
        pos ++;
        c = (char) getc(fastaFile);
        //printf("%c",c);
        while(c == '\n') {
            c = (char) getc(fastaFile);
        }
        determineKmerAmbiguity(c);
        kmerChar[i] = c; // ***
        kmer =  kmer << 2 | encode(c);
        i++;
    }
    kmer = kmer & lengthfilter;
    return 0;
}

int faReader::recChr(void) {
    printf("%lld\t",pos+len);
    while (c != '\n') { 
        c = (char) getc(fastaFile);
        printf("%c",c);
    } 
    return 1;
}


void faReader::printKmers() {
    if (is_ambiguous) {
        printf("%lld*:\t", pos);
    } else {
        printf("%lld:\t", pos);
    }
    printf("%s\t", kmerChar);
    printbits64(kmer);
    printf("\t");
    printbits64(revKmer());
    printf("\n");
}



