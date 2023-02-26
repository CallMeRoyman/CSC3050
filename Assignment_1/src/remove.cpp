/* Removed Function */

/*
#include <string>
using namespace std;
TYPE findType(string line) {
    if (line.find(",") == string::npos) return J;
    size_t found1 = line.find(",");
    size_t found2 = line.find(",", found1+1);
    if (found2 == string::npos) return I;
    string str = line.substr(found2+1);
    removeFrontSpace(str);
    removeBackSpace(str);
    if (isInteger(str)) {
        removeFrontSpace(line);
        string funcName = line.substr(0, line.find(" "));
        if (funcName == "sll") {
            return R;
        }
        return I;
    }
    return R;
}

string removeSpace(string line) {
    string str;
    for (char c : line) {
        if (!isspace(c)) {
            str.push_back(c);
        }
    }
    return str;
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

bool isInteger(string line) {
    for (char c : line) {
        if (isdigit(c) == false) return false;
    }
    return true;
}

string RType(string line) {
    removeFrontSpace(line);
    string funcName = line.substr(0, line.find(" "));
    removeSubString(funcName, line);
    removeFrontSpace(line);
    string dest = line.substr(0, line.find(","));
    removeBackSpace(dest);
    removeSubString(dest, line);
    removeSubString(",", line);
    removeFrontSpace(line);
    string first = line.substr(0, line.find(","));
    removeBackSpace(first);
    removeSubString(first, line);
    removeSubString(",", line);
    removeFrontSpace(line);
    string second = line.substr(0, line.find(" "));
    const long long op = 0b000000;
    long long rs = 0b00000;
    long long rt = 0b00000;
    long long rd = 0b00000;
    long long shamt = 0b00000;
    long long funct = 0b000000;
    
    return toBinary(op) + toBinary(rs) + toBinary(rt) +
           toBinary(rd) + toBinary(shamt) + toBinary(funct);
}

string JType(string line, LabelTable *table) {
    removeFrontSpace(line);
    string opName = line.substr(0, line.find(" "));
    removeSubString(opName, line);
    removeFrontSpace(line);
    string labelName = line.substr(0, line.find(" "));
    long long op = 0b000000;
    long long address = table->getAddress(labelName);
    return toBinary(op) + toBinary(address) + string("00");
}

string IType(string line) {
    long long op = 0b000000;
    long long rs = 0b00000;
    long long rt = 0b00000;
    long long immediate = 0b000000000000000;

    return toBinary(op) + toBinary(rs) + toBinary(rt) + toBinary(immediate);
}

void secondScan(string myFile, LabelTable *table) {
    ifstream infile;
    ofstream outfile;
    string line;
    string bin;
    TYPE IT;
    infile.open(myFile.c_str());
    outfile.open("output.txt");
    while (getline(infile, line)) {
        ignoreComment(line);
        ignoreLabel(line);
        IT = findType(line);
        switch (IT) {
        case R:
            bin = RType(line);
            break;
        case I:
            bin = IType(line);
            break;
        case J:
            bin = JType(line, table);
            break;
        default:
            break;
        }
        outfile << line << endl;
    }
    infile.close();
    outfile.close();
}

*/