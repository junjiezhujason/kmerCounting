#include "kmerCounter.h"

int printbits(uint64_t binStr, int len)
{
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

int printbits32(uint32_t binStr)
{
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

int printbits64(uint64_t binStr)
{
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

int printMapInfo(mapKmer &m) 
{ // print all kmers in an unordered map 
    uint64_t kmer;
    int64_t val;

    printf("(Unordered) Map Size: %d.\n",(int)m.size());
    for ( mapKmer::iterator it = m.begin(); it != m.end(); ++it) 
    {
        kmer = it->first;
        val = it->second;
        printbits64(kmer);
        printf("\t%lld\n", (long long int) val);
    }
    return 0;
}
 
/*
 template <size_t bitsetsize> // templatize size of bitset
void file_to_bitset(const char* fname, const int k, std::bitset<bitsetsize>& b)
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
}

//template void printbitset<bitsetsize>(std::bitset<bitsetsize> b, const uint32_t len);
*/

int printTwoArrays(int* a1, int* a2, const int binNum, const int binLen) {
    for (int i = 0; i < binNum; ++i) 
    {  
        printf("%d-", i * binLen /2 );
        printf("%d\t", i * binLen /2  + binLen - 1);
        printf("%d\t", a1[i]);
        printf("%d\n", a2[i]);
    }
    return 0;
}