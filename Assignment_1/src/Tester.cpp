#include "LabelTable.hpp"
#include "phase1.hpp"
#include "phase2.hpp"
#include <fstream>
#include <iostream>
using namespace std;

int compare_files(istream &output, istream &answer){
    char c1 = output.get();
    char c2 = answer.get();
    while(c1!=EOF && c2!=EOF){
        if(c1 != c2){
            return -1;
        }
        c1 = output.get();
        c2 = answer.get();	
    }
    return 0;
}

int main(int argc, char * argv[]){   
    if(argc < 4){
        puts("Please enter an input file, an output file, and expected output file.");
    }
    /* Get the input*/
    /* do the pass1 */
    ifstream infile;
    infile.open(argv[1]);
    LabelTable *table = new LabelTable();
    firstScan(argv[1], table);
    infile.close();

    /* Get the output*/
    /* do the pass2*/
    ofstream oufile;
    oufile.open(argv[2]);
    secondScan(argv[1], argv[2],table);
    oufile.close();

    /* Compare the output with answer*/
    ifstream output,answer;
    output.open(argv[2]);
    answer.open(argv[3]);

    if(compare_files(output,answer) == 0) {
        puts("ALL PASSED! CONGRATS :)");
    } else{
        puts("YOU DID SOMETHING WRONG :(");
    }
    output.close();
    answer.close();

    return 0;
}
