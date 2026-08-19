#pragma once

#include <vector>

#include "rule.h"

namespace recursion::css {

class Stylesheet {
public:
    Stylesheet() = default;

    void addRule(
        const StyleRule& rule
    );

    const std::vector<StyleRule>& rules() const;

private:
    std::vector<StyleRule> m_rules;
};

}