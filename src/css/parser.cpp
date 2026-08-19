#include "parser.h"

#include <algorithm>
#include <cctype>

namespace recursion::css {

Stylesheet CSSParser::parse(const std::string& css) {
    Stylesheet stylesheet;

    size_t position = 0;

    while (position < css.length()) {
        skipWhitespace(css, position);

        if (position >= css.length()) {
            break;
        }

        // CSS comment.
        if (startsWith(css, position, "/*")) {
            skipComment(css, position);
            continue;
        }

        // Find the beginning of the declaration block.
        std::string selectorText =
            parseSelector(css, position);

        if (selectorText.empty()) {
            if (position < css.length()) {
                ++position;
            }

            continue;
        }

        StyleRule rule;

        // A selector list can contain multiple selectors:
        //
        // h1, h2, .title {
        //
        size_t selectorStart = 0;

        while (selectorStart < selectorText.length()) {
            size_t comma =
                selectorText.find(',', selectorStart);

            std::string selector;

            if (comma == std::string::npos) {
                selector =
                    selectorText.substr(selectorStart);
                selectorStart =
                    selectorText.length();
            } else {
                selector =
                    selectorText.substr(
                        selectorStart,
                        comma - selectorStart
                    );

                selectorStart = comma + 1;
            }

            // Trim whitespace.
            size_t first = 0;

            while (
                first < selector.length() &&
                std::isspace(
                    static_cast<unsigned char>(
                        selector[first]
                    )
                )
            ) {
                ++first;
            }

            size_t last = selector.length();

            while (
                last > first &&
                std::isspace(
                    static_cast<unsigned char>(
                        selector[last - 1]
                    )
                )
            ) {
                --last;
            }

            if (first < last) {
                rule.addSelector(
                    Selector(
                        selector.substr(
                            first,
                            last - first
                        )
                    )
                );
            }
        }

        // We should now be positioned at '{'.
        skipWhitespace(css, position);

        if (
            position >= css.length() ||
            css[position] != '{'
        ) {
            continue;
        }

        ++position;

        // Parse declarations.
        while (position < css.length()) {
            skipWhitespace(css, position);

            if (position >= css.length()) {
                break;
            }

            // End of declaration block.
            if (css[position] == '}') {
                ++position;
                break;
            }

            // Comment inside declaration block.
            if (startsWith(css, position, "/*")) {
                skipComment(css, position);
                continue;
            }

            std::string property =
                parseProperty(css, position);

            if (property.empty()) {
                if (
                    position < css.length() &&
                    css[position] != '}'
                ) {
                    ++position;
                }

                continue;
            }

            skipWhitespace(css, position);

            // Property must be followed by ':'.
            if (
                position >= css.length() ||
                css[position] != ':'
            ) {
                while (
                    position < css.length() &&
                    css[position] != ';' &&
                    css[position] != '}'
                ) {
                    ++position;
                }

                if (
                    position < css.length() &&
                    css[position] == ';'
                ) {
                    ++position;
                }

                continue;
            }

            ++position;

            skipWhitespace(css, position);

            std::string value =
                parseValue(css, position);

            rule.addDeclaration(
                Declaration(
                    property,
                    value
                )
            );

            skipWhitespace(css, position);

            // Declaration separator.
            if (
                position < css.length() &&
                css[position] == ';'
            ) {
                ++position;
            }
        }

        stylesheet.addRule(rule);
    }

    return stylesheet;
}

void CSSParser::skipWhitespace(
    const std::string& css,
    size_t& position
) {
    while (
        position < css.length() &&
        std::isspace(
            static_cast<unsigned char>(
                css[position]
            )
        )
    ) {
        ++position;
    }
}

void CSSParser::skipComment(
    const std::string& css,
    size_t& position
) {
    if (!startsWith(css, position, "/*")) {
        return;
    }

    position += 2;

    while (
        position + 1 < css.length() &&
        !startsWith(css, position, "*/")
    ) {
        ++position;
    }

    if (position + 1 < css.length()) {
        position += 2;
    } else {
        position = css.length();
    }
}

std::string CSSParser::parseSelector(
    const std::string& css,
    size_t& position
) {
    size_t start = position;

    bool insideString = false;
    char stringQuote = '\0';
    int parenthesesDepth = 0;
    int bracketsDepth = 0;

    while (position < css.length()) {
        char character = css[position];

        if (insideString) {
            if (character == '\\') {
                // Skip escaped character.
                if (position + 1 < css.length()) {
                    position += 2;
                    continue;
                }
            }

            if (character == stringQuote) {
                insideString = false;
            }

            ++position;
            continue;
        }

        if (
            character == '"' ||
            character == '\''
        ) {
            insideString = true;
            stringQuote = character;
            ++position;
            continue;
        }

        if (
            character == '('
        ) {
            ++parenthesesDepth;
            ++position;
            continue;
        }

        if (
            character == ')' &&
            parenthesesDepth > 0
        ) {
            --parenthesesDepth;
            ++position;
            continue;
        }

        if (character == '[') {
            ++bracketsDepth;
            ++position;
            continue;
        }

        if (
            character == ']' &&
            bracketsDepth > 0
        ) {
            --bracketsDepth;
            ++position;
            continue;
        }

        if (
            character == '{' &&
            parenthesesDepth == 0 &&
            bracketsDepth == 0
        ) {
            break;
        }

        ++position;
    }

    std::string selector =
        css.substr(
            start,
            position - start
        );

    // Trim whitespace.
    size_t first = 0;

    while (
        first < selector.length() &&
        std::isspace(
            static_cast<unsigned char>(
                selector[first]
            )
        )
    ) {
        ++first;
    }

    size_t last = selector.length();

    while (
        last > first &&
        std::isspace(
            static_cast<unsigned char>(
                selector[last - 1]
            )
        )
    ) {
        --last;
    }

    if (first >= last) {
        return "";
    }

    return selector.substr(
        first,
        last - first
    );
}

std::string CSSParser::parseProperty(
    const std::string& css,
    size_t& position
) {
    size_t start = position;

    while (position < css.length()) {
        char character = css[position];

        if (
            character == ':' ||
            character == ';' ||
            character == '}'
        ) {
            break;
        }

        ++position;
    }

    std::string property =
        css.substr(
            start,
            position - start
        );

    // Trim whitespace.
    size_t first = 0;

    while (
        first < property.length() &&
        std::isspace(
            static_cast<unsigned char>(
                property[first]
            )
        )
    ) {
        ++first;
    }

    size_t last = property.length();

    while (
        last > first &&
        std::isspace(
            static_cast<unsigned char>(
                property[last - 1]
            )
        )
    ) {
        --last;
    }

    if (first >= last) {
        return "";
    }

    property =
        property.substr(
            first,
            last - first
        );

    // CSS property names are ASCII case-insensitive.
    std::transform(
        property.begin(),
        property.end(),
        property.begin(),
        [](unsigned char character) {
            return static_cast<char>(
                std::tolower(character)
            );
        }
    );

    return property;
}

std::string CSSParser::parseValue(
    const std::string& css,
    size_t& position
) {
    size_t start = position;

    bool insideString = false;
    char stringQuote = '\0';

    int parenthesesDepth = 0;
    int bracketsDepth = 0;

    while (position < css.length()) {
        char character = css[position];

        if (insideString) {
            if (character == '\\') {
                if (position + 1 < css.length()) {
                    position += 2;
                    continue;
                }
            }

            if (character == stringQuote) {
                insideString = false;
            }

            ++position;
            continue;
        }

        if (
            character == '"' ||
            character == '\''
        ) {
            insideString = true;
            stringQuote = character;
            ++position;
            continue;
        }

        if (
            character == '('
        ) {
            ++parenthesesDepth;
            ++position;
            continue;
        }

        if (
            character == ')' &&
            parenthesesDepth > 0
        ) {
            --parenthesesDepth;
            ++position;
            continue;
        }

        if (character == '[') {
            ++bracketsDepth;
            ++position;
            continue;
        }

        if (
            character == ']' &&
            bracketsDepth > 0
        ) {
            --bracketsDepth;
            ++position;
            continue;
        }

        // A semicolon terminates the declaration,
        // unless we're inside parentheses/brackets.
        if (
            character == ';' &&
            parenthesesDepth == 0 &&
            bracketsDepth == 0
        ) {
            break;
        }

        // A closing brace terminates the declaration block.
        if (
            character == '}' &&
            parenthesesDepth == 0 &&
            bracketsDepth == 0
        ) {
            break;
        }

        // CSS comments inside values.
        if (
            startsWith(css, position, "/*") &&
            parenthesesDepth == 0 &&
            bracketsDepth == 0
        ) {
            break;
        }

        ++position;
    }

    std::string value =
        css.substr(
            start,
            position - start
        );

    // Trim leading whitespace.
    size_t first = 0;

    while (
        first < value.length() &&
        std::isspace(
            static_cast<unsigned char>(
                value[first]
            )
        )
    ) {
        ++first;
    }

    // Trim trailing whitespace.
    size_t last = value.length();

    while (
        last > first &&
        std::isspace(
            static_cast<unsigned char>(
                value[last - 1]
            )
        )
    ) {
        --last;
    }

    if (first >= last) {
        return "";
    }

    return value.substr(
        first,
        last - first
    );
}

bool CSSParser::startsWith(
    const std::string& css,
    size_t position,
    const std::string& value
) const {
    if (
        position + value.length() >
        css.length()
    ) {
        return false;
    }

    return css.compare(
        position,
        value.length(),
        value
    ) == 0;
}

}