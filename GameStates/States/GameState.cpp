#include "GameState.h"

GameState::GameState(Input::InputDeviceHandler& inputHandler) :
    m_InputDeviceHandler(&inputHandler)
{}

GameState::~GameState()
{}