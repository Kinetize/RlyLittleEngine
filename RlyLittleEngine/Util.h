#ifndef UTIL_H
#define UTIL_h

#include "ResourceManager.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <SDL/SDL.h>

namespace Util {
	void Delay(int miliseconds);

	template<class Tf, class Ts> std::vector<Tf> GetKeysFromMap(const std::map<Tf, Ts>& map);
	template<class Tf, class Ts> std::vector<Tf> GetKeysFromMap(const std::unordered_map<Tf, Ts>& map);
};

#endif

