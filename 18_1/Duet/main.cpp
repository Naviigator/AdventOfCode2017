#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

#define SOUND "snd"
#define SET "set"
#define ADD "add"
#define MULTIPLY "mul"
#define MOD "mod"
#define RECIEVE "rcv"
#define JUMP_GREATER_THAN_ZERO "jgz"

class Register {
    std::map<std::string, uint64_t> m_mapRegistry;

    std::string m_sPlayingRegister = "";
    uint64_t m_nFirstRecievedSound = 0;

public:
    uint64_t GetValue(const std::string& c) const;
    void SetValue(const std::string& c, uint64_t nValue) {m_mapRegistry[c] = nValue;}

    uint64_t GetPlayingSound() const {return m_sPlayingRegister == "" ? 0 : GetValue(m_sPlayingRegister);}
    void SetPlayingRegister(const std::string& sPlayingRegister) {m_sPlayingRegister = sPlayingRegister;}
    void SetFirstRecievedSound(uint64_t nRecievedSound);
    uint64_t GetFirstRecievedSound() const {return m_nFirstRecievedSound;}
};

class Instruction {
    std::string m_sCommand;
    std::string m_sFirstArgument;
    std::string m_sSecondArgument;
    uint64_t m_nNextInstructionOffset = 1;

    uint64_t GetSecondArgumentValue(Register& r);

public:
    Instruction(const std::string& sInput);

    void Execute(Register& r);
    uint64_t GetNextInstructionOffset() const {return m_nNextInstructionOffset;}
};

uint64_t Register::GetValue(const std::string& sKey) const {
    if(m_mapRegistry.find(sKey) == m_mapRegistry.end()) {
        return 0;
    }
    return m_mapRegistry.at(sKey);
}

void Register::SetFirstRecievedSound(uint64_t nRecievedSound) {
    if(m_nFirstRecievedSound == 0) {
        m_nFirstRecievedSound = nRecievedSound;
    }
}

Instruction::Instruction(const std::string& sInput) {
    int nSpaceLocation = sInput.find(' ');
    m_sCommand = sInput.substr(0, nSpaceLocation);
    m_sFirstArgument = sInput.substr(nSpaceLocation + 1);
    nSpaceLocation = m_sFirstArgument.find(' ');
    if(nSpaceLocation != -1) {
        m_sSecondArgument = m_sFirstArgument.substr(nSpaceLocation + 1);
        m_sFirstArgument = m_sFirstArgument.substr(0, nSpaceLocation);
    }
}

uint64_t Instruction::GetSecondArgumentValue(Register& r) {

    if(m_sSecondArgument.find_first_not_of("-0123456789") == -1) {
        return atoi(m_sSecondArgument.c_str());
    }
    return r.GetValue(m_sSecondArgument);
}

void Instruction::Execute(Register& r) {
    if(m_sCommand == SOUND) {
        r.SetPlayingRegister(m_sFirstArgument);
    } else if(m_sCommand == SET) {
        r.SetValue(m_sFirstArgument, GetSecondArgumentValue(r));
    } else if(m_sCommand == ADD) {
        r.SetValue(m_sFirstArgument, r.GetValue(m_sFirstArgument) + GetSecondArgumentValue(r));
    } else if(m_sCommand == MULTIPLY) {
        r.SetValue(m_sFirstArgument, r.GetValue(m_sFirstArgument) * GetSecondArgumentValue(r));
    } else if(m_sCommand == MOD) {
        r.SetValue(m_sFirstArgument, r.GetValue(m_sFirstArgument) % GetSecondArgumentValue(r));
    } else if(m_sCommand == RECIEVE) {
        uint64_t nResult = r.GetPlayingSound();
        if(nResult != 0) {
            r.SetFirstRecievedSound(nResult);
            r.SetValue(m_sFirstArgument, nResult);
        }
    } else if(m_sCommand == JUMP_GREATER_THAN_ZERO) {
        uint64_t nResult = r.GetValue(m_sFirstArgument);
        if(nResult > 0) {
            m_nNextInstructionOffset = GetSecondArgumentValue(r);
        } else {
            m_nNextInstructionOffset = 1;
        }
    }
}

std::vector<Instruction> GetInputs() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);

    std::vector<Instruction> vectInput;

    while(!line.empty()) {
        vectInput.push_back(Instruction(line));
        std::getline(std::cin, line);
    }
    return vectInput;
}

void Solve(std::vector<Instruction>& vectInstructions) {
    uint64_t nCurrentInstruction = 0;
    Register reg;
    while(nCurrentInstruction >= 0 && nCurrentInstruction < vectInstructions.size()) {
        Instruction& currentInstruction = vectInstructions[nCurrentInstruction];
        currentInstruction.Execute(reg);
        nCurrentInstruction += currentInstruction.GetNextInstructionOffset();
        if(reg.GetFirstRecievedSound() != 0) {
            break;
        }
    }
    std::cout << reg.GetFirstRecievedSound() << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInputs());
    return 0;
}

