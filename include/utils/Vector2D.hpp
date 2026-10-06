#pragma once

#include <cmath>

struct Vector2D {
  float x = 0.0f;
  float y = 0.0f;

  Vector2D() = default;
  Vector2D(float x, float y) : x(x), y(y) {}

  Vector2D operator+(const Vector2D& v2) const { return {x + v2.x, y + v2.y}; };
  Vector2D operator-(const Vector2D& v2) const { return {x - v2.x, y - v2.y}; };
  Vector2D operator*(const float scalar) const { return {x * scalar, y * scalar}; };

  float magnitude() const { return std::sqrt(x * x + y * y); };

  void normalize() {
    const float mag = magnitude();
    if (mag > 0.0f) {
      x /= mag;
      y /= mag;
    }
  }
};