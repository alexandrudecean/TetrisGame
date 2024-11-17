#include "ColorManager.h"
#include <ctime>
#include <cstdlib>

using namespace TetrisAPI;

const Color ColorManager::Green = Color(47, 230, 23, 255);
const Color ColorManager::Red = Color(232, 18, 18, 255);
const Color ColorManager::Orange = Color(226, 116, 17, 255);
const Color ColorManager::Yellow = Color(237, 234, 4, 255);
const Color ColorManager::Purple = Color(166, 0, 247, 255);
const Color ColorManager::Cyan = Color(21, 204, 209, 255);
const Color ColorManager::Blue = Color(13, 64, 216, 255);
const Color ColorManager::LightBlue = Color(59, 85, 162, 255);
const Color ColorManager::DarkBlue = Color(44, 44, 127, 255);

ColorManager::ColorManager() :
    m_colors{ Green, Red, Orange, Yellow, Purple, Cyan, Blue, LightBlue, DarkBlue }
{}

Color ColorManager::GetRandomBlockColor() const
{
    std::srand(std::time(nullptr));
    uint16_t randomIndex = std::rand() % m_colors.size();

    return m_colors[randomIndex];
}

Color ColorManager::GetEmptyCellColor() const
{
    return Color(26, 31, 40, 255);
}
