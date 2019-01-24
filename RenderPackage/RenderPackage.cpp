#include "RenderPackage.h"

#include "Core\RenderRegister\ObjectRenderRegister.h"

class UIElement_TextBox;

RenderPackage::RenderPackage(int maxInstanceCount) :
	m_RenderGroup_Sprites(maxInstanceCount),
	m_RenderGroup_Text(),
	m_MainCamera()
{}

void RenderPackage::FillPackage()
{
    ObjectRenderRegister::Foreach<Sprite>([&](const Sprite* ptr)
    {
        m_RenderGroup_Sprites.AddObject(*ptr);
    });

    ObjectRenderRegister::Foreach<UIElement_TextBox>([&](const UIElement_TextBox* ptr)
    {
        m_RenderGroup_Text.AddText(*ptr);
    });
}

const RenderGroupContainer& RenderPackage::GetRenderGroupContainer() const
{
    return m_RenderGroup_Sprites;
}

const RenderGroup_Text& RenderPackage::GetRenderGroupText() const
{
    return m_RenderGroup_Text;
}

void RenderPackage::SetMainCamera(const Camera& camera)
{
    m_MainCamera = camera;
}

const Camera& RenderPackage::GetMainCamera() const
{
    return m_MainCamera;
}

void RenderPackage::Clean()
{
    m_RenderGroup_Sprites.Clean();
    m_RenderGroup_Text.Clean();
}