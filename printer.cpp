#include "kmerCounter.h"

int printbits(uint64_t binStr, int len){
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
    return 0;
}

int printbits32(uint32_t binStr){
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
    return 0;
}

int printbits64(uint64_t binStr){
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
    return 0;
}

int printMapInfo(mapKmer &m) { // print all kmers in an unordered map 
    uint64_t kmer;
    int64_t val;

    printf("(Unordered) Map Size: %d.\n",(int)m.size());
    for ( mapKmer::iterator it = m.begin(); it != m.end(); ++it) {
        kmer = it->first;
        val = it->second;
        printbits64(kmer);
        printf("\t%lld\n", (long long int) val);
    }
    return 0;
}