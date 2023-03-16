#ifndef PHASE1_HPP
#define PHASE1_HPP

#include <string>
//#include "LabelTable.hpp"
#define INIT_ADDRESS 0b10000000000000000000000

class LabelTable;  //forward declarations, break cyclic dependency between code

void ignoreComment(std::string& line);

bool onlySpace(std::string line);

void firstScan(std::string myFile, LabelTable *table);

#endif