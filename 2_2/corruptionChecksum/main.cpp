#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>

std::vector<std::vector<int>> GetInputs() {
    std::cout << "Please paste the input.\n";

    std::string sInput;
    std::string line;
    std::vector<std::vector<int>> inputs;
    bool bProcessing = true;
    while(bProcessing) {
        std::getline(std::cin, line);
        if(line.empty()) {
            bProcessing = false;
        } else {
            std::vector<int> vectLineContent;
            std::istringstream iss(line);
            while (iss >> sInput) {
                vectLineContent.push_back(std::atoi(sInput.c_str()));
            }
            std::sort(vectLineContent.begin(), vectLineContent.end(),
                      [](int a, int b) { return a > b;});
            inputs.push_back(std::move(vectLineContent));
        }
    }
    return inputs;
}

void CalculateChecksum() {
    int nResult = 0;
    std::vector<std::vector<int>> inputs = GetInputs();

    for(int i = 0; i < inputs.size(); ++i) {
        std::vector<int>& currentVect = inputs.at(i);
        for(int j = 0; j < currentVect.size(); ++j) {
            int nInput = currentVect.at(j);
            for(int k = j + 1; k < currentVect.size(); ++k) {
                int nPotentialDiviser = currentVect.at(k);
                if(nInput % nPotentialDiviser == 0) {
                    nResult += nInput / nPotentialDiviser;
                }
            }
        }
    }
    printf ("%d\n", nResult);
}


int main(int argc, char *argv[])
{
    CalculateChecksum();

    return 0;
}

