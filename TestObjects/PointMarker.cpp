#include "PointMarker.h"

#include "GameConstants\GameConstants.h"

PointMarker::PointMarker(float x, float y, const Colour& colour) : 
    Sprite(DisplayLayer::FLOOR, GameConstants::TextureData.GetIDWithName("Debug_PointMarker"), x, y)
{
    SetColour(colour);
    GetTransform().SetPosition_Z(0.5f);
}

void PointMarker::Update()
{}