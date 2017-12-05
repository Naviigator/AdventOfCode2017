#include <iostream>

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
public:
    SpiralCalculator(int nToCalculate) : m_nToCalculate(nToCalculate) {}
    void CalculatePosition();
    void CalculateManhattanDistance();
};

void SpiralCalculator::CalculatePosition() {
    for(int i = 2; i <= m_nToCalculate; ++i) {
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
    }
}

void SpiralCalculator::CalculateManhattanDistance() {
    CalculatePosition();
    int nResult = abs(m_nCurrentX) + abs(m_nCurrentY);

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
    calc.CalculateManhattanDistance();

    return 0;
}

