#pragma once

#include <array>

template<typename T, size_t size>
class Vector
{};

template <typename T, size_t size>
class VectorBase
{
public:

    VectorBase() = default;
    VectorBase(std::array<T, size>&& lhs) : m_Data(std::forward<std::array<T, size>>(lhs)) {}
    VectorBase(const std::array<T, size>& data) : m_Data(data) {}

    virtual ~VectorBase() = default;

    VectorBase<T, size>(const VectorBase<T, size>&) noexcept = default;
    VectorBase<T, size>& operator=(const VectorBase<T, size>&) noexcept = default;

    VectorBase<T, size>(VectorBase<T, size>&&) noexcept = default;
    VectorBase<T, size>& operator=(VectorBase<T, size>&&) noexcept = default;

    float CalculateLength_Sqr() const
    {
        float lengthSqr = 0.0f;
        for (const T& comp : m_Data) { lengthSqr += (comp*comp); }

        return lengthSqr;
    }

    float CalculateLength() const
    {
        float length = sqrt(CalculateLength_Sqr());
        return length;
    }

    void Normalise()
    {
        float length = CalculateLength();

        if (abs(length) > 0.00001f)
        {
            for (T& lhs : m_Data) { lhs /= length; }
        }
        else
        {
            m_Data.fill(0.0f);
        }
    }

    Vector<T, size> operator+ (const Vector<T, size>& rhs) const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] += rhs[i]; }

        return Vector<T, size>(std::move(lhs));
    }

    Vector<T, size> operator- (const Vector<T, size>& rhs) const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] -= rhs[i]; }

        return Vector<T, size>(std::move(lhs));
    }

    Vector<T, size> operator-() const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] = -lhs[i]; }

        return Vector<T, size>(std::move(lhs));
    }

    Vector<T, size> operator* (const Vector<T, size>& rhs) const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] *= rhs[i]; }

        return Vector<T, size>(std::move(lhs));
    }

    Vector<T, size> operator* (float rhs) const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] *= rhs; }

        return Vector<T, size>(std::move(lhs));
    }

    Vector<T, size> operator/ (const Vector<T, size>& rhs) const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] /= rhs[i]; }

        return Vector<T, size>(std::move(lhs));
    }

    Vector<T, size> operator/ (float rhs) const
    {
        std::array<T, size> lhs = m_Data;
        for (int i = 0; i < size; ++i) { lhs[i] /= rhs; }

        return Vector<T, size>(std::move(lhs));
    }

    float Dot(const Vector<T, size>& other) const
    {
        float dot = 0.0f;
        for (int i = 0; i < size; ++i)
        {
            dot += m_Data[i] * other[i];
        }
    
        return dot;
    }

    T operator[](int i) const { return m_Data[i]; }
    T& operator[](int i) { return m_Data[i]; }

    const T* const Data() const { return m_Data.data(); }

protected:
    std::array<T, size> m_Data;
};

template<typename T, size_t size>
Vector<T, size> operator+=(Vector<T, size>& lhs, const Vector<T, size>& rhs)
{
    for (int i = 0; i < size; ++i) { lhs[i] += rhs[i]; }
    return lhs;
}

template<typename T, size_t size>
Vector<T, size> operator-=(Vector<T, size>& lhs, const Vector<T, size>& rhs)
{
    for (int i = 0; i < size; ++i) { lhs[i] -= rhs[i]; }
    return lhs;
}

template<typename T, size_t size>
Vector<T, size> operator*=(Vector<T, size>& lhs, const Vector<T, size>& rhs)
{
    for (int i = 0; i < size; ++i) { lhs[i] *= rhs[i]; }
    return lhs;
}

template<typename T, size_t size>
Vector<T, size> operator*=(Vector<T, size>& lhs, float rhs)
{
    for (int i = 0; i < size; ++i) { lhs[i] *= rhs; }
    return lhs;
}

template<typename T, size_t size>
Vector<T, size> operator/=(Vector<T, size>& lhs, const Vector<T, size>& rhs)
{
    for (int i = 0; i < size; ++i) { lhs[i] /= rhs[i]; }
    return lhs;
}

template<typename T, size_t size>
Vector<T, size> operator/=(Vector<T, size>& lhs, float rhs)
{
    for (int i = 0; i < size; ++i) { lhs[i] /= rhs; }
    return lhs;
}

template<>
class Vector<float, 2> : public VectorBase<float, 2>
{
public:
    Vector() : 
        VectorBase({ 0,0 }),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector(float x, float y) :
        VectorBase({ x, y }),   
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector(const Vector<float, 2>& other) :
        VectorBase(other.m_Data),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector<float, 2>& operator=(const Vector<float, 2>& other)
    {
        if (this != &other)
        {
            VectorBase::operator=(other);
        }

        return *this;
    }

    Vector(std::array<float, 2>&& data) : 
        VectorBase(std::forward <std::array<float, 2>>(data)),  
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector(Vector<float, 2>&& other) noexcept :
    VectorBase(std::move(other)),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector<float, 2>& operator=(Vector<float, 2>&& other) noexcept
    {
        if (this != &other)
        {
            VectorBase::operator=(std::move(other));
        }

        return *this;
    }

    float& X;
    float& Y;
};

template<>
class Vector<float, 3> : public VectorBase<float, 3>
{
public:
    Vector() : 
        VectorBase({ 0,0,0 }),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2])
    {};

    Vector(float x, float y, float z) : 
        VectorBase({ x, y, z }),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2])
    {}

    Vector(const Vector<float, 3>& other) :
        VectorBase(other.m_Data),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2])
    {}

    Vector<float, 3>& operator=(const Vector<float, 3>& other)
    {
        if (this != &other)
        {
            VectorBase::operator=(other);
        }

        return *this;
    }

    Vector(std::array<float, 3>&& data) : 
        VectorBase(std::forward<std::array<float, 3>>(data)),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2])
    {}

    Vector(Vector<float, 3>&& other) noexcept :
    VectorBase(std::move(other)),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2])
    {}

    Vector<float, 3>& operator=(Vector<float, 3>&& other) noexcept
    {
        if (this != &other)
        {
            VectorBase::operator=(std::move(other));
        }

        return *this;
    }

    float& X;
    float& Y;
    float& Z;
};

template<>
class Vector<float, 4> : public VectorBase<float, 4>
{
public:
    Vector() : VectorBase({ 0,0,0,0 }),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2]),
        W(m_Data[3])
    {}

    Vector(float x, float y, float z, float w) : VectorBase({ x, y, z, w }),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2]),
        W(m_Data[3])
    {}

    Vector(const Vector<float, 4>& other) :
        VectorBase(other.m_Data),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2]),
        W(m_Data[3])
    {}

    Vector<float, 4>& operator=(const Vector<float, 4>& other)
    {
        if (this != &other)
        {
            VectorBase::operator=(other);
        }

        return *this;
    }

    Vector(std::array<float, 4>&& data) : VectorBase(std::forward<std::array<float, 4>>(data)),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2]),
        W(m_Data[3])
    {}

    Vector(Vector<float, 4>&& other) noexcept :
    VectorBase(std::move(other)),
        X(m_Data[0]),
        Y(m_Data[1]),
        Z(m_Data[2]),
        W(m_Data[3])
    {}

    Vector<float, 4>& operator=(Vector<float, 4>&& other) noexcept
    {
        if (this != &other)
        {
            VectorBase::operator=(std::move(other));
        }

        return *this;
    }

    float& X;
    float& Y;
    float& Z;
    float& W;
};

template<>
class Vector<int, 2> : public VectorBase<int, 2>
{
public:
    Vector() : 
        VectorBase({ 0,0 }),
        X(m_Data[0]),
        Y(m_Data[1]) 
    {};

    Vector(int x, int y) : 
        VectorBase({ x, y }),
        X(m_Data[0]),
        Y(m_Data[1]) 
    {}

    Vector(const Vector<int, 2>& other) :
        VectorBase(other.m_Data),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector<int, 2>& operator=(const Vector<int, 2>& other)
    {
        if (this != &other)
        {
            VectorBase::operator=(other);
        }

        return *this;
    }

    Vector(Vector<int, 2>&& other) noexcept :
    VectorBase(std::move(other)),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector<int, 2>& operator=(Vector<int, 2>&& other) noexcept
    {
        if (this != &other)
        {
            VectorBase::operator=(std::move(other));
        }

        return *this;
    }

    int& X;
    int& Y;
};

template<>
class Vector<unsigned int, 2> : public VectorBase<unsigned int, 2>
{
public:
    Vector() : 
        VectorBase({0,0}),
        X(m_Data[0]),
        Y(m_Data[1])
    {};

    Vector(unsigned int x, unsigned int y) : 
        VectorBase({ x, y }),
        X(m_Data[0]),
        Y(m_Data[1]) 
    {}

    Vector(const Vector<unsigned int, 2>& other) :
        VectorBase(other.m_Data),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector<unsigned int, 2>& operator=(const Vector<unsigned int, 2>& other)
    {
        if (this != &other)
        {
            VectorBase::operator=(other);
        }

        return *this;
    }

    Vector(Vector<unsigned int, 2>&& other) noexcept :
    VectorBase(std::move(other)),
        X(m_Data[0]),
        Y(m_Data[1])
    {}

    Vector<unsigned int, 2>& operator=(Vector<unsigned int, 2>&& other) noexcept
    {
        if (this != &other)
        {
            VectorBase::operator=(std::move(other));
        }

        return *this;
    }

    unsigned int& X;
    unsigned int& Y;
};

using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;
using Point = Vector<int, 2>;
using uPoint = Vector<unsigned int, 2>;