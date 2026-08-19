#pragma once

#include <string>

namespace recursion::css {

class Selector {
public:
    Selector() = default;

    explicit Selector(
        const std::string& selector
    );

    const std::string& value() const;

private:
    std::string m_value;
};

}