/**
 * File: LabelTable.hpp
 * 
 */

#ifndef LABELTABLE_H
#define LABELTABLE_H

#include <string>

class LabelTable {
private:
    struct Label {
        std::string label;
        int address;
        Label *next;
        Label *prev;
        Label(std::string label, int address) {
            this->label = label;
            this->address = address;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };
    Label *head;
    Label *tail;
public:
    LabelTable();
    ~LabelTable();
    void addLabel (std::string newLabel, int address);
    int getAddress (std::string labelName) const;
    void printTable() const;
};


#endif