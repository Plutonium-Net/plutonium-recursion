#include "node.h"

namespace recursion {

Node::Node(NodeType type)
    : m_type(type) {
}

NodeType Node::type() const {
    return m_type;
}

const std::string& Node::tagName() const {
    return m_tagName;
}

void Node::setTagName(const std::string& name) {
    m_tagName = name;
}

const std::string& Node::text() const {
    return m_text;
}

void Node::setText(const std::string& text) {
    m_text = text;
}

void Node::setAttribute(
    const std::string& name,
    const std::string& value
) {
    m_attributes[name] = value;
}

bool Node::hasAttribute(const std::string& name) const {
    return m_attributes.find(name) != m_attributes.end();
}

const std::string& Node::getAttribute(
    const std::string& name
) const {
    static const std::string empty;

    auto it = m_attributes.find(name);

    if (it == m_attributes.end()) {
        return empty;
    }

    return it->second;
}

const std::unordered_map<std::string, std::string>&
Node::attributes() const {
    return m_attributes;
}

void Node::appendChild(std::unique_ptr<Node> child) {
    if (child) {
        m_children.push_back(std::move(child));
    }
}

const std::vector<std::unique_ptr<Node>>&
Node::children() const {
    return m_children;
}

}