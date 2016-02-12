#include "MMath.h"

//TemP
#include <iostream>

template <typename T, unsigned int L>
Matrix<T, L>& Matrix<T, L>::MakeRotation(const Vector4f& other) {//.........
	return *this;
}

template <>
Matrix<float, 4>& Matrix<float, 4>::MakeRotation(const Vector4f& other) {
	Matrix4f rx = Matrix4f();
	Matrix4f ry = Matrix4f();
	Matrix4f rz = Matrix4f();

	float x = ToRadians(other.GetX());
	float y = ToRadians(other.GetY());
	float z = ToRadians(other.GetZ());

	if (x != 0) {
		rx[1][1] = cos(x);
		rx[1][2] =-sin(x);
		rx[2][1] = sin(x);
		rx[2][2] = cos(x);
	}

	if (y != 0) {
		ry[0][0] = cos(y);
		ry[0][2] = -sin(y);
		ry[2][0] = sin(y);
		ry[2][2] = cos(y);
	}

	if (z != 0) {
		rz[0][0] = cos(z);
		rz[0][1] = -sin(z);
		rz[1][0] = sin(z);
		rz[1][1] = cos(z);
	}

	if (x = 0) {
		if (y = 0) {
			if (z = 0) {
				MakeIdentity();
			}
			else {
				*this = rz;
			}
		}
		else {
			if (z = 0) {
				*this = ry;
			}
			else {
				*this = rz * ry;
			}
		}
	}
	else {
		if (y = 0) {
			if (z = 0) {
				*this = rx;
			}
			else {
				*this = rz * rx;
			}
		}
		else {
			if (z = 0) {
				*this = ry * rx;
			}
			else {
				*this = rz * ry * rx;
			}
		}
	}

	return *this;
}

template <typename T, unsigned int L>
void Matrix<T, L>::SetUniform(unsigned int& id) { }//TODO

template <>
void Matrix<float, 4>::SetUniform(unsigned int& id) { glUniformMatrix4fv(id, 1, true, &_values[0][0]); }