#pragma once

#include <vector>

template <typename T>
class Vector2D
{
    public:
        Vector2D() :
            m_Size(0,0)
        {}

        Vector2D(size_t size_x, size_t size_y) :
            m_Size(0,0)
        {
            Resize(size_x, size_y);
        }

        ~Vector2D() = default;
        Vector2D(const Vector2D&) = default;
        Vector2D& operator=(const Vector2D&) = default;
        Vector2D(Vector2D&&) noexcept = default;
        Vector2D& operator=(Vector2D&&) noexcept = default;

        std::vector<T>& operator[](size_t index) { return m_Data[index]; }
        const std::vector<T>& operator[](size_t index) const { return m_Data[index]; }

        void Resize(size_t size_x, size_t size_y)
        {
            m_Data.resize(size_x);
            for (std::vector<T>& vec : m_Data)
            {
                vec.resize(size_y);
            }

            m_Size.X = size_x;
            m_Size.Y = size_y;
        }

        void Emplace(size_t x, size_t y, T&& obj)
        {
            assert(x < m_Size.X);
            assert(y < m_Size.Y);

            if (x < m_Size.X+1 && y < m_Size.Y+1)
            {
                m_Data[x][y].emplace_back(std::move(obj));
            }
            else
            {
                printf("Index (%i,%i) is out of bounds");
            }
        }

        void Remove(size_t x, size_t y)
        {
            assert(x < m_Size.X);
            assert(y < m_Size.Y);

            if (x < m_Size.X+1 && y < m_Size.Y+1)
            {
                m_Data[x].remove(y);
            }
        }

        uPoint Size() const { return m_Size; }

    private:

        uPoint m_Size;
        std::vector<std::vector<T>> m_Data;

};
