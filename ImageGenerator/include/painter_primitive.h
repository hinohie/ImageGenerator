#pragma once

namespace IMAGE {

/* Primitive color */
struct Color4 {
    double r, g, b;
    double a;
};

struct Color3 {
    double r, g, b;
};

using Color = Color4;

/* Primitive elements */
struct Coord {
    double x, y;
};

struct Circle {
    Coord center;
    double radius;
};

struct Diamond {
    Coord center;
    double radius;
};

struct Rectangle {
    Coord p1, p2;
};

struct Triangle {
    Coord p1, p2, p3;
};

struct Line {
    Coord p1, p2;
    double radius;
};

} /* namespace IMAGE */

