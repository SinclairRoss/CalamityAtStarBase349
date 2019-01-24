#pragma once

#include <array>

#include "glm/glm.hpp"

#include "Vector.h"

class Matrix4
{
    public:
        Matrix4();
        ~Matrix4() = default;

        Matrix4(const Matrix4& other) = default;
        Matrix4& operator=(const Matrix4& other) = default;

        Matrix4(Matrix4&& other) noexcept = default;
        Matrix4& operator=(Matrix4&& other) noexcept = default;

        Matrix4& Matrix4::operator=(glm::mat4& other);

        void SetIdentity();

        const std::array<float, 16>& Data() const;
        Matrix4 ResolveParents() const;

        void Translate(const Vector2& vec);
        void Translate(float x, float y);
        void SetPosition(const Vector2& vec);
        void SetPosition(const Point& point);
        void SetPosition(float x, float y);
        void SetPosition(float x, float y, float z);
        void SetPosition(int x, int y);
        void SetPosition_Z(float z);
        void Scale_Local(const Vector2& vec);
        void Scale_Local(float x, float y);
        void SetScale_Local(const Vector2& vec);
        void SetScale_Local(float x, float y);
        void SetRotation(float theta);
        void Rotate(float theta);

        float CalculateDeterminant() const;
        Matrix4 CalculateCofactors() const;
        Matrix4 CalculateInverse() const;
        void Transpose();

        Matrix4& operator*=(const Matrix4& rhs);
        Matrix4 operator*(const Matrix4& rhs) const;
        Matrix4& operator*=(float rhs);
        Matrix4 operator*(float rhs) const;

        Vector2 GetPosition() const;
        Vector2 GetPosition_Local() const;
        Vector2 GetForward() const;
        Vector2 GetRight() const;
        Vector2 GetScale() const;

        Vector3 GetPosition_3() const;
        Vector3 GetForward_3() const;
        Vector3 GetRight_3() const;

        float operator[](int i) const;
        float& operator[](int i);

        void SetParent(const Matrix4* parent);
        void SetParent(const Matrix4& parent);

        static Matrix4 Ortho(float left, float right, float top, float bottom, float near, float far);

        glm::mat4 AsGlmMat4() const;
        glm::mat4 AsGlmLookAt() const;

    private:
        void Swap(int i, int j);

        std::array<float, 16> m_Matrix;

        const Matrix4* m_Parent;

        Vector2 m_Scale;
};

extern Vector4 operator*(const Vector4& lhs, const Matrix4& rhs);