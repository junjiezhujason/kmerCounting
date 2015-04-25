#include "kmerCounter.h"


int main(int argc, char* argv[]){
    //char* bamFname;
    char* mapFname;
    //char* wellFname;
    int k;    // kmer length
    //int rLen; // read length
    //int intvl; // number of bases to skip
    //char* tName; // MD or BX

    if ( argc == 3 ) {
            //bamFname  = argv[1];
            mapFname = argv[1];
            k = atoi(argv[2]); // specify k for error control
            //rLen = atoi(argv[4]);
            //intvl = atoi(argv[5]); 
            //tName = argv[6]; 
            //wellFname = argv[7];
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        exit(1);
    }


    mapKmer MapUni; // unique kmer -> string

    double duration;
    std::clock_t start;
    // -----TEST CODE STARTS HERE-----
	file_to_unimap(mapFname, MapUni, k); // load uniqueKmerMap (unordered)
    // -----TEST CODE ENDS HERE-----
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Duration: "<< duration <<" s.\n";
}

