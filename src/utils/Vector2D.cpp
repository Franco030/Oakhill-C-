#include "utils/Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D() {
  x = 0.0f;
  y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2D Vector2D::operator+(const Vector2D& v2) const {
  return Vector2D(this->x + v2.x, this->y + v2.y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const {
  return Vector2D(this->x - v2.x, this->y - v2.y);
}

Vector2D Vector2D::operator*(const float escalar) const {
  return Vector2D(this->x * escalar, this->y * escalar);
}

float Vector2D::magnitude() const { return std::sqrt((x * x) + (y * y)); }

void Vector2D::normalize() {
  float mag = magnitude();
  if (mag > 0) {
    x = x / mag;
    y = y / mag;
  }
}