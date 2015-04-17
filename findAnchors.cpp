#include "findAnchors.h"

int main(int argc, char* argv[]){
    char* fName;
    int k; 
    if ( argc == 3 ) {
            fName  = argv[1] ;
            k = atoi(argv[2]); // specify k for error control
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    umapKmer uniqueKmers;
    // load the unique kmers into an unordered map 
    // takes ~1min and ~8gb to load unique 15mers
	file_to_map(fName, uniqueKmers, k); // load uniqueKmerMap

    // Testing:
    printMapinfo(uniqueKmers); // print the kmer keys and values

    // *** make as argument
    int rLen = 19;
    int intvl = 2;

    readwKmer read(rLen, intvl, k);

    uint32_t totalR = 0;
    uint32_t anchoredR = 0; 

    // test case
    std::list<std::string> LL;
    LL.push_back(std::string("GAAAAAAAAAAAAAAAAAA"));
    LL.push_back(std::string("AAAAAAAAAAAAAAAATTT")); 
    LL.push_back(std::string("AAAAAAAAAAAAATTTTTT"));
    LL.push_back(std::string("AAAAAAAAAATTTTTTTTT"));
    std::list<std::string>::iterator it;

    std::string buffer;
    for (it = LL.begin(); it != LL.end(); ++it) {
        buffer = *it;
        read.init(buffer);
        while (!read.eor) {
            read.lookupKmer(uniqueKmers);
            read.printAll();
            read.getNextKmer();
        }
        read.determineAnchor();
        totalR ++;
        if (read.anchored) {
            anchoredR ++;
        }
    }
    printf("* %u ", anchoredR);
    printf("out of %u reads are anchored.\n", totalR);

    // To test how long: use
    //std::clock_t start;
    //double duration;
    //start = std::clock();
    // /*code here*/
    //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    //std::cout<<"Duration: "<< duration <<" s.\n";
}

