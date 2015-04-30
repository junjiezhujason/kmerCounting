#include "kmerCounter.h"

int unimap_to_file(const char* refFname, const int length, mapKmer& hist, const char* histName){
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
    int64_t pos;
    file.write(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for ( mapKmer::iterator it = hist.begin(); it != hist.end(); ++it) {
        kmer = it->first;
        pos = it->second;
        file.write(reinterpret_cast<char*>(&kmer), sizeof(kmer));
        file.write(reinterpret_cast<char*>(&pos),  sizeof(pos));
    }
    file.close();
    printf("map_to_file: file <%s> saved\n", fname.c_str());
    return 0;
}


int file_to_unimap(const char* fname, mapKmer& m, const int k){
    std::ifstream file;
    uint64_t kmer;
    int64_t pos;
    uint64_t map_size;

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
            m[kmer] = pos;
        }
    }
    file.close();
    printf("Finished loading file %s!\n", fname);
    printf("Total number of distinct kmers:\t%lld\n", (long long int) map_size);
    printf("Distinct kmers that are unique:\t%lld\n", (long long int) m.size());
    return 0;
}


int file_to_bitvec(const char* fname, const int k, bitvec& b)
{

    uint64_t kmer;
    int64_t pos;
    uint64_t map_size;
    uint32_t unikmer_size = 0;

    std::ifstream file;
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



int binstats_to_file(char* fName, int* a1, int* a2, const int binNum, const int binLen)
{
    std::string bFname(fName);
    std::string fname1(bFname);   
    fname1 += std::string("_subref"); 
    std::ofstream file1 (fname1.c_str());
    if (!file1.is_open()) {
       printf("Cannot open the file %s!\n", fname1.c_str());
       exit(1);
    }

    for (int i = 0; i < binNum; ++i) 
    {  
        file1 << a1[i] << "\t"<< a2[i] << "\n"; // record the last linePos = total number of reads
    }
    file1.close();
    printf("Finished saving file %s!\n", fname1.c_str());
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
//template void file_to_bitset<bitsetsize>(const char* fname, const int k, std::bitset<bitsetsize>& b);
*/



