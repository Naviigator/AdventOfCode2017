#include <iostream>
#include <map>
#include <utility>

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

class SpiralCalculator {
    int m_nToCalculate;
    int m_nDirection = RIGHT;
    int m_nCurrentX = 0;
    int m_nCurrentY = 0;
    int m_nMaxX = 0;
    int m_nMaxY = 0;
    int m_nMinX = 0;
    int m_nMinY = 0;
    std::map<std::pair<int, int>, int> spiral;
public:
    SpiralCalculator(int nToCalculate);
    void CalculateOneHigherThan();
};

SpiralCalculator::SpiralCalculator(int nToCalculate) : m_nToCalculate(nToCalculate) {
    std::pair<int, int> coordinates(0, 0);
    spiral[coordinates] = 1;
}

void SpiralCalculator::CalculateOneHigherThan() {
    int nResult = 1;
    while(nResult < m_nToCalculate) {
        switch (m_nDirection) {
            case RIGHT:
                {
                    ++m_nCurrentX;
                    if(m_nCurrentX > m_nMaxX) {
                        m_nMaxX = m_nCurrentX;
                        m_nDirection = UP;
                    }
                }
                break;
            case UP:
                {
                    ++m_nCurrentY;
                    if(m_nCurrentY > m_nMaxY) {
                        m_nMaxY = m_nCurrentY;
                        m_nDirection = LEFT;
                    }
                }
                break;
            case LEFT:
                {
                    --m_nCurrentX;
                    if(m_nCurrentX < m_nMinX) {
                        m_nMinX = m_nCurrentX;
                        m_nDirection = DOWN;
                    }
                }
                break;
            case DOWN:
                {
                    --m_nCurrentY;
                    if(m_nCurrentY < m_nMinY) {
                        m_nMinY = m_nCurrentY;
                        m_nDirection = RIGHT;
                    }
                }
                break;
            default:
                break;
        }
        nResult = 0;
        for(int i = -1; i < 2; ++i) {
            for(int j = -1; j < 2; ++j) {
                std::pair<int, int> coordinates(m_nCurrentX + i, m_nCurrentY + j);
                auto content = spiral.find(coordinates);
                if(content != spiral.end()) {
                    nResult += content->second;
                }
            }
        }
        std::pair<int, int> coordinates(m_nCurrentX, m_nCurrentY);
        spiral[coordinates] = nResult;
    }
    printf ("%d\n", nResult);
}

int GetInput() {
    std::cout << "Please paste the input number.\n";
    int result = 0;
    std::cin >> result;
    return result;
}

int main(int argc, char *argv[])
{
    SpiralCalculator calc(GetInput());
    calc.CalculateOneHigherThan();

    return 0;
}

