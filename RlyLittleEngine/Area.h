#ifndef AREA_H
#define AREA_H

class Area {
public:
	Area();

	~Area();

	inline bool GetGeneralArea() { return _generalArea; }

private:
	bool	_generalArea;
};

#endif

