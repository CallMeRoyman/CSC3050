/**
 * @version 2.0
 * BUG FIXED
 */


/**
 * File: phase2.cpp
 * Scan through the input file line by line
 * Identify which type of instruction the line is (R, I, J)
 * According to the instruction type, assemble the line
 * For lines with the label, refer to the stored information 
 * for the label's address
 */

#include <string>
#include <fstream>
#include <iostream>
#include "LabelTable.hpp"
#include "phase1.hpp"
#include "phase2.hpp"
#include <map>
using namespace std;

/* Utility functions */

/* BUG FIXED: the program is now able to remove tab in line */
void removeFrontSpace(string& line) {
    while (isspace(line[0]) || line[0] == '\t') {
        line.erase(0,1);
    }
}

/* BUG FIXED: the program is now able to remove tab in line */
void removeBackSpace(string& line) {
    while (isspace(line[line.length()-1]) || line[line.length()-1] == '\t') {
        line.pop_back();
    }
}

void removeSubString(const string sub,string& line) {
    size_t found = line.find(sub);
    if(found != string::npos) line = line.substr(found+sub.length());
}

void ignoreLabel(string& line) {
    size_t found = line.find(":");
    if (found != string::npos) line = line.substr(found+1);
}

string toBinary(int num, int len) {
    string str;
    while(num){
        if(num & 1) str.push_back('1');
        else str.push_back('0');
        num>>=1;
    }
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
    while (str.length() < len) str = string("0") + str;
    return str;
}

string getBin(string myKey, map<string, string> myMap) {
    for (auto const& [key, val] : myMap) {
        if (key == myKey) return val;
    }
    cout << "Cannot find " << myKey << endl;
    return "-1";
}

string twoComp(string str) {
    int len = str.length();
    string rst;
    bool firstOne = false;
    for (int i = len-1; i >= 0; --i) {
        
        if(!firstOne) rst = str[i] + rst;
        else {
            if (str[i] == '0') rst = '1' + rst;
            else rst = '0' + rst;
        }
        if(str[i] == '1') firstOne = true;
    }
    return rst;
}

void secondScan(string myFile, string outFile, LabelTable* table) {
    ifstream infile;
    ofstream outfile;
    string line;
    string funcName;
    string op;          //opcode
    string rs;
    string rt;
    string rd;
    string shamt;
    string bin;         //machine code
    string imm;
    string label;
    int cnt = 0;
    infile.open(myFile.c_str());
    outfile.open(outFile.c_str());
    while (getline(infile, line)) {
        ignoreComment(line);
        ignoreLabel(line);
        removeFrontSpace(line);
        funcName = line.substr(0, line.find(" "));
        removeSubString(funcName, line);
        removeBackSpace(funcName);  /* BUG FIXED: funcName can come with tab and tab can not be
                                        removed by the above operation */
        if (type1.count(funcName) == 1) {   //rd, rs, rt
            ++cnt;
            op = "000000";
            shamt = "00000";
            removeFrontSpace(line);
            rd = line.substr(0, line.find(","));
            removeBackSpace(rd);
            removeSubString(rd, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rs = line.substr(0, line.find(","));
            removeBackSpace(rs);
            removeSubString(rs, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rt = line.substr(0, line.find(" "));
            removeBackSpace(rt);    /* BUG FIXED: rt can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + getBin(rs, reg) + getBin(rt, reg) + getBin(rd, reg) + shamt + getBin(funcName, type1);
            outfile << bin << endl;
        }
        else if (type2.count(funcName) == 1) {  //rs, rt
            op = "000000";++cnt;
            shamt = "00000";
            rd = "00000";
            removeFrontSpace(line);
            rs = line.substr(0, line.find(","));
            removeBackSpace(rs);
            removeSubString(rd, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rt = line.substr(0, line.find(" "));
            removeBackSpace(rt);    /* BUG FIXED: rt can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + getBin(rs, reg) + getBin(rt, reg) + rd + shamt + getBin(funcName, type2);
            outfile << bin << endl;
        }
        else if (type3.count(funcName) == 1) {  //rd, rs
            op = "000000";++cnt;
            shamt = "00000";
            rt = "00000";
            removeFrontSpace(line);
            rd = line.substr(0, line.find(","));
            removeBackSpace(rd);
            removeSubString(rd, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rs = line.substr(0, line.find(" "));
            removeBackSpace(rs);    /* BUG FIXED: rs can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + getBin(rs, reg) + rt + getBin(rd, reg) + shamt + getBin(funcName, type3);
            outfile << bin << endl;
        }
        else if (type4.count(funcName) == 1) {  //rs
            op = "000000";++cnt;
            shamt = "00000";
            rd = "00000";
            rt = "00000";
            removeFrontSpace(line);
            rs = line.substr(0, line.find(" "));
            removeBackSpace(rs);    /* BUG FIXED: rs can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + getBin(rs, reg) + rt + rd + shamt + getBin(funcName, type4);
            outfile << bin << endl;
        }
        else if (type5.count(funcName) == 1) {  //rd
            op = "000000";++cnt;
            shamt = "00000";
            rs = "00000";
            rt = "00000";
            removeFrontSpace(line);
            rd = line.substr(0, line.find(" "));
            removeBackSpace(rd);    /* BUG FIXED: rd can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + rs + rt + getBin(rd, reg) + shamt + getBin(funcName, type5); /* BUG FIXED: change getBin(funcName, type4)
                                                                                        to (funcName, type5)*/
            outfile << bin << endl;
        }
        else if (type6.count(funcName) == 1) { //rd, rt, sa
            op = "000000";++cnt;
            rs = "00000";
            removeFrontSpace(line);
            rd = line.substr(0, line.find(","));
            removeBackSpace(rd);
            removeSubString(rd, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rt = line.substr(0, line.find(","));
            removeBackSpace(rt);
            removeSubString(rt, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            shamt = line.substr(0, line.find(" "));
            removeBackSpace(shamt);    /* BUG FIXED: shamt can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + rs + getBin(rt, reg) + getBin(rd, reg) + toBinary(stoi(shamt), 5) + getBin(funcName, type6);
            /* BUG FIXED: change getBin(rs, reg) to rs, shamt to toBinary(stoi(shamt), 5),
                getBin(funcName, type1) to getBin(funcName, type6) */
            outfile << bin << endl;
        }
        else if (type7.count(funcName) == 1) {  //rd, rt, rs
            op = "000000";++cnt;
            shamt = "00000";
            removeFrontSpace(line);
            rd = line.substr(0, line.find(","));
            removeBackSpace(rd);
            removeSubString(rd, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rt = line.substr(0, line.find(","));
            removeBackSpace(rt);
            removeSubString(rt, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rs = line.substr(0, line.find(" "));
            removeBackSpace(rs);    /* BUG FIXED: rs can come with tab and tab can not be
                                        removed by the above operation */
            bin = op + getBin(rs, reg) + getBin(rt, reg) + getBin(rd, reg) + shamt + getBin(funcName, type7);
            /* BUG FIXED: change getBin(funcName, type1) to getBin(funcName, type7)*/
            outfile << bin << endl;
        }
        else if (type8.count(funcName) == 1) {  //syscall
            ++cnt;
            outfile << string("000000") + "00000" + "00000" + "00000" + "00000" + "001100" << endl;
            /* BUG FIXED: add endl statement */
        }
        /* I-type */
        else if (type9.count(funcName) == 1) {  //rt, rs, imm
            ++cnt;
            removeFrontSpace(line);
            rt = line.substr(0, line.find(","));
            removeBackSpace(rt);
            removeSubString(rt, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rs = line.substr(0, line.find(","));
            removeBackSpace(rs);
            removeSubString(rs, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            imm = line.substr(0, line.find(" "));
            removeBackSpace(imm);    /* BUG FIXED: imm can come with tab and tab can not be
                                        removed by the above operation */
            if (stoi(imm) < 0) {
                imm = toBinary(stoi(imm)*(-1), 16);
                imm = twoComp(imm);
            } else {
                imm = toBinary(stoi(imm), 16);
            }
            bin = getBin(funcName, type9) + getBin(rs, reg) + getBin(rt, reg) + imm;
            outfile << bin << endl;
        }
        else if (type10.count(funcName) == 1) { //rs, rt, label
            ++cnt;
            removeFrontSpace(line);
            rs = line.substr(0, line.find(","));
            removeBackSpace(rs);
            removeSubString(rs, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            rt = line.substr(0, line.find(","));
            removeBackSpace(rt);
            removeSubString(rt, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            label = line.substr(0, line.find(" "));
            removeBackSpace(label);    /* BUG FIXED: label can come with tab and tab can not be
                                        removed by the above operation */
            int toAddress = table->getAddress(label);
            int currAddress = cnt+(INIT_ADDRESS/4);
            int diff = toAddress - currAddress;
            if (diff < 0) {
                diff = diff * (-1);
                label = toBinary(diff, 16);
                label = twoComp(label);
            } else {
                label = toBinary(diff, 16);
            }
            bin = getBin(funcName, type10) + getBin(rs, reg) + getBin(rt, reg) + label;
            outfile << bin << endl;
        }
        else if (type11.count(funcName) == 1) { //rs, label
            ++cnt;
            rt = "00001";
            removeFrontSpace(line);
            rs = line.substr(0, line.find(","));
            removeBackSpace(rs);
            removeSubString(rs, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            label = line.substr(0, line.find(" "));
            removeBackSpace(label);    /* BUG FIXED: label can come with tab and tab can not be
                                        removed by the above operation */
            int toAddress = table->getAddress(label);
            int currAddress = cnt + (INIT_ADDRESS/4);
            int diff = toAddress - currAddress;
            if (diff < 0) {
                diff = diff * (-1);
                label = toBinary(diff, 16);
                label = twoComp(label);
            } else {
                label = toBinary(diff, 16);
            }
            bin = getBin(funcName, type11) + getBin(rs, reg) + getBin(rt, reg) + label;
            outfile << bin << endl;
        }
        else if (type12.count(funcName) == 1) { //rs, label
            ++cnt;
            rt = "00000";
            removeFrontSpace(line);
            rs = line.substr(0, line.find(","));
            removeBackSpace(rs);
            removeSubString(rs, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            label = line.substr(0, line.find(" "));
            removeBackSpace(label);    /* BUG FIXED: label can come with tab and tab can not be
                                        removed by the above operation */
            int toAddress = table->getAddress(label);
            int currAddress = cnt+(INIT_ADDRESS/4);
            int diff = toAddress - currAddress;
            //cout << toAddress << ' ' << currAddress << endl;
            //cout << diff << endl;
            if (diff < 0) {
                diff = diff * (-1);
                label = toBinary(diff, 16);
                label = twoComp(label);
            } else {
                label = toBinary(diff, 16);
            }
            bin = getBin(funcName, type12) + getBin(rs, reg) + rt + label;
            outfile << bin << endl;
        }
        else if (type13.count(funcName) == 1) { //rt, imm
            ++cnt;
            rs = "00000";
            removeFrontSpace(line);
            rt = line.substr(0, line.find(","));
            removeBackSpace(rt);
            removeSubString(rt, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            imm = line.substr(0, line.find(" "));
            removeBackSpace(imm);    /* BUG FIXED: imm can come with tab and tab can not be
                                        removed by the above operation */
            if (stoi(imm) < 0) {
                imm = toBinary(stoi(imm)*(-1), 16);
                imm = twoComp(imm);
            } else {
                imm = toBinary(stoi(imm), 16);
            }
            bin = getBin(funcName, type13) + rs + getBin(rt, reg) + imm; /* BUG FIXED: change getBin(rs, reg) to rs */
            outfile << bin << endl;
        }
        else if (type14.count(funcName) == 1) { //rt, imm, rs
            ++cnt;
            removeFrontSpace(line);
            rt = line.substr(0, line.find(","));
            removeBackSpace(rt);
            removeSubString(rt, line);
            removeSubString(",", line);
            removeFrontSpace(line);
            imm = line.substr(0, line.find("("));
            removeBackSpace(imm);
            removeSubString(imm, line);
            removeSubString("(", line);
            removeFrontSpace(line);
            rs = line.substr(0, line.find(")"));
            removeBackSpace(rs);
            if (stoi(imm) < 0) {
                imm = toBinary(stoi(imm)*(-1), 16);
                imm = twoComp(imm);
            } else {
                imm = toBinary(stoi(imm), 16);
            }
            bin = getBin(funcName, type14) + getBin(rs, reg) + getBin(rt, reg) + imm;
            outfile << bin << endl;
        }
        /* J-type */
        else if (type15.count(funcName) == 1) {
            ++cnt;
            removeFrontSpace(line);
            label = line.substr(0, line.find(" "));
            removeBackSpace(label);    /* BUG FIXED: label can come with tab and tab can not be
                                        removed by the above operation */
            bin = getBin(funcName, type15) + "00" + toBinary(table->getAddress(label), 24);
            outfile << bin << endl;
        }
    }
    infile.close();
    outfile.close();
}