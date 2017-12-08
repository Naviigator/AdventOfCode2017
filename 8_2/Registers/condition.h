#pragma once
#include "comparator.h"
#include "register.h"

class Condition {
    std::string m_sVariableName;
    Comparator m_comparator;
    int m_nValueToCompareTo;
public:
    Condition(const std::string& sVariableName, const Comparator& comparator, int nValueToCompareTo)
        : m_sVariableName(sVariableName), m_comparator(comparator), m_nValueToCompareTo(nValueToCompareTo) {}

    bool IsTrue(const Register& reg) const;
};
