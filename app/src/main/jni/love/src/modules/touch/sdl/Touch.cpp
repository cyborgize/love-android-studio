/**
 * Copyright (c) 2006-2015 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

// LOVE
#include "common/config.h"
#include "common/Exception.h"
#include "Touch.h"

namespace love
{
namespace touch
{
namespace sdl
{

std::vector<int64> Touch::getTouches() const
{
	std::vector<int64> ids;
	ids.reserve(touches.size());

	for (const auto &touch : touches)
		ids.push_back(touch.first);

	return ids;
}

void Touch::getPosition(int64 id, double &x, double &y) const
{
	const auto it = touches.find(id);
	if (it == touches.end())
		throw love::Exception("Invalid active touch ID: %d", id);

	x = it->second.x;
	y = it->second.y;
}

double Touch::getPressure(int64 id) const
{
	const auto it = touches.find(id);
	if (it == touches.end())
		throw love::Exception("Invalid active touch ID: %d", id);

	return it->second.pressure;
}

const char *Touch::getName() const
{
	return "love.touch.sdl";
}

void Touch::onEvent(Uint32 eventtype, const TouchInfo &info)
{
	switch (eventtype)
	{
	case SDL_FINGERDOWN:
	case SDL_FINGERMOTION:
		touches[info.id] = info;
		break;
	case SDL_FINGERUP:
		touches.erase(info.id);
		break;
	default:
		break;
	}
}

} // sdl
} // touch
} // love
