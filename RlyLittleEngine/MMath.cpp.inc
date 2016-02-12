#pragma once
//#ifndef MATH_CPP_INC
//#define MATH_CPP_INC
//#include "mmath.h"
//#include "GL/glew.h"
//#define M_PI = 3.14159265358979323846264338327950288
//template float Vector<float, 2>::Dot(const Vector<float, 2> other) const;

template <typename T, unsigned int L>
T Vector<T, L>::Max() const {
	T max = (*this)[0];

	for (int i = 1; i < L; i++)
		if ((*this)[i] > max)
			max = (*this)[i];

	return max;
}

template <typename T, unsigned int L>
T Vector<T, L>::Min() const {
	T min = (*this)[0];

	for (int i = 1; i < L; i++)
		if ((*this)[i] < min)
			min = (*this)[i];

	return min;
}

template <typename T, unsigned int L>
T Vector<T, L>::Dot(const Vector<T, L> other) const {
	T result = 0;

	for (int i = 0; i < L; i++)
		result += (*this)[i] * other[i];

	return result;
}

template <typename T, unsigned int L>
std::string Vector<T, L>::ToString() const { 
	std::string ret = "";

	for (int i = 0; i < L; i++)
		ret += std::to_string((*this)[i]) + " ";

	return ret;
}

template<typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& other) const {
	T x = GetY() * other.GetZ() - GetZ() * other.GetY();
	T y = GetZ() * other.GetX() - GetX() * other.GetZ();
	T z = GetX() * other.GetY() - GetY() * other.GetX();

	return Vector3<T>(x, y, z);
}

template <typename T, unsigned int L>
std::string Matrix<T, L>::ToString() const { 
	std::string ret = "";

	for (int i = 0; i < L; i++) {
		for(int j = 0; j < L; j++)
			ret += std::to_string((*this)[i]) + " ";
		ret += "\n";
	}

	return ret;
}

template <typename T, unsigned int L>
Matrix<T, L>& Matrix<T, L>::MakeIdentity() {
	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			if (i == j)
				(*this)[i][j] = T(1);
			else
				(*this)[i][j] = T(0);

	return *this;
}

template <typename T, unsigned int L>
Matrix<T, L>& Matrix<T, L>::MakeTranslation(const Vector<T, L>& other) {//Richtig?!
	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			if (j == L - 1)
				(*this)[i][j] = other[i];
			else if (i == j)
				(*this)[i][j] = T(1);
			else
				(*this)[i][j] = T(0);

	return *this;
}



template <typename T, unsigned int L>
Matrix<T, L>& Matrix<T, L>::MakeScale(const Vector<T, L>& other) {
	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			if (i == j)
				(*this)[i][j] = other[i];
			else
				(*this)[i][j] = T(0);

	return *this;
}

template <typename T, unsigned int L>
T Matrix<T, L>::Det() const {
	int result = 0;

	if (L == 1)
		result = values[1][1];
	else
		for (int k = 1; k <= L; k++) {
			if ((*this)[1][k - 1] != 0)
				result += ((1 + k) % 2) == 0 ? SizedDown(1, k).Det() : -SizedDown(1, k).Det();
		}

	return result;
}

template <typename T, unsigned int L>
Matrix<T, L - 1> Matrix<T, L>::SizedDown(const unsigned int ip, const unsigned int jp) const {	
	Matrix<T, L - 1> result();
	unsigned int malus = 0;
	
	for (int i = 1; i < ip; i++)
		for (int j = 1; j < jp; j++)
				result[i - 1][j - 1] = (*this)[i - 1][j - 1];

	for (int i = ip + 1; i <= L; i++)
		for (int j = jp + 1; j <= L; j++)
			result[i - 2][j - 2] = (*this)[i - 1][j - 1];
	
	return result;
}

template <typename T, unsigned int L>
Matrix<T, L> Matrix<T, L>::Transposed() const {
	Matrix <T, L> other();
	for (int i = 0; i < L; i++)
		for (int j = 0; i < L; j++)
			other[i][j] = *(this)[j][i];
	return other;
}

template <typename T, unsigned int L>
Matrix<T, L> Matrix<T, L>::Inversed() const {
	return Matrix<T, L>();
}
//#endif