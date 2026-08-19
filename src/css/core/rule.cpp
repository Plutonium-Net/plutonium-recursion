#include "rule.h"

namespace recursion::css {

void StyleRule::addSelector(
    const Selector& selector
) {
    m_selectors.push_back(selector);
}

void StyleRule::addDeclaration(
    const Declaration& declaration
) {
    m_declarations.push_back(declaration);
}

const std::vector<Selector>&
StyleRule::selectors() const {
    return m_selectors;
}

const std::vector<Declaration>&
StyleRule::declarations() const {
    return m_declarations;
}

}