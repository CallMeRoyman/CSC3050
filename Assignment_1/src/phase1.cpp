/**
 * File: phase1.cpp
 * Scan through the input file for the first time
 * Discard all of the comment
 * Remember you only need to deal with .text segment for assembling.
 * Find all of the labels in the code, and store them with their
 * corresponding address for later reference.
 */

#include <string>
#include <fstream>
#include <iostream>
//#include <cstdio>
#include "LabelTable.hpp"
#include "phase1.hpp"
#include "phase2.hpp"
using namespace std;
#define INIT_ADDRESS 0b10000000000000000000000


void ignoreComment(string& line) {
    size_t found = line.find("#");
    if (found != string::npos) line = line.substr(0, found);
}

bool onlySpace(string line) {
    for (char ch : line) {
        if (ch != ' ') return false;
    }
    return true;
}

void firstScan(string myFile, LabelTable *table) {
    ifstream infile;
    //ofstream outfile;
    string line;
    bool atDotText = false;
    string myLabel;
    unsigned long long myaddress = INIT_ADDRESS;
    //LabelTable *table = new LabelTable();
    infile.open(myFile.c_str());
    while (getline(infile, line)) {
        /* Discard comment */
        //size_t found = line.find("#");
        //if (found != string::npos) line = line.substr(0, found);
        ignoreComment(line);
        /* go to .text section */
        if (line.find(".text") != string::npos) {
            atDotText = true;
            continue;
        }
        if (atDotText) {
            size_t found = line.find(":");
            if (found != string::npos) {
                myLabel = line.substr(0, found);
                removeSubString(myLabel+":", line);
                if (!onlySpace(line)) myaddress+=4;
                table->addLabel(myLabel, myaddress/4);
            } else {
                myaddress+=4;
            }
        }
    }
    infile.close();
    table->printTable();      /* debug session */
}


/*
int main(int args, char** argv) {
    LabelTable *table = new LabelTable();
    firstScan(argv[1], table);
}
*/








/*
void removeComment(string myFile) {
    ifstream infile;
    ofstream outfile;
    string line;
    infile.open(myFile.c_str());
    outfile.open("output.txt");
    while (getline(infile, line)) {
        size_t found = line.find("#");
        if (found != string::npos) line = line.substr(0, found);
        outfile << line << endl;
    }
    infile.close();
    outfile.close();
}

void gotoDotText() {
    ifstream infile;
    ofstream outfile;
    string line;
    infile.open("myFile.txt");
    while (getline(infile, line)) {
        if (line.find(".text") != string::npos) {
            
        }
    }
}

void findLabel() {
    ifstream infile;
    string line;
    string myLabel;
    int myaddress;
    LabelTable *table = new LabelTable();
    infile.open("output.txt");
    while (getline(infile, line)) {
        size_t found = line.find(":");
        if (found != string::npos) {
            myLabel = line.substr(0, found);
            table->addLabel(myLabel, myaddress);
        }
    }
    table->printTable();
}

int main(int args, char** argv) {
    removeComment(argv[1]);
    //remove("output.txt");
    findLabel();
}
*/