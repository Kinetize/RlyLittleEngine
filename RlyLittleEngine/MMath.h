#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <string>

typedef unsigned char byte;

#define M_PI = 3.14159265358979323846264338327950288
#define ToRadians(x) (float) (x * M_PI / 180.f)
#define ToDegrees(x) (float) (x * 180.0f / M_PI)
#define Abs(x) (x < 0 ? -x : x)

template<typename T>
inline T Clamp(const T& min, const T& max, const T& value) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

template<typename T, unsigned int L>
class Vector {
public:
	Vector<T, L>() { for (int i = 0; i < L; i++) (*this)[i] = T(0);	}

	T Max() const;
	T Min() const;
	T Dot(const Vector<T, L> other) const;

	std::string ToString() const;

	inline T Lenght() const { return sqrt(Dot(this)); }
	inline Vector<T, L> Normalized() { return (*this)/Length(); }

	inline Vector<T, L> operator+ (const T& other) {
		Vector<T, L> result;

		for (int i = 0; i < L; i++)
			result[i] = (*this)[i] + other;

		return result;
	}

	inline Vector<T, L> operator- (const T& other) {
		Vector<T, L> result;

		for (int i = 0; i < L; i++)
			result[i] = (*this)[i] - other;

		return result;
	}

	inline Vector<T, L> operator* (const T& other) {
		Vector<T, L> result;

		for (int i = 0; i < L; i++)
			result[i] = (*this)[i] * other;

		return result;
	}

	inline Vector<T, L> operator/ (const T& other) {
		Vector<T, L> result;

		for (int i = 0; i < L; i++)
			result[i] = (*this)[i] / other;

		return result;
	}

	inline Vector<T, L> operator+= (const T& other) {
		for (int i = 0; i < L; i++)
			(*this)[i] = (*this)[i] + other;

		return *this;
	}

	inline Vector<T, L> operator-= (const T& other) {
		for (int i = 0; i < L; i++)
			(*this)[i] = (*this)[i] - other;

		return *this;
	}

	inline Vector<T, L> operator*= (const T& other) {
		for (int i = 0; i < L; i++)
			(*this)[i] = (*this)[i] * other;

		return *this;
	}

	inline Vector<T, L> operator/= (const T& other) {
		for (int i = 0; i < L; i++)
			(*this)[i] = (*this)[i] / other;

		return *this;
	}

	inline Vector<T, L> operator+ (const Vector<T, L>& other) {
		Vector<T, L> result;

		for (int i = 0; i < L; i++)
			result[i] = (*this)[i] + other[i];

		return result;
	}

	inline Vector<T, L> operator- (const Vector<T, L>& other) {
		Vector<T, L> result;

		for (int i = 0; i < L; i++)
			result[i] = (*this)[i] - other[i];

		return result;
	}

	inline Vector<T, L> operator+= (const Vector<T, L>& other) {
		for (int i = 0; i < L; i++)
			(*this)[i] = (*this)[i] + other[i];

		return *this;
	}

	inline Vector<T, L> operator-= (const Vector<T, L>& other) {
		for (int i = 0; i < L; i++)
			(*this)[i] = (*this)[i] - other[i];

		return *this;
	}

	inline bool operator== (const Vector<T, L>& other) {
		for (int i = 0; i < L; i++)
			if ((*this)[i] != other[i])
				return false;
		return true;
	}

	inline bool operator!= (const Vector<T, L>& other) {
		return !operator==(other);
	}

	inline T operator [] (unsigned int index) const { return _values[index]; }
	inline T& operator [] (unsigned int index) { return _values[index]; }

protected:
	T	_values[L];
};

template <typename T>
class Vector2 : public Vector<T, 2> { //Konstruktoren etc
public:
	Vector2() : Vector() {};
	Vector2(const T x, const T y) : Vector() { Set(x, y); }
	Vector2(const Vector2<T>& other) : Vector() { Set(other.GetX(), other.GetY()); }

	T Det(const Vector2<T>& other) const { return GetX() * other.GetY() - GetY() * other.GetX(); }

	inline T GetX() const { return (*this)[0]; }
	inline T GetY() const { return (*this)[1]; }

	inline void SetX(T value) { (*this)[0] = value; }
	inline void SetY(T value) { (*this)[1] = value; }
	inline void Set(const T x, const T y) { SetX(x); SetY(y); }
};

template<typename T>
class Vector3 : public Vector<T, 3> {
public:
	Vector3() : Vector() {}
	Vector3(const T x, const T y, const T z) : Vector() { Set(x, y, z); }
	Vector3(const Vector2<T>& other) : Vector() { Set(other.GetX(), other.GetY(), 0); }
	Vector3(const Vector3<T>& other) : Vector() { Set(other.GetX(), other.GetY(), other.GetZ()); }

	Vector3<T> Cross(const Vector3<T>& other) const;

	inline T GetX() const { return (*this)[0]; }
	inline T GetY() const { return (*this)[1]; }
	inline T GetZ() const { return (*this)[2]; }
	inline Vector2<T> const GetXY() { return Vector2<T>(GetX(), GetY()); }


	inline void SetX(T value) { (*this)[0] = value; }
	inline void SetY(T value) { (*this)[1] = value; }
	inline void SetZ(T value) { (*this)[2] = value; }
	inline void Set(const T x, const T y, const T z) { SetX(x); SetY(y); SetZ(z); }
};

template<typename T>
class Vector4 : public Vector<T, 4> {
public:
	Vector4() : Vector() {}
	Vector4(const T x, const T y, const T z, const T w) : Vector() { Set(x, y, z, w); }
	Vector4(const Vector3<T>& other) : Vector() { Set(other.GetX(), other.GetY(), other.GetZ(), 0); }
	Vector4(const Vector4<T>& other) : Vector() { Set(other.GetX(), other.GetY(), other.GetZ(), other.GetW()); }

	inline T GetX() const { return (*this)[0]; }
	inline T GetY() const { return (*this)[1]; }
	inline T GetZ() const { return (*this)[2]; }
	inline T GetW() const { return (*this)[3]; }

	inline void SetX(T value) { (*this)[0] = value; }
	inline void SetY(T value) { (*this)[1] = value; }
	inline void SetZ(T value) { (*this)[2] = value; }
	inline void SetW(T value) { (*this)[3] = value; }
};

typedef Vector2<byte> Vector2b;
typedef Vector2<int> Vector2i;
typedef Vector2<long> Vector2l;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

typedef Vector3<byte> Vector3b;
typedef Vector3<int> Vector3i;
typedef Vector3<long> Vector3l;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

typedef Vector4<byte> Vector4b;
typedef Vector4<int> Vector4i;
typedef Vector4<long> Vector4l;
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

template<typename T, unsigned int L>
class Matrix {
public:
	Matrix<T, L>() { MakeIdentity(); }

	Matrix<T, L> MakeIdentity();
	Matrix<T, L> MakeTranslation(const Vector<T, L>& other);
	Matrix<T, L> MakeScale(const Vector<T, L>& other);

	inline void SetValue(const unsigned int i, const unsigned int j, const T value) { _values[i][j] = value; }

	T Det() const;
	Matrix<T, L - 1> SizedDown(const unsigned int i, const unsigned int j) const;
	Matrix<T, L> Transposed() const;
	Matrix<T, L> Inversed() const; //TODO

protected:
	T _values[L][L];
	//	00 01
	//  10 11
};

template<typename T>
class Matrix2 : public Matrix<T, 2> {

};

template<typename T>
class Matrix3 : public Matrix<T, 3> {

};

template<typename T>
class Matrix4 : public Matrix<T, 4> {

};
#endif
