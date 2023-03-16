/**
 * File: LabelTable.cpp
 * Implementation of LabelTable.hpp
 */

#include "LabelTable.hpp"
#include <iostream>
using namespace std;

LabelTable::LabelTable(): head(nullptr), tail(nullptr) { }

LabelTable::~LabelTable() {
    Label* curr = head;
    while (curr != nullptr) {
        Label* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void LabelTable::addLabel (string newLabel, int address) {
    Label *temp = new Label(newLabel, address);
    if (head != nullptr) {
        head->prev = temp;
        temp->next = head;
    }
    head = temp;
    if (tail == nullptr) tail = temp;
}

void LabelTable::printTable() const {
    Label *temp = head;
    while (temp != nullptr) {
        cout << temp->label << ' ' << temp->address << endl;
        temp = temp->next;
    }
    cout << endl;
}

int LabelTable::getAddress (std::string labelName) const {
    Label *temp = head;
    while (temp != nullptr) {
        if (temp->label == labelName) return temp->address;
        temp = temp->next;
    }
    return -1;
}