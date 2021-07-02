#pragma once

namespace IMAGE {

/* Primitive color */
struct Color3 {
    double r, g, b;

    Color3() 
        : r(0)
        , g(0)
        , b(0)
    {
    }
    Color3(double r, double g, double b)
        : r(r)
        , g(g)
        , b(b)
    {
    }
};
struct Color4 {
    double r, g, b;
    double a;

    Color4()
        : r(0)
        , g(0)
        , b(0)
        , a(0)
    {
    }
    Color4(double r, double g, double b, double a = 1.0)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }
    Color4(const Color3& color, double a = 1.0)
        : r(color.r)
        , g(color.g)
        , b(color.b)
        , a(a)
    {
    }
};

using Color = Color4;

/* Primitive elements */
struct Coord {
    double x, y;
    Coord() 
        : x(0)
        , y(0)
    {
    }
    Coord(double x, double y)
        : x(x)
        , y(y)
    {
    }

    // Simple Arithmetic operator can be used
    const Coord operator +(const Coord& q) const {
        return Coord(*this) += q;
    }
    const Coord operator -(const Coord& q) const {
        return Coord(*this) -= q;
    }
    const Coord operator *(const double& q) {
        return Coord(*this) *= q;
    }
    const Coord operator /(const double& q) {
        return Coord(*this) /= q;
    }

    Coord& operator +=(const Coord& q) {
        x += q.x;
        y += q.y;
        return *this;
    }
    Coord& operator -=(const Coord& q) {
        x -= q.x;
        y -= q.y;
        return *this;
    }
    Coord& operator *=(const double& q) {
        x *= q;
        y *= q;
        return *this;
    }
    Coord& operator /=(const double& q) {
        x /= q;
        y /= q;
        return *this;
    }

    // dot(inner) product
    const double operator *(const Coord& q) const {
        return x * q.x + y * q.y;
    }
    // outer product
    const double operator %(const Coord& q) const {
        return x * q.y - y * q.x;
    }
};

struct Circle {
    Coord center;
    double radius;

    Circle() 
        : center()
        , radius()
    {
    }
    Circle(const Coord& center, const double& radius)
        : center(center)
        , radius(radius)
    {
    }
    Circle(const double& cx, const double& cy, const double& radius)
        : center(cx, cy)
        , radius(radius)
    {
    }
};

struct Diamond {
    Coord center;
    double radius;

    Diamond()
        : center()
        , radius()
    {
    }
    Diamond(const Coord& center, const double& radius)
        : center(center)
        , radius(radius)
    {
    }
    Diamond(const double& cx, const double& cy, const double& radius)
        : center(cx, cy)
        , radius(radius)
    {
    }
};

struct Rectangle {
    Coord p1, p2;

    Rectangle()
        : p1()
        , p2()
    {
    }
    Rectangle(const Coord& topLeft, const Coord& bottomRight)
        : p1(topLeft)
        , p2(bottomRight)
    {
    }
    Rectangle(const double& p1x, const double& p1y, const double& p2x, const double& p2y)
        : p1(p1x, p1y)
        , p2(p2x, p2y)
    {
    }
};

struct Triangle {
    Coord p1, p2, p3;

    Triangle()
        : p1()
        , p2()
        , p3()
    {
    }
    Triangle(const Coord& p1, const Coord& p2, const Coord& p3)
        : p1(p1)
        , p2(p2)
        , p3(p3)
    {
    }
    Triangle(const double& p1x, const double& p1y, const double& p2x, const double& p2y, const double& p3x, const double& p3y)
        : p1(p1x, p1y)
        , p2(p2x, p2y)
        , p3(p3x, p3y)
    {
    }
};

struct Line {
    Coord p1, p2;
    double radius;

    Line()
        : p1()
        , p2()
        , radius(1.0)
    {
    }
    Line(const Coord& p1, const Coord& p2, const double& radius = 1.0)
        : p1(p1)
        , p2(p2)
        , radius(radius)
    {
    }
    Line(const double& p1x, const double& p1y, const double& p2x, const double& p2y, const double& radius = 1.0)
        : p1(p1x, p1y)
        , p2(p2x, p2y)
        , radius(radius)
    {
    }
};

} /* namespace IMAGE */

