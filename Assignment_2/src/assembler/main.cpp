/**
 * File: main.cpp
 * @author roymanclee
 *
 */

#include <iostream>
#include "phase1.hpp"
#include "phase2.hpp"
#include "LabelTable.hpp"
using namespace std;

int main(int args, char** argv) {
    LabelTable* table = new LabelTable();
    firstScan(string(argv[1]), table);
    secondScan(string(argv[1]), string(argv[2]), table);
}

