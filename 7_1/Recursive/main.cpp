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

    const std::string& GetName() {
        return m_sName;
    }

    int GetWeight() {
        return m_nWeight;
    }

    const std::vector<std::string>& GetChildren() {
        return m_vectChildren;
    }
};

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

void CalculateRootProgram(std::vector<Program> programs) {
    std::set<std::string> setChildPrograms;

    for(int i = 0; i < programs.size(); ++i) {
        Program& program = programs.at(i);
        for(int j = 0; j < program.GetChildren().size(); ++j) {
            setChildPrograms.insert(program.GetChildren().at(j));
        }
    }

    for(int i = 0; i < programs.size(); ++i) {
        Program& program = programs.at(i);
        if(setChildPrograms.find(program.GetName()) == setChildPrograms.end()) {
            std::cout << program.GetName() << "\n";
        }
    }
}

int main(int argc, char *argv[])
{
    CalculateRootProgram(GetInputs());

    return 0;
}

