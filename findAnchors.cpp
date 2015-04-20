#include "findAnchors.h"

int main(int argc, char* argv[]){
    char* bamFname;
    char* mapFname;
    char* wellFname;
    int k; 
    int rLen; // = 19;
    int intvl; // = 2;
    char* tName; // MD or BX

    if ( argc == 8 ) {
            bamFname  = argv[1];
            mapFname = argv[2];
            k = atoi(argv[3]); // specify k for error control
            rLen = atoi(argv[4]); 
            intvl = atoi(argv[5]); 
            tName = argv[6]; 
            wellFname = argv[7];
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        exit(1);
    }

    std::string bname(bamFname);
    BamTools::BamReader reader;
    if (!reader.Open(bname)) {
        std::cerr << "Could not open input BAM file." << std::endl;
        exit(1);
    }


    // load the unique kmers into an unordered map 
    
    BamTools::BamAlignment al;
    readwKmer read(rLen, intvl, k);

    umapKmer uniqueKmers; // unique kmer -> string
    mapCount MapWell;     // barcode -> number of anchored reads
    
    uint32_t totalR = 0;        // total number of reads
    uint32_t anchoredR = 0;     // total number of anchored reads
    uint32_t loReads = 0;       // number of leftover reads 
    uint32_t loAnchored = 0;    // number of leftover reads anchored
    char tagTypeName;
    barcode_str tagData;

    double duration;

    // takes ~1min and ~8gb to load unique 15mers
    std::clock_t start;
	file_to_unimap(mapFname, uniqueKmers, k); // load uniqueKmerMap (unordered)
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Duration: "<< duration <<" s. - ";
    printf("kmer map loaded.\n");

    /*
    std::clock_t start2;
    file_to_wellmap(wellFname, MapWell);      // load all of the wells (ordered)
    duration = ( std::clock() - start2 ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Duration: "<< duration <<" s. - \n";
    printf("well map loaded.\n");
    // printMapinfo(uniqueKmers); // print the kmer keys and values

    // test case
    // std::list<std::string> LL;
    // LL.push_back(std::string("GAAAAAAAAAAAAAAAAAA"));
    // LL.push_back(std::string("AAAAAAAAAAAAAAAATTT")); 
    // LL.push_back(std::string("AAAAAAAAAAAAATTTTTT"));
    // LL.push_back(std::string("AAAAAAAAAATTTTTTTTT"));
    // std::list<std::string>::iterator it;
    // read_str buffer;

    
    while (reader.GetNextAlignment(al)) {           // each BAM entry is processed in this loop
        totalR ++;
        read.init(al.QueryBases);                   // extract the read from entry
         while (!read.eor) {
            read.lookupKmer(uniqueKmers);
            // read.printAll();
            read.getNextKmer();
        }
        read.determineAnchor();
        
        if (read.anchored) {
            anchoredR ++;
            //printf("Anchored Read #: %u; \t", totalR);
            //read.printAll();

        }

        if (al.GetTagType(tName, tagTypeName)) {    // ensure that tagType matches
            if (tagTypeName == 'Z') {               // verify that type is correct
                al.GetTag(tName, tagData);          // extract the tag value from entry
                if (read.anchored) {
                    MapWell[tagData] ++;            // increment count
                }   
            } 
            else {
                printf("Warning: tagType is not Z - entry ignored \n");
                loReads ++;
                if (read.anchored) { loAnchored ++; }  
            }  
        } else {
            loReads ++;
            if (read.anchored) { loAnchored ++; }   
            // printf("Without BC - Read #: %u\n", totalR);
        }
    }

    map_to_file(bamFname, MapWell, loReads, loAnchored);

    reader.Close();
    
    printf("* %u ", anchoredR);
    printf("out of %u reads are anchored.\n", totalR);

    */

    // To test how long: use
    //std::clock_t start;
    //double duration;
    //start = std::clock();
    // /*code here*/
    //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    //std::cout<<"Duration: "<< duration <<" s.\n";
}

