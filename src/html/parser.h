#pragma once

#include <memory>
#include <string>

#include "node.h"

namespace recursion {

class HTMLParser {
public:
    HTMLParser() = default;
    ~HTMLParser() = default;

    std::unique_ptr<Node> parse(const std::string& html);

private:
    std::unique_ptr<Node> parseElement(
        const std::string& html,
        size_t& position
    );

    std::unique_ptr<Node> parseText(
        const std::string& html,
        size_t& position
    );

    void skipWhitespace(
        const std::string& html,
        size_t& position
    );

    void skipComment(
        const std::string& html,
        size_t& position
    );

    std::string parseTagName(
        const std::string& html,
        size_t& position
    );

    std::string parseAttributeName(
        const std::string& html,
        size_t& position
    );

    std::string parseAttributeValue(
        const std::string& html,
        size_t& position
    );

    std::string parseTextContent(
        const std::string& html,
        size_t& position
    );

    bool startsWith(
        const std::string& html,
        size_t position,
        const std::string& value
    ) const;

    bool isVoidElement(
        const std::string& tagName
    ) const;

}