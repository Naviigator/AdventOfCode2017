#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>

std::map<int, std::vector<int>> GetInput() {
    std::cout << "Please paste the input.\n";

    std::string line;
    std::getline(std::cin, line);

    std::map<int, std::vector<int>> mapInput;

    while(!line.empty()) {
        std::istringstream iss(line);

        int nId;
        iss >> nId;

        char cToIgnore;
        iss >> cToIgnore;//(<)->
        iss >> cToIgnore;//<(-)>
        iss >> cToIgnore;//<-(>)

        int nInput;
        std::vector<int> vectInput;

        while(iss >> nInput) {
            vectInput.push_back(nInput);
            iss >> cToIgnore;
        }
        mapInput[nId] = std::move(vectInput);
        std::getline(std::cin, line);
    }
    return mapInput;
}

void RecursivelyFindAllPathsTo(int nId, const std::map<int, std::vector<int>>& mapInput, std::set<int>& pathsPointingToZero) {
    pathsPointingToZero.insert(nId);
    for(int i : mapInput.at(nId)) {
        if(pathsPointingToZero.find(i) == pathsPointingToZero.end()) {
            RecursivelyFindAllPathsTo(i, mapInput, pathsPointingToZero);
        }
    }
}

void Solve(const std::map<int, std::vector<int>>& mapInput) {
    std::set<int> pathsPointingToZero;
    RecursivelyFindAllPathsTo(0, mapInput, pathsPointingToZero);
    std::cout << pathsPointingToZero.size() << "\n";
}

int main(int argc, char *argv[])
{
    Solve(GetInput());
    return 0;
}

