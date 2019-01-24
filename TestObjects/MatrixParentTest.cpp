#include "MatrixParentTest.h"

#include "GameConstants\GameConstants.h"
#include "Core\Utils\ColourLibrary.h"

MatrixParentTest::MatrixParentTest() :
    m_Core(DisplayLayer::OBJECT, GameConstants::TextureData.GetIDWithName("Debug_PointMarker"), 0, 0),
    m_Satellite_1(DisplayLayer::OBJECT, GameConstants::TextureData.GetIDWithName("Debug_PointMarker"), 2.0f, 0),
    m_Satellite_2(DisplayLayer::OBJECT, GameConstants::TextureData.GetIDWithName("Debug_PointMarker"), 1.0f, 0)
{
    m_Core.SetColour(ColourLibrary::SuperBlue);
    m_Satellite_1.SetColour(ColourLibrary::SexyOrange);
    m_Satellite_2.SetColour(ColourLibrary::Red);

    m_Satellite_1.GetTransform().SetParent(&m_Core.GetTransform());
    m_Satellite_2.GetTransform().SetParent(&m_Satellite_1.GetTransform());
}

void MatrixParentTest::Update()
{
    m_Satellite_1.Rotate(GameConstants::DeltaTime_Real);
    m_Satellite_2.Rotate(GameConstants::DeltaTime_Real);
}