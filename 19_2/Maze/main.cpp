#include <utility>
#include <map>
#include <iostream>
#include <string>

#define UP std::pair<int, int>(0, -1)
#define DOWN std::pair<int, int>(0, 1)
#define LEFT std::pair<int, int>(-1, 0)
#define RIGHT std::pair<int, int>(1, 0)

std::pair<int, int> Move(std::pair<int, int> pairWhereToMove, std::pair<int, int> pairOriginalCoordinates) {
    return std::make_pair(pairWhereToMove.first + pairOriginalCoordinates.first, pairWhereToMove.second + pairOriginalCoordinates.second);
}

std::pair<int, int> InverseDirection(std::pair<int, int> pairToInverse) {
    return std::make_pair(pairToInverse.first * -1, pairToInverse.second * -1);
}

std::map<std::pair<int, int>, char> GetInputs() {
    std::cout << "Please paste your input.\n";
    int y = 0;

    std::string line;
    std::getline(std::cin, line);

    std::map<std::pair<int, int>, char> mapInput;

    while(!line.empty()) {
        for(int x = 0; x < line.size(); ++x) {
            mapInput[std::make_pair(x, y)] = line.at(x);
        }

        std::getline(std::cin, line);
        ++y;
    }
    return mapInput;
}

void Solve(std::map<std::pair<int, int>, char>& mapInput) {
    std::pair<int, int> coordinates(0, 0);
    bool bStartingPointFound = false;
    //find starting area
    while(!bStartingPointFound) {
        if(mapInput[coordinates] == '|') {
            bStartingPointFound = true;
        } else {
            coordinates = Move(RIGHT, coordinates);
        }
    }

    bool bEndpointReached = false;
    std::pair<int, int> direction = DOWN;
    int nStepsTaken = 1;
    while(!bEndpointReached) {
        coordinates = Move(direction, coordinates);
        if(mapInput.find(coordinates) == mapInput.end() || mapInput[coordinates] == ' ') {
            //move back
            direction = InverseDirection(direction);
            coordinates = Move(direction, coordinates);
            if(direction == UP || direction == DOWN) {
                direction = LEFT;
            } else {
                direction = DOWN;
            }
            coordinates = Move(direction, coordinates);
            if(mapInput.find(coordinates) == mapInput.end() || mapInput[coordinates] == ' ') {
                direction = InverseDirection(direction);
                coordinates = Move(direction, coordinates);//original spot
                coordinates = Move(direction, coordinates);//new spot
            }
        }

        char cFound = mapInput[coordinates];
        if(cFound == ' ') {
            bEndpointReached = true;
        } else {
            ++nStepsTaken;
        }
    }
    std::cout << nStepsTaken << '\n';
}

int main(int argc, char *argv[])
{
    Solve(GetInputs());
    return 0;
}

