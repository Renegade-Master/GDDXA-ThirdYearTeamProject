/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

/**
*	The main function.  Called when the '.exe' is executed.
*/
int main() {
	// Declare an instance of Engine
	Engine engine;

	// Start the engine
	engine.run();

	engine.~Engine();

	// Quit in the usual way when the engine is stopped
	return 0;
}