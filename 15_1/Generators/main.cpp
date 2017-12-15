#include <iostream>
#include <sstream>
#include <cstdint>

#define GENERATOR_A_MULTIPLICATOR 16807
#define GENERATOR_B_MULTIPLICATOR 48271
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

void GenerateNext(std::pair<uint64_t, uint64_t>& pairToChange) {
    pairToChange.first *= GENERATOR_A_MULTIPLICATOR;
    pairToChange.first %= DIVIDER;
    pairToChange.second *= GENERATOR_B_MULTIPLICATOR;
    pairToChange.second %= DIVIDER;
}

void Solve(std::pair<uint64_t, uint64_t> pairInput) {
    int nBitMask = 1;
    for(int i = 0; i < BITS_TO_COMPARE - 1; ++i) {
        nBitMask |= nBitMask << 1;
    }
    int nMatches = 0;
    for(uint64_t i = 0; i < 40000000; ++i) {
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

