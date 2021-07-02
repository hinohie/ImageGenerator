#pragma once

#include "image.h"
#include "painter_primitive.h"

#include <array>
#include <vector>

namespace IMAGE {

/*
 * Helper to draw primitive elements
 */
struct Painter {
    void Draw(Image& image, const Circle& circle, const Color& color) const;
    void Draw(Image& image, const Diamond& diamond, const Color& color) const;
    void Draw(Image& image, const Rectangle& rectangle, const Color& color) const;
    void Draw(Image& image, const Triangle& triangle, const Color& color) const;
    void Draw(Image& image, const Line& line, const Color& color) const;
    void Draw(Image& image, const std::size_t n, const Coord* coords, const Color& color) const;
    void Draw(Image& image, const std::vector<Coord>& coords, const Color& color) const;

    void Draw(Image& image, const Rectangle& rectangle, const Image& sourceImage) const;

    template <std::size_t _Sz>
    void Draw(Image& image, const std::array<Coord, _Sz>& coords, const Color& color) const
    {
        Draw(image, color, _Sz, coords.size());
    }

    void DrawBorder(Image& image, const Circle& circle, const double width, const Color& color) const;
    void DrawBorder(Image& image, const Diamond& diamond, const double width, const Color& color) const;
    void DrawBorder(Image& image, const Rectangle& rectangle, const double width, const Color& color) const;

    void DrawGradient(Image& image, const Line& line, const Color3& color1, const Color3& color2) const;
};

} /* namespace IMAGE */
