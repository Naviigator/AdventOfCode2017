#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <deque>
#include <set>
#include <algorithm>

#define SEND "snd"
#define SET "set"
#define ADD "add"
#define MULTIPLY "mul"
#define MOD "mod"
#define RECIEVE "rcv"
#define JUMP_GREATER_THAN_ZERO "jgz"

class Register {
    std::map<std::string, int64_t> m_mapRegistry;

    std::deque<int64_t> m_queueSentMessages;
    int64_t m_nMessagesSent = 0;

public:
    int64_t GetValue(const std::string& c) const;
    void SetValue(const std::string& c, int64_t nValue) {m_mapRegistry[c] = nValue;}

    bool HasSameRegistry(const Register& rhs) const {return m_mapRegistry == rhs.m_mapRegistry;}

    bool HasMessage() { return m_queueSentMessages.size() > 0;}
    int64_t PopMessage();
    void SendMessage(const std::string& sPlayingRegister) { ++m_nMessagesSent; m_queueSentMessages.push_back(GetValue(sPlayingRegister));}
    std::deque<int64_t> GetMessageQueue() const {return m_queueSentMessages;}
    int64_t GetMessageSentAmount() const {return m_nMessagesSent;}
};

class Instruction {
    std::string m_sCommand;
    std::string m_sFirstArgument;
    std::string m_sSecondArgument;
    int64_t m_nNextInstructionOffset = 1;

    int64_t GetFirstArgumentValue(Register& r);
    int64_t GetSecondArgumentValue(Register& r);

public:
    Instruction(const std::string& sInput);

    void Execute(Register& r);

    bool RequiresExternalInput() {return m_sCommand == RECIEVE;}
    void ExecuteExternal(Register& r, int64_t nExternalValue);
    int64_t GetNextInstructionOffset() const {return m_nNextInstructionOffset;}
};

int64_t Register::GetValue(const std::string& sKey) const {
    if(m_mapRegistry.find(sKey) == m_mapRegistry.end()) {
        return 0;
    }
    return m_mapRegistry.at(sKey);
}

int64_t Register::PopMessage() {
    int64_t nResult = m_queueSentMessages.front();
    m_queueSentMessages.pop_front();
    return nResult;
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

int64_t Instruction::GetFirstArgumentValue(Register& r) {
    if(m_sFirstArgument.find_first_not_of("-0123456789") == -1) {
        return atoi(m_sFirstArgument.c_str());
    }
    return r.GetValue(m_sFirstArgument);
}

int64_t Instruction::GetSecondArgumentValue(Register& r) {
    if(m_sSecondArgument.find_first_not_of("-0123456789") == -1) {
        return atoi(m_sSecondArgument.c_str());
    }
    return r.GetValue(m_sSecondArgument);
}

void Instruction::Execute(Register& r) {
    if(RequiresExternalInput()) {
        throw "I shouldn't be here. Repeat after me! I SHOULDN'T BE HERE!";
    } else if(m_sCommand == SEND) {
        r.SendMessage(m_sFirstArgument);
    } else if(m_sCommand == SET) {
        r.SetValue(m_sFirstArgument, GetSecondArgumentValue(r));
    } else if(m_sCommand == ADD) {
        r.SetValue(m_sFirstArgument, r.GetValue(m_sFirstArgument) + GetSecondArgumentValue(r));
    } else if(m_sCommand == MULTIPLY) {
        r.SetValue(m_sFirstArgument, r.GetValue(m_sFirstArgument) * GetSecondArgumentValue(r));
    } else if(m_sCommand == MOD) {
        r.SetValue(m_sFirstArgument, r.GetValue(m_sFirstArgument) % GetSecondArgumentValue(r));
    } else if(m_sCommand == JUMP_GREATER_THAN_ZERO) {
        int64_t nResult = GetFirstArgumentValue(r);
        if(nResult > 0) {
            m_nNextInstructionOffset = GetSecondArgumentValue(r);
        } else {
            m_nNextInstructionOffset = 1;
        }
    }
}

void Instruction::ExecuteExternal(Register& r, int64_t nExternalValue) {
    if(!RequiresExternalInput()) {
        throw "I shouldn't be here either. Repeat after me! I SHOULDN'T BE HERE EITHER!";
    }
    if(m_sCommand == RECIEVE) {
        if(nExternalValue != 0) {
            r.SetValue(m_sFirstArgument, nExternalValue);
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
    std::map<std::vector<int64_t>, std::vector<std::vector<Register>>> mapPreviousStateDetector;
    int nRunningProgram = 0;
    std::vector<unsigned int> vectInstructionIndices = {0, 0};
    std::vector<Register> vectRegisters(2);
    vectRegisters.at(1).SetValue("p", 1);
    bool bFinished = false;

    while(!bFinished) {
        int nIdleProgram = nRunningProgram == 0 ? 1 : 0;

        if(vectInstructionIndices.at(nRunningProgram) >= vectInstructions.size()) {
            bFinished = true;//other program wants to rcv, but this one is done!
        }
        while(vectInstructionIndices.at(nRunningProgram) < vectInstructions.size()) {
            Instruction& currentInstruction = vectInstructions[vectInstructionIndices.at(nRunningProgram)];
            if(currentInstruction.RequiresExternalInput()) {
                if(!vectRegisters[nIdleProgram].HasMessage()) {
                    //check for deadlock
                    Instruction& idleInstruction = vectInstructions[vectInstructionIndices.at(nIdleProgram)];
                    if((idleInstruction.RequiresExternalInput() && !vectRegisters[nRunningProgram].HasMessage())) {
                        bFinished = true;
                    }
                    //regardless of deadlock break out of current program
                    break;
                } else {
                    currentInstruction.ExecuteExternal(vectRegisters[nRunningProgram], vectRegisters[nIdleProgram].PopMessage());
                }
            } else {
                currentInstruction.Execute(vectRegisters[nRunningProgram]);
            }
            vectInstructionIndices.at(nRunningProgram) += currentInstruction.GetNextInstructionOffset();
        }
        if(vectInstructionIndices.at(nRunningProgram) >= vectInstructions.size() && vectInstructionIndices.at(nIdleProgram) >= vectInstructions.size()) {
            bFinished = true;
        }
        nRunningProgram = nIdleProgram;
    }
    std::cout << vectRegisters.at(1).GetMessageSentAmount() << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInputs());
    return 0;
}

