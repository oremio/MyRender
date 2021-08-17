/**
* @author oremio
* @E-mail 578168741@qq.com
* @version 2021-07-15
*/
#ifndef _REDNER_HELP_H_
#define _REDNER_HELP_H_

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <map>
#include <vector>
#include <ostream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <initializer_list>

//---------------------------------------------------------------------
// ��ѧ�⣺ʸ������
//---------------------------------------------------------------------

// ͨ��ʸ����N ��ʸ��ά�ȣ�T Ϊ��������
template <size_t N, typename T>
struct  Vector
{
    T m[N];
    inline Vector() {
        for (size_t i = 0; i < N; i++)
            m[i] = T();
    }
    inline  Vector(const T* ptr) {
        for (size_t i = 0; i < N; i++)
            m[i] = ptr[i];
    }
    inline Vector(const Vector<N, T>& u) {
        for (size_t i = 0; i < N; i++)
            m[i] = u.m[i];
    }
    inline Vector(const std::initializer_list<T>& u) {
        auto it = u.begin();
        for (size_t i = 0; i < N; i++)
            m[i] = *it++;
    }
    //��ֵ
    inline const T& operator[] (size_t i) const {
        assert(i < N);
        return m[i];
    }
    //��ֵ
    inline T& operator[] (size_t i) {
        assert(i < N);
        return m[i];
    }
    inline void load(const T* ptr) {
        for (size_t i = 0; i < N; i++)
            m[i] = ptr[i];
    }
    inline void save(T* ptr) {
        for (size_t i = 0; i < N; i++)
            ptr[i] = m[i];
    }
};

// �ػ���άʸ��
template<typename T>
struct Vector<2, T>
{
    union {
        struct { T x, y; };    // Ԫ�ر���
        struct { T u, v; };    // Ԫ�ر�����������
        T m[2];                // Ԫ������
    };
    inline Vector() :x(T()), y(T()) {}
    inline Vector(T X, T Y) : x(X), y(Y) {}
    inline Vector(const Vector<2, T>& u) : x(u.x), y(u.y) {}
    inline Vector(const T* ptr) : x(ptr[0]), y(ptr[1]) {}
    inline const T& operator[](size_t i) const {
        assert(i < 2);
        return m[i];
    }
    inline T& operator[](size_t i) {
        assert(i < 2);
        return m[i];
    }
    inline void load(const T* ptr) {
        for (size_t i = 0; i < 2; i++)
            m[i] = ptr[i];
    }
    inline void save(T* ptr) {
        for (size_t i = 0; i < 2; i++)
            ptr[i] = m[i];
    }
    inline Vector<2, T> xy() const { return *this; }
    inline Vector<3, T> xy1() const { return Vector<3, T>(x, y, 1); }
    inline Vector<4, T> xy11() const { return Vector<4, T>(x, y, 1, 1); }
};

//�ػ���άʸ��
template <typename T>
struct Vector<3, T>
{
    union {
        struct { T x, y, z; };    // Ԫ�ر���
        struct { T r, g, b; };    // Ԫ�ر�������alpha��ɫ��
        T m[3];                   // Ԫ������
    };
    inline Vector() :x(T()), y(T()), z(T()) {}
    inline Vector(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    inline Vector(const Vector<3, T>& u) : x(u.x), y(u.y), z(u.z) {}
    inline Vector(const T* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
    inline const T& operator[](size_t i)const {
        assert(i < 3);
        return m[i];
    }
    inline T& operator[](size_t i) {
        assert(i < 3);
        return m[i];
    }
    inline void load(const T* ptr) {
        for (size_t i = 0; i < 3; i++)
            m[i] = ptr[i];
    }
    inline void save(T* ptr) {
        for (size_t i = 0; i < 3; i++)
            ptr[i] = m[i];
    }
    inline Vector<2, T> xy() const { return Vector<2, T>(x, y); }
    inline Vector<3, T> xyz() const { return *this; }
    inline Vector<4, T> xyz1() const { return Vector<4, T>(x, y, z, 1); }
};

//�ػ���άʸ��
template<typename T>
struct Vector<4, T>
{
    union {
        struct { T x, y, z, w; };    // Ԫ�ر���
        struct { T r, g, b, a; };    // Ԫ�ر���
        T m[4];                      // Ԫ������
    };
    inline Vector() : x(T()), y(T()), z(T()), w(T()) {}
    inline Vector(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}
    inline Vector(const Vector<4, T>& u) : x(u.x), y(u.y), z(u.z), w(u.w) {}
    inline Vector(const T* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3]) {}
    inline const T& operator[](size_t i)const {
        assert(i < 4);
        return m[i];
    }
    inline T& operator[](size_t i) {
        assert(i < 4);
        return m[i];
    }
    inline void load(const T* ptr) {
        for (size_t i = 0; i < 4; i++)
            m[i] = ptr[i];
    }
    inline void save(T* ptr) {
        for (size_t i = 0; i < 4; i++)
            ptr[i] = m[i];
    }
    inline Vector<2, T> xy() const { return Vector<2, T>(x, y); }
    inline Vector<3, T> xyz() const { return Vector<3, T>(x, y, z); }
    inline Vector<4, T> xyzw() const { return *this; }
};

//---------------------------------------------------------------------
// ��ѧ�⣺ʸ������
//---------------------------------------------------------------------

// = (+a)
template<size_t N, typename T>
inline Vector<N, T> operator + (const Vector<N, T>& a) {
    return a;
}

// = (-a)
template <size_t N, typename T>
inline Vector<N, T> operator - (const Vector<N, T>& a) {
    Vector<N, T> b;
    for (size_t i = 0; i < N; i++)
        b[i] = -a[i];
    return b;
}

// = ��a��b�Ƿ����
template <size_t N, typename T>
inline bool operator == (const Vector<N, T>& a, const Vector<N, T>& b) {
    for (size_t i = 0; i < N; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

// = ��a��b�Ƿ񲻵�
template <size_t N, typename T>
inline bool operator != (const Vector<N, T>& a, const Vector<N, T>& b) {
    return !(a == b);
}

// = a + b
template <size_t N, typename T>
inline Vector<N, T> operator + (const Vector<N, T>& a, const Vector<N, T>& b) {
    Vector<N, T> c;
    for (size_t i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    return c;
}

// = a - b
template <size_t N, typename T>
inline Vector<N, T> operator -(const Vector<N, T>& a, const Vector<N, T>& b) {
    Vector<N, T> c;
    for (size_t i = 0; i < N; i++)
        c[i] = a[i] - b[i];
    return c;
}

// = a * b��ע�⣬�����ǵ�˻��߲�ˣ���������ÿ��Ԫ�طֱ���ˣ�ɫ�ʼ���ʱ���ã�
template <size_t N, typename T>
inline Vector<N, T> operator * (const Vector<N, T>& a, const Vector<N, T>& b) {
    Vector<N, T> c;
    for (size_t i = 0; i < N; i++) c[i] = a[i] * b[i];
    return c;
}

// = a / b������Ԫ�����
template <size_t N, typename T>
inline Vector<N, T> operator / (const Vector<N, T>& a, const Vector<N, T>& b) {
    Vector<N, T> c;
    for (size_t i = 0; i < N; i++) c[i] = a[i] / b[i];
    return c;
}

// = a * x
template <size_t N, typename T>
inline Vector<N, T> operator * (const Vector<N, T>& a, T x) {
    Vector<N, T> b;
    for (size_t i = 0; i < N; i++) b[i] = a[i] * x;
    return b;
}

// = x * a
template <size_t N, typename T>
inline Vector<N, T> operator * (T x, const Vector<N, T>& a) {
    Vector<N, T> b;
    for (size_t i = 0; i < N; i++) b[i] = a[i] * x;
    return b;
}

// = a / x
template <size_t N, typename T>
inline Vector<N, T> operator / (const Vector<N, T>& a, T x) {
    Vector<N, T> b;
    for (size_t i = 0; i < N; i++) b[i] = a[i] / x;
    return b;
}

// = x / a
template <size_t N, typename T>
inline Vector<N, T> operator / (T x, const Vector<N, T>& a) {
    Vector<N, T> b;
    for (size_t i = 0; i < N; i++) b[i] = x / a[i];
    return b;
}

// a += b
template <size_t N, typename T>
inline Vector<N, T>& operator += (Vector<N, T>& a, const Vector<N, T>& b) {
    for (size_t i = 0; i < N; i++) a[i] += b[i];
    return a;
}

// a -= b
template <size_t N, typename T>
inline Vector<N, T>& operator -= (Vector<N, T>& a, const Vector<N, T>& b) {
    for (size_t i = 0; i < N; i++) a[i] -= b[i];
    return a;
}

// a *= b
template <size_t N, typename T>
inline Vector<N, T>& operator *= (Vector<N, T>& a, const Vector<N, T>& b) {
    for (size_t i = 0; i < N; i++) a[i] *= b[i];
    return a;
}

// a /= b
template <size_t N, typename T>
inline Vector<N, T>& operator /= (Vector<N, T>& a, const Vector<N, T>& b) {
    for (size_t i = 0; i < N; i++) a[i] /= b[i];
    return a;
}

// a *= x
template <size_t N, typename T>
inline Vector<N, T>& operator *= (Vector<N, T>& a, T x) {
    for (size_t i = 0; i < N; i++) a[i] *= x;
    return a;
}

// a /= x
template <size_t N, typename T>
inline Vector<N, T>& operator /= (Vector<N, T>& a, T x) {
    for (size_t i = 0; i < N; i++) a[i] /= x;
    return a;
}

//---------------------------------------------------------------------
// ��ѧ�⣺ʸ������
//---------------------------------------------------------------------

// ��ͬά�ȵ�ʸ��ת��
template <size_t N1, size_t N2, typename T>
inline Vector<N1, T> vectorConvert(const Vector<N2, T>& a, T fill = 1) {
    Vector<N1, T> b;
    for (size_t i = 0; i < N1; i++)
        b[i] = (i < N2) ? a[i] : fill;
    return b;
}

// = |a| ^ 2
template<size_t N, typename T>
inline T vectorLengthSquare(const Vector<N, T>& a) {
    T sum = 0;
    for (size_t i = 0; i < N; i++)
        sum += a[i] * a[i];
    return sum;
}

// = |a|
template<size_t N, typename T>
inline T vectorLength(const Vector<N, T>& a) {
    return sqrt(vectorLengthSquare(a));
}

// = |a| , �ػ� float ���ͣ�ʹ�� sqrtf
template<size_t N>
inline float vectorLength(const Vector<N, float>& a) {
    return sqrtf(vectorLengthSquare(a));
}

// = a / |a|
template<size_t N, typename T>
inline Vector<N, T> vectorNormalize(const Vector<N, T>& a) {
    return a / vectorLength(a);
}

// ʸ�����
template<size_t N, typename T>
inline T vectorDot(const Vector<N, T>& a, const Vector<N, T>& b) {
    T sum = 0;
    for (size_t i = 0; i < N; i++)
        sum += a[i] * b[i];
    return sum;
}

// ��άʸ����ˣ��õ�����
template<typename T>
inline T vectorCross(const Vector<2, T>& a, const Vector<2, T>& b) {
    return a.x * b.y - a.y * b.x;
}

// ��άʸ����ˣ��õ���ʸ��
template<typename T>
inline Vector<3, T> vectorCross(const Vector<3, T>& a, const Vector<3, T>& b) {
    return Vector<3, T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// ��άʸ����ˣ�ǰ��ά��ˣ���һλ����
template<typename T>
inline Vector<4, T> vectorCross(const Vector<4, T>& a, const Vector<4, T>& b) {
    return Vector<4, T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, a.w);
}

// = a + (b - a) * t ��ֵ
template<size_t N, typename T>
inline Vector<N, T> vectorLerp(const Vector<N, T>& a, const Vector<N, T>& b, float t) {
    return a + (b - a) * t;
}

// ����Ԫ��ȡ���ֵ
template<size_t N, typename T>
inline Vector<N, T> vectorMax(const Vector<N, T>& a, const Vector<N, T>& b) {
    Vector<N, T> c;
    for (size_t i = 0; i < N; i++) c[i] = (a[i] > b[i]) ? a[i] : b[i];
    return c;
}

// ����Ԫ��ȡ��Сֵ
template<size_t N, typename T>
inline Vector<N, T> vectorMin(const Vector<N, T>& a, const Vector<N, T>& b) {
    Vector<N, T> c;
    for (size_t i = 0; i < N; i++) c[i] = (a[i] < b[i]) ? a[i] : b[i];
    return c;
}

// ��ʸ����ֵ������ minx/maxx ��Χ��
template<size_t N, typename T>
inline Vector<N, T> vectorBetween(const Vector<N, T>& minx, const Vector<N, T>& maxx, const Vector<N, T>& x) {
    return vectorMin(vectorMax(minx, x), maxx);
}

// �ж�ʸ���Ƿ�ӽ�
template<size_t N, typename T>
inline bool vectorNear(const Vector<N, T>& a, const Vector<N, T>& b, T dist) {
    return (vectorLengthSquare(a - b) <= dist);
}

// �ж�����������ʸ���Ƿ����
template<size_t N>
inline bool vectorNearEqual(const Vector<N, float>& a, const Vector<N, float>& b, float e = 0.0001) {
    return vectorNear(a, b, e);
}

// �ж�����˫����ʸ���Ƿ����
template<size_t N>
inline bool vectorNearEqual(const Vector<N, double>& a, const Vector<N, double>& b, double e = 0.0000001) {
    return vectorNear(a, b, e);
}

// ��ʸ��ֵԪ�ط�Χ���Ƶ�0~1
template<size_t N, typename T>
inline Vector<N, T> vectorClamp(const Vector<N, T>& a, T minx = 0, T maxx = 1) {
    Vector<N, T> b;
    for (size_t i = 0; i < N; i++) {
        T x = (a[i] < minx) ? minx : a[i];
        b[i] = (x > maxx) ? maxx : x;
    }
    return b;
}

// ������ı���
template<size_t N, typename T>
inline std::ostream& operator << (std::ostream& os, const Vector<N, T>& a) {
    os << "[";
    for (size_t i = 0; i < N; i++) {
        os << a[i];
        if (i < N - 1) os << ", ";
    }
    os << "]";
    return os;
}

// ������ַ���
template<size_t N, typename T>
inline std::string vectorRepr(const Vector<N, T>& a) {
    std::stringstream ss;
    ss << a;
    return ss.str();
}


//---------------------------------------------------------------------
// ��ѧ�⣺����
//---------------------------------------------------------------------

// ͨ�þ���
template<size_t ROW, size_t COL, typename T>
struct Matrix
{
    T m[ROW][COL];
    inline Matrix() {}
    inline Matrix(const Matrix<ROW, COL, T>& src) {
        for (size_t r = 0; r < ROW; r++) {
            for (size_t c = 0; c < COL; c++)
                m[r][c] = src.m[r][c];
        }
    }
    inline Matrix(const std::initializer_list<Vector<COL, T>>& u) {
        auto it = u.begin();
        for (size_t i = 0; i < ROW; i++)
            setRow(i, *it++);
    }
    inline const T* operator [] (size_t row) const {
        assert(row < ROW);
        return m[row];
    }
    inline T* operator [] (size_t row) {
        assert(row < ROW);
        return m[row];
    }

    //ȡһ��
    inline Vector<COL, T> oneRow(size_t row) const {
        assert(row < ROW);
        Vector<COL, T> a;
        for (size_t i = 0; i < COL; i++)
            a[i] = m[row][i];
        return a;
    }

    //ȡһ��
    inline Vector<ROW, T> oneCol(size_t col) const {
        assert(col < COL);
        Vector<ROW, T> a;
        for (size_t i = 0; i < ROW; i++)
            a[i] = m[i][col];
        return a;
    }

    //����һ��
    inline void setRow(size_t row, const Vector<COL, T>& a) {
        assert(row < ROW);
        for (size_t i = 0; i < COL; i++)
            m[row][i] = a[i];
    }

    //����һ��
    inline void setCol(size_t col, const Vector<ROW, T>& a) {
        assert(col < COL);
        for (size_t i = 0; i < ROW; i++)
            m[i][col] = a[i];
    }

    // ȡ��ɾ��ĳ�к�ĳ�е��Ӿ�����ʽ
    inline Matrix<ROW - 1, COL - 1, T> getMinor(size_t row, size_t col)const {
        Matrix<ROW - 1, COL - 1, T>ret;
        for (size_t r = 0; r < ROW - 1; r++) {
            for (size_t c = 0; c < COL - 1; c++) {
                ret.m[r][c] = m[r < row ? r : r + 1][c < col ? c : c + 1];
            }
        }
        return ret;
    }

    // ȡ��ת�þ���
    inline Matrix<COL, ROW, T> transpose()const {
        Matrix<COL, ROW, T> ret;
        for (size_t r = 0; r < ROW; r++) {
            for (size_t c = 0; c < COL; c++)
                ret.m[c][r] = m[r][c];
        }
        return ret;
    }

    // ȡ�� 0 ����
    inline static Matrix<ROW, COL, T> getZero() {
        Matrix<ROW, COL, T> ret;
        for (size_t r = 0; r < ROW; r++) {
            for (size_t c = 0; c < COL; c++)
                ret.m[r][c] = 0;
        }
        return ret;
    }

    // ȡ�õ�λ����
    inline static Matrix<ROW, COL, T> getIdentity() {
        Matrix<ROW, COL, T> ret;
        for (size_t r = 0; r < ROW; r++) {
            for (size_t c = 0; c < COL; c++)
                ret.m[r][c] = (r == c) ? 1 : 0;
        }
        return ret;
    }
};

//---------------------------------------------------------------------
// ��ѧ�⣺��������
//---------------------------------------------------------------------

template<size_t ROW, size_t COL, typename T>
inline bool operator == (const Matrix<ROW, COL, T>& a, const Matrix<ROW, COL, T>& b) {
    for (size_t r = 0; r < ROW; r++) {
        for (size_t c = 0; c < COL; c++) {
            if (a.m[r][c] != b.m[r][c]) return false;
        }
    }
    return true;
}

template<size_t ROW, size_t COL, typename T>
inline bool operator != (const Matrix<ROW, COL, T>& a, const Matrix<ROW, COL, T>& b) {
    return !(a == b);
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator +(const Matrix<ROW, COL, T>& src) {
    return src;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator - (const Matrix<ROW, COL, T>& src) {
    Matrix<ROW, COL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < COL; i++)
            out.m[j][i] = -src.m[j][i];
    }
    return out;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator + (const Matrix<ROW, COL, T>& a, const Matrix<ROW, COL, T>& b) {
    Matrix<ROW, COL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < COL; i++)
            out.m[j][i] = a.m[j][i] + b.m[j][i];
    }
    return out;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator - (const Matrix<ROW, COL, T>& a, const Matrix<ROW, COL, T>& b) {
    Matrix<ROW, COL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < COL; i++)
            out.m[j][i] = a.m[j][i] - b.m[j][i];
    }
    return out;
}

template<size_t ROW, size_t COL, size_t NEWCOL, typename T>
inline Matrix<ROW, NEWCOL, T> operator * (const Matrix<ROW, COL, T>& a, const Matrix<COL, NEWCOL, T>& b) {
    Matrix<ROW, NEWCOL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < NEWCOL; i++) {
            out.m[j][i] = vectorDot(a.oneRow(j), b.oneCol(i));
        }
    }
    return out;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator * (const Matrix<ROW, COL, T>& a, T x) {
    Matrix<ROW, COL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < COL; i++) {
            out.m[j][i] = a.m[j][i] * x;
        }
    }
    return out;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator / (const Matrix<ROW, COL, T>& a, T x) {
    Matrix<ROW, COL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < COL; i++) {
            out.m[j][i] = a.m[j][i] / x;
        }
    }
    return out;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator * (T x, const Matrix<ROW, COL, T>& a) {
    return (a * x);
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator / (T x, const Matrix<ROW, COL, T>& a) {
    Matrix<ROW, COL, T> out;
    for (size_t j = 0; j < ROW; j++) {
        for (size_t i = 0; i < COL; i++) {
            out.m[j][i] = x / a.m[j][i];
        }
    }
    return out;
}

template<size_t ROW, size_t COL, typename T>
inline Vector<COL, T> operator * (const Vector<ROW, T>& a, const Matrix<ROW, COL, T>& m) {
    Vector<COL, T> b;//��������������˾�������������Ȼʵ�ʴ洢��������
    for (size_t i = 0; i < COL; i++)
        b[i] = vectorDot(a, m.oneCol(i));
    return b;
}

template<size_t ROW, size_t COL, typename T>
inline Vector<ROW, T> operator * (const Matrix<ROW, COL, T>& m, const Vector<COL, T>& a) {
    Vector<ROW, T> b;
    for (size_t i = 0; i < ROW; i++)
        b[i] = vectorDot(a, m.oneRow(i));
    return b;
}

//---------------------------------------------------------------------
// ��ѧ�⣺����ʽ�������ȣ����ռ�������
//---------------------------------------------------------------------

// ����ʽ��ֵ��һ��
template<typename T>
inline T matrixDet(const Matrix<1, 1, T>& m) {
    return m[0][0];
}

// ����ʽ��ֵ������
template<typename T>
inline T matrixDet(const Matrix<2, 2, T>& m) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

// ����ʽ��ֵ���������ʽ������һ��ͬ���ǵ�����ʽ������
template<size_t N, typename T>
inline T matrixDet(const Matrix<N, N, T>& m) {
    T sum = 0;
    for (size_t i = 0; i < N; i++)
        sum += m[0][i] * matrixCofactor(m, 0, i);
    return sum;
}

// ����ʽ��һ��
template<typename T>
inline T matrixCofactor(const Matrix<1, 1, T>& m, size_t row, size_t col) {
    return 0;
}

// �������ʽ����ɾ���ض����е���ʽ������ʽֵ
template<size_t N, typename T>
inline T matrixCofactor(const Matrix<N, N, T>& m, size_t row, size_t col) {
    return matrixDet(m.getMinor(row, col)) * (((row + col) % 2) ? -1 : 1);
}

// ������󣺼�����ʽ�����ת��
template<size_t N, typename T>
inline Matrix<N, N, T> matrixAdjoint(const Matrix<N, N, T>& m) {
    Matrix<N, N, T> ret;
    for (size_t j = 0; j < N; j++) {
        for (size_t i = 0; i < N; i++) {
            ret[j][i] = matrixCofactor(m, i, j);
        }
    }
    return ret;
}

// �������ʹ�ð�������������ʽ��ֵ�õ�
template<size_t N, typename T>
inline Matrix<N, N, T> matirxInvert(const Matrix<N, N, T>& m) {
    Matrix<N, N, T> ret = matrixAdjoint(m);
    T det = vectorDot(m.oneRow(0), ret.oneCol(0));//��Ҳ��������ʽ��ֵ
    return ret / det;
}

// ������ı���
template<size_t ROW, size_t COL, typename T>
inline std::ostream& operator << (std::ostream& os, const Matrix<ROW, COL, T>& m) {
    for (size_t r = 0; r < ROW; r++) {
        Vector<COL, T>row = m.oneRow(r);
        os << row << std::endl;
    }
    return os;
}

//---------------------------------------------------------------------
// ���ߺ���
//---------------------------------------------------------------------

template<typename T>
inline T abs(T x) { return (x < 0) ? (-x) : x; }

template<typename T>
inline T max(T x, T y) { return (x < y) ? y : x; }

template<typename T>
inline T min(T x, T y) { return (x > y) ? y : x; }

template<typename T>
inline bool nearEqual(T x, T y, T error) {
    return (Abs(x - y) < error);
}

template<typename T>
inline T between(T xmin, T xmax, T x) {
    return min(max(xmin, x), xmax);
}

// ��ȡ [0, 1] �ķ�Χ
template<typename T>
inline T saturate(T x) {
    return between<T>(0, 1, x);
}

// ���ͱ���
typedef Vector<2, float>  Vec2f;
typedef Vector<2, double> Vec2d;
typedef Vector<2, int>    Vec2i;
typedef Vector<3, float>  Vec3f;
typedef Vector<3, double> Vec3d;
typedef Vector<3, int>    Vec3i;
typedef Vector<4, float>  Vec4f;
typedef Vector<4, double> Vec4d;
typedef Vector<4, int>    Vec4i;

typedef Matrix<4, 4, float> Mat4x4f;
typedef Matrix<3, 3, float> Mat3x3f;
typedef Matrix<4, 3, float> Mat4x3f;
typedef Matrix<3, 4, float> Mat3x4f;

//---------------------------------------------------------------------
// 3D ��ѧ����
//---------------------------------------------------------------------

// ʸ��ת������ɫ
inline static uint32_t vectorToColor(const Vec4f& color) {
    uint32_t r = (uint32_t)between(0, 255, (int)(color.r * 255.0f));
    uint32_t g = (uint32_t)between(0, 255, (int)(color.g * 255.0f));
    uint32_t b = (uint32_t)between(0, 255, (int)(color.b * 255.0f));
    uint32_t a = (uint32_t)between(0, 255, (int)(color.a * 255.0f));
    return (r << 16) | (g << 8) | b | (a << 24);
}

// ʸ��ת��������ɫ
inline static uint32_t vectorToColor(const Vec3f& color) {
    return vectorToColor(color.xyz1());
}

// ������ɫ��ʸ��
inline static Vec4f vectorFromColor(uint32_t rgba) {
    Vec4f out;
    out.r = ((rgba >> 16) & 0xff) / 255.0f;
    out.g = ((rgba >> 8) & 0xff) / 255.0f;
    out.b = ((rgba >> 0) & 0xff) / 255.0f;
    out.a = ((rgba >> 24) & 0xff) / 255.0f;
    return out;
}

// matrix set 0
inline static Mat4x4f matrixSetZero() {
    Mat4x4f m;
    m.m[0][0] = m.m[0][1] = m.m[0][2] = m.m[0][3] = 0.0f;
    m.m[1][0] = m.m[1][1] = m.m[1][2] = m.m[1][3] = 0.0f;
    m.m[2][0] = m.m[2][1] = m.m[2][2] = m.m[2][3] = 0.0f;
    m.m[3][0] = m.m[3][1] = m.m[3][2] = m.m[3][3] = 0.0f;
    return m;
}

// set to identity
inline static Mat4x4f matrixSetIdentity() {
    Mat4x4f m;
    m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1.0f;
    m.m[0][1] = m.m[0][2] = m.m[0][3] = 0.0f;
    m.m[1][0] = m.m[1][2] = m.m[1][3] = 0.0f;
    m.m[2][0] = m.m[2][1] = m.m[2][3] = 0.0f;
    m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
    return m;
}

// ƽ�Ʊ任��ע�⣬HLSL��ʹ�õ�������������������ǵ���������������������Ҫ�ҳ����ǵ�������������hlslͬ��������ı任Ҳһ��
inline static Mat4x4f matrixSetTranslate(float x, float y, float z) {
    Mat4x4f m = matrixSetIdentity();
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}

// ���ű任
inline static Mat4x4f matrixSetScale(float x, float y, float z) {
    Mat4x4f m = matrixSetIdentity();
    m.m[0][0] = x;
    m.m[1][1] = y;
    m.m[2][2] = z;
    return m;
}

// ��ת�任��Χ��(x, y, z) ʸ����ת theta �Ƕ�
inline static Mat4x4f matrixSetRotate(float x, float y, float z, float theta) {
    float qsin = (float)sin(theta * 0.5f);//���ǵö����ǹ�ʽ��
    float qcos = (float)cos(theta * 0.5f);
    float w = qcos;
    Vec3f vec = vectorNormalize(Vec3f(x, y, z));
    x = vec.x * qsin;
    y = vec.y * qsin;
    z = vec.z * qsin;
    Mat4x4f m;
    m.m[0][0] = 1 - 2 * y * y - 2 * z * z;//���幫ʽ��LearnOpenGL
    m.m[1][0] = 2 * x * y - 2 * w * z;//���ڸþ�����Ƶ���https://zhuanlan.zhihu.com/p/56587491
    m.m[2][0] = 2 * x * z + 2 * w * y;
    m.m[0][1] = 2 * x * y + 2 * w * z;
    m.m[1][1] = 1 - 2 * x * x - 2 * z * z;
    m.m[2][1] = 2 * y * z - 2 * w * x;
    m.m[0][2] = 2 * x * z - 2 * w * y;
    m.m[1][2] = 2 * y * z + 2 * w * x;
    m.m[2][2] = 1 - 2 * x * x - 2 * y * y;
    m.m[0][3] = m.m[1][3] = m.m[2][3] = 0.0f;
    m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
    m.m[3][3] = 1.0f;
    return m;
}

// ��Ӱ���任����eye/�ӵ�λ�ã�at/�������up/ָ���Ϸ���ʸ��
inline static Mat4x4f matrixSetLookat(const Vec3f& eye, const Vec3f& at, const Vec3f& up) {
    Vec3f zaxis = vectorNormalize(at - eye);
    Vec3f xaxis = vectorNormalize(vectorCross(up, zaxis));
    Vec3f yaxis = vectorCross(zaxis, xaxis);
    Mat4x4f m;
    m.setCol(0, Vec4f(xaxis.x, xaxis.y, xaxis.z, -vectorDot(eye, xaxis)));
    m.setCol(1, Vec4f(yaxis.x, yaxis.y, yaxis.z, -vectorDot(eye, yaxis)));
    m.setCol(2, Vec4f(zaxis.x, zaxis.y, zaxis.z, -vectorDot(eye, zaxis)));
    m.setCol(3, Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
    return m;
}

// D3DXMatrixPerspectiveFovLH
inline static Mat4x4f matrixSetPerspective(float fovy, float aspect, float zn, float zf) {
    float fax = 1.0f / (float)tan(fovy * 0.5f);
    Mat4x4f m = matrixSetZero();
    m.m[0][0] = (float)(fax / aspect);
    m.m[1][1] = (float)(fax);
    m.m[2][2] = zf / (zf - zn);
    m.m[3][2] = -zn * zf / (zf - zn);
    m.m[2][3] = 1;
    return m;
}

//---------------------------------------------------------------------
// λͼ�⣺���ڼ���/����ͼƬ�����㣬���ߣ���ɫ��ȡ
//---------------------------------------------------------------------

class Bitmap
{
public:
    inline virtual ~Bitmap() {
        if (_bits)
            delete[]_bits;
        _bits = NULL;
    }
    inline Bitmap(int width, int height) :_w(width), _h(height) {
        _pitch = width * 4; // һ�������ĸ��ֽ�
        _bits = new uint8_t[_pitch * _h];
        fill(0);
    }
    inline Bitmap(const Bitmap& src) : _w(src._w), _h(src._h), _pitch(src._pitch) {
        _bits = new uint8_t[_pitch * _h];
        memcpy(_bits, src._bits, _pitch * _h);
    }
    inline Bitmap(const char* filename) {
        Bitmap* tmp = loadFile(filename);
        if (tmp == NULL) {
            std::string msg = "load failed:";
            msg.append(filename);
            throw std::runtime_error(msg);
        }
        _w = tmp->_w; _h = tmp->_h; _pitch = tmp->_pitch; _bits = tmp->_bits;
        tmp->_bits = NULL;
        delete tmp;
    }

public:
    inline int getW() const { return _w; }
    inline int getH() const { return _h; }
    inline int getPitch() const { return _pitch; }
    inline uint8_t* getBits() { return _bits; }
    inline const uint8_t* getBits() const { return _bits; }
    inline uint8_t* getLine(int y) { return _bits + _pitch * y; }
    inline const uint8_t* getLine(int y) const { return _bits + _pitch * y; }

public:
    inline void fill(uint32_t color) {
        for (int j = 0; j < _h; j++) {
            uint32_t *row= (uint32_t*)(_bits + j * _pitch);
            for (int i = 0; i < _w; i++, row++)
                memcpy(row, &color, sizeof(uint32_t));
        }
    }

    inline void setPixel(int x, int y, uint32_t color) {
        if (x >= 0 && x < _w && y >= 0 && y < _h) {
            memcpy(_bits + y * _pitch + x * 4, &color, sizeof(uint32_t));
        }
    }

    inline uint32_t getPixel(int x, int y) const {
        uint32_t color = 0;
        if (x >= 0 && x < _w && y >= 0 && y < _h) {
            memcpy(&color, _bits + y * _pitch + x * 4, sizeof(uint32_t));
        }
        return color;
    }

    // ֱ�߹�դ���㷨��DDA��ֵ΢���㷨
    inline void drawLine(int x1, int y1, int x2, int y2, uint32_t color) {
        int x, y;
        if (x1 == x2 && y1 == y2) {
            setPixel(x1, y1, color);
            return;
        }
        else if (x1 == x2) {
            int inc = (y1 <= y2) ? 1 : -1;
            for (y = y1; y != y2; y += inc)
                setPixel(x1, y, color);
            setPixel(x2, y2, color);
        }
        else if (y1 == y2) {
            int inc = (x1 <= x2) ? 1 : -1;
            for (x = x1; x != x2; x += inc)
                setPixel(x, y1, color);
            setPixel(x2, y2, color);
        }
        else {
            int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
            int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
            int rem = 0;
            if (dx >= dy) { // x���ڵ���yʱ���Ⱥ��Ż���ֱ��rem������dx��������ֱ�����ƶ�һ��
                if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; x <= x2; x++) {
                    setPixel(x, y, color);
                    rem += dy;
                    if (rem >= dx) {
                        rem -= dx;
                        y += (y2 >= y1) ? 1 : -1;
                        setPixel(x, y, color); }
                }
                setPixel(x2, y2, color);
            }
            else {
                if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; y <= y2; y++) {
                    setPixel(x, y, color);
                    rem += dx;
                    if (rem >= dy) {
                        rem -= dy;
                        x += (x2 >= x1) ? 1 : -1;
                        setPixel(x, y, color); }
                }
                setPixel(x2, y2, color);
            }
        }
    }

    struct BITMAPINFOHEADER { // bmih
        uint32_t	biSize;
        uint32_t	biWidth;
        int32_t		biHeight;
        uint16_t	biPlanes;
        uint16_t	biBitCount;
        uint32_t	biCompression;
        uint32_t	biSizeImage;
        uint32_t	biXPelsPerMeter;
        uint32_t	biYPelsPerMeter;
        uint32_t	biClrUsed;
        uint32_t	biClrImportant;
    };

    // ��ȡ BMP ͼƬ��֧�� 24/32 λ���ָ�ʽ
    inline static Bitmap* loadFile(const char* filename) {
        FILE* fp = fopen(filename, "rb");
        if (fp == NULL) return NULL;
        BITMAPINFOHEADER info;
        uint8_t header[14];
        int hr = (int)fread(header, 1, 14, fp);
        if (hr != 14) { fclose(fp); return NULL; }
        if (header[0] != 0x42 || header[1] != 0x4d) { fclose(fp); return NULL; }
        hr = (int)fread(&info, 1, sizeof(info), fp);
        if (hr != 40) { fclose(fp); return NULL; }
        if (info.biBitCount != 24 && info.biBitCount != 32) { fclose(fp); return NULL; }
        Bitmap* bmp = new Bitmap(info.biWidth, info.biHeight);
        uint32_t offset;
        memcpy(&offset, header + 10, sizeof(uint32_t));
        fseek(fp, offset, SEEK_SET);
        uint32_t pixelsize = (info.biBitCount + 7) / 8;
        uint32_t pitch = (pixelsize * info.biWidth + 3) & (~3);
        for (int y = 0; y < (int)info.biHeight; y++) {
            uint8_t* line = bmp->getLine(info.biHeight - 1 - y);
            for (int x = 0; x < (int)info.biWidth; x++, line += 4) {
                line[3] = 255;
                fread(line, pixelsize, 1, fp);
            }
            fseek(fp, pitch - info.biWidth * pixelsize, SEEK_CUR);
        }
        fclose(fp);
        return bmp;
    }

    // ���� BMP ͼƬ
    inline bool saveFile(const char* filename, bool withAlpha = false) const {
        FILE* fp = fopen(filename, "wb");
        if (fp == NULL) return false;
        BITMAPINFOHEADER info;
        uint32_t pixelsize = (withAlpha) ? 4 : 3;
        uint32_t pitch = (getW() * pixelsize + 3) & (~3);
        info.biSizeImage = pitch * getH();
        uint32_t bfSize = 54 + info.biSizeImage;
        uint32_t zero = 0, offset = 54;
        fputc(0x42, fp);
        fputc(0x4d, fp);
        fwrite(&bfSize, 4, 1, fp);
        fwrite(&zero, 4, 1, fp);
        fwrite(&offset, 4, 1, fp);
        info.biSize = 40;
        info.biWidth = getW();
        info.biHeight = getH();
        info.biPlanes = 1;
        info.biBitCount = (withAlpha) ? 32 : 24;
        info.biCompression = 0;
        info.biXPelsPerMeter = 0xb12;
        info.biYPelsPerMeter = 0xb12;
        info.biClrUsed = 0;
        info.biClrImportant = 0;
        fwrite(&info, sizeof(info), 1, fp);
        for (int y = 0; y < getH(); y++) {
            const uint8_t* line = getLine(info.biHeight - 1 - y);
            uint32_t padding = pitch - getW() * pixelsize;
            for (int x = 0; x < getW(); x++, line += 4) {
                fwrite(line, pixelsize, 1, fp);
            }
            for (int i = 0; i < (int)padding; i++) fputc(0, fp);
        }
        fclose(fp);
        return true;
    }

    // ˫���Բ�ֵ
    inline uint32_t sampleBilinear(float x, float y) const {
        int32_t fx = (int32_t)(x * 0x10000);
        int32_t fy = (int32_t)(y * 0x10000);
        // ȥС��λ
        int32_t x1 = between(0, _w - 1, fx >> 16);
        int32_t y1 = between(0, _h - 1, fy >> 16);
        int32_t x2 = between(0, _w - 1, x1 + 1);
        int32_t y2 = between(0, _h - 1, y1 + 1);
        // ȡ��8���������ı仯��
        int32_t dx = (fx >> 8) & 0xff;
        int32_t dy = (fy >> 8) & 0xff;
        if (_w <= 0 || _h <= 0) return 0;
        uint32_t c00 = getPixel(x1, y1);
        uint32_t c01 = getPixel(x2, y1);
        uint32_t c10 = getPixel(x1, y2);
        uint32_t c11 = getPixel(x2, y2);
        return bilinearInterp(c00, c01, c10, c11, dx, dy);
    }

    // �������
    inline Vec4f sample2D(float u, float v) const {
        uint32_t rgba = sampleBilinear(u * _w + 0.5f, v * _h + 0.5f);
        return vectorFromColor(rgba);
    }

    // ���������ֱ�Ӵ��� Vec2f
    inline Vec4f sample2D(const Vec2f& uv) const {
        return sample2D(uv.x, uv.y);
    }

    // ���� Vec4f ����
    inline void setPixel(int x, int y, const Vec4f& color) {
        setPixel(x, y, vectorToColor(color));
    }

    // ���·�ת
    inline void filpVertical() {
        uint8_t* buffer = new uint8_t[_pitch];
        for (int i = 0, j = _h - 1; i < j; i++, j--) {//˫ָ��
            memcpy(buffer, getLine(i), _pitch);
            memcpy(getLine(i), getLine(j), _pitch);
            memcpy(getLine(j), buffer, _pitch);
        }
        delete []buffer;
    }

    // ˮƽ��ת
    inline void filpHorizontal() {
        for (int y = 0; y < _h; y++) {
            for (int i = 0, j = _w - 1; i < j; i++, j--) {
                uint32_t c1 = getPixel(i, y);
                uint32_t c2 = getPixel(j, y);
                setPixel(i, y, c2);
                setPixel(j, y, c1);
            }
        }
    }

protected:
    /*
    Linear interpolation(1D): lerp(x, v0, v1)= v0 + x(v1 - v0)
    Two helper lerps:
                       u0 = lerp(s, u00, u10)
                       u1 = lerp(s, u01, u11)
    Final vertical lerp, to get result:
                       f(x, y) = lerp(t, u0, u1)

    */
    // ˫���Բ�ֵ���㣺�����ĸ������ɫ���Լ�����ƫ�ƣ�������
    inline static uint32_t bilinearInterp(uint32_t tl, uint32_t tr,
        uint32_t bl, uint32_t br, int32_t distx, int32_t disty) {
        uint32_t f, r;
        int32_t distxy = distx * disty;
        int32_t distxiy = (distx << 8) - distxy;  /* distx * (256 - disty) */
        int32_t distixy = (disty << 8) - distxy;  /* disty * (256 - distx) */
        int32_t distixiy = 256 * 256 - (disty << 8) - (distx << 8) + distxy;
        // b
        r = (tl & 0x000000ff) * distixiy + (tr & 0x000000ff) * distxiy
            + (bl & 0x000000ff) * distixy + (br & 0x000000ff) * distxy;
        // g
        f = (tl & 0x0000ff00) * distixiy + (tr & 0x0000ff00) * distxiy
            + (bl & 0x0000ff00) * distixy + (br & 0x0000ff00) * distxy;
        r |= f & 0xff000000;
        // ��ֹ���
        tl >>= 16; tr >>= 16; bl >>= 16; br >>= 16; r >>= 16;
        // r
        f = (tl & 0x000000ff) * distixiy + (tr & 0x000000ff) * distxiy
            + (bl & 0x000000ff) * distixy + (br & 0x000000ff) * distxy;
        r |= f & 0x00ff0000;
        // a
        f = (tl & 0x0000ff00) * distixiy + (tr & 0x0000ff00) * distxiy
            + (bl & 0x0000ff00) * distixy + (br & 0x0000ff00) * distxy;
        r |= f & 0xff000000;
        return r;
    }


protected:
    int32_t _w;
    int32_t _h;
    int32_t _pitch; // ÿ���ֽ���
    uint8_t* _bits;
};

//---------------------------------------------------------------------
// ��ɫ������
//---------------------------------------------------------------------

// ��ɫ�������ģ��� VS ���ã�������Ⱦ������������ֵ�󣬹� PS ��ȡ
struct ShaderContext {
    std::map<int, float> varying_float;    // ������ varying �б�
    std::map<int, Vec2f> varying_vec2f;    // ��άʸ�� varying �б�
    std::map<int, Vec3f> varying_vec3f;    // ��άʸ�� varying �б�
    std::map<int, Vec4f> varying_vec4f;    // ��άʸ�� varying �б�
};

// ������ɫ������Ϊ�� C++ ��д�����贫�� attribute������ 0-2 �Ķ������
// ��ɫ������ֱ������������Ŷ�ȡ��Ӧ���ݼ��ɣ������Ҫ����һ������ pos
// ���� varying ���õ� output �����Ⱦ����ֵ�󴫵ݸ� PS
typedef std::function<Vec4f(int index, ShaderContext& output)> VertexShader;


// ������ɫ�������� ShaderContext����Ҫ���� Vec4f ���͵���ɫ
// ��������ÿ����� input ����ֵ�����ǰ����������� output ��ֵ�õ�
typedef std::function<Vec4f(ShaderContext& input)> PixelShader;

//---------------------------------------------------------------------
// RenderHelp
//---------------------------------------------------------------------
class RenderHelp
{
public:
    inline virtual ~RenderHelp() { reset(); }

    inline RenderHelp() {
        _frame_buffer = NULL;
        _depth_buffer = NULL;
        _render_frame = false;
        _render_pixel = true;
    }

    inline RenderHelp(int width, int height) {
        _frame_buffer = NULL;
        _depth_buffer = NULL;
        _render_frame = false;
        _render_pixel = true;
        init(width, height);
    }

public:

    // ��λ״̬
    inline void reset() {
        _vertex_shader = NULL;
        _pixel_shader = NULL;
        if (_frame_buffer) delete _frame_buffer;
        _frame_buffer = NULL;
        if (_depth_buffer) {
            for (int j = 0; j < _fb_height; j++) {
                if (_depth_buffer[j]) delete[]_depth_buffer[j];
                _depth_buffer[j] = NULL;
            }
            delete[]_depth_buffer;
            _depth_buffer = NULL;
        }
        _color_fg = 0xffffffff;
        _color_bg = 0xff191970;
    }

    // ��ʼ�� FrameBuffer����Ⱦǰ��Ҫ�ȵ���
    inline void init(int width, int height) {
        reset();
        _frame_buffer = new Bitmap(width, height);
        _fb_width = width;
        _fb_height = height;
        _depth_buffer = new float* [height];
        for (int j = 0; j < height; j++) {
            _depth_buffer[j] = new float[width];
        }
        clear();
    }

    // ��� FrameBuffer ����Ȼ���
    inline void clear() {
        if (_frame_buffer) {
            _frame_buffer->fill(_color_bg);
        }
        if (_depth_buffer) {
            for (int j = 0; j < _fb_height; j++) {
                for (int i = 0; i < _fb_width; i++)
                    _depth_buffer[j][i] = 0.0f;
            }
        }
    }

    // ���� VS/PS ��ɫ������
    inline void setVertexShader(VertexShader vs) { _vertex_shader = vs; }
    inline void setPixelShader(PixelShader ps) { _pixel_shader = ps; }

    // ���� FrameBuffer �� BMP �ļ�
    inline void saveFile(const char* filename) {
        if (_frame_buffer)
            _frame_buffer->saveFile(filename);
    }

    // ���ñ���/ǰ��ɫ
    inline void SetBGColor(uint32_t color) { _color_bg = color; }
    inline void SetFGColor(uint32_t color) { _color_fg = color; }

    // FrameBuffer �ﻭ��
    inline void setPixel(int x, int y, uint32_t cc) { if (_frame_buffer) _frame_buffer->setPixel(x, y, cc); }
    inline void setPixel(int x, int y, const Vec4f& cc) { setPixel(x, y, vectorToColor(cc)); }
    inline void setPixel(int x, int y, const Vec3f& cc) { setPixel(x, y, vectorToColor(cc)); }

    // FrameBuffer �ﻭ��
    inline void drawLine(int x1, int y1, int x2, int y2) {
        if (_frame_buffer) _frame_buffer->drawLine(x1, y1, x2, y2, _color_fg);
    }

    // ������Ⱦ״̬���Ƿ���ʾ�߿�ͼ���Ƿ����������
    inline void setRenderState(bool frame, bool pixel) {
        _render_frame = frame;
        _render_pixel = pixel;
    }

    // �ж�һ�����ǲ��������ε����ϱ� (Top-Left Edge)
    inline bool isTopLeft(const Vec2i& a, const Vec2i& b) {
        return ((a.y == b.y) && (a.x < b.x)) || (a.y > b.y);
    }

public:

    // ����һ�������Σ��������趨����ɫ������
    inline bool drawPrimitive() {
        if (_frame_buffer == NULL || _vertex_shader == NULL)
            return false;

        // �����ʼ��
        for (int k = 0; k < 3; k++) {
            Vertex& vertex = _vertex[k];

            // ��������� varying �б�
            vertex.context.varying_float.clear();
            vertex.context.varying_vec2f.clear();
            vertex.context.varying_vec3f.clear();
            vertex.context.varying_vec4f.clear();

            // ���ж�����ɫ���򣬷��ض�������
            vertex.pos = _vertex_shader(k, vertex.context);

            // �򵥲ü����κ�һ�����㳬�� CVV ���޳�
            float w = vertex.pos.w;

            // ��һ����Խ�磬����������������Σ�����ϸ��������
            // ���Խ���˾�����οռ��ڽ��вü������Ϊ 0-2 ��������Ȼ�����
            if (w == 0.0f) return false;
            if (vertex.pos.z < 0.0f || vertex.pos.z > w) return false;
            if (vertex.pos.x < -w || vertex.pos.x > w) return false;
            if (vertex.pos.y < -w || vertex.pos.y > w) return false;

            // ���� w �ĵ�����Reciprocal of the Homogeneous W
            vertex.rhw = 1.0f / w;

            // �������ռ� /w ��һ������λ��� cvv
            vertex.pos *= vertex.rhw;

            // ������Ļ���꣬y����ӳ��
            vertex.spf.x = (vertex.pos.x + 1.0f) * _fb_width * 0.5f;
            vertex.spf.y = (1.0f - vertex.pos.y) * _fb_height * 0.5f;

            // ������Ļ���꣺�� 0.5 ��ƫ��ȡ��Ļ���ط������Ķ���
            vertex.spi.x = (int)(vertex.spf.x + 0.5f);
            vertex.spi.y = (int)(vertex.spf.y + 0.5f);

            // ������Ӿ��η�Χ
            if (k == 0) {
                _min_x = _max_x = between(0, _fb_width - 1, vertex.spi.x);
                _min_y = _max_y = between(0, _fb_height - 1, vertex.spi.y);
            }
            else {
                _min_x = between(0, _fb_width - 1, min(_min_x, vertex.spi.x));
                _max_x = between(0, _fb_width - 1, max(_max_x, vertex.spi.x));
                _min_y = between(0, _fb_height - 1, min(_min_y, vertex.spi.y));
                _max_y = between(0, _fb_height - 1, max(_max_y, vertex.spi.y));
            }
        }

        // �����߿�
        if (_render_frame) {
            drawLine(_vertex[0].spi.x, _vertex[0].spi.y, _vertex[1].spi.x, _vertex[1].spi.y);
            drawLine(_vertex[0].spi.x, _vertex[0].spi.y, _vertex[2].spi.x, _vertex[2].spi.y);
            drawLine(_vertex[2].spi.x, _vertex[2].spi.y, _vertex[1].spi.x, _vertex[1].spi.y);
        }

        // �����������ؾ��˳�
        if (_render_pixel == false) return false;

        // �ж������γ���
        Vec4f v01 = _vertex[1].pos - _vertex[0].pos;
        Vec4f v02 = _vertex[2].pos - _vertex[0].pos;
        Vec4f normal = vectorCross(v01, v02);

        // ʹ��ָ������ vtx �����������㣬����ֱ���� _vertex ���ʣ���Ϊ���ܻ����˳��
        Vertex* vtx[3] = { &_vertex[0], &_vertex[1], &_vertex[2] };

        // ��������ӵ㣬�򽻻����㣬��֤ edge equation �жϵķ���Ϊ��
        //����ϵ��˳ʱ�룬��˸�
        if (normal.z > 0.0f) {
            vtx[1] = &_vertex[2];
            vtx[2] = &_vertex[1];
        }
        else if (normal.z == 0.0f) {
            return false;
        }

        // ���������˵�λ��
        Vec2i p0 = vtx[0]->spi;
        Vec2i p1 = vtx[1]->spi;
        Vec2i p2 = vtx[2]->spi;

        // ���������Ϊ0���˳�
        float s = abs(vectorCross(p1 - p0, p2 - p0));
        if (s <= 0) return false;

        // ���������ʱ�����������ı��ϵĵ���Ҫ�������ҷ����·����ϵĵ㲻����
        // ���ж��Ƿ��� TopLeft���жϳ��������·� Edge Equation һ�����
        bool TopLeft01 = isTopLeft(p0, p1);
        bool TopLeft12 = isTopLeft(p1, p2);
        bool TopLeft20 = isTopLeft(p2, p0);

        // ������������Ӿ��ε����е�
        for (int cy = _min_y; cy <= _max_y; cy++) {
            for (int cx = _min_x; cx <= _max_x; cx++) {
                Vec2f px = { (float)cx + 0.5f, (float)cy + 0.5f };

                // Edge Equation
                // ʹ���������⸡�����
                // ����ÿ���㣬������������һ������
                // ����ÿ�������β�ˣ�������ڱߵ����Ļ�����˳���������
                int E01 = -(cx - p0.x) * (p1.y - p0.y) + (cy - p0.y) * (p1.x - p0.x);
                int E12 = -(cx - p1.x) * (p2.y - p1.y) + (cy - p1.y) * (p2.x - p1.x);
                int E20 = -(cx - p2.x) * (p0.y - p2.y) + (cy - p2.y) * (p0.x - p2.x);


                // ��������ϱߣ��� E >= 0 �жϺϷ���������±߾��� E > 0 �жϺϷ�
                // ����ͨ������һ����� 1 ������ < 0 �� <= 0 ��һ��ʽ�ӱ��
                if (E01 < (TopLeft01 ? 0 : 1)) continue;   // �ڵ�һ���ߺ���
                if (E12 < (TopLeft12 ? 0 : 1)) continue;   // �ڵڶ����ߺ���
                if (E20 < (TopLeft20 ? 0 : 1)) continue;   // �ڵ������ߺ���

                // �����˵㵽��ǰ���ʸ��
                Vec2f s0 = vtx[0]->spf - px;
                Vec2f s1 = vtx[1]->spf - px;
                Vec2f s2 = vtx[2]->spf - px;

                // ��������ϵ�������ڲ������������ a / b / c
                float a = abs(vectorCross(s1, s2));    // �������� Px-P1-P2 ���
                float b = abs(vectorCross(s2, s0));    // �������� Px-P2-P0 ���
                float c = abs(vectorCross(s0, s1));    // �������� Px-P0-P1 ���
                float s = a + b + c;                    // �������� P0-P1-P2 ���

                if (s == 0.0f) continue;

                // ������������Ա�֤��a + b + c = 1������������ֵϵ��
                a = a * (1.0f / s);
                b = b * (1.0f / s);
                c = c * (1.0f / s);

                // ���㵱ǰ��� 1/w���� 1/w ����Ļ�ռ�����Թ�ϵ����ֱ�����Ĳ�ֵ
                float rhw = vtx[0]->rhw * a + vtx[1]->rhw * b + vtx[2]->rhw * c;

                // ������Ȳ���
                // ��֮ z ������������ w ����Ȼ�����ͨ���ڽ�����ƽ���Զ����ƽ��֮��ֲ��ظ�ƽ����
                if (rhw < _depth_buffer[cy][cx]) continue;
                _depth_buffer[cy][cx] = rhw;   // ��¼ 1/w ����Ȼ���

                // ��ԭ��ǰ���ص� w
                float w = 1.0f / ((rhw != 0.0f) ? rhw : 1.0f);

                // �������������ֵ varying ��ϵ��
                // �ȳ��Ը��Զ���� w Ȼ�������Ļ�ռ��ֵȻ���ٳ��Ե�ǰ w
                float c0 = vtx[0]->rhw * a * w;
                float c1 = vtx[1]->rhw * b * w;
                float c2 = vtx[2]->rhw * c * w;

                // ׼��Ϊ��ǰ���صĸ��� varying ���в�ֵ
                ShaderContext input;

                ShaderContext& i0 = vtx[0]->context;
                ShaderContext& i1 = vtx[1]->context;
                ShaderContext& i2 = vtx[2]->context;

                // ��ֵ���� varying
                for (auto const& it : i0.varying_float) {
                    int key = it.first;
                    float f0 = i0.varying_float[key];
                    float f1 = i1.varying_float[key];
                    float f2 = i2.varying_float[key];
                    input.varying_float[key] = c0 * f0 + c1 * f1 + c2 * f2;
                }

                for (auto const& it : i0.varying_vec2f) {
                    int key = it.first;
                    const Vec2f& f0 = i0.varying_vec2f[key];
                    const Vec2f& f1 = i1.varying_vec2f[key];
                    const Vec2f& f2 = i2.varying_vec2f[key];
                    input.varying_vec2f[key] = c0 * f0 + c1 * f1 + c2 * f2;
                }

                for (auto const& it : i0.varying_vec3f) {
                    int key = it.first;
                    const Vec3f& f0 = i0.varying_vec3f[key];
                    const Vec3f& f1 = i1.varying_vec3f[key];
                    const Vec3f& f2 = i2.varying_vec3f[key];
                    input.varying_vec3f[key] = c0 * f0 + c1 * f1 + c2 * f2;
                }

                for (auto const& it : i0.varying_vec4f) {
                    int key = it.first;
                    const Vec4f& f0 = i0.varying_vec4f[key];
                    const Vec4f& f1 = i1.varying_vec4f[key];
                    const Vec4f& f2 = i2.varying_vec4f[key];
                    input.varying_vec4f[key] = c0 * f0 + c1 * f1 + c2 * f2;
                }

                // ִ��������ɫ��
                Vec4f color = { 0.0f, 0.0f, 0.0f, 0.0f };

                if (_pixel_shader != NULL) {
                    color = _pixel_shader(input);
                }

                // ���Ƶ� framebuffer �ϣ�������Լ��жϣ���� PS ���ص���ɫ alpha ����
                // С�ڵ�������������ƣ����������Ļ�Ҫ��ǰ��ĸ�����Ȼ���Ĵ���Ų������
                // ֻ����Ҫ��Ⱦ��ʱ��Ÿ�����ȡ�
                _frame_buffer->setPixel(cx, cy, color);
            }
        }

        // �����߿��ٻ�һ�α��⸲��
        if (_render_frame) {
            drawLine(_vertex[0].spi.x, _vertex[0].spi.y, _vertex[1].spi.x, _vertex[1].spi.y);
            drawLine(_vertex[0].spi.x, _vertex[0].spi.y, _vertex[2].spi.x, _vertex[2].spi.y);
            drawLine(_vertex[2].spi.x, _vertex[2].spi.y, _vertex[1].spi.x, _vertex[1].spi.y);
        }

        return true;
    }


protected:

    // ����ṹ��
    struct Vertex {
        ShaderContext context;    // ������
        float rhw;                // w �ĵ���
        Vec4f pos;                // ����
        Vec2f spf;                // ��������Ļ����
        Vec2i spi;                // ������Ļ����
    };

protected:
    Bitmap* _frame_buffer;    // ���ػ���
    float** _depth_buffer;    // ��Ȼ���

    int _fb_width;            // frame buffer ���
    int _fb_height;           // frame buffer �߶�
    uint32_t _color_fg;       // ǰ��ɫ������ʱ����
    uint32_t _color_bg;       // ����ɫ��Clear ʱ����

    Vertex _vertex[3];        // �����ε���������

    int _min_x;               // ��������Ӿ���
    int _min_y;
    int _max_x;
    int _max_y;

    bool _render_frame;       // �Ƿ�����߿�
    bool _render_pixel;       // �Ƿ��������

    VertexShader _vertex_shader;
    PixelShader _pixel_shader;
};

#endif