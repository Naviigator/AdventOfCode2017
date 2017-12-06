#include <vector>
#include <iostream>
#include <sstream>
#include <set>

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

void RedistributeLargest(std::vector<int>& vectInputsToRedistribute) {
    int nLargest = 0;
    int nPosition = 0;
    for(int i = 0; i < vectInputsToRedistribute.size(); ++i) {
        if(vectInputsToRedistribute.at(i) > nLargest) {
            nLargest = vectInputsToRedistribute.at(i);
            nPosition = i;
        }
    }

    vectInputsToRedistribute.at(nPosition) = 0;

    while(nLargest > 0) {
        ++nPosition;
        ++vectInputsToRedistribute.at(nPosition % vectInputsToRedistribute.size());
        --nLargest;
    }
}

void Solve(std::vector<int> inputs) {
    std::set<std::vector<int>> results;
    int nResult = 0;
    results.insert(inputs);
    while(nResult < results.size()) {
        ++nResult;
        RedistributeLargest(inputs);
        if(results.find(inputs) == results.end()) {
            results.insert(inputs);
        }
    }

    std::cout << nResult << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInputs());
    return 0;
}

