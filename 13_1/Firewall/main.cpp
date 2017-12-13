#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

#define UP -1
#define DOWN 1

class Firewall {
    int m_nCurrentPosition;
    int m_nDepth;
    int m_nDirection;
public:
    Firewall(int nSize) : m_nCurrentPosition(0), m_nDepth(nSize), m_nDirection(DOWN) {}
    Firewall() : Firewall(-1) {}
    void Tick();
    int GetCurrentPosition() const {return m_nCurrentPosition;}
    int GetDepth() const {return m_nDepth;}
};

void Firewall::Tick() {
    if(m_nDepth <= 1) {
        return;
    }
    if(m_nDirection == UP && m_nCurrentPosition == 0) {
        m_nDirection = DOWN;
    } else if(m_nDirection == DOWN && m_nCurrentPosition == m_nDepth - 1) {
        m_nDirection = UP;
    }
    m_nCurrentPosition += m_nDirection;
}

std::map<int, Firewall> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);

    std::map<int, Firewall> mapInput;

    while(!line.empty()) {
        std::istringstream iss(line);

        int nId;
        iss >> nId;

        char cToIgnore;
        iss >> cToIgnore;//:

        int nSize;

        iss >> nSize;
        mapInput[nId] = Firewall(nSize);
        std::getline(std::cin, line);
    }
    return mapInput;
}

void Solve(std::map<int, Firewall> mapInput) {
    int nInputLayer = 0;

    int nMaxFirewallDepth = 0;
    for(const auto& firewallEntry : mapInput) {
        nMaxFirewallDepth = std::max(firewallEntry.first, nMaxFirewallDepth);
    }

    int nCost = 0;
    for(int i = 0; i <= nMaxFirewallDepth; ++i) {
        if(mapInput.find(i) != mapInput.end()) {
            if(mapInput.at(i).GetCurrentPosition() == nInputLayer) {
                nCost += i * mapInput.at(i).GetDepth();
            }
        }
        for(auto& firewallEntry : mapInput) {
            firewallEntry.second.Tick();
        }
    }
    std::cout << nCost << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

