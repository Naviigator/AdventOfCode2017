#include <iostream>
#include <vector>

int GetInput() {
    int nInput;
    std::cin >> nInput;
    return nInput;
}

void Solve(int nInput = 0) {
    int nPos = 0;
    std::vector<int> vectLock;
    vectLock.push_back(0);
    for(int i = 1; i <= 2017; ++i) {
        nPos += nInput;
        nPos %= vectLock.size();
        ++nPos;
        vectLock.insert(vectLock.begin() + nPos, i);
    }
    std::cout << vectLock.at((nPos + 1) % vectLock.size()) << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

