#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>

std::vector<std::vector<int>> GetInputs() {
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
            inputs.push_back(std::move(vectLineContent));
        }
    }
    return inputs;
}

void CalculateChecksum() {
    int nResult = 0;
    int nMin = -1;
    int nMax = -1;
    std::cout << "Please paste the input.\n";
    std::vector<std::vector<int>> inputs = GetInputs();

    for(int i = 0; i < inputs.size(); ++i) {
        std::vector<int>& currentVect = inputs.at(i);
        for(int j = 0; j < currentVect.size(); j++) {
            int nInput = currentVect.at(j);
            if(nMin == -1 || nMin > nInput) {
                nMin = nInput;
            }
            if(nMax == -1 || nMax < nInput) {
                nMax = nInput;
            }
        }
        nResult += nMax - nMin;
        nMin = -1;
        nMax = -1;
    }
    printf ("%d\n", nResult);
}


int main(int argc, char *argv[])
{
    CalculateChecksum();

    return 0;
}

