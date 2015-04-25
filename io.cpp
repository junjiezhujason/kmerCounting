#include "kmerCounter.h"

/*
void unimap_from_fasta(const char* fastaFname, const int length, mapKmer& kmerAll, mapKmer& kmerUni, mapKmer& kmerStr){
    uint64_t total_length;     // total length of the sequence
    uint64_t total_kmers = 0;  // total number of unambigous kmers

    FILE *fastaFile;
    fastaFile = fopen(fastaFname,"r"); 
    if (fastaFile == NULL) {
       printf("fasta2ref: Cannot open FASTA file: %s!\n", fastaFname);
       exit(1);
    }
    printf("============================\nstart reading <%s>.\n", fastaFname);
    uint32_t kmercount_temp; 
    faReader reader(fastaFile,length); //  initialize the kmer string and kmer
    while (!reader.eos) { 
        if (reader.pos % 1000000 == 0) {
            printf("%d bases read...\n", reader.pos);
        }
        if (!reader.is_ambiguous) {

            // keep track of unique kmers and remove keys of non-unique kmers
            kmerAll[reader.kmer] ++;
            kmercount_temp = kmerAll[reader.kmer];
            if (kmerAll[reader.kmer] == (unsigned)1) { 
                kmerUni[reader.kmer] = reader.pos; // position of kmer
                //kmerStr[reader.kmer] = 0;          // on forward strand
            }
            if (kmerAll[reader.kmer] == (unsigned)2) { 
                kmerUni.erase(reader.kmer); 
                //kmerStr.erase(reader.kmer); 
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
    fclose(fastaFile);
    total_length = reader.pos + length;
    total_kmers = 2*total_kmers;
    
    printf("done.\n-----------------\n");
    printf("total length:\t%lld\n",static_cast<long long>(total_length));
    printf("total kmers: \t%lld\n",static_cast<long long>(total_kmers));
    printf("- number of distinct kmers (mapsize):  \t%d\n", (int) kmerAll.size());
    printf("- distinct kmers that uniquely appear: \t%d\n", (int) kmerUni.size());
    
}

*/
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



