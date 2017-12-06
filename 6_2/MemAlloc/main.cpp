#include <vector>
#include <iostream>
#include <sstream>
#include <map>

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
    std::map<std::vector<int>, int> results;
    std::map<std::vector<int>, int> collisions;
    int nResult = 0;
    bool sameStateFound = false;
    results[inputs] = 0;
    while(!sameStateFound) {
        ++nResult;
        RedistributeLargest(inputs);
        if(results.find(inputs) == results.end()) {
            results[inputs] = nResult;
        } else {
            if(collisions.find(inputs) == collisions.end()) {
                collisions[inputs] = nResult;
            } else {
                sameStateFound = true;
            }
        }
    }

    int nFirstCollisionOccurence = collisions[inputs];
    std::cout << (nResult - nFirstCollisionOccurence) << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInputs());
    return 0;
}

