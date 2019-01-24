#include "GameState_LevelEditor.h"

#include "GameConstants\GameConstants.h"
#include "Core\EventHandlers\PublisherSubscriber\BroadcastStation.h"
#include "Core\TestObjects\PointMarker.h"
#include "Core\Utils\ColourLibrary.h"

GameState_LevelEditor::GameState_LevelEditor(Input::InputDeviceHandler& inputHandler) :
    GameState(inputHandler),
    m_Camera(),
    m_Map(1),
    m_EditorController(m_Camera, m_Map),
    m_UIOverlay(nullptr),
    m_ActiveLevelTextbox(nullptr)
{
    m_UIOverlay = std::make_unique<GUIPage>(GameConstants::GUIPageData.GetPageData("Page_LevelEditor"));
    m_ActiveLevelTextbox = m_UIOverlay->GetTextBoxWithID("TextBox_Level");

    m_InputDeviceHandler->AddContext("InputContext_LevelEditor");
    m_InputDeviceHandler->AddInputCallback([this](const Input::MappedInput& inputs) {InputCallback(inputs); }, 0);
}

GameState_LevelEditor::~GameState_LevelEditor()
{
    m_InputDeviceHandler->ClearContextStack();
    m_InputDeviceHandler->ClearInputCallbacks();
}

void GameState_LevelEditor::Update(RenderPackage& renderPackage)
{
    renderPackage.SetMainCamera(m_Camera);

    m_ActiveLevelTextbox->SetPlaceholderValue("X", std::to_string(m_EditorController.GetActiveLevelIndex()+1));
    m_ActiveLevelTextbox->SetPlaceholderValue("Y", std::to_string(m_Map.GetLevelCount()));
}

void GameState_LevelEditor::InputCallback(const Input::MappedInput& inputs)
{
    m_EditorController.ParseInput(inputs);
}