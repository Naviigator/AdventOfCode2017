#include "condition.h"

bool Condition::IsTrue(const Register& reg) const
{
    if(m_comparator == Comparator::GREATER) {
        return reg.GetValue(m_sVariableName) > m_nValueToCompareTo;
    }
    if(m_comparator == Comparator::GREATER_OR_EQUAL) {
        return reg.GetValue(m_sVariableName) >= m_nValueToCompareTo;
    }
    if(m_comparator == Comparator::SMALLER) {
        return reg.GetValue(m_sVariableName) < m_nValueToCompareTo;
    }
    if(m_comparator == Comparator::SMALLER_OR_EQUAL) {
        return reg.GetValue(m_sVariableName) <= m_nValueToCompareTo;
    }
    if(m_comparator == Comparator::EQUAL) {
        return reg.GetValue(m_sVariableName) == m_nValueToCompareTo;
    }
    if(m_comparator == Comparator::NOT_EQUAL) {
        return reg.GetValue(m_sVariableName) != m_nValueToCompareTo;
    }
    throw "Something went horribly wrong, oh no!";
}
