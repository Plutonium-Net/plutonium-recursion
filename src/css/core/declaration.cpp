#include "declaration.h"

namespace recursion::css {

Declaration::Declaration(
    const std::string& property,
    const std::string& value
)
    : m_property(property),
      m_value(value) {
}

const std::string& Declaration::property() const {
    return m_property;
}

const std::string& Declaration::value() const {
    return m_value;
}

}