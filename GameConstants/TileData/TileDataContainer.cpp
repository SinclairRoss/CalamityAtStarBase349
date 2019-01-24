#include "TileDataContainer.h"

#include "Utils\TileDataReader.h"

TileDataContainer::TileDataContainer() :
    m_ElementData_Floor(TileDataReader::ReadData_Floor()),
    m_ElementData_Wall(TileDataReader::ReadData_Wall()),
    m_ElementData_Static(TileDataReader::ReadData_Static()),
    m_ElementData_Interactable(TileDataReader::ReadData_Interactable())
{}