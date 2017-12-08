#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

#include "enumhelper.h"
#include "condition.h"
#include "instruction.h"

std::vector<Instruction> GetInputs() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);
    std::vector<Instruction> vectInstructions;

    while(!line.empty()) {
        std::istringstream iss(line);
        std::string sVariableName;
        iss >> sVariableName;

        std::string sOperator;
        iss >> sOperator;

        int nAmount;
        iss >> nAmount;

        std::string sIf;
        iss >> sIf;

        std::string sConditionVarName;
        iss >> sConditionVarName;

        std::string sComparator;
        iss >> sComparator;

        int nCompareValue;
        iss >> nCompareValue;

        Condition condition(sConditionVarName, EnumHelper::To_Comparator(sComparator), nCompareValue);
        vectInstructions.push_back(Instruction(sVariableName, EnumHelper::To_Operator(sOperator), nAmount, condition));

        std::getline(std::cin, line);
    }
    return vectInstructions;
}

void SolveRiddle(const std::vector<Instruction>& instructions) {
    Register reg;
    std::for_each(instructions.begin(), instructions.end(), [&reg](const Instruction& instruction) {
            instruction.execute(reg);
    });
    std::cout << reg.GetLargestValue() << "\n";
}

int main(int argc, char *argv[])
{
    SolveRiddle(GetInputs());
    return 0;
}

