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


    mapKmer uniqueKmers; // unique kmer -> string

    double duration;
    std::clock_t start;
    // -----TEST CODE STARTS HERE-----
	file_to_unimap(mapFname, uniqueKmers, k); // load uniqueKmerMap (unordered)
    // -----TEST CODE ENDS HERE-----
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Duration: "<< duration <<" s.\n";
    

    //file_to_wellmap(wellFname, MapWell);      // load all of the wells (ordered)

    // printMapinfo(uniqueKmers); // print the kmer keys and values
    
    // test case
    // std::list<std::string> LL;
    // LL.push_back(std::string("GAAAAAAAAAAAAAAAAAA"));
    // LL.push_back(std::string("AAAAAAAAAAAAAAAATTT")); 
    // LL.push_back(std::string("AAAAAAAAAAAAATTTTTT"));
    // LL.push_back(std::string("AAAAAAAAAATTTTTTTTT"));
    // std::list<std::string>::iterator it;
    // read_str buffer;


   

    
    // To test how long: use
    //std::clock_t start;
    //double duration;
    //start = std::clock();
    // /*code here*/
    //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    //std::cout<<"Duration: "<< duration <<" s.\n";
}

