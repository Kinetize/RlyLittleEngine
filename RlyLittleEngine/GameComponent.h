#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H
#pragma once

class GameComponent {
public:
	GameComponent();

	virtual void Update();
	virtual void Render() const;

private:

};

#endif