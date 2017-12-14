#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <sstream>

#define INITIAL_LIST_MAX 255
#define ROUNDS_TO_RUN 64
#define ENTRIES_PER_SPARSE_HASH 16

std::vector<std::vector<int>> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);

    std::vector<std::vector<int>> vectResult;
    for(int i = 0; i < 128; ++i) {
        std::stringstream sStream;
        sStream << line << '-' << i;
        std::istringstream iss(sStream.str());

        char cInput;
        std::vector<int> vectInput;
        while(iss >> std::noskipws >> cInput) {
            vectInput.push_back(cInput);
        }

        vectResult.push_back(vectInput);
    }
    return vectResult;
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

std::vector<int> CreateSparseHash(const std::vector<int>& vectInput) {
    if((INITIAL_LIST_MAX + 1) % ENTRIES_PER_SPARSE_HASH != 0) {
        throw "No no no! everything is wrong! your list size should be divisible by 'entries per sparse hash'";
    }
    std::vector<int> vectResult((INITIAL_LIST_MAX + 1) / ENTRIES_PER_SPARSE_HASH);
    for(int i = 0; i < (INITIAL_LIST_MAX + 1) / ENTRIES_PER_SPARSE_HASH; ++i) {
        int nBaseIndex = i * ENTRIES_PER_SPARSE_HASH;
        int nResult = vectInput.at(nBaseIndex);
        for(int j = 1; j < ENTRIES_PER_SPARSE_HASH; ++j) {
            nResult ^=  vectInput.at(nBaseIndex + j);
        }
        vectResult.at(i) = nResult;
    }
    return vectResult;
}

std::vector<int> CreateKnotHash(std::vector<int> vectInput) {
    std::vector<int>& vectHash = GenerateInitialList();
    int nIndex = 0;
    int nSkipSize = 0;

    vectInput.push_back(17);
    vectInput.push_back(31);
    vectInput.push_back(73);
    vectInput.push_back(47);
    vectInput.push_back(23);
    for(int i = 0; i < ROUNDS_TO_RUN; ++i) {
        for(int nInput : vectInput) {
            Reverse(vectHash, nIndex, nInput);
            nIndex = (nIndex + nInput + nSkipSize) % vectHash.size();
            ++nSkipSize;
        }
    }

    return CreateSparseHash(vectHash);
}

void Solve(const std::vector<std::vector<int>> vectInput) {
    std::vector<std::vector<int>> vectResult;
    for(const auto& input : vectInput) {
        vectResult.push_back(CreateKnotHash(input));
    }
    int nUsedMemory = 0;


    for(const auto& result : vectResult) {
        for(int memory : result) {
            for(int i = 0; i < 8; ++i) {
                nUsedMemory += (memory & 1 << i) ? 1 : 0;
            }
        }
    }

    std::cout << nUsedMemory << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

