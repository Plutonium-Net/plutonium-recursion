#pragma once

#include <string>
#include <unordered_map>

namespace recursion::css {

class ComputedStyle {
public:
    ComputedStyle() = default;

    void setProperty(
        const std::string& property,
        const std::string& value
    );

    bool hasProperty(
        const std::string& property
    ) const;

    const std::string& getProperty(
        const std::string& property
    ) const;

    const std::unordered_map<std::string, std::string>&
    properties() const;

private:
    std::unordered_map<std::string, std::string>
        m_properties;
};

}