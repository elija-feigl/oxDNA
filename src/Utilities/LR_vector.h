/*
 * LR_vector.h
 *
 *  Created on: 14 ott 2019
 *      Author: lorenzo
 */

#ifndef SRC_UTILITIES_LR_VECTOR_H_
#define SRC_UTILITIES_LR_VECTOR_H_

#include <cmath>
#include <iostream>

using number = double;

/**
 * @brief A three-dimensional vector with built-in basic vectorial operations.
 */
class LR_vector {
public:
	// Data
	number x, y, z;

	// Constructors
	LR_vector(number InX, number InY, number InZ) :
					x(InX),
					y(InY),
					z(InZ) {
	}

	LR_vector() :
					x(0),
					y(0),
					z(0) {
	}

	LR_vector(number * arg) :
					x(arg[0]),
					y(arg[1]),
					z(arg[2]) {

	}

	// Operator Overloads
	inline LR_vector operator+(const LR_vector& V2) const {
		return LR_vector(x + V2.x, y + V2.y, z + V2.z);
	}

	inline LR_vector operator-(const LR_vector& V2) const {
		return LR_vector(x - V2.x, y - V2.y, z - V2.z);
	}

	inline LR_vector operator-() const {
		return LR_vector(-x, -y, -z);
	}

	inline LR_vector operator+() const {
		return LR_vector(x, y, z);
	}

	inline LR_vector operator/(number S) const {
		number fInv = ((number) 1.) / S;
		return LR_vector(x * fInv, y * fInv, z * fInv);
	}

	inline number operator*(const LR_vector& V2) const {
		return x * V2.x + y * V2.y + z * V2.z;
	}

	inline LR_vector operator*(number S) const {
		return LR_vector(x * S, y * S, z * S);
	}

	inline void operator+=(const LR_vector& V2) {
		x += V2.x;
		y += V2.y;
		z += V2.z;
	}
	inline void operator-=(const LR_vector& V2) {
		x -= V2.x;
		y -= V2.y;
		z -= V2.z;
	}

	inline void operator/=(number S) {
		x /= S;
		y /= S;
		z /= S;
	}

	inline void operator*=(number S) {
		x *= S;
		y *= S;
		z *= S;
	}

	inline number &operator[](int i) {
		if(i == 0) return x;
		else if(i == 1) return y;
		else return z;
	}

	inline LR_vector cross(const LR_vector &V2) const {
		return LR_vector(y * V2.z - z * V2.y, z * V2.x - x * V2.z, x * V2.y - y * V2.x);
	}

	number norm() const {
		return x * x + y * y + z * z;
	}

	number module() const {
		return sqrt(norm());
	}

	number sqr_distance(const LR_vector &V1) const {
		return (*this - V1).norm();
	}

	number distance(const LR_vector &V1) const {
		return sqrt(sqr_distance(V1));
	}

	inline void normalize() {
		number fMag = (x * x + y * y + z * z);
		if(fMag == 0) return;

		number fMult = ((number) 1.) / sqrtf(fMag);
		x *= fMult;
		y *= fMult;
		z *= fMult;
		return;
	}

	friend std::ostream &operator<<(std::ostream &stream, const LR_vector &vector) {
		stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}
};

LR_vector operator*(const number S, const LR_vector &v);

#endif /* SRC_UTILITIES_LR_VECTOR_H_ */
