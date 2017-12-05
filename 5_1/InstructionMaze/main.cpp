#include <vector>
#include <iostream>
#include <sstream>

std::vector<int> GetInputs() {
    std::cout << "Please paste the input.\n";

    std::vector<int> inputs;

    std::string line;
    std::getline(std::cin, line);

    while(!line.empty()) {
        int input;
        std::istringstream iss(line);
        while(iss >> input) {
            inputs.push_back(input);
        }
        std::getline(std::cin, line);
    }
    return inputs;
}

void StepsToExit(std::vector<int> input) {
    int nSteps = 0;
    int nCursor = 0;
    while(nCursor >= 0 && nCursor < input.size()) {
        ++nSteps;
        input.at(nCursor) = input.at(nCursor) + 1;
        nCursor += input.at(nCursor) - 1;
    }
    std::cout << nSteps << "\n";
}

int main(int argc, char *argv[])
{
    StepsToExit(GetInputs());

    return 0;
}

