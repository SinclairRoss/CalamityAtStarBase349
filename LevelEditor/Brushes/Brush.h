#pragma once

#include "Core\Math\MathsHelper.h"

#include <memory>

#include "Core\Renderables\Sprite.h"
#include "GameConstants\GameConstants.h"
#include "Map\Map.h"
#include "Core\Physics\Collisions\ColliderRegister\InteractionBoundsRegister.h"
#include "GameObjects\Interactables\Interactable.h"
#include "GameConstants\TileData\Utils\BrushTypes.h"

class BrushBase
{
    public:
        virtual void BrushSelected() = 0;
        virtual void BrushDeselected() = 0;
       
        virtual void NextElement() = 0;
        virtual void PreviousElement() = 0;
       
        virtual void SelectElement(std::string& name) = 0;
       
        virtual void SetPosition(const Vector2& cursorPos) = 0;
        virtual const Vector2& GetPosition() const = 0;
       
        virtual int GetRotationIndex() const = 0;
        virtual void RotateClockwise() = 0;
        virtual void RotateCounterClockwise() = 0;
        virtual void SetRotationIndex(int index) = 0;
       
        virtual void CreateObject(Map& map, int mapLevel) = 0;
        virtual void DestroyObject(Map& map, int mapLevel) = 0;
};

template <typename T>
class Brush : public BrushBase
{
    public:
        Brush() :
            m_ElementIndexWrapThreshold(GameConstants::TileData.GetElementCount<BrushType<T>::ElementData>() - 1),
            m_RotationIndex(0),
            m_Position(),
            m_Cursor(DisplayLayer::FLOOR, GameConstants::TextureData.GetIDWithName("Texture_Blank"), 0, 0),
            m_pElementData(GameConstants::TileData.GetElementDataWithID<BrushType<T>::ElementData>(0))
        {
            m_Cursor.Deregister();
        }

        void BrushSelected() override
        {
            m_Cursor.SetTextureID(m_pElementData->GetTextureID());
            m_Cursor.Register();
        }

        void BrushDeselected() override
        {
            m_Cursor.Deregister();
        }

        void NextElement() override
        {
            m_ElementIndex = MathsHelper::Wrap(m_ElementIndex + 1, 0, m_ElementIndexWrapThreshold);
            SelectElement(m_ElementIndex);

            m_Cursor.SetTextureID(m_pElementData->GetTextureID());
        }

        void PreviousElement() override
        {
            m_ElementIndex = MathsHelper::Wrap(m_ElementIndex - 1, 0, m_ElementIndexWrapThreshold);
            SelectElement(m_ElementIndex);

            m_Cursor.SetTextureID(m_pElementData->GetTextureID());
        }

        void SelectElement(std::string& name) override
        {
            int id = GameConstants::TileData.GetElementIDWithName<BrushType<T>::ElementData>(name);
            SelectElement(id);
        }

        void SelectElement(int index)
        {
            m_pElementData = GameConstants::TileData.GetElementDataWithID<BrushType<T>::ElementData>(index);
        }

        // Position
        void SetPosition(const Vector2& cursorPos) override
        {
            m_Position = cursorPos;
            m_Cursor.SetPosition(cursorPos);
        }
        const Vector2& GetPosition() const override { return m_Position; }

        // Rotation Index
        int GetRotationIndex() const override { return m_RotationIndex; }
        void RotateClockwise() override { SetRotationIndex(m_RotationIndex - 1); }
        void RotateCounterClockwise() override { SetRotationIndex(m_RotationIndex + 1); }
        void SetRotationIndex(int index) override
        {
            m_RotationIndex = MathsHelper::Wrap(index, 0, 3);
            m_Cursor.SetRotation(MathsHelper::PIOver2 * m_RotationIndex);
        }

        void CreateObject(Map& map, int mapLevel) override
        {
            map.GetMapLayer(mapLevel).AddElement<T>(*m_pElementData, *m_ElementInstanceData, m_Position, m_RotationIndex);
        }

        void DestroyObject(Map& map, int mapLevel) override
        {
            map.GetMapLayer(mapLevel).ClearElement<T>(m_Position);
        }

        template<typename... Args>
        void SetInstanceData(Args&&... args)
        {
            m_ElementInstanceData = std::make_unique<typename BrushType<T>::ElementInstanceData>(std::forward<Args>(args)...);
        }
       
        void ClearInstanceData()
        {
            m_ElementInstanceData = nullptr;
        }

    private:
        int m_ElementIndex;
        Sprite m_Cursor;

        const int m_ElementIndexWrapThreshold;

        Vector2 m_Position;
        int m_RotationIndex;

        const typename BrushType<T>::ElementData* m_pElementData;
        std::unique_ptr<typename BrushType<T>::ElementInstanceData> m_ElementInstanceData;
};