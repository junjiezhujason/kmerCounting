#include "kmerCounter.h"


int main(int argc, char* argv[]){
    /*
    Inputs: 
        uniquePos file 
    Outputs:
        uniquePos bit array file
        regional kmer statistics (# of unikmers, bases covered by unikmers) 
    */  
    char* mapFname;                 // .fasta_uniquePos file name
    uint32_t k;                     // kmer length

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


    const uint32_t refLen = 82;// 3137161264;   // length of reference 
    std::bitset<refLen> ukmerbitset; // bit string of unique kmers
    const uint32_t binLen = 20; //10000;        // length of subreference
    uint32_t binNum = refLen/(binLen/2) + 1; // number of bins

    file_to_bitset<refLen>(mapFname, k, ukmerbitset); // load the positions of unique kmers
        


    // MUST REMOVE!!!!!!!!!
//
    //
    ////
    //

    //
    //
    //
    ukmerbitset[50] = true;
    ukmerbitset[52] = true;

    ukmerbitset[81] = true;
    ukmerbitset[80] = true;
    ukmerbitset[79] = true;

//
    //

    //

    //
    //
    //
    //
    //
    //
    //
    //

    printbitset<refLen>(ukmerbitset, refLen);

    int numAnchors [binNum]; // the number of anchors in a bin
    int bpCovered  [binNum]; // the bases covered by a uniquekmer in bin
    int count, bases, spos, countdown;  // unikmer count, bases covered, start position of a bin

    // travesrse through the biset 
    for (int i = 0; i < binNum; ++i) 
    {  
        spos = i * binLen / 2; // start position of a bin
        count = 0;
        bases = 0;
        countdown = 0; // reset the covered bases
        for (int j = 0; j < binLen; ++j)
        {   
            if (spos + j >= refLen) {
                break; // handle the last bin that is not full size
            }
            if (ukmerbitset.test(spos + j)) // if there is a unique kmer at position j in bin
            {
                count ++;
                countdown = k;
            }
            if (countdown > 0)
            {
                bases ++;
            }
            countdown --; 
        }
        numAnchors[i] = count;
        bpCovered[i]  = bases;
    }
    printf("----\n");
    printf("BinSize: %u,\t", binLen);
    printf("BinNumber: %u,\t", binNum);
    printf("TotalLen: %u,\n", refLen);

    printTwoArrays(numAnchors, bpCovered, binNum, binLen);

    // test printing the two arrays
    //arrays_to_file(binLen, binNumx);


    //int rLen; // read length
    //int intvl; // number of bases to skip
    //char* tName; // MD or BX

    /*
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
    */
}

