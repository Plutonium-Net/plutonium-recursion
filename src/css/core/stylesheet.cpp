#include "stylesheet.h"

namespace recursion::css {

void Stylesheet::addRule(
    const StyleRule& rule
) {
    m_rules.push_back(rule);
}

const std::vector<StyleRule>&
Stylesheet::rules() const {
    return m_rules;
}

}