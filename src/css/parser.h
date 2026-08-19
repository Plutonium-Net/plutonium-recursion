#pragma once

#include <string>

#include "core/stylesheet.h"

namespace recursion::css {

class CSSParser {
public:
    CSSParser() = default;
    ~CSSParser() = default;

    Stylesheet parse(const std::string& css);

private:
    void skipWhitespace(
        const std::string& css,
        size_t& position
    );

    void skipComment(
        const std::string& css,
        size_t& position
    );

    std::string parseSelector(
        const std::string& css,
        size_t& position
    );

    std::string parseProperty(
        const std::string& css,
        size_t& position
    );

    std::string parseValue(
        const std::string& css,
        size_t& position
    );

    bool startsWith(
        const std::string& css,
        size_t position,
        const std::string& value
    ) const;
};

}