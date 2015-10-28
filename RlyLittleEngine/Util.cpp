#include "Util.h"

int Util::PosStringInMap(std::map<std::string, Texture> sMap, std::string text) { //verallgemeinern?
	
	int index = -1;
	
	for (auto & element : sMap) {
		index++;

		if (element.first.compare(text) == 0) 
			return index;

	}

	return -1;
}