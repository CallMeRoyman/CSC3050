/**
 * file: phase2.hpp
 * @author roymanclee
 * @version 2.0
 * delete using namespace std
*/

#ifndef PHASE2_HPP
#define PHASE2_HPP

#include <string>
#include <map>
//using namespace std;

class LabelTable; //forward declarations, break cyclic dependency between code

//enum TYPE {R, I, J};

//bool isInteger(std::string line);

void removeFrontSpace(std::string& line);

void removeBackSpace(std::string& line);

void removeSubString(const std::string sub, std::string& line);

void ignoreLabel(std::string& line);

std::string toBinary(int num, int len);

std::string getBin(std::string myKey, std::map<std::string, std::string> myMap);

std::string twoComp(std::string str);

//std::string removeSpace(std::string line);

//TYPE findType(std::string line);

void secondScan(std::string myFile, std::string outFile, LabelTable *table);

/* data */
const std::map<std::string, std::string> reg = {
    std::make_pair("$zero","00000"),
    std::make_pair("$at","00001"),
    std::make_pair("$v0","00010"),
    std::make_pair("$v1","00011"),
    std::make_pair("$a0","00100"),
    std::make_pair("$a1","00101"),
    std::make_pair("$a2","00110"), 
    std::make_pair("$a3","00111"),
    std::make_pair("$t0","01000"),
    std::make_pair("$t1","01001"),
    std::make_pair("$t2","01010"),
    std::make_pair("$t3","01011"),
    std::make_pair("$t4","01100"),
    std::make_pair("$t5","01101"),
    std::make_pair("$t6","01110"),
    std::make_pair("$t7","01111"),
    std::make_pair("$s0","10000"),
    std::make_pair("$s1","10001"),
    std::make_pair("$s2","10010"),
    std::make_pair("$s3","10011"),
    std::make_pair("$s4","10100"),
    std::make_pair("$s5","10101"),
    std::make_pair("$s6","10110"),
    std::make_pair("$s7","10111"),
    std::make_pair("$t8","11000"),
    std::make_pair("$t9","11001"),
    std::make_pair("$k0","11010"),
    std::make_pair("$k1","11011"),
    std::make_pair("$gp","11100"),
    std::make_pair("$sp","11101"),
    std::make_pair("$fp","11110"),
    std::make_pair("$ra","11111")
};

//rd, rs, rt
const std::map<std::string, std::string> type1 = {
    std::make_pair("add","100000"),
    std::make_pair("addu","100001"),
    std::make_pair("and","100100"),
    std::make_pair("nor","100111"),
    std::make_pair("or","100101"),
    std::make_pair("slt","101010"),
    std::make_pair("sltu","101011"),
    std::make_pair("srav","000111"),
    std::make_pair("sub","100010"),
    std::make_pair("subu","100011"),
    std::make_pair("xor","100110")
};

//rs, rt
const std::map<std::string, std::string> type2 = {
    std::make_pair("div","011010"),
    std::make_pair("divu","011011"),
    std::make_pair("mult","011000"),
    std::make_pair("multu","011001")
};

//rd, rs
const std::map<std::string, std::string> type3 = {
    std::make_pair("jalr","001001")
};

//rs
const std::map<std::string, std::string> type4 = {
    std::make_pair("jr","001000"),
    std::make_pair("mthi","010001"),
    std::make_pair("mtlo","010011")
};

//rd
const std::map<std::string, std::string> type5 = {
    std::make_pair("mfhi","010000"),
    std::make_pair("mflo","010010")
};

//rd, rt, sa
const std::map<std::string, std::string> type6 = {
    std::make_pair("sll","000000"),
    std::make_pair("sra","000011"),
    std::make_pair("srl","000010")
};

//rd, rt, rs
const std::map<std::string, std::string> type7 = {
    std::make_pair("sllv","000100"),
    std::make_pair("srav","000111"),
    std::make_pair("srlv","000110")
};

//syscall
const std::map<std::string, std::string> type8 = {
    std::make_pair("syscall","001100")
};

/* I-type */
//rt, rs, imm
const std::map<std::string, std::string> type9 ={
    std::make_pair("addi","001000"),
    std::make_pair("addiu","001001"),
    std::make_pair("andi","001100"),
    std::make_pair("ori","001101"),
    std::make_pair("slti","001010"),
    std::make_pair("sltiu","001011"),
    std::make_pair("xori","001110")
};

//rt, rs, label
const std::map<std::string, std::string> type10 = {
    std::make_pair("beq","000100"),
    std::make_pair("bne","000101")
};

//rs, label
const std::map<std::string, std::string> type11 = {
    std::make_pair("bgez","000001")//rt=00001
    
};

//rs, label
const std::map<std::string, std::string> type12 = {
    std::make_pair("bgts","000111"),//rt=00000
    std::make_pair("blez","000110"),
    std::make_pair("bltz","000001")
};

//rt, imm
const std::map<std::string, std::string> type13 = {
    std::make_pair("lui","001111")
};

//rt, imm, rs
const std::map<std::string, std::string> type14 = {
    std::make_pair("lb","100000"),
    std::make_pair("lbu","100100"),
    std::make_pair("lh","100001"),
    std::make_pair("lhu","100101"),
    std::make_pair("lw","100011"),
    std::make_pair("sb","101000"),
    std::make_pair("sh","101001"),
    std::make_pair("sw","101011"),
    std::make_pair("lwl","100010"),
    std::make_pair("lwr","100110"),
    std::make_pair("swl","101010"),
    std::make_pair("swr","101110")
};

/* J-type */
const std::map<std::string, std::string> type15 = {
    std::make_pair("j","000010"),
    std::make_pair("jal","000011")
};
#endif