#include "computed_style.h"

namespace recursion::css {

void ComputedStyle::setProperty(
    const std::string& property,
    const std::string& value
) {
    m_properties[property] = value;
}

bool ComputedStyle::hasProperty(
    const std::string& property
) const {
    return m_properties.find(property)
        != m_properties.end();
}

const std::string& ComputedStyle::getProperty(
    const std::string& property
) const {
    static const std::string empty;

    auto iterator =
        m_properties.find(property);

    if (iterator == m_properties.end()) {
        return empty;
    }

    return iterator->second;
}

const std::unordered_map<std::string, std::string>&
ComputedStyle::properties() const {
    return m_properties;
}

}