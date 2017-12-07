#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

class Program {
private:
    std::string m_sName;
    int m_nWeight;
    std::vector<std::string> m_vectChildren;

public:
    Program(const std::string& sName, int nWeight,
                    const std::vector<std::string>& vectChildren) : m_sName(sName), m_nWeight(nWeight), m_vectChildren(vectChildren) {}

    const std::string& GetName() const { return m_sName; }

    int GetWeight() const { return m_nWeight; }

    const std::vector<std::string>& GetChildren() const { return m_vectChildren; }
};

int CalculateWrongWeight(const std::vector<Program>& programs, const Program& program);

std::vector<Program> GetInputs() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);
    std::vector<Program> vectResults;

    while(!line.empty()) {
        std::istringstream iss(line);
        std::string sName;
        iss >> sName;
        char chTmp;
        iss >> chTmp;
        int nWeight;
        iss >> nWeight;
        iss >> chTmp;
        std::string sChild;
        iss >> sChild;//the ->
        std::vector<std::string> vectChildren;
        while(iss >> sChild) {
            sChild.erase(std::remove(sChild.begin(), sChild.end(), ','), sChild.end());
            vectChildren.push_back(sChild);
        }
        std::getline(std::cin, line);
        vectResults.push_back(Program(sName, nWeight, vectChildren));
    }
    return vectResults;
}

const Program& GetProgramByName(const std::vector<Program>& programs, const std::string& sName) {
    for(int i = 0; i < programs.size(); ++i) {
        const Program& program = programs.at(i);
        if(program.GetName() == sName) {
            return program;
        }
    }
    throw "Everything is wrong!";
}

void SolveChildWeightProblem(const std::vector<Program>& programs, const Program& program) {
    std::vector<std::pair<Program, int>> programsWithWeight;
    int nWeight1 = -1;
    int nWeight1Count = 0;
    int nWeight2 = -1;
    for(const std::string& childName : program.GetChildren()) {
        const Program& child = GetProgramByName(programs, childName);
        int nChildWeight = CalculateWrongWeight(programs, child);
        if(nWeight1 == -1 || nChildWeight == nWeight1) {
            nWeight1 = nChildWeight;
            ++nWeight1Count;
        } else {
            nWeight2 = nChildWeight;
        }
        programsWithWeight.push_back(std::pair<Program, int>(child, nChildWeight));
    }
    int nCorrectWeight = nWeight1Count == 1 ? nWeight2 : nWeight1;
    for(const std::pair<Program, int> programWeightPair : programsWithWeight) {
        if(programWeightPair.second != nCorrectWeight) {
            int nDifference = nCorrectWeight - programWeightPair.second;
            std::cout << (programWeightPair.first.GetWeight() + nDifference) << "\n";
            throw "";
        }
    }
}

int CalculateWrongWeight(const std::vector<Program>& programs, const Program& program) {
    int subWeight = 0;

    int nFirstChildWeight = -1;

    for(const std::string& childName : program.GetChildren()) {
        const Program& child = GetProgramByName(programs, childName);
        int childWeight = CalculateWrongWeight(programs, child);
        if(nFirstChildWeight == -1) {
            nFirstChildWeight = childWeight;
        } else if(nFirstChildWeight != childWeight) {
            //something is wrong with this ones children!
            SolveChildWeightProblem(programs, program);
        }
        subWeight += childWeight;
    }
    return program.GetWeight() + subWeight;
}

void CalculateWrongWeight(const std::vector<Program>& programs) {
    std::set<std::string> setChildPrograms;

    for(int i = 0; i < programs.size(); ++i) {
        const Program& program = programs.at(i);
        for(int j = 0; j < program.GetChildren().size(); ++j) {
            setChildPrograms.insert(program.GetChildren().at(j));
        }
    }

    for(const Program& program : programs) {
        if(setChildPrograms.find(program.GetName()) == setChildPrograms.end()){
            try {
                CalculateWrongWeight(programs, program);
            } catch (...) {

            }
        }
    }
}

int main(int argc, char *argv[])
{
    CalculateWrongWeight(GetInputs());

    return 0;
}

