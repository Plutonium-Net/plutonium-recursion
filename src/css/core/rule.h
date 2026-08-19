#pragma once

#include <vector>

#include "declaration.h"
#include "selector.h"

namespace recursion::css {

class StyleRule {
public:
    StyleRule() = default;

    void addSelector(
        const Selector& selector
    );

    void addDeclaration(
        const Declaration& declaration
    );

    const std::vector<Selector>& selectors() const;

    const std::vector<Declaration>&
    declarations() const;

private:
    std::vector<Selector> m_selectors;
    std::vector<Declaration> m_declarations;
};

}