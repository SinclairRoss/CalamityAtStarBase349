#pragma once

#include <string>

#include "Core\Math\Matrix4.h"
#include "Core\Renderables\Sprite.h"

#include "Core\Utils\ColourLibrary.h"

class Collider
{
    public:
        Collider(const Matrix4& parent, std::string& highlight, bool highlightOn = false, Colour colour = ColourLibrary::White);
        virtual ~Collider() = default;

        Collider(const Collider&) = default;
        Collider& operator= (const Collider&) = default;

        Collider(Collider&& other) noexcept;
        Collider& operator= (Collider&& other) noexcept;

        Matrix4& GetTransform();
        const Matrix4& GetTransform() const;
        
        Vector2 GetPosition() const;

        void OnMoveOperation(const Matrix4* parent);
        void OnMoveOperation(const Matrix4& parent);

    protected:
        Matrix4 m_Transform;
        Sprite m_Highlight;
};