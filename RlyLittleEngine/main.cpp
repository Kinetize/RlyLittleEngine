#include "Game.h"

//REMEMBER: Maus oben links 0,0; OpenGl Mitte 0,0
//...Erstmal alles zum Funktionieren bringen dann mit GameObjects, Tranform-Klassen, DLL etc. umformen
//IMPORTANT:::MMATH TESTEN!!!!
//ERROR HANDLING!!!!
//Kommentare...
//Mip Maps, Filter(ffax?) etc
//Indices n�tig? schlie�lich nur 2d, aber sch�ner...
//Un�ntige Imports, libs(z.b. devil), etc rauswerfen (pico etwas langsam --> ersetzen?)
//Licht ---> Light Oberklasse, Light Strukturen im Shader
//Transform durch Object struktur verbinden + objekte "disablen" --> rendern/updaten weder sich noch unterObj
//Transparenz
//Transform immer neu erzeugen? oder statt pos, etc?
//Shader.h/shader.cpp at noch uniform methoden --> clear
//UNIFORM-METHODDEN template

int main(int argc, char** argv){

	Game game("littleEngine");
	game.Start();
	
	return 0;
}