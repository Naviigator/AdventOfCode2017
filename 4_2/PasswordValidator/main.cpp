#include <vector>
#include <iostream>
#include <sstream>


std::vector<std::vector<std::string>> GetInputs() {
    std::cout << "Please paste the input.\n";

    std::string sInput;
    std::string line;
    std::vector<std::vector<std::string>> inputs;
    bool bProcessing = true;
    while(bProcessing) {
        std::getline(std::cin, line);
        if(line.empty()) {
            bProcessing = false;
        } else {
            std::vector<std::string> vectLineContent;
            std::istringstream iss(line);
            while (iss >> sInput) {
                std::sort(sInput.begin(), sInput.end());
                vectLineContent.push_back(sInput);
            }
            std::sort(vectLineContent.begin(), vectLineContent.end(),
                      [](std::string a, std::string b) { return a > b;});
            inputs.push_back(std::move(vectLineContent));
        }
    }
    return inputs;
}

bool IsPasswordValid(std::vector<std::string> vectPassword) {
    for(int i = 0; i < vectPassword.size() -1; ++i) {
        if(vectPassword.at(i) == vectPassword.at(i + 1)) {
            return false;
        }
    }
    return true;
}

void CountValidPasswords(std::vector<std::vector<std::string>> vectPasswords) {
    int legalPasswords = std::count_if(vectPasswords.begin(), vectPasswords.end(), IsPasswordValid);

    std::cout << legalPasswords << "\n";
}

int main(int argc, char *argv[])
{
    CountValidPasswords(GetInputs());

    return 0;
}

