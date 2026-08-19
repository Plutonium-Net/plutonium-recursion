#include "box.h"

namespace recursion::css {

LayoutBox::LayoutBox(
    const ComputedStyle& style
)
    : m_style(style) {
}

ComputedStyle& LayoutBox::style() {
    return m_style;
}

const ComputedStyle& LayoutBox::style() const {
    return m_style;
}

void LayoutBox::setPosition(
    float x,
    float y
) {
    m_x = x;
    m_y = y;
}

void LayoutBox::setSize(
    float width,
    float height
) {
    m_width = width;
    m_height = height;
}

float LayoutBox::x() const {
    return m_x;
}

float LayoutBox::y() const {
    return m_y;
}

float LayoutBox::width() const {
    return m_width;
}

float LayoutBox::height() const {
    return m_height;
}

void LayoutBox::addChild(
    std::unique_ptr<LayoutBox> child
) {
    if (child) {
        m_children.push_back(
            std::move(child)
        );
    }
}

const std::vector<
    std::unique_ptr<LayoutBox>
>& LayoutBox::children() const {
    return m_children;
}

}