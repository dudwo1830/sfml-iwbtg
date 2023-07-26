#include "stdafx.h"
#include "Variables.h"

Languages Variables::CurrentLang = Languages::KOR;
int Variables::DeathCount = 0;
sf::Vector2f Variables::CheckPoint = { 1 * 32, 15 * 32 };
bool Variables::PlayerFlip = false;