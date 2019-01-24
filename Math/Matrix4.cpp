#include "Matrix4.h"

#include <glm/gtc/type_ptr.hpp>
#include <math.h>

Matrix4::Matrix4() :
    m_Matrix(),
    m_Parent(nullptr),
    m_Scale(1.0f, 1.0f)
{
    SetIdentity();
}

Matrix4& Matrix4::operator=(glm::mat4& other)
{
    const float* pSource = (const float*)glm::value_ptr(other);

    m_Matrix[0] = pSource[0];
    m_Matrix[1] = pSource[4];
    m_Matrix[2] = pSource[8];
    m_Matrix[3] = pSource[12];

    m_Matrix[4] = pSource[1];
    m_Matrix[5] = pSource[5];
    m_Matrix[6] = pSource[9];
    m_Matrix[7] = pSource[13];

    m_Matrix[8] = pSource[2];
    m_Matrix[9] = pSource[6];
    m_Matrix[10] = pSource[10];
    m_Matrix[11] = pSource[14];

    m_Matrix[12] = pSource[3];
    m_Matrix[13] = pSource[7];
    m_Matrix[14] = pSource[11];
    m_Matrix[15] = pSource[15];

    return *this;
}

void Matrix4::SetIdentity()
{
    m_Matrix[0] = 1.0f;
    m_Matrix[1] = 0.0f;
    m_Matrix[2] = 0.0f;
    m_Matrix[3] = 0.0f;

    m_Matrix[4] = 0.0f;
    m_Matrix[5] = 1.0f;
    m_Matrix[6] = 0.0f;
    m_Matrix[7] = 0.0f;

    m_Matrix[8] = 0.0f;
    m_Matrix[9] = 0.0f;
    m_Matrix[10] = 1.0f;
    m_Matrix[11] = 0.0f;

    m_Matrix[12] = 0.0f;
    m_Matrix[13] = 0.0f;
    m_Matrix[14] = 0.0f;
    m_Matrix[15] = 1.0f;
}

void Matrix4::Translate(const Vector2& vec)
{
    Translate(vec.X, vec.Y);
}

void Matrix4::Translate(float x, float y)
{
    m_Matrix[12] += x;
    m_Matrix[13] += y;
}

void Matrix4::SetPosition(const Vector2& vec)
{
    SetPosition(vec.X, vec.Y);
}

void Matrix4::SetPosition(const Point& point)
{
    SetPosition(point.X, point.Y);
}

void Matrix4::SetPosition(int x, int y)
{
    m_Matrix[12] = static_cast<float>(x);
    m_Matrix[13] = static_cast<float>(y);
}

void Matrix4::SetPosition(float x, float y)
{
    m_Matrix[12] = x;
    m_Matrix[13] = y;
}

void Matrix4::SetPosition(float x, float y, float z)
{
    m_Matrix[12] = x;
    m_Matrix[13] = y;
    m_Matrix[14] = z;
}

void Matrix4::SetPosition_Z(float z)
{
    m_Matrix[14] = z;
}

void Matrix4::Scale_Local(const Vector2& vec)
{
    Scale_Local(vec.X, vec.Y);
}

void Matrix4::Scale_Local(float x, float y)
{
    m_Matrix[0] *= x;
    m_Matrix[1] *= y;
                
    m_Matrix[4] *= x;
    m_Matrix[5] *= y;
                
    m_Matrix[8] *= x;
    m_Matrix[9] *= y;

    m_Scale.X *= x;
    m_Scale.Y *= y;
}

void Matrix4::SetScale_Local(const Vector2& vec)
{
    SetScale_Local(vec.X, vec.Y);
}

void Matrix4::SetScale_Local(float x, float y)
{
    m_Matrix[0] = (m_Matrix[0] / m_Scale.X) * x;
    m_Matrix[1] = (m_Matrix[1] / m_Scale.Y) * y;

    m_Matrix[4] = (m_Matrix[4] / m_Scale.X) * x;
    m_Matrix[5] = (m_Matrix[5] / m_Scale.Y) * y;

    m_Matrix[8] = (m_Matrix[8] / m_Scale.X) * x;
    m_Matrix[9] = (m_Matrix[9] / m_Scale.Y) * y;

    m_Scale.X = x;
    m_Scale.Y = y;
}

void Matrix4::SetRotation(float theta)
{
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    m_Matrix[0] = cosTheta;
    m_Matrix[1] = sinTheta;

    m_Matrix[4] = -sinTheta;
    m_Matrix[5] = cosTheta;
}

void Matrix4::Rotate(float theta)
{
    Matrix4 rotationMatrix;

    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    rotationMatrix[0] = cosTheta;
    rotationMatrix[1] = sinTheta;

    rotationMatrix[4] = -sinTheta;
    rotationMatrix[5] = cosTheta;

    *this *= rotationMatrix;
}

float Matrix4::CalculateDeterminant() const 
{
    float a1 = m_Matrix[5] * ((m_Matrix[10] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[11]));
    float a2 = m_Matrix[6] * ((m_Matrix[9] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[11]));
    float a3 = m_Matrix[7] * ((m_Matrix[9] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[10]));
    float a = a1 - a2 + a3;  
                             
    float b1 = m_Matrix[4] * ((m_Matrix[10] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[11]));
    float b2 = m_Matrix[6] * ((m_Matrix[8] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[11]));
    float b3 = m_Matrix[7] * ((m_Matrix[8] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[10]));
    float b = b1 - b2 + b3;  
                             
    float c1 = m_Matrix[4] * ((m_Matrix[9] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[11]));
    float c2 = m_Matrix[5] * ((m_Matrix[8] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[11]));
    float c3 = m_Matrix[7] * ((m_Matrix[8] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[9]));
    float c = c1 - c2 + c3;

    float d1 = m_Matrix[4] * ((m_Matrix[9] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[10]));
    float d2 = m_Matrix[5] * ((m_Matrix[8] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[10]));
    float d3 = m_Matrix[6] * ((m_Matrix[8] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[9]));
    float d = d1 - d2 + d3;

    float det = (m_Matrix[0] * a) - (m_Matrix[1] * b) + (m_Matrix[2] * c) - (m_Matrix[3] * d);
    return det;
}

Matrix4 Matrix4::CalculateCofactors() const 
{
    // Row 1
    float a1 = m_Matrix[5] * ((m_Matrix[10] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[11]));
    float a2 = m_Matrix[6] * ((m_Matrix[9] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[11]));
    float a3 = m_Matrix[7] * ((m_Matrix[9] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[10]));
    float a = a1 - a2 + a3;

    float b1 = m_Matrix[4] * ((m_Matrix[10] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[11]));
    float b2 = m_Matrix[6] * ((m_Matrix[8] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[11]));
    float b3 = m_Matrix[7] * ((m_Matrix[8] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[10]));
    float b = b1 - b2 + b3;

    float c1 = m_Matrix[4] * ((m_Matrix[9] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[11]));
    float c2 = m_Matrix[5] * ((m_Matrix[8] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[11]));
    float c3 = m_Matrix[7] * ((m_Matrix[8] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[9]));
    float c = c1 - c2 + c3;

    float d1 = m_Matrix[4] * ((m_Matrix[9] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[10]));
    float d2 = m_Matrix[5] * ((m_Matrix[8] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[10]));
    float d3 = m_Matrix[6] * ((m_Matrix[8] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[9]));
    float d = d1 - d2 + d3;

    // Row 2
    float e1 = m_Matrix[1] * ((m_Matrix[10] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[11]));
    float e2 = m_Matrix[2] * ((m_Matrix[9] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[11]));
    float e3 = m_Matrix[3] * ((m_Matrix[9] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[10]));
    float e = e1 - e2 + e3;

    float f1 = m_Matrix[0] * ((m_Matrix[10] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[11]));
    float f2 = m_Matrix[2] * ((m_Matrix[8] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[11]));
    float f3 = m_Matrix[3] * ((m_Matrix[8] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[10]));
    float f = f1 - f2 + f3;

    float g1 = m_Matrix[0] * ((m_Matrix[9] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[11]));
    float g2 = m_Matrix[1] * ((m_Matrix[8] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[11]));
    float g3 = m_Matrix[3] * ((m_Matrix[8] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[9]));
    float g = g1 - g2 + g3;

    float h1 = m_Matrix[0] * ((m_Matrix[9] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[10]));
    float h2 = m_Matrix[1] * ((m_Matrix[8] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[10]));
    float h3 = m_Matrix[2] * ((m_Matrix[8] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[9]));
    float h = h1 - h2 + h3;

    // Row 3
    float i1 = m_Matrix[1] * ((m_Matrix[6]* m_Matrix[15]) - (m_Matrix[14] * m_Matrix[7]));
    float i2 = m_Matrix[2] * ((m_Matrix[5] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[7]));
    float i3 = m_Matrix[3] * ((m_Matrix[5] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[6]));
    float i = i1 - i2 + i3;

    float j1 = m_Matrix[0] * ((m_Matrix[6] * m_Matrix[15]) - (m_Matrix[14] * m_Matrix[7]));
    float j2 = m_Matrix[2] * ((m_Matrix[4] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[7]));
    float j3 = m_Matrix[3] * ((m_Matrix[4] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[6]));
    float j = j1 - j2 + j3;

    float k1 = m_Matrix[0] * ((m_Matrix[5] * m_Matrix[15]) - (m_Matrix[13] * m_Matrix[7]));
    float k2 = m_Matrix[1] * ((m_Matrix[4] * m_Matrix[15]) - (m_Matrix[12] * m_Matrix[7]));
    float k3 = m_Matrix[3] * ((m_Matrix[4] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[5]));
    float k = k1 - k2 + k3;

    float l1 = m_Matrix[0] * ((m_Matrix[5] * m_Matrix[14]) - (m_Matrix[13] * m_Matrix[6]));
    float l2 = m_Matrix[1] * ((m_Matrix[4] * m_Matrix[14]) - (m_Matrix[12] * m_Matrix[6]));
    float l3 = m_Matrix[2] * ((m_Matrix[4] * m_Matrix[13]) - (m_Matrix[12] * m_Matrix[5]));
    float l = l1 - l2 + l3;

    //Row 4
    float m1 = m_Matrix[1] * ((m_Matrix[6] * m_Matrix[11]) - (m_Matrix[10] * m_Matrix[7]));
    float m2 = m_Matrix[2] * ((m_Matrix[5] * m_Matrix[11]) - (m_Matrix[9] * m_Matrix[7]));
    float m3 = m_Matrix[3] * ((m_Matrix[5] * m_Matrix[10]) - (m_Matrix[9] * m_Matrix[6]));
    float m = m1 - m2 + m3;

    float n1 = m_Matrix[0] * ((m_Matrix[6] * m_Matrix[11]) - (m_Matrix[10] * m_Matrix[7]));
    float n2 = m_Matrix[2] * ((m_Matrix[4] * m_Matrix[11]) - (m_Matrix[8] * m_Matrix[7]));
    float n3 = m_Matrix[3] * ((m_Matrix[4] * m_Matrix[10]) - (m_Matrix[8] * m_Matrix[6]));
    float n = n1 - n2 + n3;

    float o1 = m_Matrix[0] * ((m_Matrix[5] * m_Matrix[11]) - (m_Matrix[9] * m_Matrix[7]));
    float o2 = m_Matrix[1] * ((m_Matrix[4] * m_Matrix[11]) - (m_Matrix[8] * m_Matrix[7]));
    float o3 = m_Matrix[3] * ((m_Matrix[4] * m_Matrix[9]) - (m_Matrix[8] * m_Matrix[5]));
    float o = o1 - o2 + o3;

    float p1 = m_Matrix[0] * ((m_Matrix[5] * m_Matrix[10]) - (m_Matrix[9] * m_Matrix[6]));
    float p2 = m_Matrix[1] * ((m_Matrix[4] * m_Matrix[10]) - (m_Matrix[8] * m_Matrix[6]));
    float p3 = m_Matrix[2] * ((m_Matrix[4] * m_Matrix[9]) - (m_Matrix[8] * m_Matrix[5]));
    float p = p1 - p2 + p3;

    Matrix4 cofactors;
    cofactors[0] = a;
    cofactors[1] = -b;
    cofactors[2] = c;
    cofactors[3] = -d;

    cofactors[4] = -e;
    cofactors[5] = f;
    cofactors[6] = -g;
    cofactors[7] = h;

    cofactors[8] = i;
    cofactors[9] = -j;
    cofactors[10] = k;
    cofactors[11] = -l;

    cofactors[12] = -m;
    cofactors[13] = n;
    cofactors[14] = -o;
    cofactors[15] = p;

    return cofactors;
}

Matrix4 Matrix4::CalculateInverse() const
{
    float det = CalculateDeterminant();

    Matrix4 inverse = CalculateCofactors();
    inverse.Transpose();
    inverse *= (1.0f/det);

    return inverse;
}

void Matrix4::Transpose()
{
    Swap(1, 4);
    Swap(8, 2);
    Swap(9, 6);
    Swap(12, 3);
    Swap(13, 7);
    Swap(14, 11);
}

void Matrix4::Swap(int i, int j)
{
    float temp = m_Matrix[i];
    m_Matrix[i] = m_Matrix[j];
    m_Matrix[j] = temp;
}

Vector2 Matrix4::GetPosition() const { return ResolveParents().GetPosition_Local(); }

Vector2 Matrix4::GetPosition_Local() const { return Vector2(m_Matrix[12], m_Matrix[13]); }
Vector2 Matrix4::GetForward() const { return Vector2(m_Matrix[8], m_Matrix[9]); }
Vector2 Matrix4::GetRight() const { return Vector2(m_Matrix[0], m_Matrix[1]); }
Vector2 Matrix4::GetScale() const { return m_Scale; }

Vector3 Matrix4::GetPosition_3() const { return Vector3(m_Matrix[12], m_Matrix[13], m_Matrix[14]); }
Vector3 Matrix4::GetForward_3() const { return Vector3(m_Matrix[8], m_Matrix[9], m_Matrix[10]); }
Vector3 Matrix4::GetRight_3() const { return Vector3(m_Matrix[0], m_Matrix[1], m_Matrix[2]); }

Matrix4 Matrix4::ResolveParents() const
{
    Matrix4 output(*this);
    output.SetParent(nullptr);

    const Matrix4* parent = m_Parent;
    while (parent != nullptr)
    {
        output *= *parent;
        parent = parent->m_Parent;
    }

    return output;
}

const std::array<float, 16>& Matrix4::Data() const 
{
    return m_Matrix;
}

float Matrix4::operator[](int i) const
{
    return m_Matrix[i];
}

float& Matrix4::operator[](int i)
{
    return m_Matrix[i];
}

void Matrix4::SetParent(const Matrix4* parent) { m_Parent = parent; }
void Matrix4::SetParent(const Matrix4& parent) { m_Parent = &parent; }

Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
    Matrix4 output(*this);
    output.m_Parent = nullptr;

    output[0] = (m_Matrix[0] * rhs[0]) + (m_Matrix[1] * rhs[4]) + (m_Matrix[2] * rhs[8]) + (m_Matrix[3] * rhs[12]);
    output[1] = (m_Matrix[0] * rhs[1]) + (m_Matrix[1] * rhs[5]) + (m_Matrix[2] * rhs[9]) + (m_Matrix[3] * rhs[13]);
    output[2] = (m_Matrix[0] * rhs[2]) + (m_Matrix[1] * rhs[6]) + (m_Matrix[2] * rhs[10]) + (m_Matrix[3] * rhs[14]);
    output[3] = (m_Matrix[0] * rhs[3]) + (m_Matrix[1] * rhs[7]) + (m_Matrix[2] * rhs[11]) + (m_Matrix[3] * rhs[15]);

    output[4] = (m_Matrix[4] * rhs[0]) + (m_Matrix[5] * rhs[4]) + (m_Matrix[6] * rhs[8]) + (m_Matrix[7] * rhs[12]);
    output[5] = (m_Matrix[4] * rhs[1]) + (m_Matrix[5] * rhs[5]) + (m_Matrix[6] * rhs[9]) + (m_Matrix[7] * rhs[13]);
    output[6] = (m_Matrix[4] * rhs[2]) + (m_Matrix[5] * rhs[6]) + (m_Matrix[6] * rhs[10]) + (m_Matrix[7] * rhs[14]);
    output[7] = (m_Matrix[4] * rhs[3]) + (m_Matrix[5] * rhs[7]) + (m_Matrix[6] * rhs[11]) + (m_Matrix[7] * rhs[15]);

    output[8] = (m_Matrix[8] * rhs[0]) + (m_Matrix[9] * rhs[4]) + (m_Matrix[10] * rhs[8]) + (m_Matrix[11] * rhs[12]);
    output[9] = (m_Matrix[8] * rhs[1]) + (m_Matrix[9] * rhs[5]) + (m_Matrix[10] * rhs[9]) + (m_Matrix[11] * rhs[13]);
    output[10] = (m_Matrix[8] * rhs[2]) + (m_Matrix[9] * rhs[6]) + (m_Matrix[10] * rhs[10]) + (m_Matrix[11] * rhs[14]);
    output[11] = (m_Matrix[8] * rhs[3]) + (m_Matrix[9] * rhs[7]) + (m_Matrix[10] * rhs[11]) + (m_Matrix[11] * rhs[15]);

    output[12] = (m_Matrix[12] * rhs[0]) + (m_Matrix[13] * rhs[4]) + (m_Matrix[14] * rhs[8]) + (m_Matrix[15] * rhs[12]);
    output[13] = (m_Matrix[12] * rhs[1]) + (m_Matrix[13] * rhs[5]) + (m_Matrix[14] * rhs[9]) + (m_Matrix[15] * rhs[13]);
    output[14] = (m_Matrix[12] * rhs[2]) + (m_Matrix[13] * rhs[6]) + (m_Matrix[14] * rhs[10]) + (m_Matrix[15] * rhs[14]);
    output[15] = (m_Matrix[12] * rhs[3]) + (m_Matrix[13] * rhs[7]) + (m_Matrix[14] * rhs[11]) + (m_Matrix[15] * rhs[15]);

    return output;
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    *this = *this * rhs;
    return *this;
}

Matrix4 Matrix4::operator*(float rhs) const
{
    Matrix4 mat(*this);
    mat.m_Parent = nullptr;

    mat[0] *= rhs;
    mat[1] *= rhs;
    mat[2] *= rhs;
    mat[3] *= rhs;
                
    mat[4] *= rhs;
    mat[5] *= rhs;
    mat[6] *= rhs;
    mat[7] *= rhs;
                
    mat[8] *= rhs;
    mat[9] *= rhs;
    mat[10] *= rhs;
    mat[11] *= rhs;
                 
    mat[12] *= rhs;
    mat[13] *= rhs;
    mat[14] *= rhs;
    mat[15] *= rhs;

    return mat;
}

Matrix4& Matrix4::operator*=(float rhs)
{
    *this = *this * rhs;
    return *this;
}

Matrix4 Matrix4::Ortho(float left, float right, float top, float bottom, float near, float far)
{
    Matrix4 ortho;

    ortho[0] = 2.0f / (right - left);
    ortho[1] = 0.0f;
    ortho[2] = 0.0f;
    ortho[3] = -((right + left) / (right - left));

    ortho[4] = 0.0f;
    ortho[5] = 2 / (top - bottom);
    ortho[6] = 0.0f;
    ortho[7] = -((top + bottom) / (top - bottom));

    ortho[8] = 0.0f;
    ortho[9] = 0.0f;
    ortho[10] = -(2.0f / (near - far));
    ortho[11] = -((far + near) / (far - near));

    ortho[12] = 0.0f;
    ortho[13] = 0.0f;
    ortho[14] = 0.0f;
    ortho[15] = 1.0f;

    return ortho;
}

glm::mat4 Matrix4::AsGlmMat4() const
{
    glm::mat4 mat = glm::make_mat4(m_Matrix.data());
    return mat;
}

glm::mat4 Matrix4::AsGlmLookAt() const
{
    Matrix4 tran(*this);

    tran[12] *= -1;
    tran[13] *= -1;
    tran[14] *= -1;

    glm::mat4 mat = glm::make_mat4(tran.Data().data());

    return mat;
}

Vector4 operator*(const Vector4& lhs, const Matrix4& rhs)
{
    float x = (rhs[0] * lhs.X) + (rhs[4] * lhs.Y) + (rhs[8] * lhs.Z) + (rhs[12] * lhs.W);
    float y = (rhs[1] * lhs.X) + (rhs[5] * lhs.Y) + (rhs[7] * lhs.Z) + (rhs[13] * lhs.W);
    float z = (rhs[2] * lhs.X) + (rhs[6] * lhs.Y) + (rhs[8] * lhs.Z) + (rhs[14] * lhs.W);
    float w = (rhs[3] * lhs.X) + (rhs[7] * lhs.Y) + (rhs[9] * lhs.Z) + (rhs[15] * lhs.W);

    return Vector4(x, y, z, w);
}