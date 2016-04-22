#include "Util.h"

template std::vector<resource_key> Util::GetKeysFromMap(const std::map<resource_key, ResourceTupel>& map);
template std::vector<resource_key> Util::GetKeysFromMap(const std::unordered_map<resource_key, ResourceTupel>& map);

void Util::Delay(int miliseconds) {
	SDL_Delay(1);
}

template<class Tf, class Ts>
std::vector<Tf> Util::GetKeysFromMap(const std::map<Tf, Ts>& map) {
	std::vector<Tf> keys;

	for (auto& element : map)
		keys.push_back(element.first);

	return keys;
}

template<class Tf, class Ts> 
std::vector<Tf> Util::GetKeysFromMap(const std::unordered_map<Tf, Ts>& map) {
	std::vector<Tf> keys;

	for (auto& element : map)
		keys.push_back(element.first);

	return keys;
}