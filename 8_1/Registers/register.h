#pragma once
#include <string>
#include <map>

class Register
{
private:
    std::map<std::string, int> m_mapRegistryContent;
public:
    Register() {}

    inline int GetValue(const std::string& sVariableName) const {
        auto& iterator = m_mapRegistryContent.find(sVariableName);
        return iterator == m_mapRegistryContent.end() ? 0 : iterator->second;
    }

    inline void SetValue(const std::string& sVariableName, int nValue) {
        m_mapRegistryContent[sVariableName] = nValue;
    }

    inline int GetLargestValue() const {
        int nMax = -1000000;
        for(const auto& val : m_mapRegistryContent) {
            if(val.second > nMax) {
                nMax = val.second;
            }
        }
        return nMax;
    }
};
