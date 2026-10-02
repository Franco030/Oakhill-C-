#pragma once

struct Vector2D {
  float x;
  float y;

  Vector2D();
  Vector2D(float x, float y);

  Vector2D operator+(const Vector2D& v2) const;
  Vector2D operator-(const Vector2D& v2) const;
  Vector2D operator*(const float escalar) const;

  void normalize();
  float magnitude() const;
};