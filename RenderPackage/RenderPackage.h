// name: RenderPackage
// date: 05/01/2017
// Note: Holds the information needed to render a frame. This information is held in "RenderGroups", a render group contains data about gameobjects that can be rendered using instancing.

#pragma once

#include "Core\Camera\Camera.h"
#include "Containers\RenderGroupContainer.h"
#include "RenderGroups\RenderGroup_Text.h"

class RenderPackage
{
    public:
        RenderPackage(int maxInstanceCount);

        RenderPackage(const RenderPackage&) = delete;
        RenderPackage& operator=(const RenderPackage&) = delete;

        RenderPackage(RenderPackage&&) = delete;
        RenderPackage& operator=(RenderPackage&&) = delete;

        void FillPackage();
        const RenderGroupContainer& GetRenderGroupContainer() const;
        const RenderGroup_Text& GetRenderGroupText() const;

        void SetMainCamera(const Camera& camera);
        const Camera& GetMainCamera() const;

        void Clean();

    private:
        RenderGroupContainer m_RenderGroup_Sprites;
        RenderGroup_Text m_RenderGroup_Text;
        Camera m_MainCamera;
};
