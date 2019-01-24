// Name: GameState_LevelEditor
// Date: 05/01/2017
// Note: A game state representing the main game.

#pragma once

#include "GameState.h"

#include <memory>

#include "Core\Camera\Camera.h"
#include "Core\InputHandling\InputMapping\MappedInput.h"
#include "Core\UI\GUIPage.h"
#include "LevelEditor\Controller\EditorController.h"

class GameState_LevelEditor : public GameState
{
    public:
        GameState_LevelEditor(Input::InputDeviceHandler& inputHandler);
        ~GameState_LevelEditor();

        void Update(RenderPackage& renderPackage) override;

        void InputCallback(const Input::MappedInput& inputs);

    private:
        Camera m_Camera;
        Map m_Map;
        EditorController m_EditorController;

        std::unique_ptr<GUIPage> m_UIOverlay;
        UIElement_TextBox* m_ActiveLevelTextbox;
};