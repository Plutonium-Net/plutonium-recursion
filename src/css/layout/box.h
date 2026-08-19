#pragma once

#include <memory>
#include <vector>

#include "computed_style.h"

namespace recursion::css {

class LayoutBox {
public:
    LayoutBox() = default;

    explicit LayoutBox(
        const ComputedStyle& style
    );

    ComputedStyle& style();
    const ComputedStyle& style() const;

    void setPosition(
        float x,
        float y
    );

    void setSize(
        float width,
        float height
    );

    float x() const;
    float y() const;

    float width() const;
    float height() const;

    void addChild(
        std::unique_ptr<LayoutBox> child
    );

    const std::vector<
        std::unique_ptr<LayoutBox>
    >& children() const;

private:
    ComputedStyle m_style;

    float m_x = 0.0f;
    float m_y = 0.0f;

    float m_width = 0.0f;
    float m_height = 0.0f;

    std::vector<
        std::unique_ptr<LayoutBox>
    > m_children;
};

}