#include "parser.h"

#include <algorithm>
#include <cctype>
#include <unordered_set>

namespace recursion {

std::unique_ptr<Node> HTMLParser::parse(const std::string& html) {
    auto document = std::make_unique<Node>(NodeType::Document);

    size_t position = 0;

    while (position < html.length()) {
        if (startsWith(html, position, "<!--")) {
            skipComment(html, position);
            continue;
        }

        if (html[position] == '<') {
            // Ignore DOCTYPE declarations.
            if (
                position + 2 < html.length() &&
                html[position + 1] != '/' &&
                html[position + 1] != '!' &&
                html[position + 1] != '?'
            ) {
                auto element = parseElement(html, position);

                if (element) {
                    document->appendChild(std::move(element));
                    continue;
                }
            }

            // Skip DOCTYPE and other declarations.
            if (
                startsWith(html, position, "<!DOCTYPE") ||
                startsWith(html, position, "<!doctype")
            ) {
                while (
                    position < html.length() &&
                    html[position] != '>'
                ) {
                    ++position;
                }

                if (position < html.length()) {
                    ++position;
                }

                continue;
            }

            ++position;
            continue;
        }

        auto text = parseText(html, position);

        if (text && !text->text().empty()) {
            document->appendChild(std::move(text));
        }
    }

    return document;
}

std::unique_ptr<Node> HTMLParser::parseElement(
    const std::string& html,
    size_t& position
) {
    if (
        position >= html.length() ||
        html[position] != '<'
    ) {
        return nullptr;
    }

    ++position;

    // Closing tag.
    if (
        position < html.length() &&
        html[position] == '/'
    ) {
        return nullptr;
    }

    // Comment.
    if (startsWith(html, position, "!--")) {
        --position;
        skipComment(html, position);
        return nullptr;
    }

    // Declaration.
    if (
        position < html.length() &&
        html[position] == '!'
    ) {
        while (
            position < html.length() &&
            html[position] != '>'
        ) {
            ++position;
        }

        if (position < html.length()) {
            ++position;
        }

        return nullptr;
    }

    // Processing instruction.
    if (
        position < html.length() &&
        html[position] == '?'
    ) {
        while (
            position < html.length() &&
            html[position] != '>'
        ) {
            ++position;
        }

        if (position < html.length()) {
            ++position;
        }

        return nullptr;
    }

    std::string tagName = parseTagName(
        html,
        position
    );

    if (tagName.empty()) {
        return nullptr;
    }

    auto element = std::make_unique<Node>(
        NodeType::Element
    );

    element->setTagName(tagName);

    bool selfClosing = false;

    // Parse attributes.
    while (
        position < html.length() &&
        html[position] != '>'
    ) {
        skipWhitespace(html, position);

        if (
            position >= html.length() ||
            html[position] == '>'
        ) {
            break;
        }

        // Self-closing syntax.
        if (html[position] == '/') {
            selfClosing = true;
            ++position;

            skipWhitespace(html, position);
            break;
        }

        std::string attributeName =
            parseAttributeName(
                html,
                position
            );

        if (attributeName.empty()) {
            ++position;
            continue;
        }

        skipWhitespace(html, position);

        std::string attributeValue;

        // Attribute has an explicit value.
        if (
            position < html.length() &&
            html[position] == '='
        ) {
            ++position;

            skipWhitespace(html, position);

            attributeValue =
                parseAttributeValue(
                    html,
                    position
                );
        }

        // Boolean attributes have an empty value.
        element->setAttribute(
            attributeName,
            attributeValue
        );
    }

    // Consume '>'.
    if (
        position < html.length() &&
        html[position] == '>'
    ) {
        ++position;
    }

    // Void elements cannot have children.
    if (
        selfClosing ||
        isVoidElement(tagName)
    ) {
        return element;
    }

    // Parse children.
    while (position < html.length()) {
        // Closing tag.
        if (startsWith(html, position, "</")) {
            position += 2;

            std::string closingTag =
                parseTagName(
                    html,
                    position
                );

            // Consume everything up to '>'.
            while (
                position < html.length() &&
                html[position] != '>'
            ) {
                ++position;
            }

            if (position < html.length()) {
                ++position;
            }

            // Matching closing tag.
            if (closingTag == tagName) {
                break;
            }

            continue;
        }

        // Comment.
        if (startsWith(html, position, "<!--")) {
            skipComment(html, position);
            continue;
        }

        // Child element.
        if (html[position] == '<') {
            size_t previousPosition = position;

            auto child = parseElement(
                html,
                position
            );

            if (child) {
                element->appendChild(
                    std::move(child)
                );
            }

            // Prevent infinite loops on malformed HTML.
            if (position == previousPosition) {
                ++position;
            }

            continue;
        }

        // Text node.
        auto text = parseText(
            html,
            position
        );

        if (
            text &&
            !text->text().empty()
        ) {
            element->appendChild(
                std::move(text)
            );
        }
    }

    return element;
}

std::unique_ptr<Node> HTMLParser::parseText(
    const std::string& html,
    size_t& position
) {
    size_t start = position;

    while (
        position < html.length() &&
        html[position] != '<'
    ) {
        ++position;
    }

    if (position == start) {
        return nullptr;
    }

    auto text = std::make_unique<Node>(
        NodeType::Text
    );

    text->setText(
        html.substr(
            start,
            position - start
        )
    );

    return text;
}

void HTMLParser::skipWhitespace(
    const std::string& html,
    size_t& position
) {
    while (
        position < html.length() &&
        std::isspace(
            static_cast<unsigned char>(
                html[position]
            )
        )
    ) {
        ++position;
    }
}

void HTMLParser::skipComment(
    const std::string& html,
    size_t& position
) {
    if (!startsWith(html, position, "<!--")) {
        return;
    }

    position += 4;

    while (
        position + 2 < html.length() &&
        !startsWith(html, position, "-->")
    ) {
        ++position;
    }

    if (
        position + 2 < html.length()
    ) {
        position += 3;
    } else {
        position = html.length();
    }
}

std::string HTMLParser::parseTagName(
    const std::string& html,
    size_t& position
) {
    size_t start = position;

    while (position < html.length()) {
        char character = html[position];

        if (
            std::isalnum(
                static_cast<unsigned char>(
                    character
                )
            ) ||
            character == '-' ||
            character == '_' ||
            character == ':' ||
            character == '.'
        ) {
            ++position;
        } else {
            break;
        }
    }

    std::string tagName =
        html.substr(
            start,
            position - start
        );

    std::transform(
        tagName.begin(),
        tagName.end(),
        tagName.begin(),
        [](unsigned char character) {
            return static_cast<char>(
                std::tolower(character)
            );
        }
    );

    return tagName;
}

std::string HTMLParser::parseAttributeName(
    const std::string& html,
    size_t& position
) {
    size_t start = position;

    while (position < html.length()) {
        char character = html[position];

        if (
            std::isalnum(
                static_cast<unsigned char>(
                    character
                )
            ) ||
            character == '-' ||
            character == '_' ||
            character == ':' ||
            character == '.'
        ) {
            ++position;
        } else {
            break;
        }
    }

    std::string name =
        html.substr(
            start,
            position - start
        );

    std::transform(
        name.begin(),
        name.end(),
        name.begin(),
        [](unsigned char character) {
            return static_cast<char>(
                std::tolower(character)
            );
        }
    );

    return name;
}

std::string HTMLParser::parseAttributeValue(
    const std::string& html,
    size_t& position
) {
    if (position >= html.length()) {
        return "";
    }

    // Double-quoted value.
    if (html[position] == '"') {
        ++position;

        size_t start = position;

        while (
            position < html.length() &&
            html[position] != '"'
        ) {
            ++position;
        }

        std::string value =
            html.substr(
                start,
                position - start
            );

        if (
            position < html.length() &&
            html[position] == '"'
        ) {
            ++position;
        }

        return value;
    }

    // Single-quoted value.
    if (html[position] == '\'') {
        ++position;

        size_t start = position;

        while (
            position < html.length() &&
            html[position] != '\''
        ) {
            ++position;
        }

        std::string value =
            html.substr(
                start,
                position - start
            );

        if (
            position < html.length() &&
            html[position] == '\''
        ) {
            ++position;
        }

        return value;
    }

    // Unquoted value.
    size_t start = position;

    while (position < html.length()) {
        char character = html[position];

        if (
            std::isspace(
                static_cast<unsigned char>(
                    character
                )
            ) ||
            character == '>'
        ) {
            break;
        }

        ++position;
    }

    return html.substr(
        start,
        position - start
    );
}

std::string HTMLParser::parseTextContent(
    const std::string& html,
    size_t& position
) {
    size_t start = position;

    while (
        position < html.length() &&
        html[position] != '<'
    ) {
        ++position;
    }

    return html.substr(
        start,
        position - start
    );
}

bool HTMLParser::startsWith(
    const std::string& html,
    size_t position,
    const std::string& value
) const {
    if (
        position + value.length() >
        html.length()
    ) {
        return false;
    }

    return html.compare(
        position,
        value.length(),
        value
    ) == 0;
}

bool HTMLParser::isVoidElement(
    const std::string& tagName
) const {
    static const std::unordered_set<std::string>
        voidElements = {
            "area",
            "base",
            "br",
            "col",
            "embed",
            "hr",
            "img",
            "input",
            "link",
            "meta",
            "param",
            "source",
            "track",
            "wbr"
        };

    return voidElements.contains(tagName);
}

}