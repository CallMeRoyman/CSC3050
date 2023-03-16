#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "lib.hpp"

using namespace std;

const uint64_t memorySize = 6 * 1024 * 1024;
const uint64_t textSize = 1 * 1024 * 1024;
const uint64_t startingAddress = 0x400000;
uint8_t prog[memorySize];
uint32_t reg[32+3];
uint64_t staticData = 0;
uint64_t sp = 0xA00000;
uint64_t gp = 0x508000;
uint64_t pc = startingAddress;
uint64_t machineCodeSize = 0;
vector<string> myIns;
set<int> checkpoints;

void dataHandler(string fileName) {
    ifstream infile(fileName.c_str());
    string line;
    string dataType;
    string quantity;
    string myHex;
    vector<int> nums;
    stringstream ss;
    int num = 0;
    char ch;
    uint8_t *ptr;
    int len = 0;
    int end = 0;
    int continBS = 0;
    bool atDotData = false;
    bool atDotText = false;
    if (infile.fail()) {
        cout << "fail to open " << fileName << endl;
        infile.close();
        return;
    }
    while (getline(infile, line)) {
        ignoreLabel(line);
        ignoreComment(line);
        if (line.find(".data") != string::npos) {
            atDotData = true;
            continue;
        }
        if (line.find(".text") != string::npos) {
            atDotText = true;
            break;
        }
        if (atDotData && !atDotText) {
            dataType = line.substr(0, line.find("\""));
            /*-----------------------------*/
            if (dataType.find(".asciiz") != string::npos) {
                line = line.substr(line.find("\"")+1);
                for (int i = line.length()-1; i >= 0; --i) {
                    if (line[i] == '\"') {
                        end = i;
                        break;
                    }
                }
                line = line.substr(0, end);
                len = 0;
                continBS = 0;
                for (int i = 0; i < line.length()-1; ++i) {
                    if (line[i] =='\\' && line[i+1] == '\\') {
                        ++continBS;
                        if (continBS%2 == 1) continue;
                        else {
                            prog[textSize + staticData + len] = line[i];
                            ++len;
                            continBS = 0;
                        }
                    } else if (line[i] == '\\' && line[i+1] != '\\') {
                        ++continBS;
                        if (continBS%2 == 1) continue;
                        else {
                            prog[textSize + staticData + len] = getChar(line[i]);
                            ++len;
                            continBS = 0;
                        }
                    } else if (line[i] != '\\') {
                        if (continBS == 0) {
                            prog[textSize + staticData + len] = line[i];
                            ++len;
                        } else if (continBS != 0) {
                            prog[textSize + staticData + len] = getChar(line[i]);
                            ++len;
                            continBS = 0;
                        }
                    }
                }
                if (continBS%2 != 0) {
                    prog[textSize + staticData + len] = getChar(line[line.length()-1]);
                    continBS = 0;
                } else if (continBS%2 == 0) {
                    prog[textSize + staticData + len] = line[line.length()-1];
                    continBS = 0;
                }
                ++len;
                prog[textSize + staticData + len] = '\0';
                ++len;
                if (len % 4 == 0) staticData += len;
                else {
                    staticData+=len;
                    staticData+=(4-len%4);
                }
                //cout << staticData + textSize << endl;
                continue;
            }
            if (dataType.find(".ascii") != string::npos) {
                line = line.substr(line.find("\"")+1);
                for (int i = line.length()-1; i >= 0; --i) {
                    if (line[i] == '\"') {
                        end = i;
                        break;
                    }
                }
                line = line.substr(0, end);
                len = 0;
                continBS = 0;
                for (int i = 0; i < line.length()-1; ++i) {
                    if (line[i] =='\\' && line[i+1] == '\\') {
                        ++continBS;
                        if (continBS%2 == 1) continue;
                        else {
                            prog[textSize + staticData + len] = line[i];
                            ++len;
                            continBS = 0;
                        }
                    } else if (line[i] == '\\' && line[i+1] != '\\') {
                        ++continBS;
                        if (continBS%2 == 1) continue;
                        else {
                            prog[textSize + staticData + len] = getChar(line[i]);
                            ++len;
                            continBS = 0;
                        }
                    } else if (line[i] != '\\') {
                        if (continBS == 0) {
                            prog[textSize + staticData + len] = line[i];
                            ++len;
                        } else if (continBS != 0) {
                            prog[textSize + staticData + len] = getChar(line[i]);
                            ++len;
                            continBS = 0;
                        }
                    }
                }
                if (continBS%2 != 0) {
                    prog[textSize + staticData + len] = getChar(line[line.length()-1]);
                    continBS = 0;
                } else if (continBS%2 == 0) {
                    prog[textSize + staticData + len] = line[line.length()-1];
                    continBS = 0;
                }
                ++len;
                if (len % 4 == 0) staticData += len;
                else {
                    staticData+=len;
                    staticData+=(4-len%4);
                }
                //cout << staticData + textSize << endl;
                continue;
            }
            if (dataType.find(".word") != string::npos) {
                line = line.substr(line.find(".word")+5);
                ss.clear();
                ss.str(line);
                nums.clear();
                while (ss >> num) {
                    nums.push_back(num);
                    ss >> ch;
                }
                len = nums.size();
                for (int i = 0; i < len; ++i) {
                    ptr = prog + textSize + staticData;
                    *ptr = nums[i] & 0xff;
                    *(ptr + 1) = (nums[i] >> 8) & 0xff;
                    *(ptr + 2) = (nums[i] >> 16) & 0xff;
                    *(ptr + 3) = (nums[i] >> 24) & 0xff;
                    staticData+=4;
                }
                continue;
            }
            if (dataType.find(".byte") != string::npos) {
                line = line.substr(line.find(".byte")+5);
                ss.clear();
                ss.str(line);
                nums.clear();
                while (ss >> num) {
                    nums.push_back(num);
                    ss >> ch;
                }
                len = nums.size();
                for (int i = 0; i < len; ++i) {
                    ptr = prog + textSize + staticData;
                    *ptr = nums[i] & 0xff;
                    staticData++;
                }
                if (len % 4 != 0) staticData+=(4-len%4);
                continue;
            }
            if (dataType.find(".half") != string::npos) {
                line = line.substr(line.find(".half")+5);
                ss.clear();
                ss.str(line);
                nums.clear();
                while (ss >> num) {
                    nums.push_back(num);
                    ss >> ch;
                }
                len = nums.size();
                for (int i = 0; i < len; ++i) {
                    ptr = prog + textSize + staticData;
                    *ptr = nums[i] & 0xff;
                    *(ptr + 1) = (nums[i] >> 8) & 0xff;
                    staticData+=2;
                }
                if (len % 2 != 0) staticData+=2;
                continue;
            }
        }
    }
    infile.close();
}

void textSeg(string fileName) {
    ifstream infile;
    string line;
    infile.open(fileName);
    if (infile.fail()) {
        cout << "fail to open " << fileName << endl;
        infile.close();
        return;
    }
    while (getline(infile, line)) {
        if (line.length() < 32) continue;
        myIns.push_back(line);
        for (int i = 3; i >= 0; --i) {
            prog[machineCodeSize + 3 - i] = binToNum(line.substr(8*i, 8));
        }
        machineCodeSize+=4;
    }
    infile.close();
}

void excuteCmd(string machineCode, ifstream& infile, ofstream& outfile, bool& shouldReturn, uint64_t& returnVal) {
    string opCode;
    opCode = machineCode.substr(0, 6);
    if (opCode == "000000") {
        int rs = binToNum(machineCode.substr(6, 5));
        int rt = binToNum(machineCode.substr(11, 5));
        int rd = binToNum(machineCode.substr(16, 5));
        int sa = binToNum(machineCode.substr(21, 5));
        int func = binToNum(machineCode.substr(26, 6));
        //cout << machineCode.substr(26, 6) << endl;
        switch (func) {
            case 0b100000:
                _add(rs, rt, rd);
                break;
            case 0b100001:
                _addu(rs, rt, rd);
                break;
            case 0b100100:
                _and(rs, rt, rd);
                break;
            case 0b011010:
                _div(rs, rt);
                break;
            case 0b011011:
                _divu(rs, rt);
                break;
            case 0b001001:
                _jalr(rs, rd);
                break;
            case 0b001000:
                _jr(rs);
                break;
            case 0b010000:
                _mfhi(rd);
                break;
            case 0b010010:
                _mflo(rd);
                break;
            case 0b010001:
                _mthi(rs);
                break;
            case 0b010011:
                _mtlo(rs);
                break;
            case 0b011000:
                _mult(rt, rs);
                break;
            case 0b011001:
                _multu(rt, rs);
                break;
            case 0b100111:
                _nor(rs, rt, rd);
                break;
            case 0b100101:
                _or(rs, rt, rd);
                break;
            case 0b000000:
                _sll(rd, rt, sa);
                break;
            case 0b000100:
                _sllv(rd, rs, rt);
                break;
            case 0b101010:
                _slt(rd, rs, rt);
                break;
            case 0b101011:
                _sltu(rd, rs, rt);
                break;
            case 0b000011:
                _sra(rd, rt, sa);
                break;
            case 0b000111:
                _srav(rd, rs, rt);
                break;
            case 0b000010:
                _srl(rd, rt, sa);
                break;
            case 0b000110:
                _srlv(rd, rs, rt);
                break;
            case 0b100010:
                _sub(rd, rs, rt);
                break;
            case 0b100011:
                _subu(rd, rs, rt);
                break;
            case 0b001100:
                _syscall(infile, outfile, shouldReturn, returnVal);
                break;
            case 0b100110:
                _xor(rd, rs, rt);
                break;
            default:
                break;
        }
    } else if (opCode == "000010" || opCode == "000011") {
        int target = binToNum(machineCode.substr(6,26));
        if (opCode == "000010") {
            _j(target);
        } else {
            _jal(target);
        }
    } else {
        int rs = binToNum(machineCode.substr(6, 5));
        int rt = binToNum(machineCode.substr(11, 5));
        int imm = binToNum(machineCode.substr(16, 16));
        switch (binToNum(opCode)) {
            case 0b001000:
                _addi(rt, rs, imm);
                break;
            case 0b001001:
                _addiu(rs, rs, imm);
                break;
            case 0b001100:
                _andi(rt, rs, imm);
                break;
            case 0b000100:
                _beq(rs, rt, imm);
                break;
            case 0b000001:
                if (rt == 0b00001) {
                    _bgez(rs, imm);
                } else if (rt == 0b00000) {
                    _bltz(rs, imm);
                }
                break;
            case 0b000111:
                _bgtz(rs, imm);
                break;
            case 0b000110:
                _blez(rs, imm);
                break;
            case 0b000101:
                _bne(rs, rt, imm);
                break;
            case 0b100000:
                _lb(rt, rs, imm);
                break;
            case 0b100100:
                _lbu(rt, rs, imm);
                break;
            case 0b100001:
                _lh(rs, rt, imm);
                break;
            case 0b100101:
                _lhu(rs, rt, imm);
                break;
            case 0b001111:
                _lui(rt, imm);
                break;
            case 0b100011:
                _lw(rs, rt, imm);
                break;
            case 0b001101:
                _ori(rs, rt, imm);
                break;
            case 0b101000:
                _sb(rs, rt, imm);
                break;
            case 0b001010:
                _slti(rs, rt, imm);
                break;
            case 0b001011:
                _sltiu(rs, rt, imm);
                break;
            case 0b101001:
                _sh(rs, rt, imm);
                break;
            case 0b101011:
                _sw(rs, rt, imm);
                break;
            case 0b001110:
                _xori(rs, rt, imm);
                break;
            case 0b100010:
                _lwl(rs, rt, imm);
                break;
            case 0b100110:
                _lwr(rs, rt, imm);
                break;
            case 0b101010:
                _swl(rs, rt, imm);
                break;
            case 0b101110:
                _swr(rs, rt, imm);
                break;
            default:
                break;
        }
    }
}


int main(int args, char** argv) {
    for (int i = 0; i < 32 + 3; i++) {
        reg[i] = 0;
    }
    memset(prog, 0, sizeof(prog));
    init_checkpoints(argv[4]);
    reg[_pc] = pc;
    reg[_gp] = gp;
    reg[_sp] = sp;
    reg[_fp] = sp;
    dataHandler(argv[1]);
    textSeg(argv[2]);

    ifstream infile(argv[5]);
    ofstream outfile(argv[6]);

    uint64_t returnVal = 0;
    bool shouldReturn = false;
    int idx = 0,totalInsCnt = 0;

    while (idx >= 0 && idx < myIns.size()) {
        if (checkpoints.count(totalInsCnt) != 0) {
            checkpoint_memory(totalInsCnt);
            checkpoint_register(totalInsCnt);
        }
        if (shouldReturn) break;
        auto inst = myIns[idx];
        reg[_pc] += 4;
        excuteCmd(inst, infile, outfile, shouldReturn, returnVal);
        idx = (reg[_pc] - startingAddress) >> 2;
        totalInsCnt++;
    }
    if (checkpoints.count(totalInsCnt) != 0) {
        checkpoint_memory(totalInsCnt);
        checkpoint_register(totalInsCnt);
    }
    // for (int i = 0; i < 32 + 3; i++) {
    //     reg[i] = i;
    // }
    // checkpoint_memory(58);
    // checkpoint_register(58);
    infile.close();
    outfile.close();
    return returnVal;
}