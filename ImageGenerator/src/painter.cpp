#include "painter.h"

using namespace IMAGE;

void Painter::Draw(Image& image, const Circle& circle, const Color& color) const
{
    image.draw_circle(circle.center.x, circle.center.y, circle.radius,
                      color.r, color.g, color.b, color.a);
}

void Painter::Draw(Image& image, const Diamond& diamond, const Color& color) const
{
    image.draw_diamond(diamond.center.x, diamond.center.y, diamond.radius,
                       color.r, color.g, color.b, color.a);
}

void Painter::Draw(Image& image, const Rectangle& rectangle, const Color& color) const
{
    image.draw_rectangle(rectangle.p1.x, rectangle.p1.y,
                         rectangle.p2.x, rectangle.p2.y,
                         color.r, color.g, color.b, color.a);
}

void Painter::Draw(Image& image, const Triangle& triangle, const Color& color) const
{
    image.draw_triangle(triangle.p1.x, triangle.p1.y,
                        triangle.p2.x, triangle.p2.y,
                        triangle.p3.x, triangle.p3.y,
                        color.r, color.g, color.b, color.a);
}

void Painter::Draw(Image& image, const Line& line, const Color& color) const
{
    image.draw_line(line.p1.x, line.p1.y,
                    line.p2.x, line.p2.y,
                    line.radius,
                    color.r, color.g, color.b, color.a);
}

void Painter::Draw(Image& image, const std::size_t n, const Coord* coords, const Color& color) const
{
    static_assert(sizeof(Coord) == sizeof(double) * 2, "Coord type should be 2 * double");

    const double* data_ptr = reinterpret_cast<const double*>(coords);
    image.draw_polygon(n, data_ptr,
                    color.r, color.g, color.b, color.a);
}

void Painter::Draw(Image& image, const std::vector<Coord>& coords, const Color& color) const
{
    Draw(image, coords.size(), coords.data(), color);
}

void Painter::DrawBorder(Image& image, const Circle& circle, const double width, const Color& color) const
{
    image.draw_circle_border(circle.center.x, circle.center.y, circle.radius, width,
                             color.r, color.g, color.b, color.a);
}

void Painter::DrawBorder(Image& image, const Diamond& diamond, const double width, const Color& color) const
{
    image.draw_diamond_border(diamond.center.x, diamond.center.y, diamond.radius,
                              width,
                              color.r, color.g, color.b, color.a);
}

void Painter::DrawBorder(Image& image, const Rectangle& rectangle, const double width, const Color& color) const
{

    image.draw_rectangle_border(rectangle.p1.x, rectangle.p1.y,
                                rectangle.p2.x, rectangle.p2.y,
                                width,
                                color.r, color.g, color.b, color.a);
}

void Painter::DrawGradient(Image& image, const Line& line, const Color3& color1, const Color3& color2) const
{
    image.draw_line_gradient(line.p1.x, line.p1.y,
                             line.p2.x, line.p2.y,
                             line.radius,
                             color1.r, color1.g, color1.b,
                             color2.r, color2.g, color2.b);
}



