/***************************************************************************
 * file:        Coord.h
 *
 * author:      Christian Frank
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 **************************************************************************/

#ifndef __INET_COORD_H
#define __INET_COORD_H

#include "inet/common/INETDefs.h"
#include "inet/common/INETMath.h"

namespace inet {

/**
 * @brief Class for storing 3D coordinates.
 *
 * Some comparison and basic arithmetic operators are implemented.
 *
 * @ingroup utils
 * @author Christian Frank
 */
class INET_API Coord
{
  public:
    /** @brief Constant with all values set to 0. */
    static const Coord NIL;
    static const Coord ZERO;
    static const Coord X_AXIS;
    static const Coord Y_AXIS;
    static const Coord Z_AXIS;

  public:
    /** @name x, y and z coordinate of the position. */
    /*@{*/
    double x;
    double y;
    double z;
    /*@}*/

  private:
    void copy(const Coord& other) { x = other.x; y = other.y; z = other.z; }

  public:
    /** @brief Default constructor. */
    Coord() : x(0.0), y(0.0), z(0.0) { }

    /** @brief Initializes a coordinate. */
    Coord(double x, double y, double z = 0.0) : x(x), y(y), z(z) { }

    /** @brief Initializes coordinate from other coordinate. */
    Coord(const Coord& other) { copy(other); }

    double getX() const { return x; }
    void setX(double x) { this->x = x; }

    double getY() const { return y; }
    void setY(double y) { this->y = y; }

    double getZ() const { return z; }
    void setZ(double z) { this->z = z; }

    /** @brief Returns a string with the value of the coordinate. */
    std::string str() const;

    /** @brief Returns the negated vector. */
    Coord operator-() const { return Coord(-x, -y, -z); }

    /** @brief Adds two coordinate vectors. */
    friend Coord operator+(const Coord& a, const Coord& b) {
        return Coord(a).operator+=(b);
    }

    /** @brief Subtracts two coordinate vectors. */
    friend Coord operator-(const Coord& a, const Coord& b) {
        return Coord(a).operator-=(b);
    }

    /** @brief Multiplies a coordinate vector by a real number. */
    friend Coord operator*(const Coord& a, double f) {
        return Coord(a).operator*=(f);
    }

    /** @brief Divides a coordinate vector by a real number. */
    friend Coord operator/(const Coord& a, double f) {
        return Coord(a).operator/=(f);
    }

    /**
     * @brief Multiplies this coordinate vector by a real number.
     */
    Coord& operator*=(double f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    /**
     * @brief Divides this coordinate vector by a real number.
     */
    Coord& operator/=(double f) {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    /**
     * @brief Adds coordinate vector 'a' to this.
     */
    Coord& operator+=(const Coord& a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    /**
     * @brief Dot product
     */
    float operator*(const Coord& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    /**
     * @brief Cross product
     */
    Coord operator%(const Coord& v) const {
        return Coord(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    /**
     * @brief Assigns coordinate vector 'other' to this.
     *
     * This operator can change the dimension of the coordinate.
     */
    Coord& operator=(const Coord& other) {
        if (this == &other)
            return *this;
        copy(other);
        return *this;
    }

    /**
     * @brief Subtracts coordinate vector 'a' from this.
     */
    Coord& operator-=(const Coord& a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    /**
     * @brief Tests whether two coordinate vectors are equal.
     *
     * Because coordinates are of type double, this is done through the
     * math::close function.
     */
    friend bool operator==(const Coord& a, const Coord& b) {
        // FIXME: this implementation is not transitive
        return math::close(a.x, b.x) && math::close(a.y, b.y) && math::close(a.z, b.z);
    }

    /**
     * @brief Tests whether two coordinate vectors are not equal.
     *
     * Negation of the operator==.
     */
    friend bool operator!=(const Coord& a, const Coord& b) { return !(a == b); }

    /**
     * @brief Returns the distance to Coord 'a'.
     */
    double distance(const Coord& a) const
    {
        Coord dist(*this - a);
        return dist.length();
    }

    /**
     * @brief Returns distance^2 to Coord 'a' (omits calling square root).
     */
    double sqrdist(const Coord& a) const
    {
        Coord dist(*this - a);
        return dist.squareLength();
    }

    /**
     * @brief Returns the squared distance on a torus of this to Coord 'b' (omits calling square root).
     */
    double sqrTorusDist(const Coord& b, const Coord& size) const;

    /**
     * @brief Returns the square of the length of this Coords position vector.
     */
    double squareLength() const { return x * x + y * y + z * z; }

    /**
     * @brief Returns the length of this Coords position vector.
     */
    double length() const { return sqrt(squareLength()); }

    /**
     * @brief Updates the length of this position vector to be 1.
     */
    Coord normalize() { *this /= length(); return *this; }

    /**
     * @brief Checks if this coordinate is inside a specified rectangle.
     *
     * @param lowerBound The upper bound of the rectangle.
     * @param upperBound The lower bound of the rectangle.
     */
    bool isInBoundary(const Coord& lowerBound, const Coord& upperBound) const {
        return lowerBound.x <= x && x <= upperBound.x &&
               lowerBound.y <= y && y <= upperBound.y &&
               lowerBound.z <= z && z <= upperBound.z;
    }

    bool isNil() const {
        return this == &NIL;
    }

    /**
     * Returns true if this coordinate is unspecified.
     */
    bool isUnspecified() const {
        return std::isnan(x) && std::isnan(y) && std::isnan(z);
    }

    /**
     * @brief Returns the minimal coordinates.
     */
    Coord min(const Coord& a) {
        return Coord(x < a.x ? x : a.x, y < a.y ? y : a.y, z < a.z ? z : a.z);
    }

    /**
     * @brief Returns the maximal coordinates.
     */
    Coord max(const Coord& a) {
        return Coord(x > a.x ? x : a.x, y > a.y ? y : a.y, z > a.z ? z : a.z);
    }

    /**
     * @brief Returns the angle between the two vectors.
     */
    double angle(const Coord& a) {
        return acos(*this * a / length() / a.length());
    }

    static Coord parse(const char *text) {
        if (!strcmp(text, "x") || !strcmp(text, "+x"))
            return Coord::X_AXIS;
        else if (!strcmp(text, "-x"))
            return -Coord::X_AXIS;
        else if (!strcmp(text, "y") || !strcmp(text, "+y"))
            return Coord::Y_AXIS;
        else if (!strcmp(text, "-y"))
            return -Coord::Y_AXIS;
        else if (!strcmp(text, "z") || !strcmp(text, "+z"))
            return Coord::Z_AXIS;
        else if (!strcmp(text, "-z"))
            return -Coord::Z_AXIS;
        else {
            cStringTokenizer tokenizer(text);
            double x = atof(tokenizer.nextToken());
            double y = atof(tokenizer.nextToken());
            double z = atof(tokenizer.nextToken());
            return Coord(x, y, z);
        }
    }
};

inline std::ostream& operator<<(std::ostream& os, const Coord& coord)
{
    return os << "(" << coord.x << ", " << coord.y << ", " << coord.z << ") m";
}

inline std::string Coord::str() const
{
    std::stringstream os;
    os << *this;
    return os.str();
}

} // namespace inet

#endif // ifndef __INET_COORD_H

