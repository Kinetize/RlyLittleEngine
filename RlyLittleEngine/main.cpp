#include "Game.h"

//REMEMBER: Maus oben links 0,0; OpenGl Mitte 0,0
//...Erstmal alles zum Funktionieren bringen dann mit GameObjects, Tranform-Klassen, DLL etc. umformen
//Ressource Manager...(Kein Mehrfaches laden, richtiges l�schen etc)
//ERROR HANDLING!!!!
//Kommentare...

int main(int argc, char** argv){

	Game game("littleEngine");
	game.start();

	return 0;
}