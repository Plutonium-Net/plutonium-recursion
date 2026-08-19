#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace recursion {

enum class NodeType {
    Document,
    Element,
    Text
};

class Node {
public:
    explicit Node(NodeType type);

    NodeType type() const;

    const std::string& tagName() const;
    void setTagName(const std::string& name);

    const std::string& text() const;
    void setText(const std::string& text);

    void setAttribute(
        const std::string& name,
        const std::string& value
    );

    bool hasAttribute(const std::string& name) const;

    const std::string& getAttribute(
        const std::string& name
    ) const;

    const std::unordered_map<std::string, std::string>&
    attributes() const;

    void appendChild(std::unique_ptr<Node> child);

    const std::vector<std::unique_ptr<Node>>& children() const;

private:
    NodeType m_type;

    std::string m_tagName;
    std::string m_text;

    std::unordered_map<std::string, std::string> m_attributes;

    std::vector<std::unique_ptr<Node>> m_children;
};

}