#ifndef LIB_HPP
#define LIB_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <set>
//using namespace std;

extern uint8_t prog[];
extern uint32_t reg[];
extern const uint64_t memorySize;
extern const uint64_t textSize;
extern const uint64_t startingAddress;
extern uint64_t staticData;
extern uint64_t sp;
extern uint64_t gp;
extern uint64_t pc;
extern std::set<int> checkpoints;

enum REGS {
    _zero, _at, _v0, _v1, _a0, _a1, _a2, _a3,
    _t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7,
    _s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7,
    _t8, _t9, _k0, _k1, _gp, _sp, _fp, _ra,
    _pc, _hi, _lo
};

void ignoreLabel(std::string& line);
void ignoreComment(std::string& line);
void removeFrontSpace(std::string& line);
void removeBackSpace(std::string& line);
void removeSubString(const std::string sub,std::string& line);
char getChar(char ch);
unsigned int binToNum(std::string str);
std::string toBinary(unsigned int num, int len);
std::string toHex(unsigned int num, int len);
void _add(int rs, int rt, int rd);
void _addu(int rs, int rt, int rd);
void _and(int rs, int rt, int rd);
void _div(int rs, int rt);
void _divu(int rs, int rt);
void _jalr(int rs, int rd);
void _jr(int rs);
void _mfhi(int rd);
void _mflo(int rd);
void _mthi(int rs);
void _mtlo(int rs);
void _mult(int rt, int rs);
void _multu(int rs, int rt);
void _nor(int rs, int rt, int rd);
void _or(int rs, int rt, int rd);
void _sll(int rd, int rt, int sa);
void _sllv(int rd, int rs, int rt);
void _slt(int rd, int rs, int rt);
void _sltu(int rd, int rs, int rt);
void _sra(int rd, int rt, int sa);
void _srav(int rd, int rs, int rt);
void _srl(int rd, int rt, int sa);
void _srlv(int rd, int rs, int rt);
void _sub(int rd, int rs, int rt);
void _subu(int rd, int rs, int rt);
void _xor(int rd, int rs, int rt);
void _addi(int rt, int rs, int imm);
void _addiu(int rt, int rs, int imm);
void _andi(int rt, int rs, int imm);
void _beq(int rs, int rt, int imm);
void _bgez(int rs, int imm);
void _bgtz(int rs, int imm);
void _blez(int rs, int imm);
void _bltz(int rs, int imm);
void _bne(int rs, int rt, int imm);
void _lb(int rt, int rs, int imm);
void _lbu(int rt, int rs, int imm);
void _lh(int rs, int rt, int imm);
void _lhu(int rs, int rt, int imm);
void _lui(int rt, int imm);
void _lw(int rs, int rt, int imm);
void _ori(int rs, int rt, int imm);
void _sb(int rs, int rt, int imm);
void _slti(int rs, int rt, int imm);
void _sltiu(int rs, int rt, int imm);
void _sh(int rs, int rt, int imm);
void _sw(int rs, int rt, int imm);
void _xori(int rs, int rt, int imm);
void _lwl(int rs, int rt, int imm);
void _lwr(int rs, int rt, int imm);
void _swl(int rs, int rt, int imm);
void _swr(int rs, int rt, int imm);
void _j(int target);
void _jal(int target);
void _print_int(std::ofstream& fout);
void _print_string(std::ofstream& fout);
void _read_int(std::ifstream& fin);
void _read_string(std::ifstream& fin);
void _sbrk();
int _exit(bool& toExit);
void _print_char(std::ofstream& fout);
void _read_char(std::ifstream& fin);
void _open();
void _read();
void _write();
void _close();
uint64_t _exit2(bool& toExit);
void _syscall(std::ifstream& fin, std::ofstream& fout, bool& toExit, uint64_t& returnVal);
void init_checkpoints(char* checkpoint_file);
void checkpoint_memory(int ins_count);
void checkpoint_register(int ins_count);


#endif