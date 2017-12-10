#include <iostream>
#include <vector>
#include <sstream>

#define INITIAL_LIST_MAX 255

std::vector<int> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);

    std::vector<int> vectInput;
    int nInput;
    char cComma;

    while(iss >> nInput) {
        vectInput.push_back(nInput);
        iss >> cComma;
    }
    return vectInput;
}

std::vector<int> GenerateInitialList() {
    std::vector<int> vectInitialList(INITIAL_LIST_MAX + 1);
    for(int i = 0; i <= INITIAL_LIST_MAX; ++i) {
        vectInitialList.at(i) = i;
    }
    return vectInitialList;
}

void Reverse(std::vector<int>& vectInput, int nStartingIndex, int nLength) {
    if(nLength > vectInput.size()) {
        throw "it's too long!";
    }
    for(int i = 0; i < nLength / 2; ++i) {
        int nIndex1 = (nStartingIndex + i) % vectInput.size();
        int nIndex2 = (nStartingIndex + nLength - i - 1) % vectInput.size();
        std::iter_swap(vectInput.begin() + nIndex1, vectInput.begin() + nIndex2);
    }
}

void Solve(std::vector<int>& vectHash, std::vector<int> vectInput) {
    int nIndex = 0;
    int nSkipSize = 0;
    for(int nInput : vectInput) {
        Reverse(vectHash, nIndex, nInput);
        nIndex = (nIndex + nInput + nSkipSize) % vectHash.size();
        ++nSkipSize;
    }

    std::cout << (vectHash.at(0) * vectHash.at(1)) << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GenerateInitialList(), GetInput());
    return 0;
}

