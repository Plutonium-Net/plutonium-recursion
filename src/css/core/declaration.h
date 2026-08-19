#pragma once

#include <string>

namespace recursion::css {

class Declaration {
public:
    Declaration() = default;

    Declaration(
        const std::string& property,
        const std::string& value
    );

    const std::string& property() const;
    const std::string& value() const;

private:
    std::string m_property;
    std::string m_value;
};

}