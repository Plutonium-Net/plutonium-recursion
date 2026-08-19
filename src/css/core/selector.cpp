#include "selector.h"

namespace recursion::css {

Selector::Selector(
    const std::string& selector
)
    : m_value(selector) {
}

const std::string& Selector::value() const {
    return m_value;
}

}