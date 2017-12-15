#include <iostream>
#include <sstream>
#include <cstdint>

#define GENERATOR_A_MULTIPLICATOR 16807
#define GENERATOR_A_VALUE_CRITERIUM 4
#define GENERATOR_B_MULTIPLICATOR 48271
#define GENERATOR_B_VALUE_CRITERIUM 8
#define DIVIDER 2147483647
#define BITS_TO_COMPARE 16

std::pair<uint64_t, uint64_t> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    uint64_t nInputA;
    iss >> nInputA;

    std::getline(std::cin, line);
    std::istringstream iss2(line);
    uint64_t nInputB;
    iss2 >> nInputB;
    return std::make_pair(nInputA, nInputB);
}

uint64_t GenerateNext(uint64_t nToChange, unsigned int nMultiplicator, short nCriterium) {
    nToChange *= nMultiplicator;
    nToChange %= DIVIDER;
    if(nToChange % nCriterium != 0) {
        return GenerateNext(nToChange, nMultiplicator, nCriterium);
    }
    return nToChange;
}

void GenerateNext(std::pair<uint64_t, uint64_t>& pairToChange) {
    pairToChange.first = GenerateNext(pairToChange.first, GENERATOR_A_MULTIPLICATOR, GENERATOR_A_VALUE_CRITERIUM);
    pairToChange.second = GenerateNext(pairToChange.second, GENERATOR_B_MULTIPLICATOR, GENERATOR_B_VALUE_CRITERIUM);
}

void Solve(std::pair<uint64_t, uint64_t> pairInput) {
    int nBitMask = 1;
    for(int i = 0; i < BITS_TO_COMPARE - 1; ++i) {
        nBitMask |= nBitMask << 1;
    }
    int nMatches = 0;
    for(uint64_t i = 0; i < 5000000; ++i) {
        GenerateNext(pairInput);
        if((pairInput.first & nBitMask) == (pairInput.second & nBitMask)) {
            ++nMatches;
        }
    }
    std::cout << nMatches << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());

    return 0;
}

