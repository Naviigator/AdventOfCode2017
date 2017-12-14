#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <sstream>
#include <algorithm>

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

void RecursiveMarkNeighbours(std::map<std::pair<int, int>, int>& mapMemory, std::pair<int, int> memoryLocation, int nRegion) {
    std::vector<std::pair<int, int>> vectNearbyLocations;
    vectNearbyLocations.push_back(std::pair<int, int>(memoryLocation.first -1, memoryLocation.second));
    vectNearbyLocations.push_back(std::pair<int, int>(memoryLocation.first +1, memoryLocation.second));
    vectNearbyLocations.push_back(std::pair<int, int>(memoryLocation.first, memoryLocation.second - 1));
    vectNearbyLocations.push_back(std::pair<int, int>(memoryLocation.first, memoryLocation.second + 1));
    for(std::pair<int, int> newCoordinates : vectNearbyLocations) {
        if(mapMemory.find(newCoordinates) != mapMemory.end()) {
            if(mapMemory[newCoordinates] != -1 && mapMemory[newCoordinates] != 0 && mapMemory[newCoordinates] != nRegion) {
                throw "This should not happen, WHAT HAVE YOU DONE?";
            }
            if(mapMemory[newCoordinates] == -1) {
                mapMemory[newCoordinates] = nRegion;
                RecursiveMarkNeighbours(mapMemory, newCoordinates,  nRegion);
            }
        }
    }
}

void Solve(const std::vector<std::vector<int>> vectInput) {
    std::vector<std::vector<int>> vectResult;
    for(const auto& input : vectInput) {
        vectResult.push_back(CreateKnotHash(input));
    }

    int nMaxX = 0;
    int nMaxY = 0;

    std::map<std::pair<int, int>, int> mapMemory;
    for(int i = 0; i < vectResult.size(); ++i) {
        for(int j = 0; j < vectResult[i].size(); ++j) {
            int memory = vectResult[i][j];
            for(int k = 0; k < 8; ++k) {
                int x = j * 8 + std::abs(k - 7);
                int nValue = (memory & 1 << k) ? -1 : 0;
                mapMemory[std::pair<int, int>(x, i)] = nValue;
                nMaxX = std::max(nMaxX, x);
                nMaxY = std::max(i, nMaxY);
            }
        }
    }

    int nRegion = 0;

    for(int x = 0; x <= nMaxX; ++x) {
        for(int y = 0; y <= nMaxY; ++y) {
            std::pair<int, int> memoryLocation(x, y);
            if(mapMemory[memoryLocation] == -1) {
                mapMemory[memoryLocation] = ++nRegion;
                RecursiveMarkNeighbours(mapMemory, memoryLocation, nRegion);
            }
        }
    }

    std::cout << nRegion << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

