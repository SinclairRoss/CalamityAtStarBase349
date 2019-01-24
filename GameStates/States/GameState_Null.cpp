#include "GameState_Null.h"

GameState_Null::GameState_Null(Input::InputDeviceHandler& inputHandler) :
    GameState(inputHandler)
{}

void GameState_Null::Update(RenderPackage& renderPackage)
{}