/**
 * File: lib.cpp
 * A library for MIPS instruction.
 * Note that to distinguish MIPS variables from C++, we add an underscore
 * as prefix when naming MIPS variables. For example, reg[_gp] stores the
 * value in $gp register(simulation) while gp stores the value in C++.
*/

#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
//#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include "lib.hpp"

using namespace std;

void ignoreLabel(string& line) {
    size_t found = line.find(":");
    if (found != string::npos) line = line.substr(found+1);
}

void ignoreComment(string& line) {
    size_t found = line.find("#");
    if (found != string::npos) line = line.substr(0, found);
}

void removeFrontSpace(string& line) {
    while (isspace(line[0]) || line[0] == '\t') {
        line.erase(0,1);
    }
}

void removeBackSpace(string& line) {
    while (isspace(line[line.length()-1]) || line[line.length()-1] == '\t') {
        line.pop_back();
    }
}

void removeSubString(const string sub,string& line) {
    size_t found = line.find(sub);
    if(found != string::npos) line = line.substr(found+sub.length());
}

char getChar(char ch) {
    switch (ch) {
        case '\\': return '\\';
        case '\'': return '\'';
        case '\?': return '\?';
        case 't':  return '\t';
        case 'n':  return '\n';
        case 'a':  return '\a';
        case 'b':  return '\b';
        case 'f':  return '\f';
        case 'r':  return '\r';
        case 'v':  return '\v';
        default:   return ch;
    }
}

uint32_t binToNum(string str) {
    uint32_t rst = 0;
    for (char c : str) {
        rst <<= 1;
        rst |= c - '0';
    }
    return rst;
}

string toBinary(unsigned int num, int len) {
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

string toHex(unsigned int num, int len) {
    ostringstream ss;
    ss << hex << num;
    string rst = ss.str();
    while (rst.length() < len) rst = string("0") + rst;
    return rst;
}

//0x20
void _add(int rs, int rt, int rd) {
    reg[rd] = (int)reg[rs] + (int)reg[rt];
}

//0x21
void _addu(int rs, int rt, int rd) {
    reg[rd] = reg[rs] + reg[rt];
}

void _and(int rs, int rt, int rd) {
    reg[rd] = reg[rs] & reg[rt];
}

void _div(int rs, int rt){
    reg[_lo] = (int)reg[rs] / (int)reg[rt];
    reg[_hi] = (int)reg[rs] % (int)reg[rt];
}

void _divu(int rs, int rt){
    reg[_lo] = reg[rs] / reg[rt];
    reg[_hi] = reg[rs] % reg[rt]; 
}

void _jalr(int rs, int rd) {
    reg[rd] = reg[_pc];
    reg[_pc] = reg[rs];
}

void _jr(int rs) {
    reg[_pc] = reg[rs];
}

void _mfhi(int rd) {
    reg[rd] = reg[_hi];
}

void _mflo(int rd) {
    reg[rd] = reg[_lo];
}

void _mthi(int rs) {
    reg[_hi] = reg[rs];
}

void _mtlo(int rs) {
    reg[_lo] = reg[rs];
}

void _mult(int rt, int rs) {
    int64_t rst = reg[rs] * 1LL * reg[rt];
    reg[_hi] = rst >> 32;
    reg[_lo] = rst & 0xffffffff;
}

void _multu(int rs, int rt) {
    uint64_t rst = reg[rs] * 1ULL * reg[rt];
    reg[_hi] = rst >> 32;
    reg[_lo] = rst & 0xffffffff;
}

void _nor(int rs, int rt, int rd) {
    reg[rd] = ~(reg[rs] | reg[rt]);
}

void _or(int rs, int rt, int rd) {
    reg[rd] = reg[rs] | reg[rt];
}

void _sll(int rd, int rt, int sa) {
    reg[rd] = reg[rt] << sa;
}

void _sllv(int rd, int rs, int rt) {
    reg[rd] = reg[rt] << reg[rs];
}

void _slt(int rd, int rs, int rt) {
    reg[rd] = (int)reg[rs] < (int)reg[rt] ? 1 : 0;
}

void _sltu(int rd, int rs, int rt) {
    reg[rd] = (int)reg[rs] < (int)reg[rt] ? 1 : 0;
}

void _sra(int rd, int rt, int sa) {
    uint32_t signBit = 0x80000000 & reg[rt];
    reg[rd] = reg[rt] >> sa;
    if (signBit) {
        for (int i = 0; i < 32 and i < sa; i++) {
            reg[rd] |= signBit >> i;
        }
    }
}

void _srav(int rd, int rs, int rt) {
    uint32_t signBit = 0x80000000 & reg[rt];
    reg[rd] = reg[rt] >> reg[rs];
    if (signBit) {
        for (int i = 0; i < 32 and i < reg[rs]; i++) {
            reg[rd] |= signBit >> i;
        }
    }
}

void _srl(int rd, int rt, int sa) {
    reg[rd] = reg[rt] >> sa;
}

void _srlv(int rd, int rs, int rt) {
    reg[rd] = reg[rt] >> reg[rs];
}

void _sub(int rd, int rs, int rt) {
    reg[rd] = (int)reg[rs] - (int)reg[rt];
}

void _subu(int rd, int rs, int rt) {
    reg[rd] = reg[rs] - reg[rt];
}

void _xor(int rd, int rs, int rt) {
    reg[rd] = reg[rs] ^ reg[rt];
}

void _addi(int rt, int rs, int imm) {
    reg[rt] = (int)reg[rs] + (short)imm;
}

void _addiu(int rt, int rs, int imm) {
    reg[rt] = reg[rs] + (unsigned short)imm;
}

void _andi(int rt, int rs, int imm) {
    reg[rt] = reg[rs] & (imm & 0xffff);
}

void _beq(int rs, int rt, int imm) {
    if (reg[rs] == reg[rt]) {
        reg[_pc] += (short)imm * 4;
    }
}

void _bgez(int rs, int imm) {
    if ((int)reg[rs] >= 0) {
        reg[_pc] += (short)imm * 4;
    }
}

void _bgtz(int rs, int imm) {
    if ((int)reg[rs] > 0) {
        reg[_pc] += (short)imm * 4;
    }
}

void _blez(int rs, int imm) {
    if ((int)reg[rs] <= 0) {
        reg[_pc] += (short)imm * 4;
    }
}

void _bltz(int rs, int imm) {
    if ((int)reg[rs] < 0) {
        reg[_pc] += (short)imm * 4;
    }
}

void _bne(int rs, int rt, int imm) {
    if (reg[rs] != reg[rt]) {
        reg[_pc] += (short)imm * 4;
    }
}

void _lb(int rt, int rs, int imm) {
    reg[rt] = (char)prog[reg[rs] + (short)imm - startingAddress];
}

void _lbu(int rt, int rs, int imm) {
    reg[rt] = prog[reg[rs] + (short)imm - startingAddress];
}

void _lh(int rs, int rt, int imm) {
    uint8_t hi = prog[reg[rs] + (short)imm - startingAddress + 1];
    uint8_t lo = prog[reg[rs] + (short)imm - startingAddress];
    reg[rt] = lo | (hi << 8);
    if (hi & 0x80) {
        reg[rt] |= 0xffff << 16;
    }
}

void _lhu(int rs, int rt, int imm) {
    uint8_t hi = prog[reg[rs] + (short)imm - startingAddress + 1];
    uint8_t lo = prog[reg[rs] + (short)imm - startingAddress];
    reg[rt] = lo | (hi << 8);
}

void _lui(int rt, int imm) {
    reg[rt] = imm << 16;
}

void _lw(int rs, int rt, int imm) {
    uint8_t *base = prog + reg[rs] + (short)imm - startingAddress;
    reg[rt] = base[0] | (base[1] << 8) | (base[2] << 16) | (base[3] << 24);
}

void _ori(int rs, int rt, int imm) {
    reg[rt] = reg[rs] | imm;
}

void _sb(int rs, int rt, int imm) {
    prog[reg[rs] + (short)imm - startingAddress] = reg[rt] & 0xff;
}

void _slti(int rs, int rt, int imm) {
    reg[rt] = ((int)reg[rs] < (short)imm) ? 1 : 0;
}

void _sltiu(int rs, int rt, int imm) {
    reg[rt] = (reg[rs] < (unsigned short)imm) ? 1 : 0;
}

void _sh(int rs, int rt, int imm) {
    uint8_t *base = prog + reg[rs] + (short)imm - startingAddress;
    base[0] = reg[rt] & 0xff;
    base[1] = reg[rt] >> 8;
}

void _sw(int rs, int rt, int imm) {
    uint8_t *base = prog + reg[rs] + (short)imm - startingAddress;
    base[0] = reg[rt] & 0xff;
    base[1] = (reg[rt] >> 8) & 0xff;
    base[2] = (reg[rt] >> 16) & 0xff;
    base[3] = (reg[rt] >> 24) & 0xff;
}

void _xori(int rs, int rt, int imm) {
    reg[rt] = reg[rs] ^ (unsigned short)imm;
}

void _lwl(int rs, int rt, int imm) {
    int idx = reg[rs] + (short)imm - startingAddress;
    int lowerBound = idx & (~3);
    for (int i = idx, j = 24; i >= lowerBound; i--, j -= 8) {
        reg[rt] &= ~(0xff << j);
        reg[rt] |= prog[i] << j;
    }
}

void _lwr(int rs, int rt, int imm) {
    int idx = reg[rs] + (short)imm - startingAddress;
    int upperBound = (idx + 4) & (~3);
    for (int i = idx, j = 0; i < upperBound; i++, j += 8) {
        reg[rt] &= ~(0xff << j);
        reg[rt] |= prog[i] << j;
    }
}

void _swl(int rs, int rt, int imm) {
    int idx = reg[rs] + (short)imm - startingAddress;
    int lowerBound = idx & (~3);
    for (int i = idx, j = 24; i >= lowerBound; i--, j -= 8) {
        prog[i] = (reg[rt] >> j) & 0xff;
    }
}

void _swr(int rs, int rt, int imm) {
    int idx = reg[rs] + (short)imm - startingAddress;
    int upperBound = (idx + 4) & (~3);
    for (int i = idx, j = 0; i < upperBound; i++, j += 8) {
        prog[i] = (reg[rt] >> j) & 0xff;
    }
}

void _j(int target) {
    reg[_pc] &= 0xf0000000;
    reg[_pc] |= target << 2;
}

void _jal(int target) {
    reg[_ra] = reg[_pc];
    reg[_pc] &= 0xf0000000;
    reg[_pc] |= target << 2;
}

void _print_int(ofstream& fout) {
    fout << (int)reg[_a0];
    fout.flush();
}

void _print_string(ofstream& fout) {
    fout << prog + reg[_a0] - startingAddress;
    fout.flush();
}

void _read_int(ifstream& fin) {
    int rst = 0;
    fin >> rst;
    string str;
    getline(fin, str);
    reg[_v0] = rst;
}

void _read_string(ifstream& fin) {
    string str;
    getline(fin, str);
    for (int i = 0; i < reg[_a1]; i++) {
        prog[reg[_a0] - startingAddress + i] = str[i];
    }
}

void _sbrk() {
    reg[_v0] = startingAddress + staticData + textSize;
    staticData += reg[_a0];
}

int _exit(bool& toExit) {
    toExit = true;
    return 0;
}

void _print_char(ofstream& fout) {
    fout << (char)reg[_a0];
    fout.flush();
}

void _read_char(ifstream& fin) {
    reg[_v0] = fin.get();
    string str;
    getline(fin, str);
}

void _open() {
    reg[_a0] = open((const char *)prog + reg[_a0] - startingAddress, reg[_a1], reg[_a2]);
}

void _read() {
    reg[_a0] = read(reg[_a0], prog + reg[_a1] - startingAddress, reg[_a2]);
}

void _write() {
    reg[_a0] = write(reg[_a0], prog + reg[_a1] - startingAddress, reg[_a2]);
}

void _close() {
    close(reg[_a0]);
}

uint64_t _exit2(bool& toExit) {
    toExit = true;
    return reg[_a0];
}

void _syscall(ifstream& fin, ofstream& fout, bool& toExit, uint64_t& returnVal) {
    switch (reg[_v0]) {
        case 1:
            _print_int(fout);
            break;
        case 4:
            _print_string(fout);
            break;
        case 5:
            _read_int(fin);
            break;
        case 8:
            _read_string(fin);
            break;
        case 9:
            _sbrk();
            break;
        case 10:
            returnVal = _exit(toExit);
            break;
        case 11:
            _print_char(fout);
            break;
        case 12:
            _read_char(fin);
            break;
        case 13:
            _open();
            break;
        case 14:
            _read();
            break;
        case 15:
            _write();
            break;
        case 16:
            _close();
            break;
        case 17:
            returnVal = _exit2(toExit);
            break;
        default:
            break;
    }
}

void init_checkpoints(char* checkpoint_file) {
    FILE *fp = fopen(checkpoint_file, "r");
    int tmp, i = 0;
    while (fscanf(fp, "%d", &tmp) != EOF) {
        checkpoints.insert(tmp);
    }
}

void checkpoint_memory(int ins_count) {
    if (!checkpoints.count(ins_count)) return;
    string name = "memory_" + to_string(ins_count) + ".bin";
    // FILE *fp = fopen(name.c_str(), "wb");
    // fwrite((const char *)prog, 1, 0x600000, fp);
    // fclose(fp);
    ofstream outfile(name.c_str(), ios::binary);
    outfile.write((const char *)prog, 0x600000);
    outfile.close();
}

void checkpoint_register(int ins_count) {
    if (!checkpoints.count(ins_count)) return;
    string name = "register_" + to_string(ins_count) + ".bin";
    // FILE *fp = fopen(name.c_str(), "wb");
    // fwrite((const char *)reg, sizeof(char), 35 << 2, fp);
    // fclose(fp);
    ofstream outfile(name.c_str(), ios::binary);
    outfile.write((const char *)reg, (32 + 3) << 2);
    outfile.close();
}









    // fwrite((const char *)reg[1], 4, 1, fp);
    // fwrite((const char *)reg[2], 4, 1, fp);
    // fwrite((const char *)reg[3], 4, 1, fp);
    // fwrite((const char *)reg[4], 4, 1, fp);
    // fwrite((const char *)reg[5], 4, 1, fp);
    // fwrite((const char *)reg[6], 4, 1, fp);
    // fwrite((const char *)reg[7], 4, 1, fp);
    // fwrite((const char *)reg[8], 4, 1, fp);
    // fwrite((const char *)reg[9], 4, 1, fp);
    // fwrite((const char *)reg[10], 4, 1, fp);
    // fwrite((const char *)reg[11], 4, 1, fp);
    // fwrite((const char *)reg[12], 4, 1, fp);
    // fwrite((const char *)reg[13], 4, 1, fp);
    // fwrite((const char *)reg[14], 4, 1, fp);
    // fwrite((const char *)reg[15], 4, 1, fp);
    // fwrite((const char *)reg[16], 4, 1, fp);
    // fwrite((const char *)reg[17], 4, 1, fp);
    // fwrite((const char *)reg[18], 4, 1, fp);
    // fwrite((const char *)reg[19], 4, 1, fp);
    // fwrite((const char *)reg[20], 4, 1, fp);
    // fwrite((const char *)reg[21], 4, 1, fp);
    // fwrite((const char *)reg[22], 4, 1, fp);
    // fwrite((const char *)reg[23], 4, 1, fp);
    // fwrite((const char *)reg[24], 4, 1, fp);
    // fwrite((const char *)reg[25], 4, 1, fp);
    // fwrite((const char *)reg[26], 4, 1, fp);
    // fwrite((const char *)reg[27], 4, 1, fp);
    // fwrite((const char *)reg[28], 4, 1, fp);
    // fwrite((const char *)reg[29], 4, 1, fp);
    // fwrite((const char *)reg[30], 4, 1, fp);
    // fwrite((const char *)reg[31], 4, 1, fp);
    // fwrite((const char *)reg[32], 4, 1, fp);
    // fwrite((const char *)reg[33], 4, 1, fp);
    // fwrite((const char *)reg[34], 4, 1, fp);