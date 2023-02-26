#ifndef PHASE2_HPP
#define PHASE2_HPP

#include <string>
#include <map>
using namespace std;

class LabelTable;

//enum TYPE {R, I, J};

//bool isInteger(std::string line);

void removeFrontSpace(string& line);

void removeBackSpace(string& line);

void removeSubString(const string sub,string& line);

void ignoreLabel(string& line);

string getBin(string myKey, map<string, string> myMap);

//std::string removeSpace(std::string line);

//TYPE findType(std::string line);

void secondScan(std::string myFile, string outFile, LabelTable *table);

/* data */
const map<string,string> reg = {
    make_pair("$zero","00000"),
    make_pair("$at","00001"),
    make_pair("$v0","00010"),
    make_pair("$v1","00011"),
    make_pair("$a0","00100"),
    make_pair("$a1","00101"),
    make_pair("$a2","00110"), 
    make_pair("$a3","00111"),
    make_pair("$t0","01000"),
    make_pair("$t1","01001"),
    make_pair("$t2","01010"),
    make_pair("$t3","01011"),
    make_pair("$t4","01100"),
    make_pair("$t5","01101"),
    make_pair("$t6","01110"),
    make_pair("$t7","01111"),
    make_pair("$s0","10000"),
    make_pair("$s1","10001"),
    make_pair("$s2","10010"),
    make_pair("$s3","10011"),
    make_pair("$s4","10100"),
    make_pair("$s5","10101"),
    make_pair("$s6","10110"),
    make_pair("$s7","10111"),
    make_pair("$t8","11000"),
    make_pair("$t9","11001"),
    make_pair("$k0","11010"),
    make_pair("$k1","11011"),
    make_pair("$gp","11100"),
    make_pair("$sp","11101"),
    make_pair("$fp","11110"),
    make_pair("$ra","11111")
};

//rd, rs, rt
const map<string,string> type1 = {
    make_pair("add","100000"),
    make_pair("addu","100001"),
    make_pair("and","100100"),
    make_pair("nor","100111"),
    make_pair("or","100101"),
    make_pair("slt","101010"),
    make_pair("sltu","101011"),
    make_pair("srav","000111"),
    make_pair("sub","100010"),
    make_pair("subu","100011"),
    make_pair("xor","100110")
};

//rs, rt
const map<string,string> type2 = {
    make_pair("div","011010"),
    make_pair("divu","011011"),
    make_pair("mult","011000"),
    make_pair("multu","011001")
};

//rd, rs
const map<string,string> type3 = {
    make_pair("jalr","001001")
};

//rs
const map<string,string> type4 = {
    make_pair("jr","001000"),
    make_pair("mthi","010001"),
    make_pair("mtlo","010011")
};

//rd
const map<string,string> type5 = {
    make_pair("mfhi","010000"),
    make_pair("mflo","010010")
};

//rd, rt, sa
const map<string,string> type6 = {
    make_pair("sll","000000"),
    make_pair("sra","000011"),
    make_pair("srl","000010")
};

//rd, rt, rs
const map<string,string> type7 = {
    make_pair("sllv","000100"),
    make_pair("srav","000111"),
    make_pair("srlv","000110")
};

//syscall
const map<string,string> type8 = {
    make_pair("syscall","001100")
};

/* I-type */
//rt, rs, imm
const map<string,string> type9 ={
    make_pair("addi","001000"),
    make_pair("addiu","001001"),
    make_pair("andi","001100"),
    make_pair("ori","001101"),
    make_pair("slti","001010"),
    make_pair("sltiu","001011"),
    make_pair("xori","001110")
};

//rt, rs, label
const map<string,string> type10 = {
    make_pair("beq","000100"),
    make_pair("bne","000101")
};

//rs, label
const map<string,string> type11 = {
    make_pair("bgez","000001")//rt=00001
    
};

//rs, label
const map<string, string> type12 = {
    make_pair("bgts","000111"),//rt=00000
    make_pair("blez","000110"),
    make_pair("bltz","000001")
};

//rt, imm
const map<string,string> type13 = {
    make_pair("lui","001111")
};

//rt, imm, rs
const map<string,string> type14 = {
    make_pair("lb","100000"),
    make_pair("lbu","100100"),
    make_pair("lh","100001"),
    make_pair("lhu","100101"),
    make_pair("lw","100011"),
    make_pair("sb","101000"),
    make_pair("sh","101001"),
    make_pair("sw","101011"),
    make_pair("lwl","100010"),
    make_pair("lwr","100110"),
    make_pair("swl","101010"),
    make_pair("swr","101110")
};

/* J-type */
const map<string,string> type15 = {
    make_pair("j","000010"),
    make_pair("jal","000011")
};
#endif