#include <iostream>
#include <vector>
#include <cstdint>

int GetInput() {
    int nInput;
    std::cin >> nInput;
    return nInput;
}

void Solve(int nInput = 0) {
    uint64_t nPos = 0;
    uint64_t nIndexOfZero = 0;
    uint64_t nAfterZero = -1;

    for(uint64_t i = 1; i <= 50000000; ++i) {
        nPos += nInput;
        nPos %= i;
        ++nPos;
        if(nPos == nIndexOfZero + 1) {
            nAfterZero = i;
        }
        else if(nPos <= nIndexOfZero) {
            ++nIndexOfZero;
        }
    }
    std::cout << nAfterZero << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

