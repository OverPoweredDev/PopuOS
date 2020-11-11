#include "OperatingSystem/Utility.h"
#include "OperatingSystem/RegisterBank.h"

ifstream inFile("../input.txt");
ofstream outFile("../output.txt");

int numLine = 0;
int numData = 0;
bool dataFlag = false;
string line;

string cardData[10];
int dataNum = 0;
bool done = false;
RegisterBank registerBank{};


void halt() {
    done = true;
}

void getData(int address) {
    string line = cardData[dataNum++];
    memcpy(&registerBank.memoryRegisters[address], line.c_str(), line.size());
}

void printData(int address) {
    char line[40];
    memcpy(&line, &registerBank.memoryRegisters[address], 40);
    outFile << line << endl;
}

//load data from memory address into register
void loadRegister(int address) {
    memcpy(registerBank.R, &registerBank.memoryRegisters[address], 4);
}

//store data from register into memory address
void storeRegister(int address) {
    memcpy(&registerBank.memoryRegisters[address], registerBank.R, 4);
}

void compareRegister(int address) {
    bool equal = true;
    for(int i = 0; i < 4; i++){
        cout << registerBank.memoryRegisters[address][i] << ' ' << registerBank.R[i] <<endl;
        if(registerBank.memoryRegisters[address][i] != registerBank.R[i]){
            equal = false;
            break;
        }
    }
    registerBank.C = equal;
}

void branchIfTrue(int address) {
    if (registerBank.C) {
        registerBank.IC = address;
    }
}


void readInput(byte *instruction) {
    int address = (instruction[2] - '0') * 10 + (instruction[3] - '0');
    if (instruction[0] == 'H') { halt(); }
    else if (instruction[0] == 'G' && instruction[1] == 'D') { getData(address); }
    else if (instruction[0] == 'P' && instruction[1] == 'D') { printData(address); }
    else if (instruction[0] == 'L' && instruction[1] == 'R') { loadRegister(address); }
    else if (instruction[0] == 'S' && instruction[1] == 'R') { storeRegister(address); }
    else if (instruction[0] == 'C' && instruction[1] == 'R') { compareRegister(address); }
    else if (instruction[0] == 'B' && instruction[1] == 'T') { branchIfTrue(address); }
}


int main() {

    //read everything
    while (getline(inFile, line)) {
        if (regex_match(line, regex("(\\$AMJ)(.*)"))) {
            registerBank.init();
        } else if (regex_match(line, regex("(\\$DTA)(.*)"))) {
            dataFlag = true;
        } else if (dataFlag) {
            cardData[numData++] = line;
        } else if (regex_match(line, regex("(\\$END)(.*)"))) {
            dataFlag = false;
            break;
        } else {
            memcpy(&registerBank.memoryRegisters[numLine][0], line.c_str(), line.size());
            numLine++;
        }
    }

    while (!done) {
        memcpy(registerBank.IR, registerBank.memoryRegisters[registerBank.IC], 4);
        registerBank.IC++;
        readInput(registerBank.IR);
    }

    registerBank.showRegister();
    inFile.close();
    outFile.close();

    return 0;
}