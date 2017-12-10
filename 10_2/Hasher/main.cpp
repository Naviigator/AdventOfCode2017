#include <iostream>
#include <vector>
#include <sstream>

#define INITIAL_LIST_MAX 255
#define ROUNDS_TO_RUN 64
#define ENTRIES_PER_SPARSE_HASH 16

std::vector<int> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);

    std::vector<int> vectInput;
    char cInput;

    while(iss >> std::noskipws >> cInput) {
        vectInput.push_back(cInput);
    }
    while(vectInput.at(0) == ' ') {
        vectInput.erase(vectInput.begin());
    }
    while(vectInput.at(vectInput.size() - 1) == ' ') {
        vectInput.erase(vectInput.begin() + vectInput.size() - 1);
    }
    vectInput.push_back(17);
    vectInput.push_back(31);
    vectInput.push_back(73);
    vectInput.push_back(47);
    vectInput.push_back(23);
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

void Solve(std::vector<int>& vectHash, std::vector<int> vectInput) {
    int nIndex = 0;
    int nSkipSize = 0;
    for(int i = 0; i < ROUNDS_TO_RUN; ++i) {
        for(int nInput : vectInput) {
            Reverse(vectHash, nIndex, nInput);
            nIndex = (nIndex + nInput + nSkipSize) % vectHash.size();
            ++nSkipSize;
        }
    }
    std::vector<int> vectSparseHash = CreateSparseHash(vectHash);
    char buffer[3];
    for(int nHash : vectSparseHash) {
        memset(buffer, '\0', 3);
        sprintf(buffer, "%x", nHash);
        if(buffer[1] == '\0') {
            buffer[1] = buffer[0];
            buffer[0] = '0';
        }
        std::cout << buffer;
    }

    std::cout << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GenerateInitialList(), GetInput());
    return 0;
}

