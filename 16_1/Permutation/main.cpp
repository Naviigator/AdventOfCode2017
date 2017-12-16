#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>

#define SPIN 's'
#define EXCHANGE 'x'
#define PARTNER 'p'

class DanceMove {
    char cMove;
    std::string sFrom;
    std::string sTo;
public:
    DanceMove(const std::string& sInput);
    void Perform(std::vector<char>& vectToDanceIn);
};

DanceMove::DanceMove(const std::string& sInput) : cMove(sInput.at(0)) {
    sFrom = sInput.substr(1);
    if(cMove == EXCHANGE || cMove == PARTNER) {

        sTo = sFrom.substr(sFrom.find('/') + 1);
        sFrom = sFrom.substr(0, sFrom.find('/'));
    }
}

void DanceMove::Perform(std::vector<char>& vectToDanceIn) {
    if(cMove == SPIN) {
        int nToSpin = atoi(sFrom.c_str());

        std::rotate(vectToDanceIn.begin(), vectToDanceIn.end() - nToSpin, vectToDanceIn.end());
    } else if(cMove == EXCHANGE) {
        int nFrom = atoi(sFrom.c_str());
        int nTo = atoi(sTo.c_str());
        std::swap(vectToDanceIn.at(nFrom), vectToDanceIn.at(nTo));
    } else if(cMove == PARTNER) {
        int nIndexFrom = std::find(vectToDanceIn.begin(), vectToDanceIn.end(), sFrom.at(0)) - vectToDanceIn.begin();
        int nIndexTo = std::find(vectToDanceIn.begin(), vectToDanceIn.end(), sTo.at(0)) - vectToDanceIn.begin();
        std::swap(vectToDanceIn.at(nIndexFrom), vectToDanceIn.at(nIndexTo));
    }
}

std::vector<DanceMove> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);

    std::vector<DanceMove> vectInput;

    while(!line.empty()) {
        vectInput.push_back(DanceMove(line));
        std::getline(std::cin, line);
    }
    return vectInput;
}

void Solve(std::vector<DanceMove>& vectInput) {
    std::vector<char> vectToDanceIn;
    for(char c = 'a'; c <= 'p'; ++c) {
        vectToDanceIn.push_back(c);
    }

    for(DanceMove& move : vectInput) {
        move.Perform(vectToDanceIn);
    }

    for(char c : vectToDanceIn) {
        std::cout << c;
    }
    std::cout << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

