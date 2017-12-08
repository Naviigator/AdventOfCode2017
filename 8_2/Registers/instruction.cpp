#include "instruction.h"

void Instruction::execute(Register& reg) const
{
    if(m_condition.IsTrue(reg)) {
        int nValue = reg.GetValue(m_sVariableName);
        if(m_operator == Operator::ADD) {
            nValue += m_nAmount;
        }
        if(m_operator == Operator::SUBTRACT) {
            nValue -= m_nAmount;
        }

        reg.SetValue(m_sVariableName, nValue);
    }
}
