// name: GameObject
// date: 05/01/2017
// Note: A basic entity can exist within the game world. Contains only the absolute basic information needed to draw.

#pragma once

#include "Core\Math\Matrix4.h"
#include "Core\RenderPackage\DisplayLayer.h"
#include "Core\RenderRegister\ObjectRenderRegister.h"
#include "Core\Utils\Colour.h"

class Sprite
{
	public:
        Sprite(DisplayLayer displayLayer, int textureID, float x = 0.0f, float y = 0.0f);
        ~Sprite();

        Sprite(const Sprite&) = default;
        Sprite& operator=(const Sprite&) = default;

        Sprite(Sprite&&) noexcept;
        Sprite& operator=(Sprite&&) noexcept;

		virtual void Update();

        const Matrix4& GetTransform() const;
        int GetTextureID() const;

        void SetParentTransform(const Matrix4* parent);

        void SetPosition(float x, float y);
        void SetPosition(int x, int y);
        void SetPosition(const Vector2& pos);
        void SetPosition(const Point& pos);

		void Translate(float x, float y);
		void Translate(int x, int y);
		void Translate(const Vector2& deltaVec);
		void Translate(const Point& deltaVec);
   
        void SetZDepth(float z);

        void SetScale(float x, float y);
        void SetScale(int x, int y);
        void SetScale(const Vector2& scale);
        void SetScale(const Point& scale);

        void SetRotation(float theta);
        void Rotate(float theta);

        void SetTextureID(int textureID);

        void SetColour(const Colour& colour);
        void SetAlpha(float a);

        const Colour& GetColour() const;

		const Vector2 GetPosition() const;
        DisplayLayer GetDisplayLayer() const;

        void Register();
        void Deregister();

        Matrix4& GetTransform();

    private:
        DisplayLayer m_DisplayLayer;

        Matrix4 m_Transform;
        Colour m_Colour;
        int m_TextureID;

        bool m_IsRegistered;
};
