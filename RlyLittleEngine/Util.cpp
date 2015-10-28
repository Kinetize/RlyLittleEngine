#include "Util.h"

std::pair<std::string, Texture> Util::PosStringInMap(std::map<std::string, Texture> sMap, std::string text) { //verallgemeinern?
	
	int index = -1;
	
	for (auto & element : sMap) {
		index++;

		if (element.first.compare(text) == 0) 
			return element;

	}

	return std::pair<std::string, Texture>("NotFound", Texture()); //net so geil...
}