#include "Game.h"

//REMEMBER: Maus oben links 0,0; OpenGl Mitte 0,0
//...Erstmal alles zum Funktionieren bringen dann mit GameObjects, Tranform-Klassen, DLL etc. umformen
//Ressource Manager...(Kein Mehrfaches laden, richtiges l�schen etc)
//ERROR HANDLING!!!!
//Kommentare...
//Mip Maps, Filter(ffax?) etc
//Indices n�tig? schlie�lich nur 2d, aber sch�ner...
//Un�ntige Imports, libs(z.b. devil), etc rauswerfen (pico etwas langsam --> ersetzen?)
//Tranform Uniform

int main(int argc, char** argv){

	Game game("littleEngine");
	game.start();

	return 0;
}