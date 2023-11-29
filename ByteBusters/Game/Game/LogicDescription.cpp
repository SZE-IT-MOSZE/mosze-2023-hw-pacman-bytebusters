/*
after pausing the update, the function that paused it waits for a variable to be set by the thread after it has actually stopped.
*/


while (isRunning) // the application is running
{
	while (inMenu) { // the user is in the menu

		// framestart
		//------------------------------------------------------------------------------
		// pollevent
			// quit
				// menu false
				// running false
			// ui event
				// start
					// menu false
					// playing true
					// generatemaze
				// load
					// menu false
					// playing true
					// load number plus check
			// handle ui events (let the ui push its events)
		//------------------------------------------------------------------------------
		// SDL_RenderClear(Game::renderer);
		// ui->RenderMainMenu();
		// SDL_RenderPresent(Game::renderer);
		//------------------------------------------------------------------------------
		// FPS DELAY
	}

	if (isPlaying)
	{
		// create player
		// new thread for the update (enables and starts itself)
		while (isPlaying) {
			// framestart
			//------------------------------------------------------------------------------
			// polling event
				// quit
					// stop update - return only on stop, join within function
					// destroy all inc. player 
					// playing false
					// running false
				// ui events
					// save
						// stop update - return only on stop, join within function
						// save map
						// playing false
						// menu true
					// menu
						// stop update - return only on stop, join within function
						// menu true
						// playing false
				// game event handling - keyinputs
				// ui event handling - let the ui push its events
			//------------------------------------------------------------------------------
			// clear rendered
			// render map
			// render gameobjects
			// render menu
			// present renderer
			//------------------------------------------------------------------------------
			// if all items are picked up
				// if map < 10
					// pause the update - only return if paused (no join, theread is waiting, it didnt quit)
					// destroy all except the player
					// reset the player
					// set next map
					// load the map
					// resume update
				// if not
					// stop update - return only on stop, join within function
					// destroy all inc. player 
					// playing false
					// menu true
			//------------------------------------------------------------------------------
			// if player died
				// pause the update - only return if paused (no join, theread is waiting, it didnt quit)
				// destroy all except the player
				// reset the player
				// load the map
				// resume update
			//------------------------------------------------------------------------------
			// FPS DELAY
		}
		// delete update
		// destroy everything (safe)
	}
}