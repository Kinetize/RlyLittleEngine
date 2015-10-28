#ifndef UTIL_H
#define UTIL_h
#pragma once

#include <map>
#include "Texture.h"

class Util {
public:
	static std::pair<std::string, Texture> PosStringInMap(std::map<std::string, Texture> map, std::string text); //verallgemeinern?

};

#endif

