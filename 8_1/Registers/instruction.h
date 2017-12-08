#pragma once
#include "operator.h"
#include "register.h"
#include "condition.h"

class Instruction {
private:
    const std::string m_sVariableName;
    const Operator m_operator;
    int m_nAmount;
    const Condition m_condition;
public:
    Instruction(const std::string& sVariableName, const Operator& operat, int nAmount, const Condition& condition)
        : m_sVariableName(sVariableName), m_operator(operat), m_nAmount(nAmount), m_condition(condition) {}

    void execute(Register& reg) const;
};
