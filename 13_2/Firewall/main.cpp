#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <ctime>

#define UP -1
#define DOWN 1

class Firewall {
    int m_nCurrentPosition;
    int m_nDepth;
    int m_nDirection;
public:
    Firewall(int nSize) : m_nCurrentPosition(0), m_nDepth(nSize), m_nDirection(DOWN) {}
    Firewall() : Firewall(-1) {}
    void Tick(int nPicoSecondsToTick = 1);
    int GetCurrentPosition() const {return m_nCurrentPosition;}
    int GetDepth() const {return m_nDepth;}
};

void Firewall::Tick(int nPicoSecondsToTick/* = 1*/) {
    if(m_nDepth <= 1 || nPicoSecondsToTick == 0) {
        return;
    }
    nPicoSecondsToTick = nPicoSecondsToTick % ((m_nDepth-1) * 2);
    for(int i = 0; i < nPicoSecondsToTick; ++i) {
        if(m_nDirection == UP && m_nCurrentPosition == 0) {
            m_nDirection = DOWN;
        } else if(m_nDirection == DOWN && m_nCurrentPosition == m_nDepth - 1) {
            m_nDirection = UP;
        }
        m_nCurrentPosition += m_nDirection;
    }
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
    std::clock_t start = std::clock();
    bool bPassed = false;
    int nInputLayer = 0;
    int nPicoSecondsToWait = -1;


    int nMaxFirewallDepth = 0;
    for(const auto& firewallEntry : mapInput) {
        nMaxFirewallDepth = std::max(firewallEntry.first, nMaxFirewallDepth);
    }

    while(!bPassed) {
        std::map<int, Firewall> mapFirewall = mapInput;
        ++nPicoSecondsToWait;
        bPassed = true;

        for(auto& firewallEntry : mapFirewall) {
            firewallEntry.second.Tick(nPicoSecondsToWait);
        }

        for(int i = 0; i <= nMaxFirewallDepth && bPassed; ++i) {
            if(mapFirewall.find(i) != mapFirewall.end()) {
                if(mapFirewall.at(i).GetCurrentPosition() == nInputLayer) {
                    bPassed = false;
                }
            }
            for(auto& firewallEntry : mapFirewall) {
                firewallEntry.second.Tick();
            }
        }
    }
    double duration;
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << nPicoSecondsToWait << "\n";
    std::cout << "algorithm took " << duration << " s\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

