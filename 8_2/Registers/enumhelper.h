#pragma once
#include "comparator.h"
#include "operator.h"

class EnumHelper
{
public:
    static Comparator To_Comparator(const std::string& sComparator) {
        const std::map<std::string, Comparator> comparators {
            {">", Comparator::GREATER},
            {">=", Comparator::GREATER_OR_EQUAL},
            {"<", Comparator::SMALLER},
            {"<=", Comparator::SMALLER_OR_EQUAL},
            {"==", Comparator::EQUAL},
            {"!=", Comparator::NOT_EQUAL}
        };
        return comparators.at(sComparator);
    }

    static Operator To_Operator(const std::string& sComparator) {
        const std::map<std::string, Operator> operators {
            {"inc", Operator::ADD},
            {"dec", Operator::SUBTRACT}
        };
        return operators.at(sComparator);
    }

};
