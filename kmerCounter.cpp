#include "kmerCounter.h"


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

    faReader reader(fastaFname,length); //  initialize the kmer string and kmer
    mapKmer MapUni, MapUniLoad; 



    // TEST
    //uint64_t stop = 300000000;
    uint64_t total_length = 0;

    while (!reader.eos) { 
        //reader.printKmers(); // print for testing
        //if (reader.pos % 10000000 == 0) {
        //    printf("%lld bases read...\n", (long long int) reader.pos);
        //}
        total_length ++;

        if (!reader.is_ambiguous) { // only consider non-ambigous kmers in the map
            if (MapUni.count(reader.kmer) == 0) { // if the kmer has not been encountered before
                MapUni[reader.kmer] = reader.pos;
            }
            else {
                MapUni[reader.kmer] = -1;
            }
            if (MapUni.count(reader.revKmer()) == 0) { // if the kmer has not been encountered before
                MapUni[reader.revKmer()] = reader.pos;
            }
            else {
                MapUni[reader.revKmer()] = -1;
            }
        }
        reader.getNextKmer();
    }
    const char MapUniName[] = "uniquePos";
    unimap_to_file(fastaFname, length, MapUni, MapUniName); // save counts map to .fahist file
    
    printf("- total length:\t%lld\n",static_cast<long long>(total_length));
    printf("- distinct kmers that uniquely appear: \t%d\n", (int) MapUni.size());

    //printMapInfo(MapUni); // print map for testing

    //const char fahistName[] = "unicorn.fa_30uniquePos";
    //file_to_unimap(fahistName, MapUniLoad, length); 
    //printMapInfo(MapUniLoad); // print map for testing

    return 0;
}